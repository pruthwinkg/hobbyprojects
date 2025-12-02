

'''
    Virtual Device Manager constants
'''

# In seconds (for config change detection)
DEVICE_MANAGER_PERIODIC_WAKE = 20



'''
    Virtual Device  constants
'''
DEFAULT_TELEMETRY_DELAY = 0
DEFAULT_TELEMETRY_INTERVAL = 120
DEFAULT_TELEMETRY_PRIORITY = 3

KEEPALIVE_TELEMETRY_DELAY = 0
KEEPALIVE_TELEMETRY_INTERVAL = 30
KEEPALIVE_TELEMETRY_PRIORITY = 3

HOUSEKEEPING_DELAY = 0
HOUSEKEEPING_INTERVAL = 20
HOUSEKEEPING_PRIORITY = 3


'''
    ControlPlane connect constants
'''

MESSAGE_SCHEMA = './common/messages/message_schema.json'


'''
    Virtual Dataplane constants
'''
# Device Manager names
LIGHT_MANAGER = 'dpsim_light'
FAN_MANAGER = 'dpsim_fan'

# Port numbers of various Device Managers. Make sure it is consistent with the docker-compose.yml
TEST_CONTROLPLANE_WS_PORT = 40000
WEB_APP_PORT = 7000
LIGHT_MANAGER_PORT = 20000
FAN_MANAGER_PORT = 20001

# Device URL prefix
LIGHT_MANAGER_PREFIX = '/light-manager/internal'
FAN_MANAGER_PREFIX = '/fan-manager/internal'

# Various service URLs
LIGHT_MANAGER_URL = 'http://' + LIGHT_MANAGER + ':' + str(LIGHT_MANAGER_PORT) + LIGHT_MANAGER_PREFIX
FAN_MANAGER_URL = 'http://' + FAN_MANAGER + ':' + str(FAN_MANAGER_PORT) + FAN_MANAGER_PREFIX

# ENDPOINTS
VD_EP_DEVICE_SCALE_GET = '/vdevice/scale/get'
VD_EP_DEVICE_SCALE_SET = '/vdevice/scale/set'
VD_EP_DEVICE_STATUS_GET = '/vdevice/status/get'


def get_device_url(device_type):
    if device_type == 'light':
        device_url = LIGHT_MANAGER_URL
    elif device_type == 'fan':
        device_url = FAN_MANAGER_URL
    else:
        device_url= ""
    
    return device_url