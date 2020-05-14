/*****************************************************************************
    Description : This is a simple shell program for interfacing with various
    componens of this system
******************************************************************************/

#include "shell.h"

static SHELL_APP *shell_app;

static void shell_app_read_line(void) {
	// Refer https://brennan.io/2015/01/16/write-a-shell-in-c/

  	ssize_t bufsize = SHELL_APP_MAX_CMD_SIZE; // Preallocate line buffer to avoid fragmenetation from lot of mallocs
	memset(shell_app->line, 0, SHELL_APP_MAX_CMD_SIZE);

  	if (getline(&shell_app->line, &bufsize, stdin) == -1){
    	if (feof(stdin)) {
      		exit(EXIT_SUCCESS);  // We recieved an EOF
    	} else  {
      		perror("readline");
      		exit(EXIT_FAILURE);
    	}
  	}
}

static void shell_app_split_line(char *line, uint8_t slot) {
    int position = 0;
    char **tokens = shell_app->args[slot];
    char *token;

    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SHELL_APP_TOK_DELIM);
    while (token != NULL) {
        memset(tokens[position], 0, sizeof(char) * SHELL_APP_MAX_CMD_TOK_SIZE);
        strcpy(tokens[position], token);
        position++;

        if (position >= SHELL_APP_MAX_CMD_TOK) {
			SHELL_APP_ERROR("Invalid command. Size of the command is too long");
			shell_app->args_usage[slot] = SHELL_APP_ARGS_USAGE_FREE;
			return;
        }

    	token = strtok(NULL, SHELL_APP_TOK_DELIM);
    }
    strcpy(tokens[position], ""); 
	shell_app->args_usage[slot] = SHELL_APP_ARGS_USAGE_IN_USE; 
}

void *shell_app_req_handler(void *arg) {
    if (arg == NULL) {
        SHELL_APP_ERROR("Invalid Client ID");
        return NULL;
    }   
    uint16_t cid = *(uint16_t *)arg;
	char **args;
    SHELL_APP_TRACE("%s ready to process tasks from Client ID %d", SHELL_APP_NAME, cid);
	
	// This thread will keep listening for any user commands
	boolean run_shell_app_req_loop = TRUE;
    boolean priority = FALSE;
	UTILS_DS_ID dsid = shell_app->__DSID[SHELL_APP_LOCAL_EVENT_USER_CMD];

	while(run_shell_app_req_loop) {
		SHELL_APP_PRINT("%s>", shell_app->shell_name);
		shell_app_read_line();
		
		// Check for a free slot in the **args[]
		uint8_t found_slot = SHELL_APP_MAX_CMDS;
		for (uint8_t i = 0 ; i < SHELL_APP_MAX_CMDS; i++) {
			if(shell_app->args_usage[i] == SHELL_APP_ARGS_USAGE_FREE) {
				found_slot = i;
				break;
			}
		}
		
		if(found_slot != SHELL_APP_MAX_CMDS) {
			SHELL_APP_DEBUG("Using the slot [%d] for args", found_slot);
	    	shell_app_split_line(shell_app->line, found_slot);

			// Add to the DSID and notify the process handler
			if(shell_app->args_usage[found_slot] == SHELL_APP_ARGS_USAGE_IN_USE) {
				if(utils_ds_queue_enqueue(dsid, (void *)found_slot) < 0) {
					SHELL_APP_ERROR("Failed to insert the data to DSID 0x%0x", dsid);
					return NULL;
				}	
				utils_task_handlers_send_event(TRUE, SHELL_APP_LOCAL_EVENT_USER_CMD, priority);
			}
		} else {
			SHELL_APP_ERROR("%s is busy. Please again later", SHELL_APP_NAME);
			memset(shell_app->line, 0, SHELL_APP_MAX_CMD_SIZE);
		}		
	}

	return NULL;
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
			uint8_t slot = 0;
			while(TRUE) {
				if(utils_ds_queue_is_empty(shell_app->__DSID[SHELL_APP_DSID_USER_CMD]) == TRUE) {
					break;
				}
				slot = (uint8_t *)utils_ds_queue_dequeue(shell_app->__DSID[SHELL_APP_DSID_USER_CMD]);
					
				if(slot >= SHELL_APP_MAX_CMDS) {
					SHELL_APP_ERROR("Invalid args slot %d", slot);
					continue;
				}

				SHELL_APP_DEBUG("User command available in slot [%d], line %s, processing...", slot, shell_app->line);
	
				// Check again if the slot is still in-use
				if(shell_app->args_usage[slot] != SHELL_APP_ARGS_USAGE_IN_USE ) {
					SHELL_APP_DEBUG("The args slot [%d] in not in-use", slot);
					continue;
				}
				
                shell_app_process_user_cmd(slot);
                shell_app->args_usage[slot] = SHELL_APP_ARGS_USAGE_FREE;
			}
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

/*
    This function process the user cmd and sends it to the appropriate module/app
*/
SHELL_APP_ERR shell_app_process_user_cmd(uint8_t slot) {

    // Walkthrough the args list to get the user commands
    uint8_t i = 1;
    if(!strcmp(shell_app->args[slot][0], "show")) {
        while(strcmp(shell_app->args[slot][i], "")) {
            
            i++;
        }
    } else if(!strcmp(shell_app->args[slot][0], "config")) {

    } else if(!strcmp(shell_app->args[slot][0], "debug")) {

    } else if (!strcmp(shell_app->args[slot][0], "")) {
        // Do nothing
    } else if (!strcmp(shell_app->args[slot][0], "quit")) {
        exit(0);
    } else {
        SHELL_APP_PRINT("Unknown user command\n");
        return SHELL_APP_UNKNOWN_USER_CMD;
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

/*
	This function creates a shell instance. All the buffers are statically allocated for this
	shell instance. This avoids fragmentation resulting from numerous mallocs/free over the time.

	args_usage[] is a special bitmap to indicate about the usage of **args[]. It tells which slots are
	free, in-use, reserved etc
*/
SHELL_APP* shell_app_init(char *name) {
	SHELL_APP *__shell_app = (SHELL_APP *)malloc(sizeof(SHELL_APP));
	memset(__shell_app, 0, sizeof(SHELL_APP));

	strcpy(__shell_app->shell_name, name);
	__shell_app->__DSID = (UTILS_DS_ID*)malloc(sizeof(UTILS_DS_ID) * SHELL_APP_DSID_MAX);
	__shell_app->__dsid_cb = (shell_app_dsid_cb *)malloc(sizeof(shell_app_dsid_cb) * SHELL_APP_DSID_MAX);

	__shell_app->line = (char *)malloc(sizeof(char) * SHELL_APP_MAX_CMD_SIZE);
	memset(__shell_app->line, 0, sizeof(sizeof(char) * SHELL_APP_MAX_CMD_SIZE));
	memset(__shell_app->args_usage, SHELL_APP_ARGS_USAGE_RESERVED, SHELL_APP_MAX_CMDS * sizeof(SHELL_APP_ARGS_USAGE));
	
	for (uint8_t i = 0; i < SHELL_APP_MAX_CMDS; i++) {
		__shell_app->args_usage[i] = SHELL_APP_ARGS_USAGE_FREE;
		__shell_app->args[i] = (char **)malloc(sizeof(char *) * SHELL_APP_MAX_CMD_TOK);
		for(uint8_t j = 0; j < SHELL_APP_MAX_CMD_TOK; j++) {
			__shell_app->args[i][j] = (char *)malloc(sizeof(char) * SHELL_APP_MAX_CMD_TOK_SIZE);
			memset(__shell_app->args[i][j], 0, sizeof(char) * SHELL_APP_MAX_CMD_TOK_SIZE);
		}
	}	

	return __shell_app;
}

int main() {
	COMM_MGR_LIB_CLIENT client;

    // Initialize logger & comm_mgr_lib
	comm_mgr_lib_init(LOG_LVL_ERROR, SHELL_APP_SRC_UID, FALSE);

    SHELL_APP_DEBUG("Intializing shell program");

	shell_app = shell_app_init("shell");

    // Create a Circular Queue for storing the User Commands
    UTILS_QUEUE queue;
    queue.type = UTILS_QUEUE_CIRCULAR;
    queue.size = SHELL_APP_USER_CMD_QUEUE_SIZE;
    queue.isPriority = FALSE;
    shell_app->__DSID[SHELL_APP_DSID_USER_CMD] = utils_ds_queue_create(&queue);
    if (shell_app->__DSID[SHELL_APP_DSID_USER_CMD] == 0) {
        SHELL_APP_ERROR("Failed to create SHELL_APP_DSID_USER_CMD");
        goto err;
    }    

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
	shell_app->cid = cid;    


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
