from flask import Blueprint, request, jsonify, g, current_app as app
import json
import logging
from common.constants import VD_EP_DEVICE_SCALE_GET, VD_EP_DEVICE_SCALE_SET, \
                             VD_EP_DEVICE_STATUS_GET
#from common.routes import device_manager

device_bp = Blueprint('device_bp', __name__, 
                      template_folder='templates',
                      static_folder='static')


############################# DEVICE MANAGEMENT ######################################

# /vdevice/scale/set?device-type=<device-type>&instances=<instances>
@device_bp.route(VD_EP_DEVICE_SCALE_SET, methods=['POST'])
def vdevice_scale():
    device_type = request.args.get('device-type')
    instances = request.args.get('instances')

    # Access the Device Manager instance from the application context
    device_manager = app.config['device_manager']

    # Logic to scale the device-type to 'instances'
    if device_manager.set_device_scale(device_type, instances):
        return jsonify({"message": f"Successfully scaled {device_type=} to {instances=}"})
    else:
        return jsonify({"message": f"Could not scale {device_type} to {instances}"})

# /vdevice/scale/get?device-type=<device-type>
@device_bp.route(VD_EP_DEVICE_SCALE_GET, methods=['GET'])
def get_vdevice_scale():
    device_type = request.args.get('device-type')

    # Access the Device Manager instance from the application context
    device_manager = app.config['device_manager']   

    instances = device_manager.get_current_device_scale(device_type)
    return jsonify({"message": f"Current device scale for {device_type=} {instances=}"})

# /vdevice/status/get?device-type=<device-type>
# /vdevice/status/get?device-type=<device-type>&instance-id=<instance-id>
@device_bp.route(VD_EP_DEVICE_STATUS_GET, methods=['GET'])
def get_vdevice_status():
    device_type = request.args.get('device-type')
    instance_id = request.args.get('instance-id')

    # Access the Device Manager instance from the application context
    device_manager = app.config['device_manager']     

    device_status = device_manager.get_device_status(device_type, instance_id) 
    return jsonify({"message": f"Device staus for {device_type=} {instance_id=} {device_status=}"})