import websocket
import logging
import threading
import sys
import itertools
from common.constants import *
from common.messaging import VDMessage

class ControlPlaneConnect():
    def __init__(self, server_url, message_queues, message_condition_var) -> None:
        self.server_url = server_url
        try:
            self.ws = websocket.WebSocketApp(server_url)
        except websocket.WebSocketException as e:
            logging.error(f"Failed to create WebSocketApp for {self.server_url}: {e}")
            # Handle the exception as needed (e.g., exit gracefully or raise a custom exception)

        self.controlplane_ready = False

        # Create an messaging object, so that the messages are Virtual Dataplane compliant
        self.messaging = VDMessage()

        self.message_queues = message_queues
        self.message_condition_var = message_condition_var
        # Create a lock for thread safety
        self.send_message_lock = threading.Lock()

        # Use itertools.count() for a unique counter
        self.tie_break_count_generator = itertools.count()

        logging.info(f"Created a ControlPlaneConnect for {self.server_url=}")

    def start(self):
        logging.info(f"Starting the websocket connection to {self.server_url=}")
        # Assign the callback functions to the WebSocket events
        self.ws.on_open = self.on_open
        self.ws.on_message = self.on_message
        self.ws.on_error = self.on_error
        self.ws.on_close = self.on_close    

        # Connect to the WebSocket server
        self.ws.run_forever()

    # Define callback functions for WebSocket events
    def on_open(self, ws):
        # This function is called when websocket connection is ready
        logging.info(f"Websocket connection ready")
        self.controlplane_ready = True    

    # This function is called when a message is received from the WebSocket server
    def on_message(self, ws, message):
        logging.info(f"Received message: {message}")     
        is_valid, parsed_message = self.messaging.validate_message(message)          
        if is_valid:
            logging.info(f"Received valid ControlPlane connect message")
            message_type = parsed_message.get("type", "external")
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
            logging.info(f"Received Invalid ControlPlane connect message") 

    # This function is called when an error occurs
    def on_error(self, ws, error): 
        logging.info(f"Error: {error}")
        logging.exception("Exception details:")

    # This function is called when the WebSocket connection is closed
    def on_close(self, ws, close_status_code, close_msg):
        logging.info("Websocket connection closed")

    # Use the send method to send a message to the server
    def send_message(self, message):
        with self.send_message_lock:
            self.ws.send(message)        

    def close_connect(self):
        logging.info(f"Closing the websocket connection to {self.server_url=}")
        self.ws.close()

    # This function generates a counter, which is used to resolve when the priority is same during
    # enqueue
    def tie_break_counter_function(self):
        # Get the next value from the counter
        return next(self.tie_break_count_generator)        
