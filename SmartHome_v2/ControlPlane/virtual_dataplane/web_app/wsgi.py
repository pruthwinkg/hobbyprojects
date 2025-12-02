from web_app import create_app
from common.constants import WEB_APP_PORT
import logging

app = create_app()

def run_flask():
    logging.info("Running flask")
    app.run(debug=True, host="0.0.0.0", port=WEB_APP_PORT)
    #app.run(debug=True, host="0.0.0.0", port=int(os.environ.get('FLASK_RUN_PORT', WEB_APP_PORT)))

if __name__ == '__main__':  
    logging.basicConfig(filename='web_app.log',
                        format='%(asctime)s %(levelname)s %(filename)s [%(funcName)s:%(lineno)d]:%(message)s',
                        filemode='w',
                        level=logging.INFO)
    run_flask()