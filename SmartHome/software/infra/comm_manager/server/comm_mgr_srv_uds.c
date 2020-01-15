/******************************************************************************
    Description : This file is responsbile for the creation of UDS type of
                Communication Manager instance
******************************************************************************/

#include "comm_mgr_srv_uds.h"

static COMM_MGR_SRV_MASTER uds_master;

/*
    @brief This function creates a unique instance of UDS master

*/
COMM_MGR_SRV_ERR comm_mgr_srv_create_uds_master(uint16_t *masterID) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;

    memset(&uds_master, 0, sizeof(COMM_MGR_SRV_MASTER));
    uds_master.masterAf = COMM_MGR_SRV_IPC_AF_UNIX_SOCK_STREAM;
    uds_master.reuseaddr = TRUE; 
    uds_master.nonblockingIO = TRUE; 
    uds_master.srvInactivityTimeOut = -1; // Wait even if no client activity

    // Create a Circular Queue for storing the received data from clients
    UTILS_QUEUE queue;
    queue.type = UTILS_QUEUE_CIRCULAR;
    queue.size = UDS_MASTER_RECV_QUEUE_SIZE;
    queue.isPriority = FALSE;
    uds_master.recvDSID = utils_ds_queue_create(&queue);
    if (uds_master.recvDSID == 0) {
        COMM_MGR_SRV_ERROR("Failed to create a UDS master instance");
        return COMM_MGR_SRV_UDS_MASTER_INIT_ERR;
    }
    uds_master.recv_cb = comm_mgr_srv_uds_master_recv_data;

    ret = comm_mgr_srv_init_master(&uds_master);
    if (ret != COMM_MGR_SRV_SUCCESS) {
        COMM_MGR_SRV_ERROR("Failed to create a UDS master instance");
        return ret;
    }

    uint16_t *g_masterID = (uint16_t *)malloc(sizeof(uint16_t));
    *g_masterID = uds_master.__masterID;
    comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_REQ].arg = (void *)g_masterID;    
    comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_UDS_RES].arg = (void *)g_masterID;
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

void* comm_mgr_srv_uds_response_handler(void *arg) {
    if (arg == NULL) {
        COMM_MGR_SRV_ERROR("Invalid Master ID");
        return NULL;
    }
    uint16_t masterID = *(uint16_t *)arg;
    COMM_MGR_SRV_TRACE("%s ready to send responses for master ID %d", 
                COMM_MGR_SRV_APP_NAME, masterID);

    // TODO :  See if we have to implement eventfd OR conditional var.
    // The request thread should signal the response thread to go and read from Queue
    boolean run_uds_response_loop = TRUE;
    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;

    while(run_uds_response_loop) {
       eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
       for (uint16_t i = 0; i < eventsRead; i++) {
            if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                comm_mgr_srv_uds_process_events(FALSE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));    
            } else {
                comm_mgr_srv_uds_process_events(TRUE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));
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
                                        char *data, uint32_t len) {
    boolean priority = FALSE; // This flag needs to be set depending on the
                              // payload received
    COMM_MGR_SRV_UDS_MSG *uds_msg = __comm_mgr_srv_uds_msg_encode(data, len);
    if (uds_msg == NULL) {
        COMM_MGR_SRV_ERROR("Failed to allocate memory");
        return COMM_MGR_SRV_OUT_OF_MEMORY;
    }

    COMM_MGR_SRV_DEBUG("Inserting data to DSID 0x%0x, len = %d", id, len);
    // Insert the data to Queue
    if(utils_ds_queue_enqueue(id, (void *)uds_msg) < 0) {
        COMM_MGR_SRV_ERROR("Failed to insert the data to DSID 0x%0x", id);
        return COMM_MGR_SRV_RECV_DSID_ERR;
    }

    utils_task_handlers_send_event(TRUE, COMM_MGR_SRV_LOCAL_EVENT_RECV_READY, priority);

    return COMM_MGR_SRV_SUCCESS;
}

COMM_MGR_SRV_ERR comm_mgr_srv_uds_process_events(boolean isLocalMode, uint32_t event) {
    COMM_MGR_SRV_LOCAL_EVENT ev = (COMM_MGR_SRV_LOCAL_EVENT)event;
    COMM_MGR_SRV_DEBUG("Processing the event = %d, (%s), mode = %s", 
                event, DECODE_ENUM(COMM_MGR_SRV_LOCAL_EVENT, ev), isLocalMode?"local":"global");

    COMM_MGR_SRV_UDS_MSG *uds_msg;
    char *out_data;
    uint32_t out_datalen = 0;

    switch(ev) {
        case COMM_MGR_SRV_LOCAL_EVENT_RECV_READY:
            uds_msg = (COMM_MGR_SRV_UDS_MSG *)utils_ds_queue_dequeue(uds_master.recvDSID);
            out_data = __comm_mgr_srv_uds_msg_decode(uds_msg, &out_datalen);
            if(out_data != NULL) {
                COMM_MGR_SRV_DEBUG("Event %d, datalen = %d, data = %s", ev, out_datalen, out_data);
            }
            break;

    <TODO> Depeding on the comm mgr msg type, do something. 
           Check the msg type first. Then see if for the source UID, is protocol already done.
           if not, inform the source to start a protocol. => It means we need to manitain the
           protocol current state/done/not done status in the protocol table (COMM_MGR_SRV_PROTO_TBL)

           If protocol is done for the source UID, either forward / drop / store the packet

            Start/call the state machine from here depeding on the msg type (comm_mgr_srv_protocol_statemachine)

        default:
            return COMM_MGR_SRV_UNKNOWN_EVENT;
    }
    return COMM_MGR_SRV_SUCCESS;
}

// This will be called by the utils_task_handler lib to generate
// various tables for managing the events for this task
// Mention all the events in which this task is interested
// A global interest will be created automatically by default
void comm_mgr_srv_uds_res_register_events(uint32_t taskID) {
     
    utils_task_handlers_register_event(COMM_MGR_SRV_LOCAL_EVENT_RECV_READY, taskID);    
}

/*******************************************************************************/
/*              Internal functions                                             */
/*******************************************************************************/
// This function will also allocate memory. So remember to free() it
static COMM_MGR_SRV_UDS_MSG* __comm_mgr_srv_uds_msg_encode(char *data, uint32_t datalen) {
    if ((datalen == 0) || (data == NULL)) {
        return NULL;
    }
    COMM_MGR_SRV_UDS_MSG *uds_msg = (COMM_MGR_SRV_UDS_MSG*)malloc(sizeof(COMM_MGR_SRV_UDS_MSG));
    
    uds_msg->magic = UDS_MASTER_MSG_MAGIC_NUM; 
    uds_msg->uds_datalen = datalen;
    uds_msg->uds_data = (char *)malloc(sizeof(char) * datalen);
    memset(uds_msg->uds_data, 0, sizeof(char) * datalen);
    memcpy(uds_msg->uds_data, data, sizeof(char) * datalen);

    return uds_msg;
}

static char* __comm_mgr_srv_uds_msg_decode(COMM_MGR_SRV_UDS_MSG *uds_msg, uint32_t *len) {
    if(uds_msg == NULL) {
        return NULL;
    }
    // Check for the validity of the UDS MSG    
    if(uds_msg->magic != UDS_MASTER_MSG_MAGIC_NUM) {
        return NULL;
    }
    if(uds_msg->uds_datalen == 0) {
        return NULL;
    }
    *len = uds_msg->uds_datalen;
    return uds_msg->uds_data;
}

static void __comm_mgr_srv_uds_msg_free(COMM_MGR_SRV_UDS_MSG *uds_msg) {
    if(uds_msg == NULL) {
        return;
    }

    if(uds_msg->uds_data != NULL) {
        free(uds_msg->uds_data);
    }
    uds_msg->uds_datalen = 0;
    free(uds_msg);
}

