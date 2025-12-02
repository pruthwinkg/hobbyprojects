from flask import Blueprint

telemetry_bp = Blueprint('telemetry_bp', __name__, 
                      template_folder='templates',
                      static_folder='static')


@telemetry_bp.route('/device/status', methods=['GET'])
def get_device_status():
    return 'Device Status'