from common.database.smarthome_db_session import db_session_context
from common.database.smarthome_db_orm import Users
import logging
from sqlalchemy.exc import IntegrityError
from sqlalchemy import Table
from flask_bcrypt import Bcrypt

user_properties_template = {
    'location' : ['US', 'IN', 'ALL'],
    'role': ['admin', 'user']
}

bcrypt = Bcrypt()

class UserTable():
    def __init__(self):
        self.table_name = Users.__tablename__  # Get the table name from the class

    def drop_table(self, engine, metadata):
        users_table = Table(self.table_name, metadata, autoload=True)
        users_table.drop(engine)

    @staticmethod
    def add(username, password, properties):
        if(UserTable.validate(properties)):
            with db_session_context() as sn:
                existing_user = sn.query(Users).filter_by(name=username).first()
                if existing_user:
                    return False
                hashed_password = bcrypt.generate_password_hash(password).decode('utf-8')
                user = Users(name=username, 
                                properties=properties, hashed_password=hashed_password)
                sn.add(user)
                sn.commit()
                return True
        return False

    @staticmethod
    def update(uid, new_properties=None, pid=None):
        if(UserTable.validate(new_properties)):
            with db_session_context() as sn:
                user_to_update = sn.query(Users).filter_by(uid=uid).first()    
                if user_to_update:
                    try:
                        if new_properties:
                            user_to_update.properties = new_properties
                        if pid:
                            user_to_update.pid = pid
                        sn.commit()
                        return True
                    except IntegrityError as e:
                        sn.rollback()  # Roll back the transaction                                         
        return False
    
    @staticmethod
    def delete(uid=None):
        with db_session_context() as sn:
            if uid is None:
                sn.query(Users).delete()
                sn.commit()
            else:
                user_to_delete = sn.query(Users).filter_by(uid=uid).first()
                if user_to_delete:
                    sn.delete(user_to_delete)
                    sn.commit()


    @staticmethod
    def get(uid=None, username=None):
        with db_session_context() as sn:
            query = sn.query(Users)
            if uid is not None:
                query = query.filter(Users.uid == uid)
            if username is not None:
                query = query.filter(Users.name == username)
            users = query.all()

            user_data = [user.to_dict() for user in users]
            return user_data

    @staticmethod
    def authenticate_user(username, password):
        # Retrieve hashed password and salt from database based on the username
        with db_session_context() as sn:
            existing_user = sn.query(Users).filter_by(name=username).first()
            if existing_user:
                stored_hashed_password = existing_user.hashed_password

                if stored_hashed_password is not None and \
                    bcrypt.check_password_hash(stored_hashed_password, password):
                    return True

        return False
    
    # Returns a boolean
    @staticmethod
    def validate(properties):               
        for key in properties:
            if key not in user_properties_template:
                return False
            
            template_values = user_properties_template[key]
            user_value = properties[key]
            
            if isinstance(user_value, list):
                if not all(value in template_values for value in user_value):
                    return False
            else:
                if user_value not in template_values:
                    return False
        
            return True


