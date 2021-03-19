/*****************************************************************************
    Description : This is a simple shell program for interfacing with various
    componens of this system
******************************************************************************/

#include <unistd.h>
#include "shell.h"
#include "interface_cmn.h"

extern inline uint16_t interface_lib_get_query(uint16_t id, uint8_t type, uint8_t req_type,
                                              uint16_t res_loc, void *query, uint8_t query_len, char *buf);

static SHELL_APP *shell_app;
boolean shell_app_communication_on = FALSE;

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
    
    // Try to discover the app before accepting any user-requests
    utils_task_handlers_sync(SHELL_APP_TASK_ID_MAX);
    shell_app_send_system_tasks(SHELL_APP_SYSTEM_TASK_DISCOVER, FALSE);

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

void *shell_app_communication_handler(void *arg) {
    if(arg == NULL) {
        SHELL_APP_ERROR("Invalid cid");
        return NULL;
    }   

    COMM_MGR_LIB_CLIENT_ID cid = *(uint16_t *)arg;

    COMM_MGR_LIB_ERR rc = COMM_MGR_LIB_SUCCESS;

    shell_app_communication_on = TRUE;
    rc = comm_mgr_lib_server_communicator(cid);
    shell_app_communication_on = FALSE;

    SHELL_APP_ERROR("Communication Manager Library - Server Communicator is exiting !!!!");
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
		case SHELL_APP_LOCAL_EVENT_SYSTEM:
		{
            shell_app_process_system_tasks();    
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
	uint16_t dst_uid = 0;
	SHELL_APP_ERR rc = SHELL_APP_SUCCESS;
    if(!strcmp(shell_app->args[slot][0], "show")) {	
		rc = shell_app_get_uid_from_appName(shell_app->args[slot][1], &dst_uid);
		if(rc == SHELL_APP_SUCCESS) {
			shell_app_send_user_cmd(slot, dst_uid, SHELL_APP_USER_CMD_SHOW);
		} else if (rc == SHELL_APP_DYNAMIC_APP) {
			// Query the system manager OR communication manager if they know about this app.
			// Build a local cache of Dynamic apps
		} else {
			SHELL_APP_PRINT("Unknown user command\n");
			return SHELL_APP_UNKNOWN_USER_CMD;
		}
    } else if(!strcmp(shell_app->args[slot][0], "config")) {

    } else if(!strcmp(shell_app->args[slot][0], "debug")) {

    } else if (!strcmp(shell_app->args[slot][0], "")) {
        // Do nothing
    } else if (!strcmp(shell_app->args[slot][0], "quit")) {
		shell_app_close();
        exit(0);
    } else if((!strcmp(shell_app->args[slot][0], "help")) && 
            (!strcmp(shell_app->args[slot][1], ""))) { 
        shell_app_display_help();
    } else if((!strcmp(shell_app->args[slot][0], "help")) && 
            (strcmp(shell_app->args[slot][1], ""))) { 
        shell_app_display_apps_help(shell_app->args[slot][1]);
    } else if(!strcmp(shell_app->args[slot][0], "list")) { 
        shell_app_display_list();
    } else {
        SHELL_APP_PRINT("Unknown user command\n");
        return SHELL_APP_UNKNOWN_USER_CMD;
    }
    return SHELL_APP_SUCCESS;
}

void shell_app_send_system_tasks(SHELL_APP_SYSTEM_TASK task, boolean priority) {
    shell_system_task.task = task;
    utils_task_handlers_send_event(TRUE, SHELL_APP_LOCAL_EVENT_SYSTEM, priority);
}
            
// Currently supporting only one system task per event call. Later will implement batch processing
SHELL_APP_ERR shell_app_process_system_tasks() {
    SHELL_APP_ERR rc = SHELL_APP_SUCCESS;
    switch(shell_system_task.task) {
        case SHELL_APP_SYSTEM_TASK_DISCOVER: // Initiate a pre-emptive communication
            // This increases the efficiency of shell app
            SHELL_APP_DEBUG("Initiating a pre-emptive communication to discover the app faster");
            shell_system_task.task = SHELL_APP_SYSTEM_TASK_MAX; // Clear the task
            rc = shell_app_send_discovery();            
            break;
        default:
            return SHELL_APP_UNKNOWN_SYSTEM_TASK;            
    }
    return rc;
}

/*
    This function sends a dummy payload to Communication Manager, inorder for it to be 
    discovered
*/
SHELL_APP_ERR shell_app_send_discovery() {
    char dummy_buf;

    // check if the communication system of this app is ON
    while(shell_app_communication_on == FALSE) {
        sleep(5);
    }

	if(comm_mgr_lib_send_data(shell_app->cid[SHELL_APP_NORMAL_MODE_CLIENT], 
                        SMARTHOME_SUBSYSTEM_COMM_MANAGER, &dummy_buf, 1) != COMM_MGR_LIB_SUCCESS ) { 
		SHELL_APP_ERROR("Failed to send the discovery");
        return SHELL_APP_FAILURE;
	}
    return SHELL_APP_SUCCESS;
}

/*
    This function sends the user requests to the Destination UIDs

	Only "show" "config" "debug" commands are allowed
    Queries to the 'interface library' needs to be sent in the below format
    <type (1 byte)> <req_type (1 byte)> <out_loc (2 byte)><query> <query>

	Format : buf
		<magic><type> <req_type> <out_loc> <command-token/full-query>
        
        <type> = 1
        <req_type> = 1
		<fd> field size (bytes) = 2  (File Descriptor)
		<command-token> field size (bytes) = 2 (Max)
*/
SHELL_APP_ERR shell_app_send_user_cmd(uint8_t slot, uint16_t dst_uid, SHELL_APP_USER_CMD_TYPE type) {
	if (shell_app_communication_on == FALSE) {
		SHELL_APP_DEBUG("Communication System of shell app is not ON. Cannot send requests. Exiting");
		return SHELL_APP_SEND_ERR;
	}

	if(slot >= SHELL_APP_MAX_CMDS) {
		SHELL_APP_ERROR("Invalid slot number %d", slot);
		return SHELL_APP_INVALID_ARG;
	}

	if((type != SHELL_APP_USER_CMD_SHOW) && (type != SHELL_APP_USER_CMD_CONFIG)
		&& (type != SHELL_APP_USER_CMD_DEBUG)) {
		SHELL_APP_ERROR("Invalid command type %d", type); 
		return SHELL_APP_INVALID_ARG; 
	}

	int fd = fileno(shell_app->shellFile[slot]);
	char buf[SHELL_APP_MAX_SEND_BUF_SIZE];
	uint8_t bufsize = SHELL_APP_MAX_SEND_BUF_SIZE;
	uint16_t token = 0xFFFF;
	char full_query[SHELL_APP_MAX_CMD_SIZE];
	memset(full_query, 0, sizeof(full_query));
	uint8_t i = 0, len = 0;
    int num_fds = 1;
    int fds[1];
    uint8_t num_vector = 1;
    void *anc_data[1];
    uint8_t anc_datalen[1];

	// Form the full_query again from tokens
	while(strcmp(shell_app->args[slot][i], "")) {
		strcat(full_query, shell_app->args[slot][i]);
		if (strcmp(shell_app->args[slot][i+1], "")) {
			strcat(full_query, " ");
		}
		i++;
	}

#if 0
    // Refer 'interface' library cmn/interface/interface.h for values needs to be sent
    uint16_t interface_lib_magic = 0xFACE;
    memcpy(&buf[0], &interface_lib_magic, sizeof(uint16_t)); // Interfcae magic

    buf[2] = 0; // Text - For cli based apps (shell)
	memcpy(&buf[4], &fd, sizeof(uint16_t)); // response_loc
	if(shell_app->query_req_type == 0) {
        buf[3] = 0; // Token based
		shell_app_get_token_from_query(shell_app->args[slot][1], full_query, &token);
		if (token == 0xFFFF) {
			SHELL_APP_PRINT("Unknown user command %s", full_query);
			return SHELL_APP_UNKNOWN_USER_CMD;
		}
		memcpy(&buf[6], &token, sizeof(uint16_t)); //command-token
		bufsize = sizeof(char) * 8;
	} else if (shell_app->query_req_type == 1) {
		// Send in tokenized format TODO
	} else {       
        buf[3] = 1; // Full-query
		strcpy(&buf[2], shell_app->args[slot][0]); // full query
		bufsize = strlen(shell_app->args[slot][0]) +  sizeof(uint16_t);
	}
#endif

    if(shell_app->query_req_type == 0) { 
        shell_app_get_token_from_query(shell_app->args[slot][1], full_query, &token);
        bufsize = interface_lib_get_query(INTERFACE_LIB_IDENTIFIER, 0, 0, fd, &token, 2, buf);
    } else { // Full-query
        bufsize = interface_lib_get_query(INTERFACE_LIB_IDENTIFIER, 0, 2, fd, 
                                    shell_app->args[slot][0], strlen(shell_app->args[slot][0]), buf);
    }        

	SHELL_APP_DEBUG("Sending query [%s], token [0x%x] to dst_uid [%d], src_uid [%d], slot [%d], fd [%d]", 
						full_query, token, dst_uid, SHELL_APP_SRC_UID, slot, fd);

    fds[0] = fd;
    anc_data[0] = buf;
    anc_datalen[0] = bufsize;
	//if(comm_mgr_lib_send_data(shell_app->cid, dst_uid, buf, bufsize) != COMM_MGR_LIB_SUCCESS ) {
    if(comm_mgr_lib_send_anc_data(shell_app->cid[SHELL_APP_ANCILLARY_MODE_CLIENT], dst_uid, num_vector, 
                           (char **)anc_data, anc_datalen, num_fds, fds, COMM_MGR_ANC_MSG_INTERFACE) != COMM_MGR_LIB_SUCCESS) {
		SHELL_APP_ERROR("Failed to send the data : %s", buf);
	}
	return SHELL_APP_SUCCESS;   
}

void shell_app_register_process_events(uint32_t taskID) {
	utils_task_handlers_register_event(SHELL_APP_LOCAL_EVENT_USER_CMD, taskID);
	utils_task_handlers_register_event(SHELL_APP_LOCAL_EVENT_APP_RES, taskID);
	utils_task_handlers_register_event(SHELL_APP_LOCAL_EVENT_SYSTEM, taskID);
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
	__shell_app->cid = (COMM_MGR_LIB_CLIENT_ID*)malloc(sizeof(COMM_MGR_LIB_CLIENT_ID) * 2);
	__shell_app->num_cid = 2;

	__shell_app->line = (char *)malloc(sizeof(char) * SHELL_APP_MAX_CMD_SIZE);
	memset(__shell_app->line, 0, sizeof(sizeof(char) * SHELL_APP_MAX_CMD_SIZE));
	memset(__shell_app->args_usage, SHELL_APP_ARGS_USAGE_RESERVED, SHELL_APP_MAX_CMDS * sizeof(SHELL_APP_ARGS_USAGE));
	
	char shellfileName[20];
	for (uint8_t i = 0; i < SHELL_APP_MAX_CMDS; i++) {		
		__shell_app->args_usage[i] = SHELL_APP_ARGS_USAGE_FREE;
		__shell_app->args[i] = (char **)malloc(sizeof(char *) * SHELL_APP_MAX_CMD_TOK);
		memset(shellfileName, 0, sizeof(shellfileName));
		snprintf(shellfileName, sizeof(shellfileName), "%s/shellslot%d", SHELL_APP_OUT_FILE_LOC, i);
		__shell_app->shellFile[i] = fopen(shellfileName, "w+");
		for(uint8_t j = 0; j < SHELL_APP_MAX_CMD_TOK; j++) {
			__shell_app->args[i][j] = (char *)malloc(sizeof(char) * SHELL_APP_MAX_CMD_TOK_SIZE);
			memset(__shell_app->args[i][j], 0, sizeof(char) * SHELL_APP_MAX_CMD_TOK_SIZE);
		}
	}	

	__shell_app->query_req_type = 0; // Set to send Tokens

    shell_system_task.task = SHELL_APP_SYSTEM_TASK_MAX; // Clear the system task 

	return __shell_app;
}

void shell_app_close() {
    char shellfileName[20];
	for (uint8_t i = 0; i < SHELL_APP_MAX_CMDS; i++) { 
		fclose(shell_app->shellFile[i]);
        snprintf(shellfileName, sizeof(shellfileName), "%s/shellslot%d", SHELL_APP_OUT_FILE_LOC, i);
        remove(shellfileName);
	}
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
	client.property->libInactivityTimeOut = 2; //COMM_MGR_LIB_DEFAULT_SELECT_TIMEOUT; // To increase responsiveness

	// Create two clients. Normal and Ancillary
	COMM_MGR_LIB_CLIENT_ID *cid = (COMM_MGR_LIB_CLIENT_ID *)malloc(sizeof(COMM_MGR_LIB_CLIENT_ID) * shell_app->num_cid);
	cid[0] = comm_mgr_lib_create_client(&client);

    if(cid[0] == COMM_MGR_LIB_INVALID_CLIENT) { 
        SHELL_APP_ERROR("Failed to create a Communication Manager library client");
        goto err;
    }	

    // Create one more client for ancillary communciation
    client.ancillary = TRUE;
    cid[1] = comm_mgr_lib_create_client(&client);
    if(cid[1] == COMM_MGR_LIB_INVALID_CLIENT) { 
        SHELL_APP_ERROR("Failed to create a Communication Manager library client");
        return -1;
    }

    /* Create task handlers for this test app */	
    shell_app_workers[SHELL_APP_TASK_ID_REQ].arg = (void *)&cid[0];
    shell_app_workers[SHELL_APP_TASK_ID_PROCESS].arg = (void *)&cid[0];
    shell_app_workers[SHELL_APP_TASK_ID_COMM].arg = (void *)&cid[0];
    shell_app_workers[SHELL_APP_TASK_ID_ANC_COMM].arg = (void *)&cid[1];

	shell_app->cid[0] = cid[0];    
	shell_app->cid[1] = cid[1]; 

	if(utils_task_handlers_create(SHELL_APP_TASK_ID_MAX, shell_app_workers, 
                                SHELL_APP_LOCAL_EVENT_MAX, SHELL_APP_GLOBAL_EVENT_MAX) < 0) {
		SHELL_APP_ERROR("Failed to create task handlers");
        goto err;
    }
    
    // Wait for all the task handlers to finish thier tasks
    utils_task_handlers_wait(SHELL_APP_TASK_ID_MAX, shell_app_workers);

err:
	SHELL_APP_DEBUG("Exiting shell program");

	shell_app_close();
    return 0;
}
