/******************************************************************************
    Description : This file is common code for both comm mgr server and library

******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "comm_mgr_cmn.h"

boolean comm_mgr_auxillary_send_en = COMM_MGR_USE_ANCILLARY_SEND;

static pthread_key_t datastream_key;
static pthread_once_t datastream_init_done = PTHREAD_ONCE_INIT;

uint8_t __comm_mgr_anc_vec_sizes[COMM_MGR_MAX_ANCILLARY_USER_IOV];
uint8_t __comm_mgr_psuedo_iov[COMM_MGR_MAX_ANCILLARY_RECV_BUFFER];

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
    This function creates a COMM_MGR_ANC_MSG with minimum must params. The rest
    can be set the by the Master instance / Client apps optionally

    We will override the payload pointer with the address of Ancillary Message

*/
COMM_MGR_MSG* comm_mgr_create_anc_msg(uint16_t src_uid, uint16_t dst_uid, COMM_MGR_ANC_MSG_TYPE anc_msg_type,
                                      uint8_t num_vector, char **data, uint8_t *datalen,
                                      uint8_t num_fds, int *fds) {

    COMM_MGR_MSG_TYPE msg_type = COMM_MGR_MSG_ANCILLARY;

    if(num_vector > 0) {
        // Sanitize the whole vector
        for (uint8_t i = 0; i < num_vector; i++) {
            if(datalen[i] == 0) {
                return NULL;
            }
            if(data[i] == NULL) {
                return NULL;
            }
        }    
    }

    // Create a Communication Manager header with no payload
    COMM_MGR_MSG *comm_msg = comm_mgr_create_msg(src_uid, dst_uid, msg_type, NULL, 0);
    if(comm_msg == NULL) {
        return NULL;
    }


    COMM_MGR_ANC_MSG *anc_msg = (COMM_MGR_ANC_MSG *)malloc(sizeof(COMM_MGR_ANC_MSG));
    if (anc_msg == NULL) {
        free(comm_msg);
        return NULL;
    }

    // Override the payload field of Comm Msg with the Ancillary Message
    comm_msg->payload = (char *)anc_msg;

    memset(anc_msg, 0, sizeof(COMM_MGR_ANC_MSG));
    anc_msg->hdr.magic = COMM_MGR_MSG_ANC_HDR_MAGIC;
    anc_msg->hdr.major_ver = COMM_MGR_MSG_ANC_HDR_MAJOR_VER;
    anc_msg->hdr.minor_ver = COMM_MGR_MSG_ANC_HDR_MINOR_VER;
    anc_msg->hdr.anc_msg_type = anc_msg_type;
    anc_msg->hdr.num_fd = num_fds;
    anc_msg->hdr.num_vec = num_vector;

    if(num_fds > 0) {
        anc_msg->fds = (uint32_t *)malloc(sizeof(uint32_t) * num_fds);
        memcpy(anc_msg->fds, fds, sizeof(uint32_t) * num_fds);
    }

    if(num_vector > 0) {
        anc_msg->nPayloadSize = (uint8_t *)malloc(sizeof(uint8_t) * num_vector);
        memcpy(anc_msg->nPayloadSize, datalen, sizeof(uint8_t) * num_vector);
        anc_msg->payloads = (char **)malloc(sizeof(char *) * num_vector);

        for(uint8_t i = 0; i < num_vector; i++) {
            anc_msg->payloads[i] = (char *)malloc(sizeof(char) * anc_msg->nPayloadSize[i]);
            memcpy(anc_msg->payloads[i], data[i], sizeof(char) * anc_msg->nPayloadSize[i]);
        }
    }

    return comm_msg;
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

    if(msg->hdr.msg_type == COMM_MGR_MSG_ANCILLARY) {
        comm_mgr_destroy_anc_msg(msg);
    }

    // Freeing the payload should be done at end, because payload may be
    // overloaded with other message formats in case of Ancillary or other
    // Overlay formats (SCOM)
    if (msg->hdr.payloadSize > 0) {
        free(msg->payload);
    }

    free(msg);
}

void comm_mgr_destroy_anc_msg(COMM_MGR_MSG *msg) {
    if(msg == NULL) {
        return;
    }

    COMM_MGR_ANC_MSG *anc_msg = COMM_MGR_GET_ANC_MSG(msg); 

    if(anc_msg == NULL) {
        return;
    }

    if(anc_msg->fds) {
        free(anc_msg->fds);
    }

    if(anc_msg->nPayloadSize) {
        free(anc_msg->nPayloadSize);
    }                

    for(uint8_t i = 0; i < anc_msg->hdr.num_vec; i++) {
        if(anc_msg->payloads[i]) {
            free(anc_msg->payloads[i]);
        }            
    }

    free(anc_msg->payloads);
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
        free(comm_mgr_msg);
        return NULL;
    }

    // Even the number of bytes received also need to match with comm msg size
    if (len > (sizeof(COMM_MGR_MSG_HDR) + 
            sizeof(char) * comm_mgr_msg->hdr.payloadSize)) {
        free(comm_mgr_msg);             
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

    // Allocate more pointers in case if ancillary message type
    if(comm_mgr_msg->hdr.msg_type == COMM_MGR_MSG_ANCILLARY) {
        COMM_MGR_ANC_MSG *anc_msg = (COMM_MGR_ANC_MSG *)malloc(sizeof(COMM_MGR_ANC_MSG));
        if (anc_msg == NULL) {
            free(comm_mgr_msg);
            return NULL;
        }

        // Override the payload field of Comm Msg with the Ancillary Message
        comm_mgr_msg->payload = (char *)anc_msg;
        memset(anc_msg, 0, sizeof(COMM_MGR_ANC_MSG));
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
    This function tells if a given comm_mgr msg is valid or not
*/
boolean comm_mgr_is_valid_msg(COMM_MGR_MSG *msg) {
    if(msg == NULL) {
        return FALSE;
    }

    // Validate the Common header first
    if ((msg->hdr.magic != COMM_MGR_MSG_HDR_MAGIC) ||
        (msg->hdr.msg_type >= COMM_MGR_MSG_MAX)) {
        return FALSE;
    }

    // If it is a Ancillary message type, validate all its internal header
    if(msg->hdr.msg_type == COMM_MGR_MSG_ANCILLARY) {
        COMM_MGR_ANC_MSG *anc_msg = COMM_MGR_GET_ANC_MSG(msg);
        if (anc_msg == NULL) { 
            return FALSE;
        }
        if((anc_msg->hdr.magic != COMM_MGR_MSG_ANC_HDR_MAGIC) ||
          (anc_msg->hdr.anc_msg_type >= COMM_MGR_MSG_ANC_MSG_MAX) ||
          (anc_msg->hdr.num_fd > COMM_MGR_MAX_ANCILLARY_FD) ||
          (anc_msg->hdr.num_vec > COMM_MGR_MAX_ANCILLARY_USER_IOV)){
            return FALSE;
        }
        if((anc_msg->hdr.num_fd > 0) && (anc_msg->fds == NULL)) {
            return FALSE;
        }
        if(((anc_msg->hdr.num_vec > 0) && (anc_msg->nPayloadSize == NULL)) ||
            ((anc_msg->hdr.num_vec > 0) && (anc_msg->payloads == NULL))) {
            return FALSE;
        }
    }
    return TRUE;
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

    Each vector is limited to 256 bytes in size. Depending on the flags set only those data is
    passed back to the application

*/
COMM_MGR_CMN_ERR comm_mgr_send(int sock, COMM_MGR_FLAG flag, COMM_MGR_MSG *comm_msg) { 
    int send_count = 0;
    uint8_t num_sendfds = 0;
    uint8_t num_vector = 0;
    uint32_t len = 0;
    char *datastream = NULL;

    if(comm_msg == NULL){
        return COMM_MGR_CMN_INVALID_ARG;
    }

    // To make this function mutli-thread and re-entrant
    pthread_once(&datastream_init_done, comm_mgr_datastream_thread_init);
    datastream = (char *)pthread_getspecific(datastream_key);
    if(datastream == NULL) {
        datastream = malloc(sizeof(char) * COMM_MGR_PACKET_MAX_SIZE);
        if(datastream == NULL) {
            return COMM_MGR_CMN_NO_MEMORY;
        }
        pthread_setspecific(datastream_key, datastream);
    }

    /* 
        Check if Default mode is set

        Depending on the msg_type, normal or ancillary send will be used
    */
    if (flag == COMM_MGR_FLAG_MODE_DEFAULT) {
        if((comm_msg->hdr.msg_type == COMM_MGR_MSG_ANCILLARY) &&
            (comm_msg->hdr.payloadSize == 0)) { // Ancillary message
            COMM_MGR_ANC_MSG *anc_msg = COMM_MGR_GET_ANC_MSG(comm_msg); 
            if(anc_msg == NULL) {
                return COMM_MGR_CMN_INVALID_ARG;
            }
            return  __comm_mgr_send_with_ancillary_msg(sock, &comm_msg->hdr, anc_msg);
        } else {
            if(comm_msg->hdr.payloadSize > 0) { // Communication Manager message
    	        len = sizeof(COMM_MGR_MSG_HDR) + (comm_msg->hdr.payloadSize);
    	        memset(datastream, 0, sizeof(datastream));
    	        memcpy(datastream, comm_msg, sizeof(COMM_MGR_MSG_HDR));
    	        memcpy(datastream + sizeof(COMM_MGR_MSG_HDR), comm_msg->payload, (comm_msg->hdr.payloadSize));

                send_count = send(sock, datastream, len, 0);
                if(send_count < 0) {
                    return COMM_MGR_CMN_FAILURE;
                } else if(send_count == 0) {
                    return COMM_MGR_CMN_PEER_DOWN;
                }
                return COMM_MGR_CMN_SUCCESS;
            }
            return COMM_MGR_CMN_INVALID_ARG;
        }
    }

    // Check if Normal flag is set.
    if(flag & COMM_MGR_FLAG_MODE_NORMAL) {
    	len = sizeof(COMM_MGR_MSG_HDR) + (comm_msg->hdr.payloadSize);
    	memset(datastream, 0, sizeof(datastream));
    	memcpy(datastream, comm_msg, sizeof(COMM_MGR_MSG_HDR));
    	memcpy(datastream + sizeof(COMM_MGR_MSG_HDR), comm_msg->payload, (comm_msg->hdr.payloadSize));

        send_count = send(sock, datastream, len, 0);
        if(send_count < 0) {
            return COMM_MGR_CMN_FAILURE;
        } else if(send_count == 0) {
            return COMM_MGR_CMN_PEER_DOWN;
        }
        return COMM_MGR_CMN_SUCCESS;
    }

    // If not Default/Normal mode then it must be custom Ancillary mode.
    // Many flags can override the Ancillary Data
    COMM_MGR_ANC_MSG *anc_msg = COMM_MGR_GET_ANC_MSG(comm_msg); 
    if(anc_msg == NULL) {
        return COMM_MGR_CMN_INVALID_ARG;
    }
 
    if (!(flag & COMM_MGR_FLAG_MODE_FD)) {
        anc_msg->hdr.num_fd = 0;
    }

    if (!(flag & COMM_MGR_FLAG_MODE_VECTOR)) {
        anc_msg->hdr.num_vec = 0;
    }

    return __comm_mgr_send_with_ancillary_msg(sock, &comm_msg->hdr, anc_msg);
}


/*
    The comm_mgr_recv() function is enhanced to get the data and determine what kind of data and
    appriopriately construct a COMM_MGR_MSG. With this no need to call comm_mgr_get_msg() to allocate
    memory. This function can receive multiple comm_msgs

    Depending on the flag passed, function behaves differently.
*/
COMM_MGR_CMN_ERR comm_mgr_recv(int sock, COMM_MGR_FLAG flag, COMM_MGR_MSG **msg[], uint8_t *num_msgs) {
    COMM_MGR_CMN_ERR rc = COMM_MGR_CMN_SUCCESS;
    COMM_MGR_MSG *comm_mgr_msg = NULL;
    COMM_MGR_ANC_MSG *anc_msg = NULL;
    int recv_count = 0;
    COMM_MGR_MSG **ret_msgs;
    uint8_t ret_msgs_cnt = 0;

    // Check if Normal flag is set. 
    if(flag & COMM_MGR_FLAG_MODE_NORMAL) {
        char buffer[COMM_MGR_MAX_NORMAL_MODE_RECV_BUFFER];
        recv_count = recv(sock, buffer, sizeof(buffer), 0);

        *msg = NULL;
        if(recv_count > 0) {
            comm_mgr_msg = (COMM_MGR_MSG*)buffer;
            if (comm_mgr_msg == NULL) {
                return COMM_MGR_CMN_BAD_COMM_MSG;
            }            

            // Multi message case
            if (recv_count > (sizeof(COMM_MGR_MSG_HDR) + 
                    sizeof(char) * comm_mgr_msg->hdr.payloadSize)) {
                // First count the number of comm msgs in the received buffer 
                while(comm_mgr_msg) {                
                    comm_mgr_msg = comm_mgr_get_next_msg((char *)comm_mgr_msg);
                    ret_msgs_cnt++;
                }
                ret_msgs = (COMM_MGR_MSG **)malloc(sizeof(COMM_MGR_MSG *) * ret_msgs_cnt);

                // Now allocate memory for ret_msgs_cnt msgs
                comm_mgr_msg = (COMM_MGR_MSG*)buffer;
                for (uint8_t i = 0 ; i < ret_msgs_cnt; i++) {
                    ret_msgs[i] = comm_mgr_get_msg((char *)comm_mgr_msg, COMM_MGR_MSG_SIZE(comm_mgr_msg));
                    comm_mgr_msg = comm_mgr_get_next_msg((char *)comm_mgr_msg);
                }
                *msg = ret_msgs;
                *num_msgs = ret_msgs_cnt;
            } else {            
                ret_msgs = (COMM_MGR_MSG **)malloc(sizeof(COMM_MGR_MSG *));
        
                comm_mgr_msg = comm_mgr_get_msg(buffer, recv_count);
                if (comm_mgr_msg == NULL) {
                    return COMM_MGR_CMN_BAD_COMM_MSG;
                }

                ret_msgs[0] = comm_mgr_msg;
                *msg = ret_msgs;
                *num_msgs = 1;
            }           
            return COMM_MGR_CMN_SUCCESS;
        } else if (recv_count == 0) {
            return COMM_MGR_CMN_PEER_DOWN;
        } else {
            return COMM_MGR_CMN_FAILURE;
        }
    }

    //If not Normal mode then it must be Ancillary mode 
    // First receive the entire ancillary message
    char vec[COMM_MGR_MAX_ANCILLARY_USER_IOV][COMM_MGR_MAX_ANCILLARY_IOV_SIZE];
    uint8_t vec_size[COMM_MGR_MAX_ANCILLARY_USER_IOV];
    char *vec_ptrs[COMM_MGR_MAX_ANCILLARY_USER_IOV];
    uint8_t vec_num = 0;
    uint32_t fd_arr[COMM_MGR_MAX_ANCILLARY_FD];
    uint8_t fd_num = 0;

    COMM_MGR_MSG_HDR comm_hdr;
    memset(&comm_hdr, 0, sizeof(comm_hdr));
    COMM_MGR_ANC_MSG t_anc_msg;
    memset(&t_anc_msg, 0, sizeof(t_anc_msg));
    
    t_anc_msg.fds = fd_arr;
    t_anc_msg.nPayloadSize = vec_size;
    t_anc_msg.payloads = vec_ptrs;

    // Assign each row of the local 2-D array to temp anc payload
    for (uint8_t i = 0; i < COMM_MGR_MAX_ANCILLARY_USER_IOV; i++) {
        vec_ptrs[i] = (char *)&vec[i][0]; 
    }

    rc = __comm_mgr_recv_with_ancillary_msg(sock, &comm_hdr, &t_anc_msg);
    
    if(rc != COMM_MGR_CMN_SUCCESS) {
        // For peer down, the server needs to know about it
        if(rc == COMM_MGR_CMN_PEER_DOWN) {
            return COMM_MGR_CMN_PEER_DOWN;
        }
        // All other error types can be combined as CMN_FAILURE
        return COMM_MGR_CMN_FAILURE;
    }

    // We will also malloc memory and pass it back to the caller to consume
    comm_mgr_msg = comm_mgr_get_msg((char *)&comm_hdr, sizeof(COMM_MGR_MSG_HDR));
    if(comm_mgr_msg == NULL) {
        return COMM_MGR_CMN_FAILURE;
    }
    anc_msg = COMM_MGR_GET_ANC_MSG(comm_mgr_msg);
    memcpy(&anc_msg->hdr, &t_anc_msg, sizeof(COMM_MGR_ANC_MSG_HDR));

    // Depending on the flag set FD/VECTOR will be filled/ignored even though received
    if(flag & COMM_MGR_FLAG_MODE_FD) {
        anc_msg->fds = malloc(sizeof(uint32_t) * t_anc_msg.hdr.num_fd);
        memcpy(anc_msg->fds, t_anc_msg.fds, sizeof(uint32_t) * t_anc_msg.hdr.num_fd);
        anc_msg->hdr.num_fd = t_anc_msg.hdr.num_fd;
    }

    if(flag & COMM_MGR_FLAG_MODE_VECTOR) {
        anc_msg->hdr.num_vec = t_anc_msg.hdr.num_vec;
        anc_msg->nPayloadSize = malloc(sizeof(uint8_t) * t_anc_msg.hdr.num_vec);
        memcpy(anc_msg->nPayloadSize, t_anc_msg.nPayloadSize, sizeof(uint8_t) * t_anc_msg.hdr.num_vec);
        anc_msg->payloads = (char **)malloc(sizeof(char *) * t_anc_msg.hdr.num_vec);
        for(uint8_t i = 0 ; i < anc_msg->hdr.num_vec; i++) {
            anc_msg->payloads[i] = malloc(sizeof(char) * anc_msg->nPayloadSize[i]);
            memcpy(anc_msg->payloads[i], t_anc_msg.payloads[i], sizeof(char) * anc_msg->nPayloadSize[i]);
        }            
    }

    // Finally validate the received and sculpted message before passing it back to the application
    if(comm_mgr_is_valid_msg(comm_mgr_msg) == FALSE) {
        comm_mgr_destroy_msg(comm_mgr_msg);
        return COMM_MGR_CMN_FAILURE;
    }

    ret_msgs = (COMM_MGR_MSG **)malloc(sizeof(COMM_MGR_MSG *));
    ret_msgs[0] = comm_mgr_msg;
    *msg = ret_msgs;
    *num_msgs = 1;
    return COMM_MGR_CMN_SUCCESS; 
}


/*
    This is a new function added to the  communication manager. This function is
    capable of sending ancillary control data along with the regular user data as well.

    This function can also send multiple buffers 

    It can be used to send array of file descriptors, credentials etc

    Format of the messages:

    Comm_Mgr Hdr | IOV[0] Anc_Hdr | IOV[1] Vector Sizes | ...... (Vectors)
                                  | Control Packets (FDs)      ----> FDs go via the control packets

    Refer : https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/apis/sendms.htm

    Note: A software limit is put on this function for how many scatter/gather array (iov) can be used. And also
    a limit is put for number of file descriptors that can be sent

    <TODO> Upgrade this function with sendmmsg()/recvmmsg() to support > 1 NIOVs 
    (Refer https://linux.die.net/man/2/sendmmsg AND https://linux.die.net/man/2/recvmmsg)

    Note : Return value of -2 is used to indicate some error about the arguments passed
        Usually on failure while sending the return value will be -1 and errono is set
*/
static COMM_MGR_CMN_ERR __comm_mgr_send_with_ancillary_msg(int fd,
                                                           COMM_MGR_MSG_HDR *comm_hdr, 
                                                           COMM_MGR_ANC_MSG *anc_msg) {
    struct msghdr   msg;
    struct iovec    iov[COMM_MGR_MAX_ANCILLARY_USER_IOV+COMM_MGR_MAX_ANCILLARY_INTERNAL_IOV+1];
    struct cmsghdr  *cmptr;
    ssize_t sent_bytes = 0;
    memset(&msg, 0, sizeof(msg));

    if((comm_mgr_auxillary_send_en == FALSE) ||
        (anc_msg == NULL) || (comm_hdr == NULL) ||
        (fd < 0) || ((anc_msg->hdr.num_fd > 0) && (anc_msg->fds == NULL)) ||
        (anc_msg->hdr.num_fd > COMM_MGR_MAX_ANCILLARY_FD) ||
        ((anc_msg->hdr.num_vec > 0) && (anc_msg->nPayloadSize == NULL))){
        return COMM_MGR_CMN_INVALID_ARG;
    }

    if (anc_msg->hdr.num_fd > 0) {
        char control[CMSG_SPACE(sizeof(int) * COMM_MGR_MAX_ANCILLARY_FD)];
        uint8_t fdsize = sizeof(int) * anc_msg->hdr.num_fd;

        msg.msg_control = control;
        msg.msg_controllen = sizeof(control);

        cmptr = CMSG_FIRSTHDR(&msg);
        cmptr->cmsg_level = SOL_SOCKET;
        cmptr->cmsg_type = SCM_RIGHTS;
        cmptr->cmsg_len = CMSG_LEN(fdsize);
        memcpy(CMSG_DATA(cmptr), anc_msg->fds, fdsize);
    } else {
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
    }   

    // Support only connected sockets
    msg.msg_name = NULL;
    msg.msg_namelen = 0;  

    // Communication Manager Header
    iov[0].iov_base = (char *)comm_hdr;
    iov[0].iov_len = sizeof(COMM_MGR_MSG_HDR);

    // Ancillary Header
    iov[1].iov_base = (char *)(&anc_msg->hdr);
    iov[1].iov_len = sizeof(COMM_MGR_ANC_MSG_HDR);

    // For simplicity, always pack the anc_vec_sizes even if anc_msg->hdr.num_vec = 0
    iov[2].iov_base = __comm_mgr_anc_vec_sizes;
    iov[2].iov_len = sizeof(__comm_mgr_anc_vec_sizes);

    msg.msg_iov = iov;
    msg.msg_iovlen = COMM_MGR_MAX_ANCILLARY_INTERNAL_IOV;

    for (uint8_t i = 0; i < anc_msg->hdr.num_vec; i++) {
        __comm_mgr_anc_vec_sizes[i] = anc_msg->nPayloadSize[i];
        iov[i+COMM_MGR_MAX_ANCILLARY_INTERNAL_IOV].iov_base = anc_msg->payloads[i];
        iov[i+COMM_MGR_MAX_ANCILLARY_INTERNAL_IOV].iov_len = anc_msg->nPayloadSize[i];
    }       

    msg.msg_iov = iov; 
    msg.msg_iovlen = anc_msg->hdr.num_vec + COMM_MGR_MAX_ANCILLARY_INTERNAL_IOV;

    printf("niov = %d\n", anc_msg->hdr.num_vec);
    __comm_mgr_print_AncillaryMsg_Header(&msg, cmptr);

    sent_bytes = sendmsg(fd, &msg, 0); 
    if(sent_bytes < 0) { 
        printf("Failed to send data\n");
        return COMM_MGR_CMN_FAILURE; 
    }   
    return COMM_MGR_CMN_SUCCESS;
}

static COMM_MGR_CMN_ERR __comm_mgr_recv_with_ancillary_msg(int fd,
                                                           COMM_MGR_MSG_HDR *comm_hdr,
                                                           COMM_MGR_ANC_MSG *anc_msg) {
    struct msghdr   msg;
    struct iovec    iov[COMM_MGR_MAX_ANCILLARY_USER_IOV+COMM_MGR_MAX_ANCILLARY_INTERNAL_IOV];
    ssize_t         recv_bytes;
    struct cmsghdr  *cmptr;
    char control[CMSG_SPACE(sizeof(int) * COMM_MGR_MAX_ANCILLARY_FD)];
    uint8_t num_recvfds_tmp = 0;
    uint16_t offset = 0;
    uint8_t i = 0;
    memset(__comm_mgr_anc_vec_sizes, 0, sizeof(__comm_mgr_anc_vec_sizes));
    memset(__comm_mgr_psuedo_iov, 0, sizeof(__comm_mgr_psuedo_iov));

    if((comm_hdr == NULL) || (anc_msg == NULL)) {
        return COMM_MGR_CMN_INVALID_ARG;
    }
    
    memset(&msg, 0, sizeof(msg));

    msg.msg_control = control;
    msg.msg_controllen = sizeof(control);

    // Support only connected sockets 
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    // Communication Manager Header
    iov[0].iov_base = (char *)comm_hdr;
    iov[0].iov_len = sizeof(COMM_MGR_MSG_HDR);

    // Ancillary Header 
    iov[1].iov_base = (char *)(&anc_msg->hdr);
    iov[1].iov_len = sizeof(COMM_MGR_ANC_MSG_HDR);

    iov[2].iov_base = (char *)__comm_mgr_anc_vec_sizes;
    iov[2].iov_len = sizeof(__comm_mgr_anc_vec_sizes);

    // There can be multiple user IOVs in this psuedo iov
    iov[3].iov_base = __comm_mgr_psuedo_iov;
    iov[3].iov_len = sizeof(__comm_mgr_psuedo_iov);

    msg.msg_iov = iov;
    msg.msg_iovlen = COMM_MGR_MAX_ANCILLARY_INTERNAL_IOV + 1; // Internal IOVs + 1 pseudo user IOV

    if ((recv_bytes = recvmsg(fd, &msg, 0)) < 0) {
    //if ((recv_bytes = recvmmsg(fd, &msgs, 4, 0, NULL)) < 0) {
        printf("Failed to recv data, recv_bytes = %zd\n", recv_bytes);
        return COMM_MGR_CMN_FAILURE; 
    } else if(recv_bytes == 0) {
        printf("Peer closed the connection\n");
        return COMM_MGR_CMN_PEER_DOWN;
    }

    // Validate the Ancillary Msg Header
    if (anc_msg->hdr.magic != COMM_MGR_MSG_ANC_HDR_MAGIC){
        printf("Received bad Ancillary Message");
        return COMM_MGR_CMN_BAD_ANC_MSG;
    }

    // Now pack the received user IOVs to the anc_msg
    for (uint8_t i = 0; i < anc_msg->hdr.num_vec; i++) {
        printf("anc_vec_sizes[%d] = %d\n", i, __comm_mgr_anc_vec_sizes[i]);
        memcpy(anc_msg->payloads[i], __comm_mgr_psuedo_iov+offset, __comm_mgr_anc_vec_sizes[i]);
        anc_msg->nPayloadSize[i] = __comm_mgr_anc_vec_sizes[i]; 
        offset = __comm_mgr_anc_vec_sizes[i]; 
    }    
 
    // Some control data is available
    if(msg.msg_controllen > 0) {    
        cmptr = CMSG_FIRSTHDR(&msg);
        while((cmptr != NULL)) {
            if(cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
                if ((cmptr->cmsg_level == SOL_SOCKET) && (cmptr->cmsg_type == SCM_RIGHTS)) {
                    anc_msg->fds[num_recvfds_tmp] = *((int *) CMSG_DATA(cmptr));
                    num_recvfds_tmp++;
                }   
            }   

            cmptr = CMSG_NXTHDR(&msg, cmptr);
        }   
        if(num_recvfds_tmp != anc_msg->hdr.num_fd) {
            return COMM_MGR_CMN_BAD_ANC_MSG;
        }
    }   

    return COMM_MGR_CMN_SUCCESS;
}

static void comm_mgr_datastream_thread_init(void) {
    pthread_key_create(&datastream_key, free);
}

static void __comm_mgr_print_AncillaryMsg_Header(struct msghdr  *msg, struct cmsghdr  *cmptr) {
    printf("\n\n----------------------------------------\n\n");
    printf("msg.msg_control = %p\n", msg->msg_control);
    printf("msg.msg_controllen = %ld\n", msg->msg_controllen);
    printf("cmptr->cmsg_level = %ld\n", cmptr->cmsg_level);
    printf("cmptr->cmsg_type = %d\n", cmptr->cmsg_type);
    printf("cmptr->cmsg_len = %d\n", cmptr->cmsg_len);


    printf("msg.msg_iov = %p\n", msg->msg_iov);
    printf("msg.msg_iovlen = %ld\n", msg->msg_iovlen);
   
    for (uint8_t i = 0 ; i < msg->msg_iovlen; i++) {
        printf("iov[%d].iov_base = %p\n", i, msg->msg_iov[i].iov_base);
        printf("iov[%d].iov_len = %ld\n", i, msg->msg_iov[i].iov_len);
    }   
    printf("----------------------------------------\n\n");
}

