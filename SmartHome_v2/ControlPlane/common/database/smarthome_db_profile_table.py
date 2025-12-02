from common.database.smarthome_db_session import db_session_context
from common.database.smarthome_db_orm import Profile
from sqlalchemy import Table
import logging
import json

profile_properties_template = {
    'access' : ['ro', 'wo', 'rw'],
    'device_types' : ['all', 'fan', 'light', ['fan', 'sensors']],
    'mode': ['real', 'sim'],
    'priority': ['high', 'mid', 'low']    
}

class ProfileTable():
    def __init__(self):
        self.table_name = Profile.__tablename__  # Get the table name from the class

    def drop_table(self, engine, metadata):
        profile_table = Table(self.table_name, metadata, autoload=True)
        profile_table.drop(engine)    

    @staticmethod
    def add(name, properties):
        if(ProfileTable.validate(properties)):
            with db_session_context() as sn:
                existing_profile = sn.query(Profile).filter_by(name=name).first()
                if existing_profile:
                    return False
                profile = Profile(name=name, 
                                properties=properties)
                logging.info(f"{profile=}")
                sn.add(profile)
                sn.commit()
                return True
        return False

    @staticmethod
    def update(pid, new_properties):
        if(ProfileTable.validate(new_properties)):
            with db_session_context() as sn:
                profile_to_update = sn.query(Profile).filter_by(pid=pid).first()    
                if profile_to_update:
                    profile_to_update.properties = new_properties
                    sn.commit()
                    return True
        return False
    
    @staticmethod
    def delete(pid=None):
        with db_session_context() as sn:
            if pid is None:
                sn.query(Profile).delete()
                sn.commit()
            else:
                profile_to_delete = sn.query(Profile).filter_by(pid=pid).first()
                if profile_to_delete:
                    sn.delete(profile_to_delete)
                    sn.commit()


    @staticmethod
    def get(pid):
        with db_session_context() as sn:
            query = sn.query(Profile)
            if pid is not None:
                query = query.filter(Profile.pid == pid)
        
            profiles = query.all()

            profile_data = [{'pid': profile.pid, 'name': profile.name, 'properties': profile.properties} for profile in profiles]
            return json.dumps(profile_data)

    # Returns a boolean
    @staticmethod
    def validate(properties):               
        for key in properties:
            if key not in profile_properties_template:
                return False
            
            template_values = profile_properties_template[key]
            user_value = properties[key]
            
            if isinstance(user_value, list):
                if not all(value in template_values for value in user_value):
                    return False
            else:
                if user_value not in template_values:
                    return False
        
            return True


