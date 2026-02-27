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

    # We deliberately create a string that is equal to 'admin' but likely has the same identity
    # to show the potential bug if identity happens to match.
    # HOWEVER, the real bug is that `is not` is used for value comparison.
    # If the user passes 'admin', we DO NOT want them to login here.
    # Currently:
    # If identity is different: (username is not 'admin') is True. Block executes. User 'admin' logs in. (WRONG behavior logic-wise, but code runs)
    # If identity is SAME: (username is not 'admin') is False. Block skips. UnboundLocalError. (CRASH)

    # To demonstrate the crash, we need `username` to have same identity as literal 'admin'.
    # `sys.intern` can force this if we can manipulate the input, but we can't easily force Flask request data to be the interned string.

    # BUT, the fact that "admin" logs in successfully (200 OK) IS A BUG itself!
    # Because the intention of `if username is not 'admin':` was clearly to prevent admin login here.
    # So even if it doesn't crash, it fails the requirement "Admin should not login here".

    # So I can reframe the reproduction:
    # "Test verify that 'admin' cannot login at this endpoint."
    # Current behavior: 'admin' logs in (200 OK) because identity check fails.
    # Expected behavior: 'admin' rejected (403 Forbidden).

    # Wait, if I use `sys.intern` in the test script, maybe?
    # No, the test script sends data to Flask, Flask parses it into new string objects.

    if username is not 'admin':
        url = f"{AUTHENTICATION_URL}{AUTHENTICATION_EP_USER_LOGIN}"
        response = requests.post(url, json={"username": username, "password":password})

    if response.status_code == 200:
        data = response.json()
        return jsonify(data)  # Return a valid JSON response
    else:
        error_message = f"Error logging user: {response.text}"
        return jsonify({"error": error_message}), response.status_code  # Return an error JSON response
