from flask import Flask

def create_app():
    app = Flask(__name__)

    with app.app_context():
        # Include our Routes
        from .home import routes as home_routes
        from .configuration import routes as config_routes
        from .telemetry import routes as telemetry_routes
        from .admin import routes as admin_routes
        
        # Register the blueprint with the app
        app.register_blueprint(home_routes.home_bp)
        app.register_blueprint(admin_routes.admin_bp)
        app.register_blueprint(config_routes.config_bp)
        app.register_blueprint(telemetry_routes.telemetry_bp)

    return app