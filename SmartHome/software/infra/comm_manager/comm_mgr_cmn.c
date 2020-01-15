/******************************************************************************
    Description : This file is common code for both comm mgr server and library

******************************************************************************/
#include "comm_mgr_cmn.h"

COMM_MGR_MSG* comm_mgr_create_msg(uint16_t src_uid, uint16_t dst_uid, 
                                 COMM_MGR_MSG_TYPE msg_type, char *payload,
                                 uint16_t payloadSize) {
    COMM_MGR_MSG *msg = (COMM_MGR_MSG *)malloc(sizeof(COMM_MGR_MSG));
    if (msg == NULL) {
        return NULL;
    }
    msg->hdr.magic = COMM_MGR_MSG_HDR_MAGIC;
    msg->hdr.major_ver = COMM_MGR_MSG_HDR_MAJOR_VER;
    msg->hdr.minor_ver = COMM_MGR_MSG_HDR_MINOR_VER;
    msg->hdr.msg_type = msg_type;

    msg->hdr.payloadSize = payloadSize;
    if (payloadSize > 0) {    
        msg->payload = payload;
    } else {
        msg->payload = NULL;
    }

    return msg;
}
