'''
This program is responsible for managing (create/delete/update/read) multiple instances of Light device.
This program is started by the supervisord

'''
from common.virtual_device_manager import VDDeviceManager
from common.task_manager import VDTaskManager
from common.constants import LIGHT_MANAGER_PORT, LIGHT_MANAGER_PREFIX

LIGHT_MANAGER_PROGRAM = './light/light.py'
LIGHT_MANAGER_CONFIG = './light/light.config'
DEVICE_TYPE = 'LIGHT'

device = {
            'type': DEVICE_TYPE,
            'program': LIGHT_MANAGER_PROGRAM,
            'config': LIGHT_MANAGER_CONFIG,
            'device_manager_port': LIGHT_MANAGER_PORT,
            'device_manager_prefix': LIGHT_MANAGER_PREFIX,
        }

class LightManager():
    def __init__(self) -> None:
        # Get a virtual Device Manager for Light Device type
        self.light = VDDeviceManager(device)

if __name__ == '__main__':   
    lm = LightManager()
    lm.light.task_manager.start()