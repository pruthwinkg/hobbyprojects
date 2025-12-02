'''
    This module will take of managing various kinds of messages supported by the 
    Virtual Dataplane layer

     - Messaging will be catergorized into Internal, External, Interconnect

     Read the README for more details about messaging

     This module uses Protobuf for message serialization/deserialization (better efficiency) and
     JsonSchema for message validation (supports complex validations)
'''
import sys
import json
import logging
import jsonschema
from jsonschema.exceptions import ValidationError
from common.constants import MESSAGE_SCHEMA

class VDMessage():
    def __init__(self) -> None:
        # Load the JSON Schema from the file
        with open(MESSAGE_SCHEMA, 'r') as schema_file:
            self.schemas = json.load(schema_file)

    def validate_message(self, message):
        try:
            if not message:
                logging.info("Empty message received.")
                return False, {}

            parsed_message = json.loads(message)
            jsonschema.validate(parsed_message, self.schemas[1])
            return True, parsed_message
        except json.JSONDecodeError:
            print("JSON decoding error:", sys.exc_info()[1])
            return False, {}
        except ValidationError as e:
            print("Validation error:", e)
            return False, {}
        
    '''
        This function will generate a message based on the 'type'
        for the 'payload'

        Depending on the 'type' passed, the 'payload' is validated
        against the respective schema.

        If validate is set to False, the validation is skipped. Useful
        to reduce overhead for time bound messages

        'type' supported:
            - internal
            - external
            - interconnect
    '''
    def create_message(self, type, payload, validate=True):
        pass

    def custom_validation(self, instance, schema):
        # Perform custom validation logic here
        if instance["target"] == "device" and "device" not in instance["payload"]:
            raise jsonschema.ValidationError("'device' is a required property when 'target' is 'device'")
        if instance["target"] == "service" and "service" not in instance["payload"]:
            raise jsonschema.ValidationError("'service' is a required property when 'target' is 'service'")


cp_message1 = {
    "application": "smarthome",
    "version": "0.1",
    "type": "external",
    "priority": "low",
    "target" : "device",
    "payload": {
        "scope": "unicast",
        "subtype": "config",
        "source" : { 
            "origin": "configuration",
            "uuid": "abc-def",
        },        
        "destination" : { 
            "service": ["light"],
            "uuid": ["abc-def"],
        },                
        "message": { # This is optional and apps need to validate, NOT infra
            # This could be anything
            "ack": "ack",  # Optional
            "liveliness": "alive", # Optional
            "config": "power-on",
            "target": "device1",
            "duration": 60            
        }       
    }    
}

cp_message2 = {
    "application": "smarthome",
    "version": "0.1",
    "type": "external",
    "priority": "low",
    "target" : "device",  
    "payload": {
        "scope": "unicast",
        "subtype": "config",
        "source" : { 
            "origin": "configuration",
            "uuid": "xyz-abc",
        },
        "destination" : { 
            "service": ["light"],
            "uuid": ["abc-def"],
        }       
    }
}

cp_message3 = {
    "application": "smarthome", # Required
    "version": "0.1", # Required
    "type": ["external", "internal", "interconnect"], # Required # Defines the scope
    "priority": ["low", "mid", "high"], # Required
    "target" : ["device", "service"], # Required # Defines the direction (north/south/east/west) 
    "payload": { # Required
        "scope": ["unicast", "broadcast", "multicast"], # Required
        "subtype": ["config", "telemetry", "system"], # Required
        "source" : { # Required
            "origin": "configuration",
            "uuid": "xyz-abc",
        },
        "destination" : { # Required
            "device": ["light"], # Required # or "service": ["auth"], => depending on target. This is a list of dests
            "uuid": ["abc-def"], # Required # This is a list of dests
        },
        "message": { # This is optional and apps need to validate, NOT infra
            # This could be anything
            "ack": "ack",  # Optional
            "liveliness": "alive", # Optional
            "config": "power-on",
            "target": "device1",
            "duration": 60            
        }       
    }    
}

# Sample message for virtual dataplane internal message
cp_message4 = {
    "application": "smarthome",
    "version": "0.1",
    "type": "internal",
    "priority": "low",
    "target" : "device",  
    "payload": {
        "scope": "unicast",
        "subtype": "system",
        "source" : { 
            "origin": "light",
            "uuid": "xyz-abc",
        },
        "destination" : { 
            "device": ["light"],
            "uuid": [""],
        } ,
        "message": { # apps need to validate, NOT infra
            "device_info": "",            
        }             
    }
}


if __name__ == '__main__':
    messaging = VDMessage()
    is_valid, parsed_message = messaging.validate_message(json.dumps(cp_message4))
    if is_valid:
        print("Valid message")
    else:
        print("Invalid message")

