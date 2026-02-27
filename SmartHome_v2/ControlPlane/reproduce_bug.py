import sys
import os
from flask import Flask
from unittest.mock import MagicMock

# Add path
sys.path.append(os.getcwd())

# Mock the constants imports if necessary, but since we are running in the correct dir, it might find them.
# However, we need to make sure 'common' is importable.
# If we run this script from SmartHome_v2/ControlPlane/, 'common' is in the current directory.

try:
    from web_app.home.routes import home_bp
except ImportError as e:
    # If import fails because home is not a package (missing __init__.py), we might need to fix that or adjust import.
    # But let's see if it works as is, maybe python 3 handles it.
    print(f"ImportError: {e}")
    # Try to mock the missing pieces if possible, or just exit.
    sys.exit(1)

app = Flask(__name__)
app.register_blueprint(home_bp)

client = app.test_client()

print("Attempting login with 'admin'...")
try:
    response = client.post('/login', data={'username': 'admin', 'password': 'password'})
    print(f"Status: {response.status_code}")
    print(f"Response: {response.get_data(as_text=True)}")
except UnboundLocalError as e:
    print(f"Caught expected error: {e}")
except Exception as e:
    print(f"Caught unexpected error: {type(e).__name__}: {e}")
