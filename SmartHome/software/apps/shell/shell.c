/*****************************************************************************
    Description : This is a simple shell program for interfacing with various
    componens of this system
******************************************************************************/

#include "shell.h"


void *shell_app_req_handler(void *arg) {


}

void *shell_app_process_handler(void *arg) {
    if (arg == NULL) {
        SHELL_APP_ERROR("Invalid Client ID");
        return NULL;
    }   
    uint16_t cid = *(uint16_t *)arg;
    SHELL_APP_TRACE("%s ready to process tasks from Client ID %d", SHELL_APP_NAME, cid);
  
    // The process thread get a notification from the request handler to go and read from DSID and process it
    boolean run_shell_app_process_loop = TRUE;
    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;

    while(run_shell_app_process_loop) {
       eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
       for (uint16_t i = 0; i < eventsRead; i++) {
            if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                shell_app_process_events(cid, FALSE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));    
            } else {
                shell_app_process_events(cid, TRUE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));
            }
       }
    }
	return NULL;
}

SHELL_APP_ERR shell_app_process_events(uint16_t cid, boolean isLocalMode, uint32_t event) {
    SHELL_APP_LOCAL_EVENT ev = (SHELL_APP_LOCAL_EVENT)event;
    SHELL_APP_DEBUG("Processing the event = %d, mode = %s", 
                                            event, isLocalMode?"local":"global");	

	switch(ev) {
		case SHELL_APP_LOCAL_EVENT_USER_CMD:
		{
			

		}
			break;
		case SHELL_APP_LOCAL_EVENT_APP_RES:
		{

		}	
			break;
		default:
			SHELL_APP_ERROR("Unkown shell app event");
			return SHELL_APP_UNKNOWN_EVENT;
	}
	return SHELL_APP_SUCCESS;
}

void shell_app_register_process_events(uint32_t taskID) {
	utils_task_handlers_register_event(SHELL_APP_LOCAL_EVENT_USER_CMD, taskID);
	utils_task_handlers_register_event(SHELL_APP_LOCAL_EVENT_APP_RES, taskID);
}

void shell_app_comm_lib_cb(COMM_MGR_LIB_EVENT event) {
	SHELL_APP_LOCAL_EVENT app_ev = SHELL_APP_LOCAL_EVENT_MAX;
	boolean priority = FALSE;

    // Process the events first
    switch(event) {
        case COMM_MGR_LIB_EVENT_RECV_READY:
            COMM_MGR_LIB_DEBUG("Received the COMM_MGR_LIB_EVENT_RECV_READY from Comm Library"); 
            app_ev = SHELL_APP_LOCAL_EVENT_APP_RES;
            break;
        default:
            SHELL_APP_ERROR("Invalid Communication Manager Library event");
            break;
    }

    // Enrich the information by optionally querying the COMM_MGR_LIB_STATUS
    //comm_mgr_lib_get_status();

    // Finally notify the other app-task handlers about this event (Send app specific events)
    if(app_ev != SHELL_APP_LOCAL_EVENT_MAX) {
        if(utils_task_handlers_send_event(TRUE, app_ev, priority) < 0) {
            SHELL_APP_ERROR("Unable to send the event [%d]", app_ev);
        }
    }
}

int main() {
	COMM_MGR_LIB_CLIENT client;

    log_lib_init(NULL, LOG_LVL_DEBUG); // Initialize logger
	comm_mgr_lib_init(LOG_LVL_DEBUG, SHELL_APP_SRC_UID, FALSE);

    SHELL_APP_DEBUG("Intializing shell program");

	// Create a Communication Manager Library client
	memset(&client, 0, sizeof(COMM_MGR_LIB_CLIENT));
	client.clientAf = COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM;
	client.property = (COMM_MGR_LIB_CLIENT_PROPERTY*)malloc(sizeof(COMM_MGR_LIB_CLIENT_PROPERTY));
	client.property->app_cb = shell_app_comm_lib_cb;
	client.property->comm_mgr_lib_recv_queue_size = SHELL_APP_COMM_MGR_LIB_RECV_QUEUE_SIZE;
	client.property->comm_mgr_lib_send_queue_size = SHELL_APP_COMM_MGR_LIB_SEND_QUEUE_SIZE;
	client.property->libInactivityTimeOut = COMM_MGR_LIB_DEFAULT_SELECT_TIMEOUT;
	COMM_MGR_LIB_CLIENT_ID *cid = (COMM_MGR_LIB_CLIENT_ID *)malloc(sizeof(COMM_MGR_LIB_CLIENT_ID));
	*cid = comm_mgr_lib_create_client(&client);

    if(*cid == COMM_MGR_LIB_INVALID_CLIENT) { 
        SHELL_APP_ERROR("Failed to create a Communication Manager library client");
        goto err;
    }	

    /* Create task handlers for this test app */	
    shell_app_workers[SHELL_APP_TASK_ID_REQ].arg = (void *)cid;
    shell_app_workers[SHELL_APP_TASK_ID_PROCESS].arg = (void *)cid;
    
	if(utils_task_handlers_create(SHELL_APP_TASK_ID_MAX, shell_app_workers, 
                                SHELL_APP_LOCAL_EVENT_MAX, SHELL_APP_GLOBAL_EVENT_MAX) < 0) {
		SHELL_APP_ERROR("Failed to create task handlers");
        goto err;
    }
    
    // Wait for all the task handlers to finish thier tasks
    utils_task_handlers_wait(SHELL_APP_TASK_ID_MAX, shell_app_workers);

err:
	SHELL_APP_DEBUG("Exiting shell program");

    return 0;
}
