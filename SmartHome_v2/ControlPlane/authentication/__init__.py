from flask import Flask
from common.utils.constants import AUTHENTICATION_PREFIX
from flask_jwt_extended import JWTManager
import os

def create_app():
    app = Flask(__name__)

    # Retrieve the secret key from the environment variable
    auth_secret_key = os.environ.get('JWT_SECRET_KEY')
    if auth_secret_key is None:
        raise ValueError("AUTH_SECRET_KEY environment variable is not set")    

    app.config['JWT_SECRET_KEY'] = auth_secret_key
    app.config['JWT_TOKEN_LOCATION'] = ['headers']
    jwt = JWTManager(app)

    with app.app_context():
        # Include our Routes
        from .profiles import routes as profile_routes
        from .users import routes as user_routes
     
        # Register the blueprint with the app
        app.register_blueprint(profile_routes.profile_bp, url_prefix=AUTHENTICATION_PREFIX)
        app.register_blueprint(user_routes.user_bp, url_prefix=AUTHENTICATION_PREFIX)

    return app