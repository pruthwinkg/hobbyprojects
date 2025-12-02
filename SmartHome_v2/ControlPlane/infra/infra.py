from infra import create_app
from common.utils.constants import INFRA_PORT
from infra.database.database_manager import DatabaseInitializer
import logging
import threading

app = create_app()

def housekeeper():
    logging.info("Running Houskeeper")
    logging.info("Initialized the smarthome database")
    db_instance = DatabaseInitializer()    

def run_flask():
    logging.info("Running flask")
    app.run(debug=True, use_reloader=False, use_debugger=False, host="0.0.0.0", port=INFRA_PORT)
    #app.run(debug=True, host="0.0.0.0", port=INFRA_PORT)

if __name__ == '__main__':  
    logging.basicConfig(filename='infra.log',
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
