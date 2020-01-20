/******************************************************************************
    Description : This file is responsbile for the creation of UDS type of
                Communication Manager instance
******************************************************************************/

#include "comm_mgr_srv_uds.h"


/*
    @brief This function creates a unique instance of UDS master

    Each Master instance will have it own set of tasks identified by task IDs
*/
COMM_MGR_SRV_ERR comm_mgr_srv_create_uds_master(uint16_t *masterID, COMM_MGR_SRV_MASTER_INSTANCE instance) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_SRV_MASTER uds_master;

    memset(&uds_master, 0, sizeof(COMM_MGR_SRV_MASTER));
    uds_master.masterAf = COMM_MGR_SRV_IPC_AF_UNIX_SOCK_STREAM;
    uds_master.reuseaddr = TRUE; 
    uds_master.nonblockingIO = TRUE; 
    uds_master.srvInactivityTimeOut = -1; // Wait even if no client activity

    // For now, only the default DSIDs are sufficient for UDS
    uds_master.__DSID = (UTILS_DS_ID *)malloc(sizeof(UTILS_DS_ID) * COMM_MGR_SRV_DSID_MAX);
    uds_master.__dsid_cb = (comm_mgr_srv_dsid_cb *)malloc(sizeof(comm_mgr_srv_dsid_cb) * COMM_MGR_SRV_DSID_MAX);

    // Create a Circular Queue for storing the received data from clients
    UTILS_QUEUE queue;
    queue.type = UTILS_QUEUE_CIRCULAR;
    queue.size = UDS_MASTER_RECV_QUEUE_SIZE;
    queue.isPriority = FALSE;
    uds_master.__DSID[COMM_MGR_SRV_DSID_RECV] = utils_ds_queue_create(&queue);
    if (uds_master.__DSID[COMM_MGR_SRV_DSID_RECV] == 0) {
        COMM_MGR_SRV_ERROR("Failed to create a UDS master instance");
        return COMM_MGR_SRV_UDS_MASTER_INIT_ERR;
    }
    uds_master.__dsid_cb[COMM_MGR_SRV_DSID_RECV] = comm_mgr_srv_uds_master_recv_data;
    uds_master.__dsid_cb[COMM_MGR_SRV_DSID_PROTO] = comm_mgr_srv_uds_master_proto_data;

    ret = comm_mgr_srv_init_master(&uds_master);
    if (ret != COMM_MGR_SRV_SUCCESS) {
        COMM_MGR_SRV_ERROR("Failed to create a UDS master instance");
        return ret;
    }

    // Each type of Master Instances (UDS, IDS, etc), share a gloabl protocol queue.
    // That is all UDS masters share same protocol queue, and similarly IDS 

    uint16_t *g_masterID = (uint16_t *)malloc(sizeof(uint16_t));
    *g_masterID = uds_master.__masterID;

    switch(instance) {
        case COMM_MGR_SRV_MASTER_DEFAULT_UDS:
            comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_REQ].arg = (void *)g_masterID;    
            comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_PROCESS].arg = (void *)g_masterID;
            comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_RES_STATIC_UID].arg = (void *)g_masterID;
            comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_RES_STATIC_UID].arg = (void *)g_masterID;
            break;
        default:
            COMM_MGR_SRV_ERROR("Not yet supported");
            return COMM_MGR_SRV_UDS_MASTER_INIT_ERR;
            break;
    }
    *masterID = *g_masterID;

    COMM_MGR_SRV_TRACE("Created a UDS master instance ID 0x%x", *masterID);

    return COMM_MGR_SRV_SUCCESS;
}

void* comm_mgr_srv_uds_request_handler(void *arg) {
    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid Master ID");
        return NULL;
    }
    uint16_t masterID = *(uint16_t *)arg;
    COMM_MGR_SRV_TRACE("%s ready to accept requests for master ID %d", 
                COMM_MGR_SRV_APP_NAME, masterID);
    comm_mgr_srv_accept_clients(masterID);
}

void* comm_mgr_srv_uds_process_handler(void *arg) {
    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid Master ID");
        return NULL;
    }
    uint16_t masterID = *(uint16_t *)arg;
    COMM_MGR_SRV_TRACE("%s ready to process requests for master ID %d", 
                COMM_MGR_SRV_APP_NAME, masterID);

    // The request thread should signal the process thread to go and read from Queue
    boolean run_uds_process_loop = TRUE;
    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;

    while(run_uds_process_loop) {
       eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
       for (uint16_t i = 0; i < eventsRead; i++) {
            if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                comm_mgr_srv_uds_process_events(masterID, FALSE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));    
            } else {
                comm_mgr_srv_uds_process_events(masterID, TRUE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));
            }
       }
    }
}

void* comm_mgr_srv_uds_response_static_handler(void *arg) {
    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid Master ID");
        return NULL;
    }
    uint16_t masterID = *(uint16_t *)arg;
    COMM_MGR_SRV_TRACE("%s ready to send responses for static UIDs from master ID %d", 
                COMM_MGR_SRV_APP_NAME, masterID);
  
    // The process thread should signal the response thread to go and read from protocol Queue
    boolean run_uds_response_loop = TRUE;
    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;

    while(run_uds_response_loop) {
       eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
       for (uint16_t i = 0; i < eventsRead; i++) {
            if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                comm_mgr_srv_uds_process_events(masterID, FALSE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));    
            } else {
                comm_mgr_srv_uds_process_events(masterID, TRUE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));
            }
       }
    }
}

void* comm_mgr_srv_uds_response_dynamic_handler(void *arg) {
    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid Master ID");
        return NULL;
    }
    uint16_t masterID = *(uint16_t *)arg;
    COMM_MGR_SRV_TRACE("%s ready to send responses for dynamic UIDs from master ID %d", 
                COMM_MGR_SRV_APP_NAME, masterID);
  
    // The process thread should signal the response thread to go and read from protocol Queue
    boolean run_uds_response_loop = TRUE;
    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;

    while(run_uds_response_loop) {
       eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
       for (uint16_t i = 0; i < eventsRead; i++) {
            if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                comm_mgr_srv_uds_process_events(masterID, FALSE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));    
            } else {
                comm_mgr_srv_uds_process_events(masterID, TRUE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));
            }
       }
    }
}




/*
    This function is a callback from the communication manager core.

    Depending on the data, we have to send events to other tasks.
    For ex : COMM_MGR_SRV_LOCAL_EVENT_RECV_READY, etc.

    Even the state machine can be triggered from here

    Note : While inserting the data to the utils_ds, we have to encode the
    data such that, the reading tasks can easily decode it. Because, the
    utils_ds is data agnostic library. Its upto the apps to make sure that
    correct data is decoded.


    Data Format :
       | Magic (UDS) | Data len | Data (COMM_MGR_MSG) |
*/
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_recv_data(UTILS_DS_ID id, 
                                        char *data, uint32_t len, void *arg) {
    boolean priority = FALSE; // This flag needs to be set depending on the
                              // payload received
    COMM_MGR_SRV_UDS_MSG *uds_msg = __comm_mgr_srv_uds_msg_encode(data, len, NULL, 0);
    if (uds_msg == NULL) {
        COMM_MGR_SRV_ERROR("Failed to allocate memory");
        return COMM_MGR_SRV_OUT_OF_MEMORY;
    }

    COMM_MGR_SRV_DEBUG("Inserting data to DSID 0x%0x, len = %d", id, len);
    // Insert the data to Queue
    if(utils_ds_queue_enqueue(id, (void *)uds_msg) < 0) {
        COMM_MGR_SRV_ERROR("Failed to insert the data to DSID 0x%0x", id);
        return COMM_MGR_SRV_UTILS_DSID_ERR;
    }

    utils_task_handlers_send_event(TRUE, COMM_MGR_SRV_LOCAL_EVENT_RECV_READY, priority);

    return COMM_MGR_SRV_SUCCESS;
}

// For this function value always comes in *arg
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_proto_data(UTILS_DS_ID id, 
                                            char *data, uint32_t len, void *arg) {
    boolean priority = FALSE; // Priority can be set to Normal, because since only protocol packets
                              // gets enqueued to protocol queue, all are treated with equal priority

    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid argument. arg is NULL");
        return COMM_MGR_SRV_INVALID_ARG;
    }
    COMM_MGR_MSG *msg = (COMM_MGR_MSG *)arg;

    // Enqueue the message to protocol queue after encoding in UDS format
    COMM_MGR_SRV_UDS_MSG *uds_msg = __comm_mgr_srv_uds_msg_encode(NULL, 0, arg, 0); // Hint that no need to malloc by arg_size=0
     if (uds_msg == NULL) {
        COMM_MGR_SRV_ERROR("Failed to allocate memory");
        return COMM_MGR_SRV_OUT_OF_MEMORY;
    }

    COMM_MGR_SRV_DEBUG("Inserting data to DSID 0x%0x, len = %d", id, len);
    // Insert the data to Queue
    if(utils_ds_queue_enqueue(id, (void *)uds_msg) < 0) {
        COMM_MGR_SRV_ERROR("Failed to insert the data to DSID 0x%0x", id);
        return COMM_MGR_SRV_UTILS_DSID_ERR;
    }

    utils_task_handlers_send_event(TRUE, COMM_MGR_SRV_LOCAL_EVENT_PROTO_SEND, priority); 

    return COMM_MGR_SRV_SUCCESS;
}





COMM_MGR_SRV_ERR comm_mgr_srv_uds_process_events(uint16_t masterID, boolean isLocalMode, uint32_t event) {
    COMM_MGR_SRV_LOCAL_EVENT ev = (COMM_MGR_SRV_LOCAL_EVENT)event;
    COMM_MGR_SRV_DEBUG("Processing the event = %d, (%s), mode = %s", 
                event, DECODE_ENUM(COMM_MGR_SRV_LOCAL_EVENT, ev), isLocalMode?"local":"global");

    COMM_MGR_SRV_UDS_MSG *uds_msg;
    char *out_data;
    uint32_t out_datalen = 0;
    void *arg;
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;

    // Check who is Master instance of this task 
    COMM_MGR_SRV_MASTER *master = comm_mgr_srv_get_master(masterID); 
    if(master == NULL) {
        COMM_MGR_SRV_ERROR("Not to able to identify the Master for the event [%d]", event);
        return COMM_MGR_SRV_UDS_PROCESS_EVENT_ERR; // What to do the packet inside the queue during this ?? 
    }

    switch(ev) {
        case COMM_MGR_SRV_LOCAL_EVENT_RECV_READY: // Called by UDS process task
            //Process all the old data packets as well
            {
                while(TRUE) {
                    uds_msg = (COMM_MGR_SRV_UDS_MSG *)utils_ds_queue_dequeue(master->__DSID[COMM_MGR_SRV_DSID_RECV]);
                    if (uds_msg == NULL) {
                        break; // Queue is empty
                    }
                    if(__comm_mgr_srv_uds_msg_decode(uds_msg, &out_data, &out_datalen, NULL) != COMM_MGR_SRV_SUCCESS) {
                        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet, if unable to decode it (Bad UDS packet)
                        __comm_mgr_srv_uds_msg_action(uds_msg); 
                        continue; // Process next in queue
                    }
                    if(out_data != NULL) {
                        COMM_MGR_SRV_DEBUG("Event %d, datalen = %d, data = %s", ev, out_datalen, out_data);
                    }
                    COMM_MGR_MSG *comm_mgr_msg = comm_mgr_get_msg(out_data, out_datalen);
                    if(comm_mgr_msg == NULL) {
                        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet, if unable to get the comm msg (Bad Comm packet)
                        __comm_mgr_srv_uds_msg_action(uds_msg);
                        continue; // Process next in queue
                    }
                    // Process the packet    
                    ret = comm_mgr_srv_protocol_process_packet(comm_mgr_msg);
                    if(ret == COMM_MGR_SRV_PROTO_BAD_PACKET) { // If its a bad packet drop it
                        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet
                        __comm_mgr_srv_uds_msg_action(uds_msg);
                        continue; // Process next in queue        
                    } else if (ret == COMM_MGR_SRV_PROTO_ERR) {
                        // should we drop this current packet and ask the client to send a packet again ??
                    }
                }
                // What to do for other return codes ?? <TODO>
            }
            break;

        case COMM_MGR_SRV_LOCAL_EVENT_PROTO_SEND: // Called by response task
            //Process all the old protocol packets as well
            {
                while(TRUE) {
                    uds_msg = (COMM_MGR_SRV_UDS_MSG *)utils_ds_queue_dequeue(master->__DSID[COMM_MGR_SRV_DSID_RECV]);
                    if (uds_msg == NULL) {
                        break; // Queue is empty
                    }                  
                    if(__comm_mgr_srv_uds_msg_decode(uds_msg, NULL, 0, &arg) != COMM_MGR_SRV_SUCCESS) {
                        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet, if unable to decode it (Bad UDS packet)
                        __comm_mgr_srv_uds_msg_action(uds_msg); 
                        continue; // Process next in queue
                    }
                    COMM_MGR_MSG *comm_mgr_msg = (COMM_MGR_MSG *)arg; // arg was already in COMM_MGR_MSG format when enqueued 
                    if(comm_mgr_msg == NULL) {
                        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet
                        __comm_mgr_srv_uds_msg_action(uds_msg);
                        continue; // What to do after dropping a protocol packet ?? 
                    }

                    // Send the protocol packet to the client
                    ret = comm_mgr_srv_send_data(master, comm_mgr_msg);
                    if(ret != COMM_MGR_SRV_SUCCESS) {
                        //COMM_MGR_SRV_ERR("Failed to send the comm msg.");
                        // <TODO> We might need to set the packet to UDS_MASTER_MSG_ACTION_HOLD to try again later 
                    } else if (ret == COMM_MGR_SRV_SUCCESS) {      
                        // Upon successful send anyway drop the packet
                        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet
                        __comm_mgr_srv_uds_msg_action(uds_msg);
                    }
                }
            }
            break;

        default:
            return COMM_MGR_SRV_UNKNOWN_EVENT;
    }
    return COMM_MGR_SRV_SUCCESS;
}


// This will be called by the utils_task_handler lib to generate
// various tables for managing the events for this task
// Mention all the events in which this task is interested
// A global interest will be created automatically by default
void comm_mgr_srv_uds_process_register_events(uint32_t taskID) {
     
    utils_task_handlers_register_event(COMM_MGR_SRV_LOCAL_EVENT_RECV_READY, taskID);    
}

void comm_mgr_srv_uds_response_static_register_events(uint32_t taskID) {

    utils_task_handlers_register_event(COMM_MGR_SRV_LOCAL_EVENT_PROTO_SEND, taskID);    
}

void comm_mgr_srv_uds_response_dynamic_register_events(uint32_t taskID) {

    utils_task_handlers_register_event(COMM_MGR_SRV_LOCAL_EVENT_PROTO_SEND, taskID);    
}


/*******************************************************************************/
/*              Internal functions                                             */
/*******************************************************************************/
/*
    This function executes the action/s set in the uds message
    This can be called by a dedicated task or by one of the existing
    tasks.

    A UDS message can have multiple actions also set at the same time.
    If DROP is set all other actions will be ignored.
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_uds_msg_action(COMM_MGR_SRV_UDS_MSG *uds_msg) {
    if(uds_msg == NULL) {
        COMM_MGR_SRV_ERROR("Bad UDS packet. Unable to take action");
        return COMM_MGR_SRV_UDS_BAD_PACKET;
    } 

    if (uds_msg->action & UDS_MASTER_MSG_ACTION_DROP) {
        COMM_MGR_SRV_DEBUG("Dropping the UDS message");
        __comm_mgr_srv_uds_msg_free(uds_msg);
    }
    COMM_MGR_SRV_DEBUG("Unsupported action. Not yet implemented");
     
    return COMM_MGR_SRV_SUCCESS;
}



// This function will also allocate memory. So remember to free() it
// If datalen or arg_size is 0, then the encoding assumes that, its already been allocated somewhere
static COMM_MGR_SRV_UDS_MSG* __comm_mgr_srv_uds_msg_encode(char *data, uint32_t datalen, void *arg, uint32_t arg_size) {
    if ((data == NULL) && (arg == NULL)) { // Both cannot be NULL
        return NULL;
    }

    COMM_MGR_SRV_UDS_MSG *uds_msg = (COMM_MGR_SRV_UDS_MSG*)malloc(sizeof(COMM_MGR_SRV_UDS_MSG));
    
    uds_msg->magic = UDS_MASTER_MSG_MAGIC_NUM;
    uds_msg->action = UDS_MASTER_MSG_ACTION_PROCESS; // Default action

    if (data != NULL) {
        uds_msg->uds_datalen = datalen;
        if (datalen > 0) {
            uds_msg->uds_data = (char *)malloc(sizeof(char) * datalen);
            memcpy(uds_msg->uds_data, data, sizeof(char) * datalen);
        } else {
            uds_msg->uds_data = data; // data is already allocated
        }
    }
    
    if(arg != NULL) {
        uds_msg->arg_size = arg_size;
        if (arg_size > 0) {
            uds_msg->arg = (void *)malloc(arg_size);
            memcpy(uds_msg->arg, arg, arg_size);
        } else {
            uds_msg->arg = arg;
        }
    }

    return uds_msg;
}

static COMM_MGR_SRV_ERR __comm_mgr_srv_uds_msg_decode(COMM_MGR_SRV_UDS_MSG *uds_msg, char **data, uint32_t *datalen,
                                          void **arg) {
    if(uds_msg == NULL) {        
        return COMM_MGR_SRV_UDS_BAD_PACKET;
    }
    // Check for the validity of the UDS MSG    
    if(uds_msg->magic != UDS_MASTER_MSG_MAGIC_NUM) {
        return COMM_MGR_SRV_UDS_BAD_PACKET;
    }
   
    if (data != NULL) { 
        *data = uds_msg->uds_data;
        *datalen = uds_msg->uds_datalen;
    }
    if (arg != NULL) {
        *arg = uds_msg->arg;
    }
    return COMM_MGR_SRV_SUCCESS;
}

// Free everything even if not allocated during UDS encode
static void __comm_mgr_srv_uds_msg_free(COMM_MGR_SRV_UDS_MSG *uds_msg) {
    if(uds_msg == NULL) {
        return;
    }

    if(uds_msg->uds_data != NULL) {
        free(uds_msg->uds_data);
    }
    uds_msg->uds_datalen = 0;
    
    if(uds_msg->arg != NULL) {
        free(uds_msg->arg);
    }
    uds_msg->arg_size = 0;

    free(uds_msg);
}

