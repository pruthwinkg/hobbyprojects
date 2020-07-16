/******************************************************************************
    Description : This file is responsbile for the creation of UDS type of
                Communication Manager instance
******************************************************************************/

#include "comm_mgr_srv_uds.h"

uint8_t g_comm_mgr_uds_master_instances_num = 0;
boolean g_comm_mgr_uds_loadsharing_en = FALSE;

/*
    @brief This function creates a unique set of instances of UDS type

    Each Master instance will have it own set of tasks identified by task IDs.
    If loadsharing option is enabled, then most of the task IDs will be shared

    This function needs to be called only once.

    Refer the SoftwareSpecifications Documents - Communication Manager Multi-master instace
    section to undertsand about the Mluti-Master design.

    A secondary UDS Master is created to serve the Ancillary data/Advanced communication
    facilties

*/
COMM_MGR_SRV_ERR comm_mgr_srv_create_uds_master(uint16_t *masterID, COMM_MGR_SRV_MASTER_INSTANCE *instances,
                                               uint8_t num_instances, boolean loadsharing) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_SRV_MASTER uds_master;
  
    g_comm_mgr_uds_master_instances_num = num_instances;
    g_comm_mgr_uds_loadsharing_en = loadsharing;

    uint16_t *g_masterID = (uint16_t *)malloc(sizeof(uint16_t) * num_instances);

    for (uint8_t i = 0; i < num_instances; i++) {
        memset(&uds_master, 0, sizeof(COMM_MGR_SRV_MASTER));
        uds_master.masterAf = COMM_MGR_SRV_IPC_AF_UNIX_SOCK_STREAM;
        switch(instances[i]) {
            case COMM_MGR_SRV_MASTER_DEFAULT_UDS:
                uds_master.uds_file = SOCKET_FILE_PATH;
                uds_master.ancillary = FALSE;
                break;
            case COMM_MGR_SRV_MASTER_SECONDARY_UDS:
                uds_master.uds_file = ANC_SOCKET_FILE_PATH;
                uds_master.ancillary = TRUE;
                break;
             default:
                COMM_MGR_SRV_ERROR("Not yet supported");
                return COMM_MGR_SRV_UDS_MASTER_INIT_ERR;
        }                
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
        queue.isProtected = FALSE;
        uds_master.__DSID[COMM_MGR_SRV_DSID_RECV] = utils_ds_queue_create(&queue);
        if (uds_master.__DSID[COMM_MGR_SRV_DSID_RECV] == 0) {
            COMM_MGR_SRV_ERROR("Failed to create a UDS master instance");
            return COMM_MGR_SRV_UDS_MASTER_INIT_ERR;
        }

        // Create a Circular Queue for storing the data to be sent to clients
        queue.type = UTILS_QUEUE_CIRCULAR;
        queue.size = UDS_MASTER_SEND_QUEUE_SIZE;
        queue.isPriority = FALSE;
        queue.isProtected = FALSE;
        uds_master.__DSID[COMM_MGR_SRV_DSID_SEND] = utils_ds_queue_create(&queue);
        if (uds_master.__DSID[COMM_MGR_SRV_DSID_SEND] == 0) {
            COMM_MGR_SRV_ERROR("Failed to create a UDS master instance");
            return COMM_MGR_SRV_UDS_MASTER_INIT_ERR;
        }

        // Create a Circular Queue for storing the data to be sent to clients
        queue.type = UTILS_QUEUE_CIRCULAR;
        queue.size = UDS_MASTER_SEND_QUEUE_SIZE;
        queue.isPriority = FALSE;
        uds_master.__DSID[COMM_MGR_SRV_DSID_HOUSEKEEP] = utils_ds_queue_create(&queue);
        if (uds_master.__DSID[COMM_MGR_SRV_DSID_HOUSEKEEP] == 0) {
            COMM_MGR_SRV_ERROR("Failed to create a UDS master instance");
            return COMM_MGR_SRV_UDS_MASTER_INIT_ERR;
        }

        uds_master.__dsid_cb[COMM_MGR_SRV_DSID_RECV] = comm_mgr_srv_uds_master_recv_data;
        uds_master.__dsid_cb[COMM_MGR_SRV_DSID_PROTO] = comm_mgr_srv_uds_master_proto_data;
        uds_master.__dsid_cb[COMM_MGR_SRV_DSID_SEND] = comm_mgr_srv_uds_master_send_data;
        uds_master.__dsid_cb[COMM_MGR_SRV_DSID_HOUSEKEEP] = comm_mgr_srv_uds_master_housekeeper;

        ret = comm_mgr_srv_init_master(&uds_master);
        if (ret != COMM_MGR_SRV_SUCCESS) {
            COMM_MGR_SRV_ERROR("Failed to create a UDS master instance");
            return ret;
        }

        masterID[i] = uds_master.__masterID;
        COMM_MGR_SRV_TRACE("Created a UDS master instance ID 0x%x", *masterID);

        g_masterID[i] = uds_master.__masterID;

        // Req worker threads cannot be shared
        switch(instances[i]) {
            case COMM_MGR_SRV_MASTER_DEFAULT_UDS:
                comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_REQ].arg = (void *)g_masterID;    
                break;
            case COMM_MGR_SRV_MASTER_SECONDARY_UDS:
                comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_SEC_UDS_REQ].arg = (void *)g_masterID;
                break;
            default:
                COMM_MGR_SRV_ERROR("Not yet supported");
                return COMM_MGR_SRV_UDS_MASTER_INIT_ERR;
        }
    }

    // If loadsharing is enabled, then below worker threads are shared
    comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_PROCESS].arg = (void *)g_masterID;
    comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_RES_STATIC_UID].arg = (void *)g_masterID;
    comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_RES_DYNAMIC_UID].arg = (void *)g_masterID;
    comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_HOUSEKEEPER].arg = (void *)g_masterID;    

    return COMM_MGR_SRV_SUCCESS;
}

/*
    Request Handler has to be run in seperate worker thread in multi-master cases
*/
void* comm_mgr_srv_uds_request_handler(void *arg) {
    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid Master ID");
        return NULL;
    }
    uint16_t *masterID = (uint16_t *)arg;

    for (uint8_t i = 0; i < g_comm_mgr_uds_master_instances_num; i++) {
        COMM_MGR_SRV_TRACE("%s ready to accept requests for master ID %d", 
                        COMM_MGR_SRV_APP_NAME, masterID[i]);
    }                
    comm_mgr_srv_accept_clients(masterID[0]);
}

/*
    A generic run loop for UDS masters. Any worker thread can call this function to
    wait for events and process it.
*/
static void __comm_mgr_srv_uds_run_loop(uint16_t *masterID) {
    boolean run_uds_loop = TRUE;
    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;

    while(run_uds_loop) {
       eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
       for (uint16_t i = 0; i < eventsRead; i++) {
            if(g_comm_mgr_uds_loadsharing_en == TRUE) {
                for (uint8_t j = 0; j < g_comm_mgr_uds_master_instances_num; j++) {
                    if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                        comm_mgr_srv_uds_process_events(masterID[j], FALSE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));    
                    } else {
                        comm_mgr_srv_uds_process_events(masterID[j], TRUE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));
                    }
                }
            } else {
                if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                    comm_mgr_srv_uds_process_events(masterID[0], FALSE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));    
                } else {
                    comm_mgr_srv_uds_process_events(masterID[0], TRUE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));
                }
            }
       }
    }
}

/*
    If loadsharing is enabled in multi-master case, then the same worker thread is used
    to process the events from all the masters
*/
void* comm_mgr_srv_uds_process_handler(void *arg) {
    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid Master ID");
        return NULL;
    }
    uint16_t *masterID = (uint16_t *)arg;
    
    if(g_comm_mgr_uds_loadsharing_en == TRUE) {
        for(uint8_t i = 0; i < g_comm_mgr_uds_master_instances_num; i++) {
            COMM_MGR_SRV_TRACE("%s ready to process requests for master ID %d", 
                        COMM_MGR_SRV_APP_NAME, masterID[i]);
        }
    } else {
        COMM_MGR_SRV_TRACE("%s ready to process requests for master ID %d", 
               COMM_MGR_SRV_APP_NAME, masterID[0]);
    }

    // The request thread should signal the process thread to go and read from Queue
    __comm_mgr_srv_uds_run_loop(masterID);
}

/*
    If loadsharing is enabled in multi-master case, then the same worker thread is used
    to process the events from all the masters
*/
void* comm_mgr_srv_uds_response_static_handler(void *arg) {
    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid Master ID");
        return NULL;
    }
    uint16_t *masterID = (uint16_t *)arg;

    if(g_comm_mgr_uds_loadsharing_en == TRUE) {
        for(uint8_t i = 0; i < g_comm_mgr_uds_master_instances_num; i++) {
            COMM_MGR_SRV_TRACE("%s ready to send responses for static UIDs from master ID %d", 
                        COMM_MGR_SRV_APP_NAME, masterID[i]);
        }
    } else {
        COMM_MGR_SRV_TRACE("%s ready to send responses for static UIDs from master ID %d", 
               COMM_MGR_SRV_APP_NAME, masterID[0]);
    }

    // The process thread should signal the response thread to go and read from protocol Queue
    __comm_mgr_srv_uds_run_loop(masterID);
}

/*
    If loadsharing is enabled in multi-master case, then the same worker thread is used
    to process the events from all the masters
*/
void* comm_mgr_srv_uds_response_dynamic_handler(void *arg) {
    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid Master ID");
        return NULL;
    }
    uint16_t *masterID = (uint16_t *)arg;

    if(g_comm_mgr_uds_loadsharing_en == TRUE) {
        for(uint8_t i = 0; i < g_comm_mgr_uds_master_instances_num; i++) {
            COMM_MGR_SRV_TRACE("%s ready to send responses for dynamic UIDs from master ID %d", 
                        COMM_MGR_SRV_APP_NAME, masterID[i]);
        }
    } else {
        COMM_MGR_SRV_TRACE("%s ready to send responses for dynamic UIDs from master ID %d", 
               COMM_MGR_SRV_APP_NAME, masterID[0]);
    }

    // The process thread should signal the response thread to go and read from protocol Queue
    __comm_mgr_srv_uds_run_loop(masterID);
}

/*
    If loadsharing is enabled in multi-master case, then the same worker thread is used
    to process the events from all the masters
*/
void* comm_mgr_srv_uds_housekeeping_handler(void *arg) {
    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid Master ID");
        return NULL;
    }
    uint16_t *masterID = (uint16_t *)arg;

    if(g_comm_mgr_uds_loadsharing_en == TRUE) {
        for(uint8_t i = 0; i < g_comm_mgr_uds_master_instances_num; i++) {
            COMM_MGR_SRV_TRACE("%s ready to handle housekeeping tasks from master ID %d", 
                        COMM_MGR_SRV_APP_NAME, masterID[i]);
        }
    } else {
        COMM_MGR_SRV_TRACE("%s ready to handle housekeeping tasks from master ID %d", 
               COMM_MGR_SRV_APP_NAME, masterID[0]);
    }

    __comm_mgr_srv_uds_run_loop(masterID);
}


/*
    This function is a callback from the communication manager core.

    Depending on the data, we have to send events to other tasks.
    For ex : COMM_MGR_SRV_LOCAL_EVENT_RECV_READY, etc.

    Even the state machine can be triggered from here

   Note : In the 'arg2', the Communication Manager Core sends us the server fd
          on which the data is received. Map it to UID

    Note : There can be multiple messages in the data received by the Comm Server Core.
        We need identify those indivisual messages and enqueue properly

*/
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_recv_data(UTILS_DS_ID id, void *arg1, void *arg2, void **arg) {
    boolean priority = FALSE; // This flag needs to be set depending on the
                              // payload received
    
    if(arg1 == NULL) {
        return COMM_MGR_SRV_INVALID_ARG;       
    }

    COMM_MGR_SRV_RECV_MSG *comm_srv_rcv_msg = (COMM_MGR_SRV_RECV_MSG *)arg1;
    
    COMM_MGR_MSG **comm_msg = comm_srv_rcv_msg->msg;
    uint8_t comm_num_msgs = comm_srv_rcv_msg->num_msgs;
    uint32_t server_fd = comm_srv_rcv_msg->server_fd;

    if (id == 0) {
        COMM_MGR_SRV_ERROR("Invalid DSID");
        return COMM_MGR_SRV_UTILS_DSID_ERR;
    }

    for(uint8_t i = 0 ; i < comm_num_msgs; i++) {
        COMM_MGR_SRV_UDS_MSG *uds_msg = __comm_mgr_srv_uds_msg_create((void *)comm_msg[i], server_fd);
        if (uds_msg == NULL) {
            COMM_MGR_SRV_ERROR("Failed to allocate memory");
            return COMM_MGR_SRV_OUT_OF_MEMORY;
        }

        COMM_MGR_SRV_DEBUG("Inserting data to DSID 0x%0x, server fd = %d", id, server_fd);
        // Insert the data to Queue
        if(utils_ds_queue_enqueue(id, (void *)uds_msg) < 0) {
            COMM_MGR_SRV_ERROR("Failed to insert the data to DSID 0x%0x", id);
            //return COMM_MGR_SRV_UTILS_DSID_ERR; // Out of multiple msgs if one fails, we shouldnt stop
                            // sending event out for other msgs we have enqueued
        }
    }

    // Finally send one event for all those msgs
    utils_task_handlers_send_event(TRUE, COMM_MGR_SRV_LOCAL_EVENT_RECV_READY, priority);

    return COMM_MGR_SRV_SUCCESS;
}

// For this function value always comes in *arg1
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_proto_data(UTILS_DS_ID id, void *arg1, void *arg2, void **arg) {
    boolean priority = FALSE; // Priority can be set to Normal, because since only protocol packets
                              // gets enqueued to protocol queue, all are treated with equal priority

    if (arg1 == NULL) {
        COMM_MGR_SRV_ERROR("Invalid argument. arg1 is NULL");
        return COMM_MGR_SRV_INVALID_ARG;
    }
    if (id == 0) {
        COMM_MGR_SRV_ERROR("Invalid DSID");
        return COMM_MGR_SRV_UTILS_DSID_ERR;
    }

    COMM_MGR_SRV_MSG *srv_msg = (COMM_MGR_SRV_MSG *)arg1;

    // Enqueue the message to protocol queue after encoding in UDS format
    COMM_MGR_SRV_UDS_MSG *uds_msg = __comm_mgr_srv_uds_msg_create((void *)srv_msg, 0);
     if (uds_msg == NULL) {
        COMM_MGR_SRV_ERROR("Failed to allocate memory");
        return COMM_MGR_SRV_OUT_OF_MEMORY;
    }

    COMM_MGR_SRV_DEBUG("Inserting data to DSID 0x%0x", id);
    // Insert the data to Queue
    if(utils_ds_queue_enqueue(id, (void *)uds_msg) < 0) {
        COMM_MGR_SRV_ERROR("Failed to insert the data to DSID 0x%0x", id);
        return COMM_MGR_SRV_UTILS_DSID_ERR;
    }

    utils_task_handlers_send_event(TRUE, COMM_MGR_SRV_LOCAL_EVENT_PROTO_SEND, priority); 

    return COMM_MGR_SRV_SUCCESS;
}

/*
    This function is used to send regular data packets to the destination UID
    This function doesnt do any memory allocations to keep it light. Any actions
    also will be honoured directly from the srv_msg without requiring to encode
    in UDS message format
   
    Since it is best effort, in case of any error case, the data will be dropped
    and sender will be notified only if required (explicitly asked by sender)
*/
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_send_data(UTILS_DS_ID id, void *arg1, void *arg2, void **arg) {
    boolean priority = FALSE;

    if (arg1 == NULL) {
        COMM_MGR_SRV_ERROR("Invalid argument. arg is NULL");
        return COMM_MGR_SRV_INVALID_ARG;
    }
    if (id == 0) {
        COMM_MGR_SRV_ERROR("Invalid DSID");
        return COMM_MGR_SRV_UTILS_DSID_ERR;
    }

    COMM_MGR_SRV_MSG *srv_msg = (COMM_MGR_SRV_MSG *)arg1;

    COMM_MGR_SRV_DEBUG("Inserting data to DSID 0x%0x", id);
    // Insert the data to Queue
    if(utils_ds_queue_enqueue(id, (void *)srv_msg) < 0) {
        COMM_MGR_SRV_ERROR("Failed to insert the data to DSID 0x%0x", id);
        return COMM_MGR_SRV_UTILS_DSID_ERR;
    }
   
    utils_task_handlers_send_event(TRUE, COMM_MGR_SRV_LOCAL_EVENT_DATA_SEND, priority); 

    return COMM_MGR_SRV_SUCCESS;
}

/*
    This DSID callback is used to send jobs to the HouseKeeping task to perform
    certain actions/tasks on its behalf.

    The jobs are enqued in COMM_MGR_SRV_UDS_HK_JOB structure format

    Here the caller has to allocate the memory to arg before calling this
*/
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_housekeeper(UTILS_DS_ID id, void *arg1, void *arg2, void **arg) {
    boolean priority = FALSE;

    if (arg1 == NULL) {
        COMM_MGR_SRV_ERROR("Invalid argument. arg1 is NULL");
        return COMM_MGR_SRV_INVALID_ARG;
    }

    if (id == 0) {
        COMM_MGR_SRV_ERROR("Invalid DSID");
        return COMM_MGR_SRV_UTILS_DSID_ERR;
    }

    COMM_MGR_SRV_UDS_HK_JOB *hk_job = (COMM_MGR_SRV_UDS_HK_JOB *)arg1;

    COMM_MGR_SRV_UDS_MSG *uds_msg = __comm_mgr_srv_uds_msg_create((void *)hk_job, 0);
     if (uds_msg == NULL) {
        COMM_MGR_SRV_ERROR("Failed to allocate memory");
        return COMM_MGR_SRV_OUT_OF_MEMORY;
    }

    COMM_MGR_SRV_DEBUG("Inserting data to DSID 0x%0x", id);
    // Insert the data to Queue
    if(utils_ds_queue_enqueue(id, (void *)uds_msg) < 0) {
        COMM_MGR_SRV_ERROR("Failed to insert the data to DSID 0x%0x", id);
        return COMM_MGR_SRV_UTILS_DSID_ERR;
    }
   
    utils_task_handlers_send_event(TRUE, COMM_MGR_SRV_LOCAL_EVENT_HOUSEKEEP, priority);

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
                    
                    COMM_MGR_MSG *comm_mgr_msg = (COMM_MGR_MSG *)uds_msg->msg;
                    if(comm_mgr_msg == NULL) {
                        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet, if unable to get the comm msg (Bad Comm packet)
                        __comm_mgr_srv_uds_msg_action(uds_msg);
                        continue; // Process next in queue
                    }

                    COMM_MGR_SRV_DEBUG("Event %d, msg type = %d, submsg_type = %d, src uid = %d, dst uid = %d, payload size = %d", 
                                                            ev, comm_mgr_msg->hdr.msg_type, comm_mgr_msg->hdr.submsg_type, 
                                                            comm_mgr_msg->hdr.src_uid, 
                                                            comm_mgr_msg->hdr.dst_uid, comm_mgr_msg->hdr.payloadSize);
                    
                    //COMM_MGR_SRV_MSG is the message format used by Comm Mgr to carry internal headers + actual comm msg
                    // There will be two copies of a packet received. (uds_msg and srv_msg)
                    COMM_MGR_SRV_MSG *comm_mgr_srv_msg = (COMM_MGR_SRV_MSG *)malloc(sizeof(COMM_MGR_SRV_MSG));
                    memset(comm_mgr_srv_msg, 0, sizeof(COMM_MGR_SRV_MSG));
                    comm_mgr_srv_msg->server_fd = uds_msg->server_fd;
                    comm_mgr_srv_msg->msg = comm_mgr_msg;
                    
                    // Process the packet
                    // <TODO> All the ACTIONs can be offloaded to a housekeeping TASK <TODO> <TODO>

                    // <TODO TODO TODO>
                    // Free the UDS msg, comm_mgr_msg, comm_mgr_srv_msg

                    ret = comm_mgr_srv_protocol_process_packet(comm_mgr_srv_msg);
                    if(ret == COMM_MGR_SRV_PROTO_BAD_PACKET) { // If its a bad packet drop it
                        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet
                        __comm_mgr_srv_uds_msg_action(uds_msg);
                        continue; // Process next in queue        
                    } else if (ret == COMM_MGR_SRV_PROTO_ERR) {
                        // should we drop this current packet and ask the client to send a packet again ??
                    } else if (ret == COMM_MGR_SRV_SUCCESS) {
                        // Check if any actions is requested by Comm Mgr Core
                        if (comm_mgr_srv_msg->action & COMM_MGR_SRV_MSG_ACTION_HOLD) {
                            uds_msg->action = UDS_MASTER_MSG_ACTION_HOLD; // In case of Discovery start
                        }

                        if (comm_mgr_srv_msg->action & COMM_MGR_SRV_MSG_ACTION_DROP) {
                            uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet
                            __comm_mgr_srv_uds_msg_action(uds_msg);
                            continue; // Process next in queue
                        }
                    }
                    // What to do for other return codes ?? <TODO>

                }
                COMM_MGR_SRV_DEBUG("Processed the DSID [0x%0x] completely for event %d", 
                                                    master->__DSID[COMM_MGR_SRV_DSID_RECV], event);
            }
            break;

        case COMM_MGR_SRV_LOCAL_EVENT_PROTO_SEND: // Called by response task
            //Process all the old protocol packets as well
            {
                while(TRUE) {
                    uds_msg = (COMM_MGR_SRV_UDS_MSG *)utils_ds_queue_dequeue(master->__DSID[COMM_MGR_SRV_DSID_PROTO]);
                    if (uds_msg == NULL) {
                        break; // Queue is empty
                    }                  
                    
                    COMM_MGR_SRV_MSG *comm_mgr_srv_msg = (COMM_MGR_SRV_MSG *)uds_msg->msg;
                    if(comm_mgr_srv_msg == NULL) {
                        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet
                        __comm_mgr_srv_uds_msg_action(uds_msg);
                        continue; // What to do after dropping a protocol packet ?? 
                    }

                    // Send the protocol packet to the client
                    ret = comm_mgr_srv_send_data(master, comm_mgr_srv_msg);
                    if(ret != COMM_MGR_SRV_SUCCESS) {
                        //COMM_MGR_SRV_ERR("Failed to send the comm msg.");
                        // <TODO> We might need to set the packet to UDS_MASTER_MSG_ACTION_HOLD to try again later 
                    } else if (ret == COMM_MGR_SRV_SUCCESS) {
                        COMM_MGR_SRV_DEBUG("Sent the Protocol Packet msg_type [%d], sub_type [%d] to UID [%d] successfully",
                                                                comm_mgr_srv_msg->msg->hdr.msg_type, 
                                                                comm_mgr_srv_msg->msg->hdr.submsg_type, 
                                                                comm_mgr_srv_msg->msg->hdr.dst_uid);
                        // Upon successful send anyway drop the packet
                        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet
                        __comm_mgr_srv_uds_msg_action(uds_msg);
                    }
                }
                COMM_MGR_SRV_DEBUG("Processed the DSID [0x%0x] completely for event %d", 
                                                    master->__DSID[COMM_MGR_SRV_DSID_PROTO], event);
            }
            break;
        case COMM_MGR_SRV_LOCAL_EVENT_DATA_SEND:
            //Process all the old data packets as well
            {
                while(TRUE) {
                    COMM_MGR_SRV_MSG *srv_msg = (COMM_MGR_SRV_MSG *)utils_ds_queue_dequeue(master->__DSID[COMM_MGR_SRV_DSID_SEND]);
                    if (srv_msg == NULL) {
                        break; // Queue is empty
                    }                  

                    // Send the data packet to the client
                    ret = comm_mgr_srv_send_data(master, srv_msg);
                    if(ret != COMM_MGR_SRV_SUCCESS) {
                        //COMM_MGR_SRV_ERR("Failed to send the comm msg.");
                        // <TODO> We might need to set the packet to UDS_MASTER_MSG_ACTION_HOLD to try again later 
                    } else if (ret == COMM_MGR_SRV_SUCCESS) {
                        COMM_MGR_SRV_DEBUG("Sent the Data Packet msg_type [%d], sub_type [%d], Dest UID [%d], Src UID [%d] successfully",
                                                                srv_msg->msg->hdr.msg_type, 
                                                                srv_msg->msg->hdr.submsg_type, 
                                                                srv_msg->msg->hdr.dst_uid,
                                                                srv_msg->msg->hdr.src_uid);
                        comm_mgr_srv_msg_action(srv_msg);
                    }
                }
                COMM_MGR_SRV_DEBUG("Processed the DSID [0x%0x] completely for event %d", 
                                                    master->__DSID[COMM_MGR_SRV_DSID_SEND], event);
            }

            break;
        case COMM_MGR_SRV_LOCAL_EVENT_HOUSEKEEP:
            ret = comm_mgr_srv_uds_handle_housekeeping_events(master);
            break;
        default:
            return COMM_MGR_SRV_UNKNOWN_EVENT;
    }
    return ret;
}

COMM_MGR_SRV_ERR comm_mgr_srv_uds_handle_housekeeping_events(COMM_MGR_SRV_MASTER *master) {
    boolean handle_housekeeping_event_loop = TRUE;
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_SRV_UDS_MSG *uds_msg;
    COMM_MGR_SRV_UDS_HK_JOB *hk_job;

    while(handle_housekeeping_event_loop) {
    // Process all the house keeping events which are pending
        uds_msg = (COMM_MGR_SRV_UDS_MSG *)utils_ds_queue_dequeue(master->__DSID[COMM_MGR_SRV_DSID_HOUSEKEEP]);
        if (uds_msg == NULL) {
            break; // Queue is empty
        }                  

        hk_job = (COMM_MGR_SRV_UDS_HK_JOB *)uds_msg->msg;
        if(hk_job == NULL) {
            break; // Queue is empty
        }
        switch(hk_job->event) {
            case COMM_MGR_SRV_HOUSEKEEP_EVENT_CLIENT_DOWN:
                COMM_MGR_SRV_DEBUG("Received Hosekeeping event [%d] (%s)", 
                            hk_job->event, DECODE_ENUM(COMM_MGR_SRV_HOUSEKEEP_EVENT, hk_job->event));
                ret = comm_mgr_srv_protocol_client_event(hk_job->event, hk_job->eventData); 
                break;
            default:
                COMM_MGR_SRV_ERROR("Unknown Housekeeping event [%d]", hk_job->event);
                break;
        }
        
        // Once housekkeping job is done, drop the job
        uds_msg->action = UDS_MASTER_MSG_ACTION_DROP; // Drop the packet
        __comm_mgr_srv_uds_msg_action(uds_msg);
    }
    COMM_MGR_SRV_DEBUG("Processed the DSID [0x%0x] completely for event %d", 
                           master->__DSID[COMM_MGR_SRV_DSID_HOUSEKEEP], COMM_MGR_SRV_LOCAL_EVENT_HOUSEKEEP);

    return ret;
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
    utils_task_handlers_register_event(COMM_MGR_SRV_LOCAL_EVENT_DATA_SEND, taskID);    
}

void comm_mgr_srv_uds_response_dynamic_register_events(uint32_t taskID) {

    utils_task_handlers_register_event(COMM_MGR_SRV_LOCAL_EVENT_PROTO_SEND, taskID);    
    utils_task_handlers_register_event(COMM_MGR_SRV_LOCAL_EVENT_DATA_SEND, taskID);    
}

void comm_mgr_srv_uds_housekeeping_register_events(uint32_t taskID) {

    utils_task_handlers_register_event(COMM_MGR_SRV_LOCAL_EVENT_HOUSEKEEP, taskID);    
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
        return COMM_MGR_SRV_SUCCESS;
    }
    COMM_MGR_SRV_DEBUG("Unsupported action. Not yet implemented");
     
    return COMM_MGR_SRV_SUCCESS;
}

// This function will also allocate memory. So remember to free() it
static COMM_MGR_SRV_UDS_MSG* __comm_mgr_srv_uds_msg_create(void *msg, uint32_t server_fd) {
    if (msg == NULL) {
        return NULL;
    }

    COMM_MGR_SRV_UDS_MSG *uds_msg = (COMM_MGR_SRV_UDS_MSG*)malloc(sizeof(COMM_MGR_SRV_UDS_MSG));
    if(uds_msg == NULL) {
        return NULL;
    }

    uds_msg->action = UDS_MASTER_MSG_ACTION_PROCESS; // Default action
    uds_msg->msg = msg; // Copy the communication manager message to the uds msg
    uds_msg->server_fd = server_fd;

    return uds_msg;
}

static void __comm_mgr_srv_uds_msg_free(COMM_MGR_SRV_UDS_MSG *uds_msg) {
    if(uds_msg == NULL) {
        return;
    }

    comm_mgr_destroy_msg(uds_msg->msg);
    free(uds_msg);
}

