/******************************************************************************
    Description : This file is common code for both comm mgr server and library

******************************************************************************/
#include <stdlib.h>
#include "comm_mgr_cmn.h"

/*
    This function creates a COMM_MGR_MSG with minimum must params. The rest
    can be set the by the Master instance / Client apps optionally
*/
COMM_MGR_MSG* comm_mgr_create_msg(uint16_t src_uid, uint16_t dst_uid, 
                                 COMM_MGR_MSG_TYPE msg_type, char *payload,
                                 uint16_t payloadSize) {
    COMM_MGR_MSG *msg = (COMM_MGR_MSG *)malloc(sizeof(COMM_MGR_MSG));
    if (msg == NULL) {
        return NULL;
    }
    if (msg_type >= COMM_MGR_MSG_MAX) {
        return NULL;
    }
    
    msg->hdr.magic = COMM_MGR_MSG_HDR_MAGIC;
    msg->hdr.major_ver = COMM_MGR_MSG_HDR_MAJOR_VER;
    msg->hdr.minor_ver = COMM_MGR_MSG_HDR_MINOR_VER;
    msg->hdr.msg_type = msg_type;
    msg->hdr.priority = COMM_MGR_MSG_PRIORITY_NORMAL; // This can be overwritten on need basis
    msg->hdr.ack_required = FALSE;
    msg->hdr.msg_backing_time = 0;    

    // Payloads can be NULL in case of protocol packets
    msg->hdr.payloadSize = payloadSize;
    if (payloadSize > 0) { 
        msg->payload = payload;
    } else {
        msg->payload = NULL;
    }

    return msg;
}

/*
    This function is used to get the COMM_MSG from the byte stream receive from
    the clients/Master instances. 

*/
COMM_MGR_MSG* comm_mgr_get_msg(char *msg, uint16_t len) {
    if ((msg == NULL) || (len == 0)) {
        return NULL;
    }

    COMM_MGR_MSG *comm_mgr_msg = (COMM_MGR_MSG *)msg;

    // Verify the data received. No need to verify the version
    // numbers since they can be different in case of inter-system
    // communication. 
    // Depending on the version number received, some of these checks
    // might need to be loosened later
    if ((comm_mgr_msg->hdr.magic != COMM_MGR_MSG_HDR_MAGIC) ||
        (comm_mgr_msg->hdr.msg_type >= COMM_MGR_MSG_MAX)) {
        return NULL;
    }

    // Even the number of bytes received also need to match with comm msg size
    if (len >= (sizeof(COMM_MGR_MSG_HDR) + 
            sizeof(char) * comm_mgr_msg->hdr.payloadSize)) {
        return NULL;
    }

    return comm_mgr_msg;
}
