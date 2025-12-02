from sqlalchemy_utils import create_database, database_exists
from common.database.smarthome_db_orm import Base
from common.database.smarthome_db_session import DATABASE_URL, db_session_context
import logging

# Singleton class
class DatabaseInitializer:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            try:
                with db_session_context() as sn:
                    cls._instance.engine = sn.get_bind()
                    if not database_exists(DATABASE_URL):
                        logging.info("Creating the SmartHome database")
                        create_database(DATABASE_URL)
                    else:
                        logging.info("SmartHome DB already exists") 

                    Base.metadata.create_all(cls._instance.engine)
                    cls._instance.metadata = Base.metadata
            except Exception as ex:
                logging.error("Failed to create smarthome-db")

        return cls._instance       

'''
def smarthome_db_init():
    try:
        with db_session_context() as sn:
            engine = sn.get_bind()
            if not database_exists(DATABASE_URL):
                logging.info("Creating the SmartHome database")
                create_database(DATABASE_URL)
            else:
                logging.info("SmartHome DB already exists") 

            Base.metadata.create_all(engine)
    except Exception as ex:
        logging.error("Failed to create smarthome-db") 
'''