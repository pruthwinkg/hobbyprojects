'''
Common code responsible for
 - Creating and Stopping multiple instances of a device type.
 - Should be used the individual device managers like LightManager, FanManager etc
 - Periodic Config monitoring or via supervisorctl HUP
'''

from common.config_manager import VDConfigManager
from common.local_connect import LocalConnect
from common.task_manager import VDTaskManager
from common.utils import generate_uuid
from common.constants import *
import threading
import logging
import subprocess
import os
import signal
import json
import sys
import hashlib
import time
import queue
import itertools
from flask import Flask, current_app

class NamedQueue(queue.PriorityQueue):
    def __init__(self, name, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.name = name

'''
 Example usage in LightManager app:
    VDDeviceManager('light.py', './light.config')
'''

class VDDeviceManager():
    def __init__(self, device, debugLevel=logging.INFO, periodic=True):
        if not os.path.exists("logs"):
            os.makedirs("logs")
        log_file = os.path.join("logs", "light.log") 
        logging.basicConfig(filename=log_file,
                            format='%(asctime)s %(levelname)s %(filename)s [%(funcName)s:%(lineno)d]:%(message)s',
                            filemode='w',
                            level=debugLevel)
      
        self.device = device
        self.periodic_management = periodic
        self.configFile = device['config']
        self.config_changed = False  # Flag to track configuration changes
        self.config_hash = self.calculate_file_hash()

        try:
            self.config_manager = VDConfigManager(self.configFile)
            self.config = self.config_manager.get_config()
            logging.debug(f"Initial configuration = {self.config}")
        except FileNotFoundError:
            raise
        except Exception as e:
            logging.error(e)

        if self.periodic_management is False:
            # Register the SIGHUP signal handler
            signal.signal(signal.SIGHUP, self.sighup_handler)

        # Register the signal handler
        signal.signal(signal.SIGTERM, self.signal_handler)
        signal.signal(signal.SIGINT, self.signal_handler)

        # Initialize the should_exit flag to False
        self.should_exit = False        

        self.localplane_connect = None

        self.running_device_processes = []  

        # Create queues and condition variables for internal/interconnect (ingress/egress)
        # sub-type in the message will determine the kind of message.
        # These are main interfacing queues for the device instance with outside
        self.message_queues = {
            "internal-ingress": NamedQueue("internal-ingress", maxsize=0),
            "interconnect-ingress": NamedQueue("interconnect-ingress", maxsize=0),
            "internal-egress": NamedQueue("internal-egress", maxsize=0),
            "interconnect-egress": NamedQueue("interconnect-egress", maxsize=0),                    
        }

        self.message_condition_var = {
            "internal-ingress": threading.Condition(),
            "interconnect-ingress": threading.Condition(),
            "internal-egress": threading.Condition(),
            "interconnect-egress": threading.Condition(),            
        }     

        # These queues are mainly used internally between threads once the message is dequed from ingress/egress queues
        # Even these queues are priority based
        self.internal_message_queues = {
            "system": NamedQueue("system", maxsize=0),
        }  

        # Device information.
        self.virtual_device_status = {}

        # Use itertools.count() for a unique counter        
        self.tie_break_count_generator = itertools.count()                

        # Create a list of thread functions and arguments
        thread_functions = [
            (self.start, ()),            
            (self.internal_msg_server, ()), 
            (self.handle_internal_ingress_message, ()),
            (self.handle_internal_egress_message, ()),            
            (self.handle_system, ()),
            (self.start_webapp , (self.device['device_manager_port'], self.device['device_manager_prefix'])),
        ]

        # Use the task_manager obj to start the virtual device manager in the actual device manager
        self.task_manager = VDTaskManager(thread_functions)
        
    def start(self):
        if self.periodic_management:
            # Always run self.restart_devices() the very first time
            if not self.config_changed:
                self.config_changed = True
                self.restart_devices()
            else:            
                # Periodically check for configuration changes
                current_hash = self.calculate_file_hash()          
                if current_hash != self.config_hash:
                    self.config_hash = current_hash
                    new_configuration = self.config_manager.get_config()
                    logging.info(f"{self.config=} {new_configuration=}")
                    self.config = new_configuration
                    logging.info("Detected configuration change.")   
                    self.restart_devices()

        threading.Timer(DEVICE_MANAGER_PERIODIC_WAKE, self.start).start()
       

    def restart_devices(self):     
        # Stop existing device processes if anything is running
        logging.info(f"Before restart {self.running_device_processes=}")
        for process in self.running_device_processes.copy():
            self.stop_device(process)
            self.running_device_processes.remove(process)

        self.running_device_processes.clear()
        self.virtual_device_status.clear()
        
        self.create_device(int(self.config['scale']['instances']))
        logging.info(f"After restart {self.running_device_processes=}")

    '''
        Function to start 'instance' number of device process

        When the parent (device manager) is terminated all children die
        When the parent (device manager) detects a config change, it kills only children. Parent will be alive

        One can pass 'instance_config' to change the behaviour of any specific instance    
        Note that by default 'self.config' is applied on each instance. 'instance_config' is applied on top of that
            
    '''
    def create_device(self, instances, instance_config=None):
        # Convert the config dictionary to a JSON string
        if instance_config is not None:
           config_json = self.config_manager.modify_config(self.config, instance_config)
        else:
            config_json = json.dumps(self.config)

        # Set the PYTHONPATH environment variable to include the 'common' directory
        env = os.environ.copy()
        env['PYTHONPATH'] = '/code'    

        processes = []

        for _ in range(instances):
            process = subprocess.Popen(["python", self.device['program'], config_json], env=env, preexec_fn=os.setpgrp())                 
            logging.info(f"Created device process {process.pid} in group {os.getpgid(process.pid)}")             
            processes.append(process)
        
        self.running_device_processes.extend(processes)        

    def stop_device(self, process):
        logging.info(f"Stopping process {process.pid}")
        
        # Send a SIGTERM signal to the child process
        process.send_signal(signal.SIGTERM)        
        try:
            # Wait for the child process to finish, with a timeout (adjust as needed)
            process.wait(timeout=10)
            logging.info(f"Process {process.pid} has terminated gracefully.")
        except subprocess.TimeoutExpired:
            logging.warning(f"Process {process.pid} did not terminate within the timeout. Sending SIGKILL.")
            
            # If the child process doesn't terminate within the timeout, send a SIGKILL signal
            process.send_signal(signal.SIGKILL)
            process.wait()
            logging.info(f"Process {process.pid} has been forcefully terminated.")

    def sighup_handler(self, signum, frame):
        logging.info("Received SIGHUP signal. Reloading configuration...")
        self.restart_devices()

    # Signal handler to gracefully terminate subprocesses
    def signal_handler(self, signum, frame):
        logging.error(f"Received {signum} signal")

        for process in self.running_device_processes:
            self.stop_device(process)  

        self.should_exit = True  # Set the flag to indicate threads should exit gracefully 

        # Exit the program
        sys.exit()

    def calculate_file_hash(self):
        # Calculate the hash of the config file
        hasher = hashlib.md5()
        with open(self.configFile, "rb") as file:
            while True:
                data = file.read(4096)
                if not data:
                    break
                hasher.update(data)
        return hasher.hexdigest()
    
    def internal_msg_server(self):
        logging.info("Creating internal message server")

        # Create a localplane_connect object for internal messages
        self.localplane_connect = LocalConnect(self.device['type'], message_queues=self.message_queues, message_condition_var=self.message_condition_var)

        # Start the localplane_connect in server mode
        self.localplane_connect.server()

    # The recv method for IPC (internal) or TCP (interconnect)
    def handle_internal_ingress_message(self):
        while not self.should_exit:
            with self.message_condition_var["internal-ingress"]:
                self.message_condition_var["internal-ingress"].wait(timeout=0.1)
                self.process_message(self.message_queues["internal-ingress"], 0.1)  

            with self.message_condition_var["interconnect-ingress"]:
                self.message_condition_var["interconnect-ingress"].wait(timeout=0.1)  
                self.process_message(self.message_queues["interconnect-ingress"], 0.1)  

    # The send method for IPC (internal) or TCP (interconnect)
    def handle_internal_egress_message(self):
        while not self.should_exit:
            with self.message_condition_var["internal-egress"]:
                self.message_condition_var["internal-egress"].wait(timeout=0.1)
                while not self.message_queues["internal-egress"].empty():
                    priority, message = self.message_queues["internal-egress"].get()
                    if self.localplane_connect and self.localplane_connect.localplane_ready: 
                        try:
                            self.localplane_connect.send_message(message)                      
                        except Exception as e:
                            logging.error(f"Got exception {e}") 

            with self.message_condition_var["interconnect-egress"]:
                self.message_condition_var["interconnect-egress"].wait(timeout=0.1)  
                while not self.message_queues["interconnect-egress"].empty():
                    priority, message = self.message_queues["interconnect-egress"].get()
                    if self.localplane_connect and self.localplane_connect.localplane_ready: 
                        try:
                            self.localplane_connect.send_message(message)                      
                        except Exception as e:
                            logging.error(f"Got exception {e}") 

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

                device_queue.task_done() 
        except Exception as e:
            logging.error(f"Exception in process_message loop: {e}")  
            logging.exception("Exception details:") 

    def handle_system(self): 
        while not self.should_exit:
            try:
                priority, _, message = self.internal_message_queues["system"].get()
                logging.info(f"Got the system message = {message}")
                device_status = message['payload']['message']               
                uuid = device_status['device_info']['uuid']
                self.virtual_device_status[uuid] = device_status
            except queue.Empty:
                pass    

    # This function generates a counter, which is used to resolve when the priority is same during
    # enqueue
    def tie_break_counter_function(self):
        # Get the next value from the counter
        return next(self.tie_break_count_generator)                    
    
    ###################### WEB APP related code #############################
    def create_app(self, url_prefix):
        app = Flask(__name__)

        with app.app_context():
            # Store the Device Manager instance in the application context
            current_app.config['device_manager'] = self

            # Include our Routes
            from common import routes as device_routes          
        
            # Register the blueprint with the app
            app.register_blueprint(device_routes.device_bp, url_prefix=url_prefix)

        return app

    def start_webapp(self, webapp_port, url_prefix=None):
        self.app = self.create_app(url_prefix)    
        logging.info("Running flask")
        self.app.run(debug=False, host="0.0.0.0", port=webapp_port)  
    
    def get_current_device_scale(self, device_type):
        return len(self.running_device_processes)
    
    def set_device_scale(self, device_type, instances):
        self.config['scale']['instances'] = instances
        try:
            self.config_manager.set_config(self.config)
            return True
        except:
            return False
    
    # If instance-id (uuid) is not passed, this function will return the below status for all devices
    #    status = {"uuid": "", 
    #               "mac": ""}
    # If instance-id is passed, then this function will give more detailed status for the instance-id
    def get_device_status(self, device_type, instance_id):
        if instance_id is None:    
            device_status = []       
            for uuid, message in self.virtual_device_status.items():
                device_summary = {
                'uuid': uuid,
                'mac': message['device_info']['mac']
                }
                device_status.append(device_summary)   
            return device_status
        else:
            if instance_id in self.virtual_device_status:
                return self.virtual_device_status[instance_id]
            else:
                return f"Invalid {instance_id=}"
