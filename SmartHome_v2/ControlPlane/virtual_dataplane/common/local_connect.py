import socket
import select
import queue
import os
import logging
import threading
import errno
import json
import itertools
from common.constants import *
from common.messaging import VDMessage


MAX_MESSAGE_LEN = 1024
CLIENT_SELECT_LOOP_TIMEOUT = 2

'''
    This class handles the internal and interconnect type of messaging.
    When a client connects to server, it shares its pid as the very message, through
    which server will build a mapping between client sockets and pids.
    This enables app (parent) using server to braodcast/multicast/unicast messages to its children.

    For internal messages it uses UNIX domain sockets
    For interconnect messages it uses INET sockets
'''
class LocalConnect():
    def __init__(self, device_type, is_interconnect=False, server_port=0, message_queues=None, message_condition_var=None) -> None:        
        self.localplane_ready = False        
        self.is_interconnect = is_interconnect
        self.server_port = server_port
        self.device_type = device_type

        if message_queues is not None:
            self.message_queues = message_queues

        if message_condition_var is not None:
            self.message_condition_var = message_condition_var

        # Flag to check which mode the class is running
        self.server_mode = False        

        self.server_message_queues = {} # Egress queue
        self.server_inputs = []
        self.server_outputs = []
        self.server_sockets_pid_map = {} # Mapping between pids and client sockets (connections)

        self.client_message_queues = None # Egress queue
        self.client_inputs = []
        self.client_outputs = [] 

        # Locks for server inputs, outputs, and sockets_pid_map
        self.server_inputs_lock = threading.Lock()
        self.server_message_queues_lock = threading.Lock()
        self.server_outputs_lock = threading.Lock()
        self.server_sockets_pid_map_lock = threading.Lock()    

        # Locks for client inputs, outputs, and message_queues
        self.client_inputs_lock = threading.Lock()
        self.client_outputs_lock = threading.Lock()
        self.client_message_queues_lock = threading.Lock()

        # Create an messaging object, so that the messages are Virtual Dataplane compliant
        self.messaging = VDMessage()   

        # Use itertools.count() for a unique counter
        self.tie_break_count_generator = itertools.count()             

    '''
        This function is to be run in parent process in a dedicated thread.
        It will handle communication with all children
    '''
    def server(self):
        self.server_mode = True

        socket_path = f"/tmp/vd_device_socket_{self.device_type}"
        if not self.is_interconnect:
            server_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
            if os.path.exists(socket_path):
                os.remove(socket_path)   
                
            server_socket.bind(socket_path)            
        else:
            server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            server_socket.bind(('localhost', self.server_port))

        server_socket.listen(5)                       
        logging.info("Server started to listen...")             

        self.server_inputs = [server_socket]
        self.server_message_queues = {server_socket: queue.Queue()}    

        self.localplane_ready = True

        while self.server_inputs:
            readable, writable, exceptional = select.select(self.server_inputs, self.server_outputs, self.server_inputs)

            for s in readable:
                if s is server_socket:
                    connection, client_address = s.accept()
                    pid_msg = connection.recv(MAX_MESSAGE_LEN)
                    pid = int(pid_msg.decode())  # Assuming the PID is sent as a string
                    logging.info(f"Accepted connection from {pid=} {client_address=} {connection=}")
                    connection.setblocking(False)
                    self.server_inputs.append(connection)
                    with self.server_message_queues_lock:
                        self.server_message_queues[connection] = queue.Queue()
                    with self.server_sockets_pid_map_lock:
                        self.server_sockets_pid_map[pid] = connection
                else:
                    data = s.recv(MAX_MESSAGE_LEN)
                    if data:
                        logging.info(f"Received data: {data.decode()} from {s.getpeername()}")
                        self.recv_message(data.decode())
                    else:  
                        with self.server_outputs_lock, self.server_message_queues_lock, self.server_sockets_pid_map_lock:                      
                            if s in self.server_outputs:
                                self.server_outputs.remove(s)
                            self.server_inputs.remove(s)
                            s.close()
                            del self.server_message_queues[s] 
                            # Remove the closed connection from the mapping
                            try:
                                pid_to_remove = next(pid for pid, socket in self.server_sockets_pid_map.items() if socket == s)
                                del self.server_sockets_pid_map[pid_to_remove]                        
                            except StopIteration:
                                logging.error("Error: Could not find PID to remove for the closed connection.")
                            logging.info(f"Closed the connection for pid = {pid_to_remove}")

            for s in writable:
                try:
                    next_msg = self.server_message_queues[s].get_nowait()
                except queue.Empty:
                    self.server_outputs.remove(s)
                else:
                    logging.info(f"Sending data: {next_msg.decode()} to {s.getpeername()}")
                    try:
                        s.send(next_msg.encode())      
                    except Exception as e:
                        logging.error(f"Got exception {e}")                 

            for s in exceptional:
                self.server_inputs.remove(s)
                if s in self.server_outputs:
                    self.server_outputs.remove(s)
                s.close()
                del self.server_message_queues[s] 
                # Remove the closed connection from the mapping
                try:
                    pid_to_remove = next(pid for pid, socket in self.server_sockets_pid_map.items() if socket == s)
                    del self.server_sockets_pid_map[pid_to_remove]                        
                except StopIteration:
                    logging.error("Error: Could not find PID to remove for the closed connection.")  
                logging.info(f"Handling exceptional condition for pid = {pid_to_remove}")                                                                                              

    '''
        This is to be run in each child process in a dedicated thread.
    '''
    def client(self):
        self.server_mode = False        

        if not self.is_interconnect:
            socket_path = f"/tmp/vd_device_socket_{self.device_type}"
            client_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)                
            try:
                client_socket.connect(socket_path)
                # Send the client's identifier (e.g., PID) to the server
                client_socket.send(str(os.getpid()).encode())               
            except socket.error as e:
                logging.error(f"Error during connection: {e}")        

            logging.info(f"Client connected to {socket_path}")          
        else:
            client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client_socket.connect(('localhost', self.server_port))
            # Send the client's identifier (e.g., PID) to the server
            client_socket.send(str(os.getpid()).encode())             
            logging.info(f"Client connected to localhost at port {self.server_port}")

        client_socket.setblocking(False)  # Set socket to non-blocking

        self.client_message_queues = queue.Queue()
        self.client_inputs = [client_socket]
        self.client_outputs = []

        self.localplane_ready = True
        logging.info("Local plane is ready now")

        while self.client_inputs:
            readable, writable, exceptional = select.select(self.client_inputs, self.client_outputs, self.client_inputs, CLIENT_SELECT_LOOP_TIMEOUT)
            
            for s in readable:
                try:
                    data = s.recv(MAX_MESSAGE_LEN)
                except socket.error as e:
                    if e.errno == errno.EAGAIN:
                        continue  # No data available, move to the next socket  
                    else:                  
                        logging.error(f"Error during recv: {e}")
                        data = b''  # Set data to empty in case of an error

                if data:
                    logging.info(f"Received data: {data.decode()} from server")
                    self.recv_message(data.decode())
                else:
                    logging.info("Server closed the connection")
                    self.client_inputs.remove(s)

            for s in writable:
                with self.client_outputs_lock, self.client_message_queues_lock:
                    try:
                        next_msg = self.client_message_queues.get_nowait()
                    except queue.Empty:
                        logging.debug(f"Queue is empty. Removing {s} from client_outputs")
                        self.client_outputs.remove(s)
                    else:
                        logging.info(f"Sending data: {next_msg} to server")
                        try:
                            s.send(next_msg.encode())
                        except Exception as e:
                            logging.error(f"Got exception {e}")

            for s in exceptional:
                logging.info(f"Handling exceptional condition for {s.getpeername()}")
                self.client_inputs.remove(s)
                if s in self.client_outputs:
                    self.client_outputs.remove(s)
                s.close()                                         

    '''
        Send a message to list of pids ()
        In server_mode, list of pids is valid (useful for broadcasting/multicasting to devices)
        In client_mode, message is always sent to server

        Note: The message have to be Virtual Dataplane compliant
    '''
    def send_message(self, message, pids=None):
        # Only in server_mode, list of pids is valid
        if not self.localplane_ready:
            logging.error("LocalPlane connections not ready yet")
            return
                        
        if self.server_mode:
            with self.server_message_queues_lock, self.server_outputs_lock:
                for pid in pids:
                    socket = self.server_sockets_pid_map[pid]
                    self.server_message_queues[socket].put(json.dumps(message))
                    logging.debug(f"Sending to client {pid=} {message=}")
                    if socket not in self.server_outputs:
                        self.server_outputs.append(socket)
        else:
            with self.client_outputs_lock, self.client_message_queues_lock:
                if self.client_inputs:          
                    self.client_message_queues.put(json.dumps(message))            
                    if self.client_inputs[0] not in self.client_outputs:                
                        logging.debug(f"Sending to server {message=} {self.client_inputs[0]=}")
                        self.client_outputs.append(self.client_inputs[0])            
                else:
                    logging.info("Server has closed the connection. Cannot send the message")

    '''
        This function will decode the message and enqueue to the appropriate message queues

        Note: The message have to be Virtual Dataplane compliant
    '''
    def recv_message(self, message):
        is_valid, parsed_message = self.messaging.validate_message(message)
        if is_valid:
            logging.info(f"Received valid Virtual DataPlane connect message")   
            message_type = parsed_message.get("type", "internal")
            message_type = message_type + "-ingress"  # All the received messages go to respective ingress queues    
            priority_mapping = {"high": 1, "mid": 2, "low": 3}
            priority = priority_mapping.get(parsed_message.get("priority", "low"), 3) # Default to 3 (low) if not found            

            # Use a 3-element tuple for the priority queue (priority, entry_count, parsed_message)
            tie_break_count = self.tie_break_counter_function()
            queue_entry = (priority, tie_break_count, parsed_message)
            self.message_queues[message_type].put(queue_entry)

            # Notify the appropriate condition variable based on message type
            with self.message_condition_var[message_type]:
                self.message_condition_var[message_type].notify()                  
        else:
            logging.info(f"Received Invalid Virtual DataPlane connect message") 

    def close_connect(self, pids_to_close=None):
        if self.server_mode:
            # Acquire locks for server inputs, outputs, and sockets_pid_map
            with self.server_inputs_lock, self.server_outputs_lock, self.server_message_queues_lock, self.server_sockets_pid_map_lock:
                if pids_to_close:
                    for pid in pids_to_close:
                        if pid in self.server_sockets_pid_map:
                            connection = self.server_sockets_pid_map[pid]
                            connection.close()
                            self.server_inputs.remove(connection)
                            if connection in self.server_outputs:
                                self.server_outputs.remove(connection)
                            del self.server_message_queues[connection]
                            del self.server_sockets_pid_map[pid]
                            logging.info(f"Closed connection for pid = {pid}")
                else:
                    # Close all connections if no specific PIDs are provided
                    for s in self.server_inputs:
                        s.close()
                    self.server_inputs.clear()
                    self.server_outputs.clear()
                    self.server_message_queues.clear()
                    self.server_sockets_pid_map.clear()
                    logging.info("Closed all connections")
        else:
            # Acquire locks for client inputs, outputs, and message_queues
            with self.client_inputs_lock, self.client_outputs_lock, self.client_message_queues_lock:
                for s in self.client_inputs:
                    s.close()
                self.client_inputs.clear()
                self.client_outputs.clear()
                self.client_message_queues = None
                logging.info("Closed client connection")

    # This function generates a counter, which is used to resolve when the priority is same during
    # enqueue
    def tie_break_counter_function(self):
        # Get the next value from the counter
        return next(self.tie_break_count_generator)                   