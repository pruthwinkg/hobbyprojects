import asyncio
import websockets
import json
from common.constants import TEST_CONTROLPLANE_WS_PORT

# Example usage:
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
            "uuid": "xyz-abc",
        },
        "destination" : { 
            "service": ["light"],
            "uuid": ["abc-def"],
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

cp_message3 = {
    "application": "smarthome",
    "version": "0.1",
    "type": "external",
    "priority": "low",
    "target" : "device",  
    "payload": {
        "scope": "unicast",
        "subtype": "system",
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

async def main():
    async with websockets.serve(handler, host='0.0.0.0', port=TEST_CONTROLPLANE_WS_PORT):
        await asyncio.Event().wait()

async def handler(websocket, path):
    # This function is called for each WebSocket connection
    counter = 0
    try:
        while True:
            # Wait for a message from the client
            message = await websocket.recv()
            counter += 1
            # Process the message (you can add your custom logic here)
            # For this example, we'll simply echo the message back to the client
            if counter % 3 == 0:
                cp_message = cp_message1
            elif counter % 3 == 1:
                cp_message = cp_message2
            else:
                cp_message = cp_message3
            await websocket.send(f"{json.dumps(cp_message)}")

    except websockets.exceptions.ConnectionClosedOK:
        # The client closed the connection gracefully
        print("Client closed the connection.")

if __name__ == "__main__":
    asyncio.run(main())
