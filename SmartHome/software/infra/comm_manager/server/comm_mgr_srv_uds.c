/******************************************************************************
    Description : This file is responsbile for the creation of UDS type of
                Communication Manager instance
******************************************************************************/

#include "comm_mgr_srv.h"
#include "comm_mgr_srv_protocol.h"
#include "utils.h"

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
    
}
