from flask import Blueprint, render_template, request, redirect, url_for, jsonify
from common.database.smarthome_db_profile_table import ProfileTable
from common.utils.constants import AUTHENTICATION_URL
from common.utils.constants import AUTHENTICATION_EP_CREATE_PROFILES, AUTHENTICATION_EP_DELETE_PROFILES, \
                                    AUTHENTICATION_EP_UPDATE_PROFILES, AUTHENTICATION_EP_LIST_PROFILES
from common.utils.constants import AUTHENTICATION_EP_CREATE_USERS, AUTHENTICATION_EP_DELETE_USERS, \
                                    AUTHENTICATION_EP_UPDATE_USERS, AUTHENTICATION_EP_LIST_USERS, \
                                    AUTHENTICATION_EP_USER_LOGIN
import logging
import requests

admin_bp = Blueprint('admin_bp', __name__, 
                      template_folder='templates',
                      static_folder='static')

# This is admin with full control
@admin_bp.route('/admin/login', methods=['POST'])
def admin_login():
    username = request.form['username']
    password = request.form['password']
    url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_USER_LOGIN}"
    response = requests.post(url, json={"username": username, "password":password})

    if response.status_code == 200:
        data = response.json()
        return jsonify(data)  # Return a valid JSON response
    else:
        error_message = f"Error logging admin: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response



@admin_bp.route('/admin/dashboard')
def admin_dashboard():
    return render_template('admin_dashboard.html')

############################# PROFILE MANAGEMENT ######################################

# /admin/create_profile?profile-name=<profile-name>
@admin_bp.route('/admin/create_profile', methods=['POST'])
def create_profile():
    profile_name = request.args.get('profile-name')
    profile_properties = request.json.get('profile-properties')
    query_params = {'profile-name': profile_name} if profile_name else {}

    # Get the access token from the headers
    access_token = request.headers.get('Authorization', '').replace('Bearer ', '')
    # Include the access token in the headers of the request to the authentication service
    headers = {"Authorization": f"Bearer {access_token}"}  

    url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_CREATE_PROFILES}"
    response = requests.post(url, json={"profile-properties": profile_properties}, params=query_params, headers=headers)
    
    if response.status_code == 200:
        data = response.json()
        return jsonify(data)  # Return a valid JSON response
    else:
        error_message = f"Error creating profile: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response


# /admin/list_profiles
# /admin/list_profiles?profile-id=<profile-id>
@admin_bp.route('/admin/list_profiles')
def list_profiles(): 
    profile_id = request.args.get('profile-id')
    query_params = {'profile-id': profile_id} if profile_id else {}

    # Get the access token from the headers
    access_token = request.headers.get('Authorization', '').replace('Bearer ', '')
    # Include the access token in the headers of the request to the authentication service
    headers = {"Authorization": f"Bearer {access_token}"}  

    url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_LIST_PROFILES}"
    response = requests.get(url, params=query_params, headers=headers)
        
    if response.status_code == 200:
        data = response.json()
        return data  # Return a valid response
    else:
        error_message = f"Error listing profiles: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response    
    

# /admin/delete_profiles
# /admin/delete_profiles?profile-id=<profile-id>
@admin_bp.route('/admin/delete_profiles', methods=['POST'])
def delete_profiles():
    profile_id = request.args.get('profile-id')
    query_params = {'profile-id': profile_id} if profile_id else {}

    # Get the access token from the headers
    access_token = request.headers.get('Authorization', '').replace('Bearer ', '')
    # Include the access token in the headers of the request to the authentication service
    headers = {"Authorization": f"Bearer {access_token}"}  

    url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_DELETE_PROFILES}"
    response = requests.post(url, params=query_params, headers=headers)

    if response.status_code == 200:
        data = response.json()
        return data  # Return a valid response
    else:
        return None


# /admin/update_profiles?profile-id=<profile-id>
@admin_bp.route('/admin/update_profiles', methods=['POST'])
def update_profile():
    profile_id = request.args.get('profile-id')
    new_profile_properties = request.json.get('profile-properties')
    query_params = {'profile-id': profile_id} if profile_id else {}

    # Get the access token from the headers
    access_token = request.headers.get('Authorization', '').replace('Bearer ', '')
    # Include the access token in the headers of the request to the authentication service
    headers = {"Authorization": f"Bearer {access_token}"}  

    url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_UPDATE_PROFILES}"
    response = requests.post(url, json={"profile-properties": new_profile_properties}, params=query_params, headers=headers)

    if response.status_code == 200:
        data = response.json()
        return jsonify(data)  # Return a valid JSON response
    else:
        error_message = f"Error creating profile: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response
    

############################## USER MANAGEMENT ####################################

# /admin/create_user?user-name=<user-name>
@admin_bp.route('/admin/create_user', methods=['POST'])
def create_user():
    user_name = request.args.get('user-name')
    query_params = {'user-name': user_name} if user_name else {}

    # Get the access token from the headers
    access_token = request.headers.get('Authorization', '').replace('Bearer ', '')
    # Include the access token in the headers of the request to the authentication service
    headers = {"Authorization": f"Bearer {access_token}"}  

    url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_CREATE_USERS}"
    response = requests.post(url, params=query_params, headers=headers)
    
    if response.status_code == 200:
        data = response.json()
        return jsonify(data)  # Return a valid JSON response
    else:
        error_message = f"Error creating user: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response


# /admin/list_users
# /admin/list_users?user-id=<user-id>
@admin_bp.route('/admin/list_users')
def list_users(): 
    user_id = request.args.get('user-id')
    query_params = {'user-id': user_id} if user_id else {}

    # Get the access token from the headers
    access_token = request.headers.get('Authorization', '').replace('Bearer ', '')
    # Include the access token in the headers of the request to the authentication service
    headers = {"Authorization": f"Bearer {access_token}"}    

    url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_LIST_USERS}"
    response = requests.get(url, params=query_params, headers=headers)
    
    if response.status_code == 200:
        data = response.json()
        return data  # Return a valid response
    else:
        error_message = f"Error listing user: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response
    

# /admin/delete_users
# /admin/delete_users?user-id=<user-id>
@admin_bp.route('/admin/delete_users', methods=['POST'])
def delete_users():
    user_id = request.args.get('user-id')
    query_params = {'user-id': user_id} if user_id else {}

    # Get the access token from the headers
    access_token = request.headers.get('Authorization', '').replace('Bearer ', '')
    # Include the access token in the headers of the request to the authentication service
    headers = {"Authorization": f"Bearer {access_token}"}  

    url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_DELETE_USERS}"
    response = requests.post(url, params=query_params, headers=headers)

    if response.status_code == 200:
        data = response.json()
        return data  # Return a valid response
    else:
        return None


# /admin/update_users?user-id=<user-id>
@admin_bp.route('/admin/update_users', methods=['POST'])
def update_user():
    user_id = request.args.get('user-id')
    profile_id = request.args.get('profile-id')
    query_params = {}
    if user_id:
        query_params['user-id'] = user_id
    if profile_id:
        query_params['profile-id'] = profile_id

    # Get the access token from the headers
    access_token = request.headers.get('Authorization', '').replace('Bearer ', '')
    # Include the access token in the headers of the request to the authentication service
    headers = {"Authorization": f"Bearer {access_token}"}          

    url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_UPDATE_USERS}"
    response = requests.post(url, params=query_params, headers=headers)

    if response.status_code == 200:
        data = response.json()
        return jsonify(data)  # Return a valid JSON response
    else:
        error_message = f"Error creating user: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response