from flask import Blueprint, render_template, request, redirect, url_for, jsonify
from common.database.smarthome_db_user_table import UserTable
from common.utils.constants import AUTHENTICATION_EP_CREATE_USERS, AUTHENTICATION_EP_DELETE_USERS, \
                                    AUTHENTICATION_EP_UPDATE_USERS, AUTHENTICATION_EP_LIST_USERS, \
                                    AUTHENTICATION_EP_USER_LOGIN
from common.utils.utils import generate_random_string
from flask_jwt_extended import create_access_token, jwt_required, get_jwt_identity
from authentication.authentication import role_required, get_user_properties
import logging
import json

user_bp = Blueprint('user_bp', __name__)

# User login route
@user_bp.route(AUTHENTICATION_EP_USER_LOGIN, methods=['POST'])
def login():
    username = request.json.get('username')
    password = request.json.get('password')
    if(UserTable.authenticate_user(username, password)):
        access_token = create_access_token(identity=username)
        return jsonify(access_token=access_token)
    else:
        return jsonify({"message": "Invalid credentials"}), 401


# /create_user?user-name=<user-name>
@user_bp.route(AUTHENTICATION_EP_CREATE_USERS, methods=['POST'])
@jwt_required()
@role_required(allowed_roles=['admin'])
def create_user():
    user_name = request.args.get('user-name')
    user_properties = get_user_properties()
    password = generate_random_string(10)
    if(UserTable.add(user_name, password, user_properties)):
        return jsonify({"message": f"User {user_name=} {password=} created successfully. Please save the username/password"})
    else:
        return jsonify({"message": f"User {user_name} was not created"})


# /list_users
# /list_users?user-id=<user-id>
@user_bp.route(AUTHENTICATION_EP_LIST_USERS, methods=['GET'])
@jwt_required()
@role_required(allowed_roles=['admin'])
def list_users():
    user_id = request.args.get('user-id')
    users = UserTable.get(user_id)
    return json.dumps(users)


# /delete_users
# /delete_users?user-id=<user-id>
@user_bp.route(AUTHENTICATION_EP_DELETE_USERS, methods=['POST'])
@jwt_required()
@role_required(allowed_roles=['admin'])
def delete_users():
    user_id = request.args.get('user-id')
    UserTable.delete(user_id)
    if user_id is None:
        return jsonify({"message": f"All Users deleted successfully {user_id=}"})
    else:
        return jsonify({"message": f"Users deleted successfully {user_id=}"})

# /update_users?user-id=<user-id>
# /update_users?user-id=<user-id>&profile-id=<profile-id>
@user_bp.route(AUTHENTICATION_EP_UPDATE_USERS, methods=['POST'])
@jwt_required()
@role_required(allowed_roles=['admin'])
def update_user():
    user_id = request.args.get('user-id')
    profile_id = request.args.get('profile-id')
    new_user_properties = get_user_properties()
    ret_val = UserTable.update(user_id, new_user_properties, profile_id)
    if user_id is None:
        return jsonify({"message": f"Bad User id was passed {user_id=}"})
    if ret_val is True:
        return jsonify({"message": f"User updated successfully {user_id=}"})
    else:
        return jsonify({"message": f"User was not updated {user_id=}"})