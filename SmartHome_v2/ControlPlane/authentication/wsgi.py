from authentication import create_app
from common.utils.constants import AUTHENTICATION_PORT
from common.database.smarthome_db_user_table import UserTable
import logging
import threading

app = create_app()

def run_flask():
    logging.info("Running flask")
    app.run(debug=True, use_reloader=False, use_debugger=False, host="0.0.0.0", port=AUTHENTICATION_PORT)
    #app.run(debug=True, host="0.0.0.0", port=AUTHENTICATION_PORT)
    #app.run(debug=True, host="0.0.0.0", port=int(os.environ.get('FLASK_RUN_PORT', AUTHENTICATION_PORT)))

def housekeeper():
    logging.info("Running Houskeeper")
    user_name = 'admin'
    password = 'adminpass'
    user_properties = {
        "location": "ALL",
        "role": "admin"
    }
    if(UserTable.add(user_name, password, user_properties)):
        logging.info({f"User {user_name=} {password=} created successfully"})
    else:
        logging.info({f"User {user_name} was not created"})    

if __name__ == '__main__':  
    logging.basicConfig(filename='authentication.log',
                        format='%(asctime)s %(levelname)s %(filename)s [%(funcName)s:%(lineno)d]:%(message)s',
                        filemode='w',
                        level=logging.INFO)
    
    flask_thread = threading.Thread(target=run_flask)
    housekeeping_thread = threading.Thread(target=housekeeper)
    
    flask_thread.start()
    housekeeping_thread.start()

    flask_thread.join()
    housekeeping_thread.join()

    logging.info("Main thread finished")