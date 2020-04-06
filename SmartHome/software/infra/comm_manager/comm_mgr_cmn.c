/******************************************************************************
    Description : This file is common code for both comm mgr server and library

******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
    msg->hdr.src_uid = src_uid;
    msg->hdr.dst_uid = dst_uid;
    msg->hdr.priority = COMM_MGR_MSG_PRIORITY_NORMAL; // This can be overwritten on need basis
    msg->hdr.ack_required = FALSE;
    msg->hdr.msg_backing_time = 0;    

    // Payloads can be NULL in case of protocol packets
    msg->hdr.payloadSize = payloadSize;
    if (payloadSize > 0) {
        msg->payload = (char *)malloc(payloadSize);
        memcpy(msg->payload, payload, payloadSize);
    } else {
        msg->payload = NULL;
    }

    return msg;
}

/*
    This function just creates COMM_MGR_MSG with only header part of
    it filled.

    This function doesnt allocate any memory. Hence it is very useful
    in cases like sending a comm msg in format of byte stream to avoid
    lot of malloc leading to fragmentation
*/
COMM_MGR_MSG comm_mgr_create_msg_hdr(uint16_t src_uid, uint16_t dst_uid, 
                                    COMM_MGR_MSG_TYPE msg_type,
                                    uint16_t payloadSize) {
    COMM_MGR_MSG msg;
    memset(&msg, 0, sizeof(msg));

    if (msg_type >= COMM_MGR_MSG_MAX) {
        return msg;
    }
    
    msg.hdr.magic = COMM_MGR_MSG_HDR_MAGIC;
    msg.hdr.major_ver = COMM_MGR_MSG_HDR_MAJOR_VER;
    msg.hdr.minor_ver = COMM_MGR_MSG_HDR_MINOR_VER;
    msg.hdr.msg_type = msg_type;
    msg.hdr.src_uid = src_uid;
    msg.hdr.dst_uid = dst_uid;
    msg.hdr.priority = COMM_MGR_MSG_PRIORITY_NORMAL; // This can be overwritten on need basis
    msg.hdr.ack_required = FALSE;
    msg.hdr.msg_backing_time = 0;    
    msg.hdr.payloadSize = payloadSize;
    msg.payload = NULL;

    return msg;
}


void comm_mgr_destroy_msg(COMM_MGR_MSG *msg) {
    if (msg == NULL) {
        return;
    }

    if (msg->hdr.payloadSize > 0) {
        free(msg->payload);
    }

    free(msg);
}

/*
    This function is used to get the COMM_MSG from the byte stream receive from
    the clients/Master instances.

    This function mallocs the memory for the COMM_MGR_MSG. Take care to free it
    when required

*/
COMM_MGR_MSG* comm_mgr_get_msg(char *msg, uint16_t len) {
    if ((msg == NULL) || (len == 0)) {
        return NULL;
    }

    COMM_MGR_MSG *comm_mgr_msg = (COMM_MGR_MSG*)malloc(sizeof(COMM_MGR_MSG));
    if (comm_mgr_msg == NULL) {
        return NULL;
    }

    memcpy((char *)comm_mgr_msg, msg, sizeof(COMM_MGR_MSG_HDR)); // Copy the header part

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
    if (len > (sizeof(COMM_MGR_MSG_HDR) + 
            sizeof(char) * comm_mgr_msg->hdr.payloadSize)) {
        return NULL;
    }

    // Copy the payload. Payload is sent in byte stream format.
    // Payloads can be NULL in case of protocol packets
    if (comm_mgr_msg->hdr.payloadSize > 0) {
        comm_mgr_msg->payload = (char *)malloc(comm_mgr_msg->hdr.payloadSize);
        memcpy(comm_mgr_msg->payload, msg + sizeof(COMM_MGR_MSG_HDR), comm_mgr_msg->hdr.payloadSize);
    } else {
        comm_mgr_msg->payload = NULL;
    }

    return comm_mgr_msg;
}

/*
    This function extracts the next COMM_MGR_MSG from msg
    if available, else return NULL.
    
    Typically, this function should be called in a loop,
    till it returns NULL

    This function doesnt do any memory allocation
*/
COMM_MGR_MSG* comm_mgr_get_next_msg(char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    COMM_MGR_MSG *comm_mgr_msg = (COMM_MGR_MSG*)msg;

    // Validate the first msg header
    if ((comm_mgr_msg->hdr.magic != COMM_MGR_MSG_HDR_MAGIC) ||
        (comm_mgr_msg->hdr.msg_type >= COMM_MGR_MSG_MAX)) {
        return NULL;
    }

    // Point to the next comm msg
    comm_mgr_msg = (COMM_MGR_MSG *)(msg + (sizeof(COMM_MGR_MSG_HDR) + comm_mgr_msg->hdr.payloadSize));

    // Validate the pointer
    if ((comm_mgr_msg->hdr.magic != COMM_MGR_MSG_HDR_MAGIC) ||
        (comm_mgr_msg->hdr.msg_type >= COMM_MGR_MSG_MAX)) {
        return NULL;
    }

    return comm_mgr_msg;    
}

/*
    @brief This function will dislay the COMM_MSG_HDR in a human reable format
            in the buf passed by the application. 

    @param, len Length of buf passed

    Note :  This function doesnt validate to check if the sanity of header is fine.
        It blindly prints all the header information
*/
void comm_mgr_print_msg_hdr(COMM_MGR_MSG *msg, char *buf, uint16_t len) {
    if ((buf == NULL) || (len == 0) || (msg == NULL)) {
        return;
    }
    memset(buf, 0, len);

    snprintf(buf, len, "\nCommunication Manager Msg Header Info : \n");
    snprintf(buf + strlen(buf), len, "\t Magic                    : 0x%0x\n", msg->hdr.magic);
    snprintf(buf + strlen(buf), len, "\t Major ver                : 0x%0x\n", msg->hdr.major_ver);
    snprintf(buf + strlen(buf), len, "\t Minor ver                : 0x%0x\n", msg->hdr.minor_ver);
    snprintf(buf + strlen(buf), len, "\t Msg type                 : 0x%0x\n", msg->hdr.msg_type);
    snprintf(buf + strlen(buf), len, "\t SubMsg type              : 0x%0x\n", msg->hdr.submsg_type);
    snprintf(buf + strlen(buf), len, "\t Src UID                  : 0x%0x\n", msg->hdr.src_uid);
    snprintf(buf + strlen(buf), len, "\t Dst UID                  : 0x%0x\n", msg->hdr.dst_uid);
    snprintf(buf + strlen(buf), len, "\t Priority                 : 0x%0x\n", msg->hdr.priority);
    snprintf(buf + strlen(buf), len, "\t ACK Required             : 0x%0x\n", msg->hdr.ack_required);
    snprintf(buf + strlen(buf), len, "\t Msg backing time(mins)   : 0x%0x\n", msg->hdr.msg_backing_time);
    snprintf(buf + strlen(buf), len, "\t Payload Size             : 0x%0x\n", msg->hdr.ack_required);
    
}







