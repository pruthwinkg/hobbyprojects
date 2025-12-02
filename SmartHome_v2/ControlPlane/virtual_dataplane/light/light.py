import logging
from common.virtual_device import VDDevice


LIGHT_TELEMETRY_FREQUENCY = 10
DEVICE_TYPE = 'LIGHT'

class Light():
    def __init__(self):
        self.name = DEVICE_TYPE

    def power(self, on):
        logging.info(f"Switching {on} the light")


def device_start():
    # Create a virtual device of type Light 
    light_vd = VDDevice(Light())
    light_vd.task_manager.start()

if __name__ == '__main__':
    device_start()