from flask import Blueprint, render_template, request, redirect, url_for, jsonify
import requests
from common.constants import VD_EP_DEVICE_SCALE_GET, VD_EP_DEVICE_SCALE_SET, \
                             VD_EP_DEVICE_STATUS_GET, get_device_url

dpsim_bp = Blueprint('dpsim_bp', __name__, 
                      template_folder='templates',
                      static_folder='static')


############################# DEVICE MANAGEMENT ######################################

# /vdevice/scale/set?device-type=<device-type>&instances=<instances>
@dpsim_bp.route(VD_EP_DEVICE_SCALE_SET, methods=['POST'])
def vdevice_scale():
    device_type = request.args.get('device-type')
    instances = request.args.get('instances')

    # Create a query_params dictionary with the extracted values
    query_params = {}
    if device_type:
        query_params['device-type'] = device_type
    if instances:
        query_params['instances'] = instances    

    device_url = get_device_url(device_type)
    if device_url == "":
        error_message = f"Invalid device-type passed {device_type}"
        return jsonify({"error": error_message})

    url = f"{device_url}{VD_EP_DEVICE_SCALE_SET}"
    response = requests.post(url, params=query_params)

    if response.status_code == 200:
        data = response.json()
        return data  # Return a valid response
    else:
        return None
    

# /vdevice/scale/get?device-type=<device-type>
@dpsim_bp.route(VD_EP_DEVICE_SCALE_GET, methods=['GET'])
def get_vdevice_scale():
    device_type = request.args.get('device-type')
    query_params = {'device-type': device_type} if device_type else {}

    device_url = get_device_url(device_type)
    if device_url == "":
        error_message = f"Invalid device-type passed {device_type}"
        return jsonify({"error": error_message})

    url = f"{device_url}{VD_EP_DEVICE_SCALE_GET}"
    response = requests.get(url, params=query_params)
        
    if response.status_code == 200:
        data = response.json()
        return data  # Return a valid response
    else:
        error_message = f"Error listing virtual devices: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response 
    

# /vdevice/status/get?device-type=<device-type>
# /vdevice/status/get?device-type=<device-type>&instance-id=<instance-id>
@dpsim_bp.route(VD_EP_DEVICE_STATUS_GET, methods=['GET'])
def get_vdevice_status():
    device_type = request.args.get('device-type')
    instance_id = request.args.get('instance-id')

    # Create a query_params dictionary with the extracted values
    query_params = {}
    if device_type:
        query_params['device-type'] = device_type
    if instance_id:
        query_params['instance-id'] = instance_id      

    device_url = get_device_url(device_type)
    if device_url == "":
        error_message = f"Invalid device-type passed {device_type}"
        return jsonify({"error": error_message})

    url = f"{device_url}{VD_EP_DEVICE_STATUS_GET}"
    response = requests.get(url, params=query_params)
        
    if response.status_code == 200:
        data = response.json()
        return data  # Return a valid response
    else:
        error_message = f"Error retriviewing virtual device status: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response 