/*******************************************************************************
    Description : Comm manager client library
          Note  : Clients modules should spwan a thread for communications 
*******************************************************************************/
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "comm_mgr_lib.h"
#include "comm_mgr_cmn.h"
#include "system_mgr.h"


boolean comm_mgr_lib_initialized = FALSE;

COMM_MGR_LIB_ERR comm_mgr_lib_init(LOG_LEVEL level) {
    log_lib_init(NULL, level);
    comm_mgr_lib_initialized = TRUE;
    return COMM_MGR_LIB_SUCCESS; 
}

COMM_MGR_LIB_ERR comm_mgr_lib_destroy() {
    COMM_MGR_LIB_TRACE("Not yet implemented");
    comm_mgr_lib_initialized = FALSE;
    return COMM_MGR_LIB_SUCCESS; 
}

COMM_MGR_LIB_ERR comm_mgr_lib_create_client(COMM_MGR_LIB_CLIENT *client) {
    struct sockaddr_un un_addr;
    struct sockaddr_in in_addr;
    int fd;

    if(comm_mgr_lib_initialized == FALSE) {
        COMM_MGR_LIB_ERROR("%s not yet initialized", COMM_MGR_LIB_NAME); 
        return COMM_MGR_LIB_NOT_INITIALIZED;
    }

    if (client == NULL) {
        return COMM_MGR_LIB_INVALID_ARG;
    }

    client->__clientReady = 0;

    switch(client->clientAf) {
        case COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM:
            {
                if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
                    COMM_MGR_LIB_ERROR("socket error");
                    return COMM_MGR_LIB_SOCKET_CREATE_ERR;
                }
                memset(&un_addr, 0, sizeof(un_addr));
                un_addr.sun_family = AF_UNIX;
                strcpy(un_addr.sun_path, SOCKET_FILE_PATH); 

                if (connect(fd, (struct sockaddr*)&un_addr, sizeof(un_addr)) == -1) {
                    COMM_MGR_LIB_ERROR("connect error");
                    return COMM_MGR_LIB_CONNECT_ERR;
                } 
            }
            break;
        case COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM:
            {
                struct hostent *server = &(client->server);

                if (server == NULL) {
                    COMM_MGR_LIB_ERROR("Invalid Server\n");
                    return COMM_MGR_LIB_INVALID_ARG;
                }

                if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                    COMM_MGR_LIB_ERROR("socket error");
                    return COMM_MGR_LIB_SOCKET_CREATE_ERR;
                }
                
                if (server->h_name) { // If Only h_name is supplied
                    server = gethostbyname(server->h_name);
                }

                if (server == NULL) {
                    COMM_MGR_LIB_ERROR("No such host\n");
                    return COMM_MGR_LIB_BAD_SERVER;
                }
                                
                COMM_MGR_LIB_DEBUG("Server address : %s : %d\n", 
                                    inet_ntoa(*(struct in_addr*) server->h_addr), client->portNum);


                memset(&in_addr, 0, sizeof(in_addr));
                in_addr.sin_family = AF_INET;
                memcpy((char *)&in_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);	
                in_addr.sin_port = htons(client->portNum);

                if (connect(fd, (struct sockaddr*)&in_addr, sizeof(in_addr)) == -1) {
                    COMM_MGR_LIB_ERROR("connect error");
                    return COMM_MGR_LIB_CONNECT_ERR;
                }
            }    
            break;
        default:
            COMM_MGR_LIB_ERROR("Unknown AF type");
            return COMM_MGR_LIB_UNKNOWN_AF_TYPE;
            break;
    }
  
    client->__src_uid = 1; // <TODO> Either make an API or depend on sysmanager for SELF UID
    client->__fd = fd;
    client->__clientReady = 1;
	
    return COMM_MGR_LIB_SUCCESS;    
}

/*
    @brief This function is used to send protocol/ack/data packets. It can also e called
           directly by the clients, in case they need to fine tune some of the default
           comm msg parameters, though its not recommended

        @param msg It can be NULL also in case of ACK and Protocol packets
*/
COMM_MGR_LIB_ERR comm_mgr_lib_send_msg(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG_HDR *hdr, 
                                      char *msg, int len) {
    struct hostent *server = &(client->server);
    uint32_t comm_msg_size = 0; 
    if (client == NULL) {
        return COMM_MGR_LIB_INVALID_ARG;
    }

    if(!client->__clientReady) {
        COMM_MGR_LIB_ERROR("Client is not yet created\n");
        return COMM_MGR_LIB_CLIENT_NOT_CREATED;
    }
 
    if (client->clientAf == COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM) {
        if (client->server.h_name) { // If Only h_name is supplied
            server = gethostbyname(server->h_name);
        }   
        COMM_MGR_LIB_DEBUG("Server address : %s : %d\n", 
                                        inet_ntoa(*(struct in_addr*) (server->h_addr)), client->portNum);
    } else {
        COMM_MGR_LIB_DEBUG("Sending via Unix Domain Socket\n");
    }

    COMM_MGR_MSG *comm_mgr_msg = comm_mgr_create_msg(client->__src_uid, hdr->dst_uid, hdr->msg_type, msg, len);
    if (comm_mgr_msg == NULL) {
        COMM_MGR_LIB_ERROR("Couldn't create the COMM_MGR_MSG packet. Not sending the msg");
        return COMM_MGR_LIB_SEND_ERR;
    }

    /* Clients can set some more paramaters on default */
    comm_mgr_msg->hdr.submsg_type = hdr->submsg_type; 
    comm_mgr_msg->hdr.priority = hdr->priority;
    comm_mgr_msg->hdr.ack_required = hdr->ack_required;
    comm_mgr_msg->hdr.msg_backing_time = hdr->msg_backing_time;

    comm_msg_size = sizeof(COMM_MGR_MSG_HDR) + (comm_mgr_msg->hdr.payloadSize * sizeof(char));

    COMM_MGR_LIB_DEBUG("Sending msg type [%d], src_uid [%d], dst_uid [%d]\n", 
                    comm_mgr_msg->hdr.msg_type, comm_mgr_msg->hdr.src_uid, comm_mgr_msg->hdr.dst_uid);
    
    // Now send the message to Communication Manager
    if (send(client->__fd, (char *)comm_mgr_msg, comm_msg_size, 0) == -1) {
        free(comm_mgr_msg);
        COMM_MGR_LIB_ERROR("Send error\n");
        return COMM_MGR_LIB_SEND_ERR;        
    }
    
    free(comm_mgr_msg);
    return COMM_MGR_LIB_SUCCESS;
}


/*
    @brief This function is explicitly used to send user data ONLY.
*/
COMM_MGR_LIB_ERR comm_mgr_lib_send_data(COMM_MGR_LIB_CLIENT *client, uint16_t dst_uid, 
                                        char *msg, int len) {
    if((client == NULL) || (msg == NULL) || (len == 0)) {
        COMM_MGR_LIB_ERROR("Input arguments are wrong");
        return COMM_MGR_LIB_INVALID_ARG;
    }

    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;
    COMM_MGR_MSG_HDR hdr;
    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    // Just the dst_uid and msg type is enough
    hdr.msg_type = COMM_MGR_MSG_DATA;
    hdr.dst_uid = dst_uid;

    ret = comm_mgr_lib_send_msg(client, &hdr, msg, len);

    return ret;
}

/*
    @brief This function is explicitly used to send ACK ONLY.
*/
COMM_MGR_LIB_ERR comm_mgr_lib_send_ack(COMM_MGR_LIB_CLIENT *client, uint16_t dst_uid) {
    if(client == NULL) {
        COMM_MGR_LIB_ERROR("Input arguments are wrong");
        return COMM_MGR_LIB_INVALID_ARG;
    }

    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;
    COMM_MGR_MSG_HDR hdr;
    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    // Just the dst_uid and msg type is enough
    hdr.msg_type = COMM_MGR_MSG_ACK;
    hdr.dst_uid = dst_uid;

    ret = comm_mgr_lib_send_msg(client, &hdr, NULL, 0);

    return ret;
}

/*
    @brief This function is explicitly used to send protocol packets ONLY.

    Protocol is always between the initiating client and Communication 
    Manager.
*/
COMM_MGR_LIB_ERR comm_mgr_lib_send_protocol(COMM_MGR_LIB_CLIENT *client, COMM_MGR_SUBMSG_TYPE submsg_type) {
    if(client == NULL) {
        COMM_MGR_LIB_ERROR("Input arguments are wrong");
        return COMM_MGR_LIB_INVALID_ARG;
    }

    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;
    COMM_MGR_MSG_HDR hdr;
    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    // Just the dst_uid and msg type is enough
    hdr.msg_type = COMM_MGR_MSG_PROTOCOL;
    hdr.submsg_type = submsg_type;
    hdr.dst_uid = SYS_MGR_SYSTEM_UID_COMM_MANAGER; // Communication Manager's UID always

    ret = comm_mgr_lib_send_msg(client, &hdr, NULL, 0);

    return ret;
}




COMM_MGR_LIB_ERR comm_mgr_lib_recv_data(COMM_MGR_LIB_CLIENT *client, char *msg, int len) {
    struct hostent *server = &(client->server);

    if ((client == NULL) || (msg == NULL)) {
        return COMM_MGR_LIB_INVALID_ARG;
    }

    if(!client->__clientReady) {
        COMM_MGR_LIB_ERROR("Client is not yet created\n");
        return COMM_MGR_LIB_CLIENT_NOT_CREATED;
    }

    if (recv(client->__fd, msg, len, 0) == -1) {
        COMM_MGR_LIB_ERROR("Receive error\n");
        return COMM_MGR_LIB_RECV_ERR;        
    }

    return COMM_MGR_LIB_SUCCESS;
}

/******************************************************************************
                            Internal Functions
******************************************************************************/




