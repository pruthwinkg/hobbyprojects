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
    snprintf(buf + strlen(buf), len, "\t Payload Size             : 0x%0x\n", msg->hdr.payloadSize);
    
}

/*
    This function is a generic communication manager send/recv pairs which can handle all kinds
    of formats which are recognized by the Communication Manager. The behaviour of these 
    functions are strictly controlled by the COMM_MGR_FLAG. There various combinations of
    behaviour which can be set as desired by the caller

    Also, these pair of functions are designed to be common for both server and library

    The Ancillary family of send/recv uses a complex message packing to keep the packets
    compatbile with the existing system and also for easy interpretation of the messages in the
    rest of the system. All the complexeties are hidden under these two APIs.
*/
int comm_mgr_send(int sock, COMM_MGR_FLAG flag, 
                 uint8_t num_vector, char **data, uint8_t *datalen,
                 uint8_t num_sendfds, int *sendfds) {
    int send_count = 0;

    // Always first check if Normal flag is set.
    if(flag & COMM_MGR_FLAG_MODE_NORMAL) {
        // It is expected to get the data in the 0th index
        if((data == NULL) || (data[0] == NULL) || 
           (datalen == NULL) || (datalen[0] == 0)) {
            return -1;
        }

        send_count = send(sock, data[0], datalen[0], 0);
        return send_count;
    }



}


/*
    The comm_mgr_recv() function is enhanced to get the data and determine what kind of data and
    appriopriately construct a COMM_MGR_MSG. With this no need to call comm_mgr_get_msg() to allocate
    memory.

    Depending on the flag passed, function behaves differently.
*/
int comm_mgr_recv(int sock, COMM_MGR_FLAG flag, COMM_MGR_MSG **msg) {
    int recv_count = 0;
    COMM_MGR_MSG *comm_mgr_msg = NULL;

    // Always first check if Normal flag is set. 
    if(flag & COMM_MGR_FLAG_MODE_NORMAL) {
        char buffer[COMM_MGR_MAX_NORMAL_MODE_RECV_BUFFER];
        recv_count = recv(sock, buffer, sizeof(buffer), 0);
    
        if(recv_count > 0) {
            comm_mgr_msg = comm_mgr_get_msg(buffer, recv_count);
        }

        return recv_count;
    }
}


/*
    This is a new function added to the  communication manager. This function is
    capable of sending ancillary control data along with the regular user data as well.

    This function can also send multiple buffers 

    It can be used to send array of file descriptors, credentials etc

    This function follows a 2-bytes protocol to identify the message its carrying

    Refer : https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/apis/sendms.htm

    Note: A software limit is put on this function for how many scatter/gather array (iov) can be used. And also
    a limit is put for number of file descriptors that can be sent

    <TODO> Upgrade this function with sendmmsg()/recvmmsg() to support > 1 NIOVs 
    (Refer https://linux.die.net/man/2/sendmmsg AND https://linux.die.net/man/2/recvmmsg)

    Note : Return value of -2 is used to indicate some error about the arguments passed
        Usually on failure while sending the return value will be -1 and errono is set
*/
int comm_mgr_send_with_ancillary_msg(int fd, 
                                     void **ptr, uint8_t *nbytes, uint8_t niov,
                                     int *sendfds, uint8_t num_sendfds) {
    struct msghdr   msg;
    struct iovec    iov[COMM_MGR_MAX_ANCILLARY_IOV+1]; // iov[0] is used internally by communication manager
    struct cmsghdr  *cmptr;
    ssize_t sent_bytes = 0;
    memset(&msg, 0, sizeof(msg));
    char comm_internal_protocol[COMM_MGR_ANCILLARY_PROTO_SIZE];

    if((comm_mgr_auxillary_send_en == FALSE) ||
        (fd < 0)i || ((num_sendfds > 0) && (sendfds == NULL)) ||
        (num_sendfds > COMM_MGR_MAX_ANCILLARY_FD) ||
        ((niov > 0) && (nbytes == NULL))){
        return -2;
    }

    // Sanitize the whole niov
    if(niov > 0) {
        for (uint8_t i = 0; i < niov; i++) {
            if(nbytes[i] == 0) {
                return -2;
            }
            if(ptr[i] == NULL) {
                return -2;
            }
        }
    }

    if (num_sendfds > 0) {
        char control[CMSG_SPACE(sizeof(int) * COMM_MGR_MAX_ANCILLARY_FD)];
        uint8_t fdsize = sizeof(int) * num_sendfds;

        msg.msg_control = control;
        msg.msg_controllen = sizeof(control);

        cmptr = CMSG_FIRSTHDR(&msg);
        cmptr->cmsg_level = SOL_SOCKET;
        cmptr->cmsg_type = SCM_RIGHTS;
        cmptr->cmsg_len = CMSG_LEN(fdsize);
        memcpy(CMSG_DATA(cmptr), sendfds, fdsize);
    } else {
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
    }   

    // Support only connected sockets
    msg.msg_name = NULL;
    msg.msg_namelen = 0;  

    iov[0].iov_base = comm_internal_protocol;
    iov[0].iov_len = sizeof(comm_internal_protocol);
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    if(niov > 0) { 
        for (uint8_t i = 0; i < niov; i++) {
            iov[i+1].iov_base = ptr[i];
            iov[i+1].iov_len = nbytes[i];
            printf("nbytes[%d] = %d, ptr[%d] = %p, data = %s\n", i, nbytes[i], i, ptr[i], ptr[i]);
        }   
        msg.msg_iov = iov; 
        msg.msg_iovlen = niov+1;    
    }

    printf("niov = %d\n", niov);

    sent_bytes = sendmsg(fd, &msg, 0); 
    if(sent_bytes < 0) { 
        printf("Failed to send data\n");
        return -1; 
    }   
    return sent_bytes;
}

int comm_mgr_recv_with_ancillary_msg(int fd,
                                     void **ptr, uint8_t *nbytes, uint8_t *niov,
                                     int *recvfds, uint8_t *num_recvfds) {
    struct msghdr   msg;
    struct iovec    iov[COMM_MGR_MAX_ANCILLARY_IOV+1]; // 1 internal IOV
    ssize_t         recv_bytes;
    struct cmsghdr  *cmptr;
    char control[CMSG_SPACE(sizeof(int) * COMM_MGR_MAX_ANCILLARY_FD)];
    uint8_t num_recvfds_tmp = 0;
    char comm_internal_protocol[COMM_MGR_ANCILLARY_PROTO_SIZE]; 
    uint16_t offset = 0;
    uint8_t i = 0;
    uint8_t local_buffer[COMM_MGR_MAX_ANCILLARY_RECV_BUFFER];

    memset(local_buffer, 0, sizeof(local_buffer));
    memset(&msg, 0, sizeof(msg));

    msg.msg_control = control;
    msg.msg_controllen = sizeof(control);

    // Support only connected sockets 
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    iov[0].iov_base = comm_internal_protocol;
    iov[0].iov_len = sizeof(comm_internal_protocol);

    iov[1].iov_base = local_buffer;
    iov[1].iov_len = sizeof(local_buffer);

    msg.msg_iov = iov;
    msg.msg_iovlen = 2;

    if ((recv_bytes = recvmsg(fd, &msg, 0)) < 0) {
    //if ((recv_bytes = recvmmsg(fd, &msgs, 4, 0, NULL)) < 0) {
        printf("Failed to recv data, recv_bytes = %d\n", recv_bytes);
        return -1; 
    } else if(recv_bytes == 0) {
        printf("Peer closed the connection\n");
        return 0;
    }   

    while((i < COMM_MGR_ANCILLARY_PROTO_SIZE) && (comm_internal_protocol[i]  > 0)) {
        printf("protocol = %d\n", comm_internal_protocol[i]);
        memcpy(ptr[i], local_buffer + offset, comm_internal_protocol[i]);
        nbytes[i] = comm_internal_protocol[i];    
        offset = comm_internal_protocol[i];
        i++;    
    }   
    *niov = i;

    printf("Received data = %s\n", local_buffer);
    printf("------------------------------\n");
    
    // Some control data is available
    if(msg.msg_controllen > 0) {    
        cmptr = CMSG_FIRSTHDR(&msg);
        while((cmptr != NULL)) {
            if(cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
                if ((cmptr->cmsg_level == SOL_SOCKET) && (cmptr->cmsg_type == SCM_RIGHTS)) {
                    recvfds[num_recvfds_tmp] = *((int *) CMSG_DATA(cmptr));
                    num_recvfds_tmp++;
                }   
            }   

            cmptr = CMSG_NXTHDR(&msg, cmptr);
        }   
        *num_recvfds = num_recvfds_tmp;
    }   

    return recv_bytes;
}


