from flask import Blueprint, render_template, request, redirect, url_for, jsonify
from common.database.smarthome_db_profile_table import ProfileTable
from flask_jwt_extended import jwt_required, get_jwt_identity
from authentication.authentication import role_required
from common.utils.constants import AUTHENTICATION_EP_CREATE_PROFILES, AUTHENTICATION_EP_DELETE_PROFILES, \
                                    AUTHENTICATION_EP_UPDATE_PROFILES, AUTHENTICATION_EP_LIST_PROFILES
import logging

profile_bp = Blueprint('profile_bp', __name__)

# /create_profile?profile-name=<profile-name>
@profile_bp.route(AUTHENTICATION_EP_CREATE_PROFILES, methods=['POST'])
@jwt_required()
@role_required(allowed_roles=['admin'])
def create_profile():
    profile_name = request.args.get('profile-name')
    profile_properties = request.json.get('profile-properties')
    if(ProfileTable.add(profile_name, profile_properties)):
        return jsonify({"message": f"Profile {profile_name} created successfully"})
    else:
        return jsonify({"message": f"Profile {profile_name} was not created"})


# /list_profiles
# /list_profiles?profile-id=<profile-id>
@profile_bp.route(AUTHENTICATION_EP_LIST_PROFILES, methods=['GET'])
@jwt_required()
@role_required(allowed_roles=['admin'])
def list_profiles():
    profile_id = request.args.get('profile-id')
    profiles = ProfileTable.get(profile_id)
    return profiles


# /delete_profiles
# /delete_profiles?profile-id=<profile-id>
@profile_bp.route(AUTHENTICATION_EP_DELETE_PROFILES, methods=['POST'])
@jwt_required()
@role_required(allowed_roles=['admin'])
def delete_profiles():
    profile_id = request.args.get('profile-id')
    ProfileTable.delete(profile_id)
    if profile_id is None:
        return jsonify({"message": f"All Profiles deleted successfully {profile_id=}"})
    else:
        return jsonify({"message": f"Profiles deleted successfully {profile_id=}"})

# /update_profiles?profile-id=<profile-id>
@profile_bp.route(AUTHENTICATION_EP_UPDATE_PROFILES, methods=['POST'])
@jwt_required()
@role_required(allowed_roles=['admin'])
def update_profile():
    profile_id = request.args.get('profile-id')
    new_profile_properties = request.json.get('profile-properties')
    ret_val = ProfileTable.update(profile_id, new_profile_properties)
    if profile_id is None:
        return jsonify({"message": f"Bad Profile id was passed {profile_id=}"})
    if ret_val is True:
        return jsonify({"message": f"Profile updated successfully {profile_id=}"})
    else:
        return jsonify({"message": f"Profile was not updated {profile_id=}"})
