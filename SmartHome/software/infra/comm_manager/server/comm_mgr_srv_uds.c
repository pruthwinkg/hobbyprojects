/******************************************************************************
    Description : This file is responsbile for the creation of UDS type of
                Communication Manager instance
******************************************************************************/

#include "comm_mgr_srv.h"
#include "comm_mgr_srv_protocol.h"
#include "utils.h"

#define UDS_MASTER_RECV_QUEUE_SIZE      (5)
/*
    @brief This function creates a unique instance of UDS master

*/
COMM_MGR_SRV_ERR comm_mgr_srv_create_uds_master(uint16_t *masterID) {
    COMM_MGR_SRV_MASTER uds_master;
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
    
}

COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_recv_data(UTILS_DS_ID id, 
                                        char *data, uint32_t len) {

    char *buffer = (char *)malloc(sizeof(char) * len);
    if (buffer == NULL) {
        COMM_MGR_SRV_ERROR("Failed to allocate memory");
        return COMM_MGR_SRV_OUT_OF_MEMORY;
    }
    memset(buffer, 0, sizeof(char) * len);
    memcpy(buffer, data, sizeof(char) * len);
    COMM_MGR_SRV_DEBUG("Inserting data to DSID %d", id);
    // Insert the data to Queue
    utils_ds_queue_enqueue(id, (void *)buffer);
    return COMM_MGR_SRV_SUCCESS;
}

COMM_MGR_SRV_ERR comm_mgr_srv_uds_res_process_events(boolean isLocalMode, uint32_t event) {
    COMM_MGR_SRV_LOCAL_EVENT ev = (COMM_MGR_SRV_LOCAL_EVENT)event;
    switch(ev) {
        case COMM_MGR_SRV_LOCAL_EVENT_RECV_READY:

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
void comm_mgr_srv_uds_res_register_events(uint8_t taskID) {
     
    utils_task_handlers_register_event(COMM_MGR_SRV_LOCAL_EVENT_RECV_READY, taskID);    
    //utils_task_handlers_register_event(COMM_MGR_SRV_EVENT_RECV_READY);    
    //utils_task_handlers_register_event(COMM_MGR_SRV_EVENT_RECV_READY);    
    //utils_task_handlers_register_event(COMM_MGR_SRV_EVENT_RECV_READY);    
    //utils_task_handlers_register_event(COMM_MGR_SRV_EVENT_RECV_READY);    
}

