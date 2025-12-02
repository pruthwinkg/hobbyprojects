'''
    Should be used by individual devices (Ex: Light, Fan etc)

    Simplifies the implementation of a device type. 
        - Every VDDevice by default has below threads which might use schedulers
            - Websocket connection (1 thread)
            - Ingress/Egress x (internal/external/interconnect) threads (6 threads)
            - System message and housekeeping (1 thread)
            - Config handling (policies/rules, firmware upgrade) (1 thread)
            - Telemetry (There can be multiple telemetry at multiple frequencies) (1 thread)
                - Heartbeats (Higher freq, small payload)
                - Generic device info (Lower freq, medium payload)
                - Device/Use case specific telemetries (Telemetry func should be supplied by Device)
             
        - The individual devices can create more threads if needed for its own purpose
        - Handles most of the boiler plate code  
            - Generate UUID for each device
            - Generate MAC/IP for each device
        - Generates and Exports telemetry data by default
            - By default UUID and some basic data will be extracted from config files and exported.
            - Devices need to define a function which fills more telemetry data if needed
        

'''
from common.utils import generate_uuid, generate_mac_address
import threading
import logging
import json
import sys
import os
import sched
import time
import signal
from functools import partial
import queue
import itertools
from common.controlplane_connect import ControlPlaneConnect
from common.local_connect import LocalConnect
from common.task_manager import VDTaskManager
from common.constants import *

# Unsecured
server_url = "ws://test_controlplane:40000"

# Secured
#server_url = "wss://localhost:8080"

class NamedQueue(queue.PriorityQueue):
    def __init__(self, name, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.name = name

class VDDevice():
    def __init__(self, device, debugLevel=logging.INFO) -> None:
        if not os.path.exists("logs"):
            os.makedirs("logs")                
        self.pid = os.getpid()
        log_file = os.path.join("logs", 'light.log.' + str(self.pid)) 
        logging.basicConfig(filename=log_file,
                            format='%(asctime)s %(levelname)s %(filename)s [%(funcName)s:%(lineno)d]:%(message)s',
                            filemode='w',
                            level=debugLevel)

        # Register the signal handler
        signal.signal(signal.SIGTERM, self.signal_handler)
        signal.signal(signal.SIGINT, self.signal_handler) 

        # Initialize the should_exit flag to False
        self.should_exit = False

        # Create queues and condition variables for internal/external/interconnect (ingress/egress)
        # sub-type in the message will determine the kind of message.
        # These are main interfacing queues for the device instance with outside
        self.message_queues = {
            "internal-ingress": NamedQueue("internal-ingress", maxsize=0),
            "external-ingress": NamedQueue("external-ingress", maxsize=0),
            "interconnect-ingress": NamedQueue("interconnect-ingress", maxsize=0),
            "internal-egress": NamedQueue("internal-egress", maxsize=0),
            "external-egress": NamedQueue("external-egress", maxsize=0),
            "interconnect-egress": NamedQueue("interconnect-egress", maxsize=0),                    
        }

        self.message_condition_var = {
            "internal-ingress": threading.Condition(),
            "external-ingress": threading.Condition(),
            "interconnect-ingress": threading.Condition(),
            "internal-egress": threading.Condition(),
            "external-egress": threading.Condition(),
            "interconnect-egress": threading.Condition(),            
        }

        # These queues are mainly used internally between threads once the message is dequed from ingress/egress queues
        # Even these queues are priority based
        self.internal_message_queues = {
            "system": NamedQueue("system", maxsize=0),
            "configuration": NamedQueue("configuration", maxsize=0), 
        }
        # Use itertools.count() for a unique counter
        self.tie_break_count_generator = itertools.count()

        # Store the ControlPlaneConnect instance as an attribute
        self.controlplane_connect = None
        self.localplane_connect = None
        self.device = device
        self.uuid = generate_uuid(self.device.name, 10)
        self.mac = generate_mac_address()
        self.config = self.get_device_config() # Common for a device type
        self.device_instance_config = {} # This is optional. Instance specific config     

        # Create a list of thread functions and arguments
        thread_functions = [
            (self.handle_websockets, ()),
            (self.handle_internal_communication, ()),
            (self.handle_external_ingress_message, ()),
            (self.handle_internal_ingress_message, ()),            
            (self.handle_external_egress_message, ()),
            (self.handle_internal_egress_message, ()),
            (self.handle_system, ()),
            (self.handle_configuration, ()),
            (self.handle_telemetry, ()),               
        ]
        self.task_manager = VDTaskManager(thread_functions) 

        if 'device' in self.config and 'logging' in self.config['device']:
            dbglvl = self.config['device']['logging']
            if dbglvl == 'error':
                debugLevel = logging.ERROR
            elif dbglvl == 'info':
                debugLevel = logging.INFO
            else:
                debugLevel = logging.DEBUG  

    def get_device_config(self):
        config_json = sys.argv[1]
        device_config = json.loads(config_json)
        return device_config

    '''
     This thread waits for any messages in its queue OR periodically wakes and does
     some chores
    '''
    def handle_websockets(self):
        logging.info("Connecting to ControlPlane")
        self.controlplane_connect = ControlPlaneConnect(server_url, self.message_queues, self.message_condition_var)        
        self.controlplane_connect.start()

    '''
        This thread handles the internal/interconnect communication between device and device-manager
        
    '''
    def handle_internal_communication(self):
        logging.info("Creating LocalPlane connections")
        try:
            self.localplane_connect = LocalConnect(self.device.name, message_queues=self.message_queues, message_condition_var=self.message_condition_var)
            self.localplane_connect.client() # Run the localplane_connect in client mode
        except TypeError as e:
            logging.error(f"Error creating LocalConnect: {e}")
        

    # This function dequeues the most urgent message from the ingress queues and processes it
    # The recv method for websockets (external)
    # Depending on the sub-type (system, config, telemetry etc) process further
    def handle_external_ingress_message(self):
        while not self.should_exit:
            with self.message_condition_var["external-ingress"]:
                self.message_condition_var["external-ingress"].wait()                
                self.process_message(self.message_queues["external-ingress"], 0.1)  

    # The recv method for IPC (internal) or TCP (interconnect)
    def handle_internal_ingress_message(self):
        while not self.should_exit:
            with self.message_condition_var["internal-ingress"]:
                self.message_condition_var["internal-ingress"].wait(timeout=0.1)

            with self.message_condition_var["interconnect-ingress"]:
                self.message_condition_var["interconnect-ingress"].wait(timeout=0.1)  

    # This function dequeues the most urgent message from the egress queues and sends it
    # The send method for websockets (external)
    def handle_external_egress_message(self):
        while not self.should_exit:
            with self.message_condition_var["external-egress"]:
                self.message_condition_var["external-egress"].wait()
                while not self.message_queues["external-egress"].empty():
                    priority, message = self.message_queues["external-egress"].get()
                    self.controlplane_connect.send_message(message)                               

    # The send method for IPC (internal) or TCP (interconnect)
    def handle_internal_egress_message(self):
        while not self.should_exit:
            with self.message_condition_var["internal-egress"]:
                self.message_condition_var["internal-egress"].wait(timeout=0.1)
                while not self.message_queues["internal-egress"].empty():
                    priority, message = self.message_queues["internal-egress"].get()
                    self.localplane_connect.send_message(message)                      

            with self.message_condition_var["interconnect-egress"]:
                self.message_condition_var["interconnect-egress"].wait(timeout=0.1)  
                while not self.message_queues["interconnect-egress"].empty():
                    priority, message = self.message_queues["interconnect-egress"].get()
                    self.localplane_connect.send_message(message, True)                   


    def process_message(self, device_queue, timeout=None):
        # Check for new messages and process them    
        try:    
            while not device_queue.empty():
                try:
                    priority, _, message = device_queue.get(timeout=timeout)
                except queue.Empty:
                    continue  # No messages, continue waiting

                logging.info(f"Processing the {message=} {priority=} from the queue = {device_queue.name}")
                subtype_value = message.get("payload", {}).get("subtype")
                if(subtype_value == "system"):
                    # Use a 3-element tuple for the priority queue (priority, entry_count, parsed_message)
                    tie_break_count = self.tie_break_counter_function()
                    queue_entry = (priority, tie_break_count, message)
                    self.internal_message_queues["system"].put(queue_entry)
                if(subtype_value == "config"):
                    tie_break_count = self.tie_break_counter_function()
                    queue_entry = (priority, tie_break_count, message)                    
                    self.internal_message_queues["configuration"].put(queue_entry)

                device_queue.task_done() 
        except Exception as e:
            logging.error(f"Exception in process_message loop: {e}")  
            logging.exception("Exception details:")              

    def handle_system(self):
        # Schedule the periodic task to run every 60 seconds
        periodic_tasks = [(self.perform_periodic_chores, HOUSEKEEPING_DELAY, HOUSEKEEPING_INTERVAL, HOUSEKEEPING_PRIORITY, ())]
        self.task_manager.schedule_device_tasks(periodic_tasks, True) # Run this in a seperate thread   
 
        while not self.should_exit:
            try:
                message = self.internal_message_queues["system"].get()
                logging.error(f"Got the system message = {message}")
            except queue.Empty:
                pass

    def handle_configuration(self):
        while not self.should_exit:
            # Wait for a configuration message to arrive
            message = self.internal_message_queues["configuration"].get()
            logging.error(f"Got the configuration message = {message}")

    def handle_telemetry(self):
        logging.info(f"Scheduling telemetry")
        telemetry_tasks = [
            (self.default_telemetry, DEFAULT_TELEMETRY_DELAY, DEFAULT_TELEMETRY_INTERVAL, DEFAULT_TELEMETRY_PRIORITY, ()),
            (self.keepalive_telemetry, KEEPALIVE_TELEMETRY_DELAY, KEEPALIVE_TELEMETRY_INTERVAL, KEEPALIVE_TELEMETRY_PRIORITY, ()),
        ]
        self.task_manager.schedule_device_tasks(telemetry_tasks)

    def default_telemetry(self, *args):
        telemetry = {}
        telemetry["type"] = self.config["device"]["type"]
        telemetry["firmware"] = self.config["device"]["firmware"]
        logging.info(f"Exporting telemetry data {telemetry=}")      

    def keepalive_telemetry(self, *args):
        telemetry = {}
        telemetry["heartbeat"] = self.get_device_liveliness()     
        if self.controlplane_connect and self.controlplane_connect.controlplane_ready:
            logging.info(f"Exporting telemetry data {telemetry=}")
            self.controlplane_connect.send_message(telemetry["heartbeat"])

    def perform_periodic_chores(self, *args):
        # Perform your periodic chores here
        logging.error("Performing periodic chores...")
        self.share_device_info()
            
    '''
        This function shares the device information with its manager.
        This is mainly for micro-managing individual device instances by its device-manager
        Device information could contain below information:            
            - Current configuration on which this device-instance is running
            - UUID/MAC/IP of the device
            - Health of the device (Memory/CPU)
            - ControlPlane connection status
        These device data will be periodically shared with the Manager or Manager could ask for the
        device-instance at any point of time
    '''
    def share_device_info(self):  
        internal_msg_template = {
            "application": "smarthome",
            "version": "0.1",
            "type": "internal",
            "priority": "low",
            "target" : "device",  
            "payload": {
                "scope": "unicast",
                "subtype": "system",
                "source" : { 
                    "origin": "",
                    "uuid": "",
                },
                "destination" : { 
                    "device": [""],
                    "uuid": [""],
                } ,
                "message": { # apps need to validate, NOT infra
                    "device_info": "",            
                }             
            }
        }        
        process_info = self.get_process_info()
        device_info = {
                    "uuid": self.uuid,
                    "mac": self.mac,
                    "config": self.config,
                    "health": process_info
                    }      

        # Its an internal message. So uuid of destination is not required
        # The device manager should be able to figure out that the message is destined for it
        internal_msg_template["payload"]["source"]["origin"] = self.device.name
        internal_msg_template["payload"]["source"]["uuid"] = self.uuid
        internal_msg_template["payload"]["destination"]["device"] = [self.device.name]
        internal_msg_template["payload"]["message"]["device_info"] = device_info

        if self.localplane_connect and self.localplane_connect.localplane_ready:  
            try:      
                logging.info(f"Exporting device info {internal_msg_template=}")
                self.localplane_connect.send_message(internal_msg_template)
            except Exception as e:
                logging.error(f"Got exception {e}")                   


    def get_process_info(self):
        # Get process information by process ID
        try:
            # Get process information using ps command
            ps_output = os.popen(f"ps -p {self.pid} -o %cpu,%mem,rss,vsz").readlines()[1].split()     
             # Extract information from the ps command output
            cpu_percent = float(ps_output[0])
            memory_percent = float(ps_output[1])
            rss = int(ps_output[2])
            vsz = int(ps_output[3])

            return {
                'cpu_percent': cpu_percent,
                'memory_percent': memory_percent,
                'rss': rss,
                'vsz': vsz
            }

        except Exception as e:
            logging.error(f"Unable to get the process information for pid={self.pid}, exception={e}")
            return {}

            
    def get_device_liveliness(self):
        return "alive"
    
    def signal_handler(self, signum, frame):
        logging.info(f"Received {signum} signal")
        self.should_exit = True  # Set the flag to indicate threads should exit gracefully
        # You can also send specific signals to threads if needed

        # Exit the program
        sys.exit()    

    # This function generates a counter, which is used to resolve when the priority is same during
    # enqueue
    def tie_break_counter_function(self):
        # Get the next value from the counter
        return next(self.tie_break_count_generator)
