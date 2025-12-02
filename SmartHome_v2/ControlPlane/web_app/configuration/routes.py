from flask import Blueprint

config_bp = Blueprint('config_bp', __name__, 
                      template_folder='templates',
                      static_folder='static')


@config_bp.route('/device/config', methods=['GET'])
def get_device_config():
    return 'Device Config'