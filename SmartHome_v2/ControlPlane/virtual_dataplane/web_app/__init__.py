from flask import Flask

def create_app():
    app = Flask(__name__)

    with app.app_context():
        # Include our Routes
        from web_app import routes as dpsim_routes
        
        # Register the blueprint with the app
        app.register_blueprint(dpsim_routes.dpsim_bp)

    return app