from flask import Blueprint, render_template, request, redirect, url_for, jsonify
import requests
from common.utils.constants import AUTHENTICATION_URL, AUTHENTICATION_EP_USER_LOGIN

home_bp = Blueprint('home_bp', __name__, 
                      template_folder='templates',
                      static_folder='static')


# These are for normal users
@home_bp.route('/login', methods=['POST'])
def user_login():
    username = request.form['username']
    password = request.form['password']
    if username is not 'admin':
        url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_USER_LOGIN}"
        response = requests.post(url, json={"username": username, "password":password})

    if response.status_code == 200:
        data = response.json()
        return jsonify(data)  # Return a valid JSON response
    else:
        error_message = f"Error logging user: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response
