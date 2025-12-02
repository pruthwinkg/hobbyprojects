from functools import wraps
from flask_jwt_extended import verify_jwt_in_request, get_jwt_identity
from flask import request, jsonify
from common.database.smarthome_db_user_table import UserTable
import logging

def role_required(allowed_roles):
    def decorator(fn):
        @wraps(fn)
        def wrapper(*args, **kwargs):

            # Get the user's identity from the access token
            current_user = get_jwt_identity()
            user_info = UserTable.get(username=current_user)

            logging.info(f"{current_user=} {user_info[0]=}")

            # Check if the user's role is allowed for the endpoint
            if user_info[0] and (user_info[0]['properties']['role'] in allowed_roles):
                return fn(*args, **kwargs)  # User has the required role
            else:
                return jsonify(message="Access denied"), 403  # Forbidden

        return wrapper
    return decorator


# Currently hardcoding. Later change it to make it dynamic
def get_user_properties():
    user_properties = {
        'location': 'US',
        'role' : 'user'
    }
    return user_properties