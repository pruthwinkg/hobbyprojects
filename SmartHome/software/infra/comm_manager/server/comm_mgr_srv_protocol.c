/*****************************************************************************/
/*  Description : This file handles all the communication manager protocol   */
/*                related functionalities                                    */
/*****************************************************************************/
#include "comm_mgr_srv.h"
#include "comm_mgr_cmn.h"
#include "comm_mgr_srv_protocol.h"
#include "utils.h"

// Two <UID, fd> tables are created. One for Static UIDs and another for dynamic. 
// The tables are indexed with the UIDs. Since the static and dynamic UID ranges 
//are different two tables are required
COMM_MGR_SRV_PROTO_TBL *comm_mgr_srv_protocol_static_uid_tbl; // For ALL infra modules and some user apps
COMM_MGR_SRV_PROTO_TBL *comm_mgr_srv_protocol_dynamic_uid_tbl; // For ALL user apps

int comm_mgr_srv_protocol_curr_state;
/***********************************************************
    @brief This function initializes the protocol needed
           for communication manager

            Only static tbl is created during the init time.
            For the dynamic tbl creation, the app manager has to
            request the communication manager.
***********************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_init() {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    
    comm_mgr_srv_protocol_static_uid_tbl = 
                    comm_mgr_srv_protocol_create_uid_tbl(SYS_MGR_CLIENT_MAX_CLIENTS);

    if(comm_mgr_srv_protocol_static_uid_tbl == NULL) {
        COMM_MGR_SRV_ERROR("Failed to create the static uid table");
        return COMM_MGR_SRV_PROTO_INIT_ERR;
    }

    // Init the protocol state machine current state
    comm_mgr_srv_protocol_curr_state = COMM_MGR_PROTO_DISCOVERY_START;

    return ret;
}

/*
    @brief This function maintains a statemachine of the protocol
           required for a reliable data exchange. It describes a
           series of steps leading to a successful connection
           between any apps
*/
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_statemachine(
                             COMM_MGR_PROTO_STATES state) {
    switch(state) {
        case COMM_MGR_PROTO_DISCOVERY_START:

            break;
        case COMM_MGR_PROTO_DISCOVERY_DONE:

            break;
        case COMM_MGR_PROTO_LEARNING_START:

            break;
        case COMM_MGR_PROTO_LEARNING_DONE:

            break;
        case COMM_MGR_PROTO_DATATRANSFER_READY:

            break;
        default:
            COMM_MGR_SRV_ERROR("Invalid protocol state");
            return COMM_MGR_SRV_PROTO_INVALID_STATE;
    }
    return COMM_MGR_SRV_SUCCESS;
}


static 
COMM_MGR_SRV_PROTO_TBL* comm_mgr_srv_protocol_create_uid_tbl(int size) {
    int total_size = size * sizeof(COMM_MGR_SRV_PROTO_TBL);
    COMM_MGR_SRV_PROTO_TBL *uid_tbl = 
                        (COMM_MGR_SRV_PROTO_TBL*)malloc(total_size);

    memset(uid_tbl, 0, total_size);

    return uid_tbl;
}


