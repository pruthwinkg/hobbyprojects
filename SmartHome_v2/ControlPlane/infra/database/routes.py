from flask import Blueprint, render_template, request, redirect, url_for, jsonify
import requests
from common.utils.constants import INFRA_URL, INFRA_EP_DROP_TABLE, \
                                    INFRA_EP_LIST_TABLES, INFRA_EP_RECREATE_TABLES
from common.database.smarthome_db_user_table import UserTable
from common.database.smarthome_db_profile_table import ProfileTable
from infra.database.database_manager import DatabaseInitializer
from sqlalchemy import MetaData
import logging
from sqlalchemy.engine import reflection

db_bp = Blueprint('db_bp', __name__, 
                   template_folder='templates',
                   static_folder='static')

db_instance = DatabaseInitializer()
db_engine = db_instance.engine
db_metadata = db_instance.metadata

# /list_tables
@db_bp.route(INFRA_EP_LIST_TABLES, methods=['GET'])
def list_tables():
    insp = reflection.Inspector.from_engine(db_engine)    
    return jsonify({"tables": insp.get_table_names()})

# /drop_table?table-name=<table-name>
@db_bp.route(INFRA_EP_DROP_TABLE, methods=['POST'])
def db_drop_table():
    table_name = request.args.get('table-name')
    logging.info(f"Dropping the table {table_name}")

    response = list_tables()
    tables = response.json
    if table_name not in tables["tables"]:
        return jsonify({"message": f"Table {table_name} doesn't exist in the DB"})
    
    try:
        if table_name == 'users':
            usertbl = UserTable()
            usertbl.drop_table(db_engine, db_metadata)
        elif table_name == 'profile':
            profiletbl = ProfileTable()
            profiletbl.drop_table(db_engine, db_metadata)
        return jsonify({"message": f"Dropped the table {table_name}"})
    except Exception as ex:
        return jsonify({"error": str(ex)})
    
# /recreate_tables?table-name=<table-name>
@db_bp.route(INFRA_EP_RECREATE_TABLES, methods=['POST'])
def db_recreate_tables():
    table_name = request.args.get('table-name')
    logging.info(f"Recreating the table {table_name}")
    try:
        if table_name is None:
            # Recreate the tables
            db_metadata.create_all(db_instance.engine)
            return jsonify({"message": "Tables recreated successfully"})
        else:
            # Recreate a specific table
            table = db_metadata.tables.get(table_name)
            if table is None:
                return jsonify({"message": f"Table {table_name} not found"})
            table.create(db_instance.engine)
            return jsonify({"message": f"Table {table_name} recreated successfully"})        
    except Exception as ex:
        return jsonify({"error": str(ex)})