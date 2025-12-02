from flask import Flask
from common.utils.constants import INFRA_PREFIX

def create_app():
    app = Flask(__name__)

    with app.app_context():
        # Include our Routes
        from .database import routes as db_routes
        
        # Register the blueprint with the app
        app.register_blueprint(db_routes.db_bp, url_prefix=INFRA_PREFIX)

    return app