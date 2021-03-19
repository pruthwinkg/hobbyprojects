/*******************************************************************************
    Description : Comm manager client library
          Note  : Clients modules should spwan a thread for communications.
          One thread per client. If mutliple lib client are created, then the 
          app needs to spwan one thread for each.
*******************************************************************************/
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#include "comm_mgr_lib.h"
#include "comm_mgr_cmn.h"
#include "system_mgr.h"

static COMM_MGR_LIB_CLIENT __comm_mgr_lib_clients[COMM_MGR_LIB_MAX_CLIENTS];

static uint16_t comm_mgr_lib_static_uid_base = 0;
static uint16_t comm_mgr_lib_static_uid_max = 0;
static uint16_t comm_mgr_lib_dynamic_uid_base = 0;
static uint16_t comm_mgr_lib_dynamic_uid_max = 0;

// Below two maps are used by the library to determine what is current
// learning status of various apps in the system. This acts like a
// local cache for the protocol results (via learning results)
static uint16_t *comm_mgr_lib_static_uid_learning_cache = NULL;
static uint16_t *comm_mgr_lib_dynamic_uid_learning_cache = NULL;

static uint16_t comm_mgr_lib_src_uid = 0;

static boolean comm_mgr_lib_epoll_en = FALSE;
static boolean comm_mgr_lib_auxillary_send_en = COMM_MGR_LIB_USE_ANCILLARY_SEND;


boolean comm_mgr_lib_initialized = FALSE;

static COMM_MGR_LIB_STATUS __comm_mgr_lib_status[COMM_MGR_LIB_MAX_CLIENTS];
COMM_MGR_LIB_APP_PROPERTY __comm_mgr_lib_app_property;

COMM_MGR_LIB_ERR comm_mgr_lib_init(LOG_LEVEL level, uint16_t src_uid, boolean epoll_en) {
    log_lib_init(NULL, level);
    utils_ds_init(); // Initialize utils data structure library

    for (uint16_t i = 0; i < COMM_MGR_LIB_MAX_CLIENTS; i++) {
        __comm_mgr_lib_clients[i].client_ptr = NULL; // This indicates Invalid client
    }
    comm_mgr_lib_src_uid = src_uid;
    comm_mgr_lib_initialized = TRUE;
    comm_mgr_lib_epoll_en = epoll_en;

    for (uint16_t i = 0; i < COMM_MGR_LIB_MAX_CLIENTS; i++) {
        memset(&__comm_mgr_lib_status[i], 0, sizeof(COMM_MGR_LIB_STATUS));
    }

    memset(&__comm_mgr_lib_app_property, 0, sizeof(COMM_MGR_LIB_APP_PROPERTY));

    return COMM_MGR_LIB_SUCCESS; 
}

COMM_MGR_LIB_ERR comm_mgr_lib_destroy() {
    COMM_MGR_LIB_TRACE("Not yet implemented");

    for (uint16_t i = 0; i < COMM_MGR_LIB_MAX_CLIENTS; i++) {
        __comm_mgr_lib_clients[i].client_ptr = NULL; // This indicates Invalid client
        free(&__comm_mgr_lib_clients[i]);
    }

    comm_mgr_lib_initialized = FALSE;
    comm_mgr_lib_epoll_en = FALSE;

    return COMM_MGR_LIB_SUCCESS; 
}

/*
    @brief This function must be called by the clients to start its communication
        system.

    @return COMM_MGR_LIB_CLIENT_ID A unique ID for making communication.

    Note : Multiple IDs also can be created per client depending on apps use case.
        But a MAX of COMM_MGR_LIB_MAX_CLIENTS client IDs are allowed per client.
*/
COMM_MGR_LIB_CLIENT_ID comm_mgr_lib_create_client(COMM_MGR_LIB_CLIENT *client) {
    struct sockaddr_un un_addr;
    struct sockaddr_in in_addr;
    int fd;

    if(comm_mgr_lib_initialized == FALSE) {
        COMM_MGR_LIB_ERROR("%s not yet initialized", COMM_MGR_LIB_NAME); 
        return COMM_MGR_LIB_INVALID_CLIENT;
    }

    if (client == NULL) {
        return COMM_MGR_LIB_INVALID_CLIENT;
    }

    uint16_t id = __comm_mgr_lib_get_free_client();
    if (id == COMM_MGR_LIB_INVALID_CLIENT) {
        COMM_MGR_LIB_ERROR("Reached max limit for client creation");
        return COMM_MGR_LIB_INVALID_CLIENT;
    }

    __comm_mgr_lib_clients[id].clientAf = client->clientAf;
    __comm_mgr_lib_clients[id].ancillary = client->ancillary;
    __comm_mgr_lib_clients[id].server = client->server;
    __comm_mgr_lib_clients[id].portNum = client->portNum;

    __comm_mgr_lib_clients[id].client_ptr = 
                (COMM_MGR_LIB_CLIENT_INTERNAL *)malloc(sizeof(COMM_MGR_LIB_CLIENT_INTERNAL));
    __comm_mgr_lib_clients[id].client_ptr->__clientReady = 0;

    switch(__comm_mgr_lib_clients[id].clientAf) {
        case COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM:
            {                
                if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
                    COMM_MGR_LIB_ERROR("socket error");
                    goto cleanup;
                }
                memset(&un_addr, 0, sizeof(un_addr));
                un_addr.sun_family = AF_UNIX;
                if(client->ancillary) {
                    strcpy(un_addr.sun_path, ANC_SOCKET_FILE_PATH);
                } else {
                    strcpy(un_addr.sun_path, SOCKET_FILE_PATH);
                }

                if (connect(fd, (struct sockaddr*)&un_addr, sizeof(un_addr)) == -1) {
                    COMM_MGR_LIB_ERROR("connect error");
                    goto cleanup;
                } 
            }
            break;
        case COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM:
            {
                struct hostent *server = &(__comm_mgr_lib_clients[id].server);

                if (server == NULL) {
                    COMM_MGR_LIB_ERROR("Invalid Server");
                    goto cleanup;
                }

                if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                    COMM_MGR_LIB_ERROR("socket error");
                    goto cleanup;
                }
                
                if (server->h_name) { // If Only h_name is supplied
                    server = gethostbyname(server->h_name);
                }

                if (server == NULL) {
                    COMM_MGR_LIB_ERROR("No such host\n");
                    goto cleanup;
                }
                                
                COMM_MGR_LIB_DEBUG("Server address : %s : %d", 
                   inet_ntoa(*(struct in_addr*) server->h_addr), __comm_mgr_lib_clients[id].portNum);


                memset(&in_addr, 0, sizeof(in_addr));
                in_addr.sin_family = AF_INET;
                memcpy((char *)&in_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);	
                in_addr.sin_port = htons(__comm_mgr_lib_clients[id].portNum);

                if (connect(fd, (struct sockaddr*)&in_addr, sizeof(in_addr)) == -1) {
                    COMM_MGR_LIB_ERROR("connect error");
                    goto cleanup;
                }
            }    
            break;
        default:
            COMM_MGR_LIB_ERROR("Unknown AF type");
            goto cleanup;
            break;
    }

    if(comm_mgr_set_non_blocking_io(fd) != COMM_MGR_LIB_SUCCESS) {
        goto cleanup;
    }    
  
    __comm_mgr_lib_clients[id].client_ptr->__src_uid = comm_mgr_lib_src_uid;
    __comm_mgr_lib_clients[id].client_ptr->__fd = fd;
    __comm_mgr_lib_clients[id].client_ptr->__clientReady = 1;
    __comm_mgr_lib_clients[id].client_ptr->__proto_state = COMM_MGR_PROTO_DISCOVERY_START;
    __comm_mgr_lib_clients[id].__clientID = (id | (client->clientAf << 4));
    __comm_mgr_lib_clients[id].property = (COMM_MGR_LIB_CLIENT_PROPERTY*)malloc(sizeof(COMM_MGR_LIB_CLIENT_PROPERTY));
    __comm_mgr_lib_clients[id].client_ptr->__app_property = &__comm_mgr_lib_app_property;

    // Copy the user supplied client properties, if present. Else set default
    if(client->property != NULL) {
        memcpy(__comm_mgr_lib_clients[id].property, client->property, sizeof(COMM_MGR_LIB_CLIENT_PROPERTY)); 
    } else {
        __comm_mgr_lib_clients[id].property->comm_mgr_lib_recv_queue_size = COMM_MGR_LIB_RECV_QUEUE_SIZE;
        __comm_mgr_lib_clients[id].property->comm_mgr_lib_send_queue_size = COMM_MGR_LIB_SEND_QUEUE_SIZE;
        if(comm_mgr_lib_epoll_en) {
            __comm_mgr_lib_clients[id].property->libInactivityTimeOut = COMM_MGR_LIB_DEFAULT_EPOLL_TIMEOUT;
        } else {
            __comm_mgr_lib_clients[id].property->libInactivityTimeOut = COMM_MGR_LIB_DEFAULT_SELECT_TIMEOUT;
        }
    }
    
    // Enabling epoll based comm_mgr_lib
    if(comm_mgr_lib_epoll_en) {
        COMM_MGR_LIB_DEBUG("Enabling the epoll based system for cid %d", __comm_mgr_lib_clients[id].__clientID);
        //int pollingfd = epoll_create( 0xCAFE ); 
        // Refer : https://www.ulduzsoft.com/2014/01/select-poll-epoll-practical-difference-for-system-architects/
    }

    // Create default DSIDs which is needed by the lib per client
    __comm_mgr_lib_clients[id].client_ptr->__DSID = 
            (UTILS_DS_ID*)malloc(sizeof(UTILS_DS_ID) * COMM_MGR_LIB_DSID_MAX);
    __comm_mgr_lib_clients[id].client_ptr->__dsid_cb = 
            (comm_mgr_lib_dsid_cb *)malloc(sizeof(comm_mgr_lib_dsid_cb) * COMM_MGR_LIB_DSID_MAX);

    // Create a Circular Queues for each DSIDs
    UTILS_QUEUE queue;
    queue.type = UTILS_QUEUE_CIRCULAR;
    queue.size = COMM_MGR_LIB_PROTO_QUEUE_SIZE;
    queue.isPriority = FALSE;
    __comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO_RECV] = utils_ds_queue_create(&queue);
    if (__comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO_RECV] == 0) {
        COMM_MGR_LIB_ERROR("Failed to create COMM_MGR_LIB_DSID_PROTO_RECV");
        goto cleanup;
    }

    queue.size = COMM_MGR_LIB_PROTO_QUEUE_SIZE;
    __comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO_SEND] = utils_ds_queue_create(&queue);
    if (__comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO_SEND] == 0) {
        COMM_MGR_LIB_ERROR("Failed to create COMM_MGR_LIB_DSID_PROTO_SEND");
        goto cleanup;
    }

    queue.size = __comm_mgr_lib_clients[id].property->comm_mgr_lib_recv_queue_size;
    __comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_RECV] = utils_ds_queue_create(&queue);
    if (__comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_RECV] == 0) {
        COMM_MGR_LIB_ERROR("Failed to create COMM_MGR_LIB_DSID_DATA_RECV");
        goto cleanup;
    }

    queue.size = __comm_mgr_lib_clients[id].property->comm_mgr_lib_send_queue_size;
    __comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_SEND] = utils_ds_queue_create(&queue);
    if (__comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_SEND] == 0) {
        COMM_MGR_LIB_ERROR("Failed to create COMM_MGR_LIB_DSID_DATA_SEND");
        goto cleanup;
    }

    // Update the Global Library App properties
    if(client->ancillary == TRUE) {
        __comm_mgr_lib_app_property.isAncillaryCapable = TRUE;
        __comm_mgr_lib_app_property.anc_cid = __comm_mgr_lib_clients[id].__clientID; 
    }

    return __comm_mgr_lib_clients[id].__clientID;

cleanup:
    COMM_MGR_LIB_ERROR("Client creation failed");
    comm_mgr_lib_delete_client(id); // Clean up                                                    
    return COMM_MGR_LIB_INVALID_CLIENT;
}

COMM_MGR_LIB_ERR comm_mgr_lib_delete_client(COMM_MGR_LIB_CLIENT_ID id) {
    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id);

    if(cid > COMM_MGR_LIB_MAX_CLIENTS) {
        COMM_MGR_LIB_ERROR("Invalid client. Cannot delete");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR;
    }
    free(__comm_mgr_lib_clients[cid].client_ptr);
    __comm_mgr_lib_clients[cid].client_ptr = NULL;

    return COMM_MGR_LIB_SUCCESS;
}

/*
    @brief This function is the gateway to the Communication Manager.
          It handles the requests coming from and to be sent to
          Communication Manager. This function should never return under
          normal conditions.

          It relies on the below DSIDs for receving/sending protocol/data/ack
          COMM_MGR_LIB_DSID_PROTO_RECV - DSID for receiving protocols/ack      
          COMM_MGR_LIB_DSID_PROTO_SEND - DSID for sending protocols/ack      
          COMM_MGR_LIB_DSID_DATA_RECV - DSID for receiving the Data/ack
          COMM_MGR_LIB_DSID_DATA_SEND - DSID for sending the Data/ack

          All these DSIDs are per client
        Algorithm :
          If there is some msg is available in the DSIDs (according to priority),
          then the message will be dequed and sent.
          Once a message is sent again we will check if there is any activity on readfds.
          If so, then the message will be received and enqued.
          Note : With this logic, always one msg is sent and any receive activity is checked.
          And again a next msg is sent if its available in DSIDs. With this, the receiver is
          also priortized

    Note : Based on "comm_mgr_lib_epoll_en" it uses epoll() / select() based event handling
        This is enabled/disabled per APP only
*/
COMM_MGR_LIB_ERR comm_mgr_lib_server_communicator(COMM_MGR_LIB_CLIENT_ID id) {
    if(comm_mgr_lib_epoll_en) {        
        COMM_MGR_LIB_DEBUG("Using the epoll based event handling mechansim");
        return __comm_mgr_lib_server_communicator_with_epoll(id);
    } else {
        COMM_MGR_LIB_DEBUG("Using the select based event handling mechansim");
        return __comm_mgr_lib_server_communicator_with_select(id);
    }
    return COMM_MGR_LIB_SUCCESS;
}

/*
    @brief This function is explicitly used to send user data ONLY.
*/
COMM_MGR_LIB_ERR comm_mgr_lib_send_data(COMM_MGR_LIB_CLIENT_ID id, uint16_t dst_uid, 
                                        char *msg, int len) {                                    
    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id);
    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;
    COMM_MGR_MSG_HDR hdr;
    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    if((msg == NULL) || (len == 0)) {
        COMM_MGR_LIB_ERROR("Input arguments are wrong");
        return COMM_MGR_LIB_INVALID_ARG;
    }
    if(id > COMM_MGR_LIB_MAX_CLIENTS) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR;
    }
    if(__comm_mgr_lib_clients[cid].client_ptr == NULL) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR;
    }

    // Just the dst_uid and msg type is enough
    hdr.msg_type = COMM_MGR_MSG_DATA;
    hdr.dst_uid = dst_uid;

    ret = __comm_mgr_lib_send_msg(&__comm_mgr_lib_clients[cid], &hdr, (void *)msg, len);

    return ret;
}

/*
    This function is used to send Ancillary data. This is a powerful send function
    which can be used to send file descriptors, credetials, vectors etc
*/
COMM_MGR_LIB_ERR comm_mgr_lib_send_anc_data(COMM_MGR_LIB_CLIENT_ID id, uint16_t dst_uid, 
                                            uint8_t num_vector, char **data, uint8_t *datalen,
                                            uint8_t num_fds, int *fds, COMM_MGR_ANC_MSG_TYPE msg_type) {

    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id);
    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;
    COMM_MGR_MSG_HDR hdr;
    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    // Do a validation here as much as possible, even the internal common comm_mgr functions
    // are fully capable of handling all kinds of error situation. This will avoid error
    // checking in the inner-most functions and we can immediately inform the caller about this.
    if(num_vector > 0) {
        // Sanitize the whole vector
        for (uint8_t i = 0; i < num_vector; i++) {
            if(datalen[i] == 0) {
                COMM_MGR_LIB_ERROR("Invalid datalen");
                return COMM_MGR_LIB_INVALID_ARG;
            }
            if(data[i] == NULL) {
                COMM_MGR_LIB_ERROR("Invalid data pointer");
                return COMM_MGR_LIB_INVALID_ARG;
            }
        }
    }

    // There are certain software defined artifical limitation as well. Validate them
    if(num_fds > COMM_MGR_MAX_ANCILLARY_FD) {
        COMM_MGR_LIB_ERROR("Max number of FD allowed is %d", COMM_MGR_MAX_ANCILLARY_FD);
        return COMM_MGR_LIB_INVALID_ARG;
    }
    if(num_vector > COMM_MGR_MAX_ANCILLARY_USER_IOV) {
        COMM_MGR_LIB_ERROR("Max number of Vectors allowed is %d", COMM_MGR_MAX_ANCILLARY_USER_IOV);
        return COMM_MGR_LIB_INVALID_ARG; 
    }


    if(id > COMM_MGR_LIB_MAX_CLIENTS) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR;
    }
    if(__comm_mgr_lib_clients[cid].client_ptr == NULL) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR;
    }

    // Just the dst_uid and msg type is enough
    hdr.msg_type = COMM_MGR_MSG_ANCILLARY;
    hdr.dst_uid = dst_uid;

    // This is like a container, used to hold the user passed pointers. No need to
    // fill other fileds like magic, version etc.
    COMM_MGR_ANC_MSG anc_msg;
    memset(&anc_msg, 0, sizeof(anc_msg));
    anc_msg.hdr.anc_msg_type = msg_type;
    anc_msg.hdr.num_fd = num_fds;
    anc_msg.hdr.num_vec = num_vector;
    anc_msg.payloads = data;
    anc_msg.nPayloadSize = datalen;
    anc_msg.fds = fds;

    ret = __comm_mgr_lib_send_msg(&__comm_mgr_lib_clients[cid], &hdr, (void *)&anc_msg, 0);

    return ret;

}

/*
    @brief This function is explicitly used to send ACK ONLY.
*/
COMM_MGR_LIB_ERR comm_mgr_lib_send_ack(COMM_MGR_LIB_CLIENT_ID id, uint16_t dst_uid, COMM_MGR_SUBMSG_TYPE submsg) {
    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id);
    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;
    COMM_MGR_MSG_HDR hdr;
    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));


    if(id > COMM_MGR_LIB_MAX_CLIENTS) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR;
    }
    if(__comm_mgr_lib_clients[cid].client_ptr == NULL) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR;
    }

    switch(submsg) {
        case COMM_MGR_SUBMSG_PROTO_ACK:
        case COMM_MGR_SUBMSG_PROTO_NACK:
        case COMM_MGR_SUBMSG_DATA_ACK:
        case COMM_MGR_SUBMSG_DATA_NACK:
            hdr.submsg_type = submsg;
            break;
        default:
            COMM_MGR_LIB_ERROR("Bad sub message type passed %d", submsg);
            return COMM_MGR_LIB_INVALID_ARG;
    }

    // Just the dst_uid and msg type is enough
    hdr.msg_type = COMM_MGR_MSG_ACK;
    hdr.dst_uid = dst_uid;

    ret = __comm_mgr_lib_send_msg(&__comm_mgr_lib_clients[cid], &hdr, NULL, 0);

    return ret;
}

/*
    This function is used to retrieve the data which has been received by the
    Communication Manager library

    This function will read the data from COMM_MGR_LIB_DSID_DATA_RECV

    The application should keep calling this function to get the data depending
    on COMM_MGR_LIB_EVENT_FLAGS

    Note : It is the responsibility of the application to free the comm_msg
    dequed once it has used the message.
*/
COMM_MGR_MSG* comm_mgr_lib_recv_data(COMM_MGR_LIB_CLIENT_ID id) {
    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id);

    if(id > COMM_MGR_LIB_MAX_CLIENTS) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return NULL;
    }
    if(__comm_mgr_lib_clients[cid].client_ptr == NULL) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return NULL;
    }

    UTILS_DS_ID dsid = __comm_mgr_lib_clients[cid].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_RECV];
    COMM_MGR_MSG *comm_mgr_msg = (COMM_MGR_MSG *)utils_ds_queue_dequeue(dsid);

    return comm_mgr_msg;
}

/*
    This function get the status of various groups related to the library

    <TODO> Might need to implement the Multiple Reader - Single Writer lock with Writer priority
*/
uint8_t comm_mgr_lib_get_status(uint8_t cid, COMM_MGR_LIB_STATUS_GRP grp) {
    uint8_t status = 0;

    switch(grp) {
        case COMM_MGR_LIB_STATUS_GRP_DATA: // Data grp is a bitmap. It can hold multiple values
            status = __comm_mgr_lib_status[cid].comm_mgr_lib_data_recv_status;            
            break;
        case COMM_MGR_LIB_STATUS_GRP_GENERIC:
            status = __comm_mgr_lib_status[cid].comm_mgr_lib_generic_status;
            break;
        case COMM_MGR_LIB_STATUS_GRP_ERROR:
            status = __comm_mgr_lib_status[cid].comm_mgr_lib_error_status;
            break;
        default:
            return 0xFF;
    }
    return status;
}

void comm_mgr_lib_free_msg(COMM_MGR_MSG *msg) {
    if(msg == NULL) {
        return;
    }
    comm_mgr_destroy_msg(msg); 
}

/******************************************************************************
                            Internal Functions
******************************************************************************/
static uint16_t __comm_mgr_lib_get_free_client() {
    for (uint16_t i = 1; i < COMM_MGR_LIB_MAX_CLIENTS; i++) {
        if (__comm_mgr_lib_clients[i].client_ptr == NULL) {            
            return i;
        }
    }
    return COMM_MGR_LIB_INVALID_CLIENT;
}

static void __comm_mgr_lib_delete_client(COMM_MGR_LIB_CLIENT_ID id) {
    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id);

    if(cid > COMM_MGR_LIB_MAX_CLIENTS) {
        return;
    }
    free(__comm_mgr_lib_clients[cid].client_ptr);
    __comm_mgr_lib_clients[cid].client_ptr = NULL;
}

static COMM_MGR_LIB_ERR comm_mgr_set_non_blocking_io(int socket_fd) {
    int rc = 0;
    rc = fcntl(socket_fd, F_SETFL, (fcntl(socket_fd, F_GETFL, 0) | O_NONBLOCK));
    if (rc < 0) {
       COMM_MGR_LIB_ERROR("Failed to set the socket %d to Non-blocking mode", socket_fd);
       return COMM_MGR_LIB_FCNTL_NON_BLOCK_ERR;
    }
    return COMM_MGR_LIB_SUCCESS;
}

/*
	This function will enqueue the raw bytes received into the proto/recv DSIDs

    The protocol packets will be handled transparent of apps. That is the apps will
    never know about the protocol going behind screen.

    For data/ack packets, the apps can register for events or can keep polling the 
    USER_DSID which will be supplied by the apps to the lib
*/
static COMM_MGR_LIB_ERR  __comm_mgr_lib_receive_packets(COMM_MGR_LIB_CLIENT_ID id, COMM_MGR_MSG *msg) {
    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id); 

    if (msg == NULL) {
        COMM_MGR_LIB_ERROR("Received bad packet from Communication Manager");
        return COMM_MGR_LIB_BAD_PACKET;
    }

    COMM_MGR_LIB_DEBUG("CID[%d]: Received msg_type [%d], submsg_type [%d]", 
                       COMM_MGR_LIB_GET_CLIENT_ID(id), msg->hdr.msg_type, msg->hdr.submsg_type);

    switch(msg->hdr.msg_type) {
        case COMM_MGR_MSG_PROTOCOL:
            __comm_mgr_lib_protocol_handler(&__comm_mgr_lib_clients[cid], msg);
            break;
        case COMM_MGR_MSG_ACK:
            __comm_mgr_lib_ack_handler(&__comm_mgr_lib_clients[cid], msg);
            break;
        case COMM_MGR_MSG_DATA:
        case COMM_MGR_MSG_ANCILLARY:
            __comm_mgr_lib_data_handler(&__comm_mgr_lib_clients[cid], msg);
            break;            
        default:
            return COMM_MGR_LIB_BAD_PACKET;
    }
    return COMM_MGR_LIB_SUCCESS;
}

/*
    @brief This function is used to send protocol/ack/data packets. It can also e called
           directly by the clients, in case they need to fine tune some of the default
           comm msg parameters, though its not recommended

        @param msg It can be NULL also in case of ACK and Protocol packets
*/
static COMM_MGR_LIB_ERR __comm_mgr_lib_send_msg(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG_HDR *hdr, 
                                                void *msg, int len) {
    struct hostent *server = &(client->server);
    uint32_t comm_msg_size = 0;
    COMM_MGR_MSG *comm_mgr_msg = NULL;

    if (client == NULL) {
        return COMM_MGR_LIB_INVALID_ARG;
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

    if(hdr->msg_type == COMM_MGR_MSG_ANCILLARY) {
        COMM_MGR_ANC_MSG *anc_msg = (COMM_MGR_ANC_MSG *)msg;
        if(anc_msg == NULL) {
            COMM_MGR_LIB_ERROR("Invalid ancillary message");
            return COMM_MGR_LIB_INVALID_ARG; 
        }
        comm_mgr_msg = comm_mgr_create_anc_msg(client->client_ptr->__src_uid, hdr->dst_uid, anc_msg->hdr.anc_msg_type,
                                               anc_msg->hdr.num_vec, anc_msg->payloads, anc_msg->nPayloadSize,
                                               anc_msg->hdr.num_fd, anc_msg->fds);
    } else {
        comm_mgr_msg = comm_mgr_create_msg(client->client_ptr->__src_uid, 
                                    hdr->dst_uid, hdr->msg_type, (char *)msg, len);
    }

    if (comm_mgr_msg == NULL) {
        COMM_MGR_LIB_ERROR("Couldn't create the COMM_MGR_MSG packet. Not sending the msg");
        return COMM_MGR_LIB_SEND_ERR;
    }

    /* Clients can set some more paramaters on default */
    comm_mgr_msg->hdr.submsg_type = hdr->submsg_type; 
    comm_mgr_msg->hdr.priority = hdr->priority;
    comm_mgr_msg->hdr.ack_required = hdr->ack_required;
    comm_mgr_msg->hdr.msg_backing_time = hdr->msg_backing_time;

    //comm_msg_size = sizeof(COMM_MGR_MSG_HDR) + (comm_mgr_msg->hdr.payloadSize * sizeof(char));
    comm_msg_size = COMM_MGR_MSG_SIZE(comm_mgr_msg);

    COMM_MGR_LIB_DEBUG("Sending msg type [%d], submsg_type [%d], size [%d], src_uid [%d], dst_uid [%d]\n", 
                                            comm_mgr_msg->hdr.msg_type, comm_mgr_msg->hdr.submsg_type, 
                                            comm_msg_size,
                                            comm_mgr_msg->hdr.src_uid, comm_mgr_msg->hdr.dst_uid);
   
    // Now send the message to Communication Manager
    // If its a Protocol packet OR an ACK related to Protocol, enqueue in Protocol DSID
    if ((comm_mgr_msg->hdr.msg_type == COMM_MGR_MSG_PROTOCOL) ||
        ((comm_mgr_msg->hdr.msg_type == COMM_MGR_MSG_ACK) && 
        ((comm_mgr_msg->hdr.submsg_type == COMM_MGR_SUBMSG_PROTO_ACK) || 
        (comm_mgr_msg->hdr.submsg_type == COMM_MGR_SUBMSG_PROTO_NACK)))) {
        if(utils_ds_queue_enqueue(client->client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO_SEND], (void *)comm_mgr_msg) < 0) {
            COMM_MGR_LIB_ERROR("Failed to insert the Protocol packet to DSID 0x%0x", 
                                                client->client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO_SEND]);
            return COMM_MGR_LIB_UTILS_DSID_ERR; 
        }
    } else { // For now, enqueue rest of the packets to DATA DSID
        if(utils_ds_queue_enqueue(client->client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_SEND], (void *)comm_mgr_msg) < 0) {
            COMM_MGR_LIB_ERROR("Failed to insert the Protocol packet to DSID 0x%0x",
                                            client->client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_SEND]);
            return COMM_MGR_LIB_UTILS_DSID_ERR; 
        }
    }
 
    return COMM_MGR_LIB_SUCCESS;
}

/*
    @brief This function is explicitly used to send protocol packets ONLY.

    Protocol is always between the initiating client and Communication 
    Manager.
*/
static COMM_MGR_LIB_ERR __comm_mgr_lib_send_protocol(COMM_MGR_LIB_CLIENT *client, 
                                                     COMM_MGR_SUBMSG_TYPE submsg_type,
                                                     char *payload,
                                                     uint16_t payloadsize) {
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

    ret = __comm_mgr_lib_send_msg(client, &hdr, (void *)payload, payloadsize);

    return ret;
}

/*  
    @brief This function takes care of handling the protocol from the client
        side. It has its own state machine to handle all cases

        All the instructions by the Comm Manager will be honoured by the client

        The protocol for the client takes places under the hood without any intervention
        from the client

        Note : The protocol is always initiated by the Server. If client tries to send a protocol
        packet on its own, the server will drop it. The client lib just responds to the protocol
        queries and moves to appropriate states in its local state machine
*/
static COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_handler(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg) {
  
    if ((msg == NULL) || (msg->hdr.magic != COMM_MGR_MSG_HDR_MAGIC)){
        COMM_MGR_LIB_ERROR("Received a bad protocol packet");
        return COMM_MGR_LIB_PROTO_BAD_PACKET;
    }

    switch(msg->hdr.submsg_type) {
        case COMM_MGR_SUBMSG_DISCOVERY:
        case COMM_MGR_SUBMSG_LEARNING:
        case COMM_MGR_SUBMSG_DATATXREADY:
            __comm_mgr_lib_protocol_statemachine(client, msg);
            break;
        case COMM_MGR_SUBMSG_ANC_LEARNING:
            __comm_mgr_lib_protocol_anc_learning(client, msg);
            break;
        default:
            COMM_MGR_LIB_ERROR("Received a bad protocol packet"); 
            return COMM_MGR_LIB_PROTO_BAD_PACKET;
    }

    return COMM_MGR_LIB_SUCCESS;
}

/*
    This function takes care of handling the ACK/NACK coming to Client.

    The acks can come from Communication Manager / the other apps
*/
static COMM_MGR_LIB_ERR __comm_mgr_lib_ack_handler(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg) {
    if ((msg == NULL) || (msg->hdr.magic != COMM_MGR_MSG_HDR_MAGIC)){
        COMM_MGR_LIB_ERROR("Received a bad ack packet");
        return COMM_MGR_LIB_PROTO_BAD_PACKET;
    }

    if (msg->hdr.msg_type != COMM_MGR_MSG_ACK) {
        COMM_MGR_LIB_ERROR("Received a bad ack packet");
        return COMM_MGR_LIB_ACK_BAD_PACKET;
    }

    switch(msg->hdr.submsg_type) {
        case COMM_MGR_SUBMSG_PROTO_ACK:
        case COMM_MGR_SUBMSG_PROTO_NACK:
            __comm_mgr_lib_protocol_statemachine(client, msg);
            break;
        case COMM_MGR_SUBMSG_DATA_ACK:
        case COMM_MGR_SUBMSG_DATA_NACK:

            break;
        default:
            COMM_MGR_LIB_ERROR("Received a bad ack packet");
            return COMM_MGR_LIB_ACK_BAD_PACKET;
    }
    return COMM_MGR_LIB_SUCCESS;
}

/*
    This function takes care of handlig the Data packets coming to the client. The Data ACK/NACK
    will be handled by the ack_handler

    COMM_MGR_LIB_DSID_DATA_RECV will be used to enqueue the Data Packets. The applications need
    to either poll for this DSID or setup an event and get notification from the library as well.

    To poll keep calling comm_mgr_lib_recv_data()

    The event notification mechanism is recommended. To get notification, enable the events on the
    comunication task and register for default data event provided by the comm library
*/
static COMM_MGR_LIB_ERR __comm_mgr_lib_data_handler(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg) {

    if (client == NULL) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR; 
    }

    if(msg == NULL) {
        COMM_MGR_LIB_ERROR("Invalid data received. Discarding");
        return COMM_MGR_LIB_BAD_PACKET;
    }

    UTILS_DS_ID dsid = client->client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_RECV];

    if(utils_ds_queue_enqueue(dsid, (void *)msg) < 0) {
        COMM_MGR_LIB_ERROR("Failed to insert the data to DSID 0x%0x", dsid);
        return COMM_MGR_LIB_UTILS_DSID_ERR;
    }

    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(client->__clientID);
    // Indicate that some data is available
    __comm_mgr_lib_update_status(cid, COMM_MGR_LIB_STATUS_GRP_DATA, COMM_MGR_LIB_DATA_STATUS_RECV_PENDING);

    // Check if the application has registered for a callback 
    if(client->property && client->property->app_cb) {
        client->property->app_cb(COMM_MGR_LIB_EVENT_RECV_READY);
    }

    return COMM_MGR_LIB_SUCCESS;
}

/*
    @brief This function maintains a statemachine of the protocol
           required for a reliable data exchange. It describes a
           series of steps leading to a successful connection
           between the app and Communication Manager

    @param client  Client for which statemachine is run 

    The Protocol packets uses one dedicated queue for ALL clients.
    Once the new protocol packet is added to the queue, it will
    be immediatley processed discarding all other data/ack packets
    from apps

    NOTE : For a client, its proto state should be at least in COMM_MGR_PROTO_DISCOVERY_DONE
        state to send a USer packet to any dest UID. The lib will discard any packets to
        any dest UIDs, if the app tries to send the packet, till the client reaches 
        COMM_MGR_PROTO_DISCOVERY_DONE.

        After this state, the User send depends on the Learning State. The learning state is
        a function of Dest UID and not clients state.  If a Dest UID D1 is not yet learnt by
        the Communication Manager, the lib will discard all user packets to this particular
        Dest UID D1, till it is learnt. But the apps are still allowed to try to send to other
        Dest UIDs and the same rule applies for those Dest UIDs if they are not yet learnt by
        Communication Manager

        The lib maintains a bitmap of Dest UIDs which are learnt
*/
static 
COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_statemachine(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg) {
    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;    
    COMM_MGR_PROTO_STATES proto_state;

    switch(client->client_ptr->__proto_state) {
        case COMM_MGR_PROTO_DISCOVERY_START:
            ret = __comm_mgr_lib_protocol_discovery_start(client, msg); 
            break;
        case COMM_MGR_PROTO_DISCOVERY_DONE:
            ret = __comm_mgr_lib_protocol_discovery_done(client, msg); 
            break;
        case COMM_MGR_PROTO_DATATRANSFER_READY:
            ret = __comm_mgr_lib_protocol_datatransfer_ready(client, msg);
            break;
        default:
            COMM_MGR_LIB_ERROR("Invalid protocol state");
            return COMM_MGR_LIB_PROTO_INVALID_STATE;
    }
    return ret;
}

/*
    This function should do the below:        
        - Create the local lib UID map
        - First send an ACK/NACK for the discovery packet it has received depending on payload 
        - Create a new protocol comm msg with same state and respond with the first dest UID
        - Once it gets gets the ACK packet, should change the client state tp DISCOVERY_DONE
        - Discard any user packets
*/
static 
COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_discovery_start(COMM_MGR_LIB_CLIENT *client, 
                                                         COMM_MGR_MSG *msg) {
    uint16_t payload[COMM_MGR_MSG_PROTOCOL_LIB_DISCOVERY_SIZE/2];                                                         

    if(msg->hdr.submsg_type != COMM_MGR_SUBMSG_DISCOVERY) {
        COMM_MGR_LIB_ERROR("Received a non-discovery protocol packet in discovery state");
        goto send_nack;
    }

    // We need ask the Communication Manager to send the discovery packet again. Send NACK
    if(__comm_mgr_lib_update_local_uid_map(msg) != COMM_MGR_LIB_SUCCESS) {
        // Create a NACK packet and enqueue in PROTO DSID
        // <COMM_MGR_MSG_ACK : COMM_MGR_SUBMSG_PROTO_NACK> message
        COMM_MGR_LIB_TRACE("Sending the NACK for the Discovery packet received"); 
        goto send_nack;
    }

    // If Comm Manager requires an ACK
    if (msg->hdr.ack_required == TRUE) {
        // Send a Positive Ack to Communication manager
        if(comm_mgr_lib_send_ack(client->__clientID, SYS_MGR_SYSTEM_UID_COMM_MANAGER, 
                    COMM_MGR_SUBMSG_PROTO_ACK) != COMM_MGR_LIB_SUCCESS) {
            COMM_MGR_LIB_ERROR("Failed to send ACK PROTO packet to Communication Manager");
            return COMM_MGR_LIB_SEND_ACK_ERR;
        }
    }

    // The Communication Manager usually responds with the Dest UID received in the first Dest UID
    // sent by the app, in Discovery message
    payload[0] = COMM_MGR_MSG_PROTOCOL_MAGIC;
    memcpy(&payload[1], &msg->payload[10], sizeof(uint16_t));
    COMM_MGR_LIB_DEBUG("Payload[6] in Discovery message = %d\n", payload[1]);

    // Drop the msg received since we done using it
    comm_mgr_lib_free_msg(msg);

    //Create a new protocol comm msg with same state and respond with apps UID
    if(__comm_mgr_lib_send_protocol(client, COMM_MGR_SUBMSG_DISCOVERY, 
                                   (char *)payload, sizeof(payload)) != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Failed to send Discovery message to Communication Manager");
        return COMM_MGR_LIB_PROTO_ERR;
    }

    // Move the current state of the Client to Discovery Done
    client->client_ptr->__proto_state = COMM_MGR_PROTO_DISCOVERY_DONE;

    return COMM_MGR_LIB_SUCCESS;

send_nack:
    // We need ask the Communication Manager to send the discovery packet again. Send NACK
    if(comm_mgr_lib_send_ack(client->__clientID, SYS_MGR_SYSTEM_UID_COMM_MANAGER, 
                COMM_MGR_SUBMSG_PROTO_NACK) != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Failed to send NACK PROTO packet to Communication Manager");
    }

    // Drop the msg received since we done using it 
    comm_mgr_lib_free_msg(msg); 

    return COMM_MGR_LIB_PROTO_BAD_PACKET;
}

/*  This function should do the below: 
       - Next should wait for an ACK from the Communication Manager
       - Wait for either Learning packets OR DataTransfer Ready packet
       - Change the proto state of the client to learning start / DataTransfer Ready
       - Discard any user packets

    Note : Moving the client to Data Transfer Ready doesn tmean that the Client can 
    send packets to any Destinations. It just indicates that the client has been 
    Discovered by the Communication Manager and it can/cannot send the packets to
    a particular destination depeding on whether that Dest UID has been learnt by the
    Communication manager
*/
static 
COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_discovery_done(COMM_MGR_LIB_CLIENT *client,
                                                        COMM_MGR_MSG *msg) {
    if (msg->hdr.msg_type != COMM_MGR_MSG_ACK) {
        COMM_MGR_LIB_ERROR("Received a bad ack packet");
        goto send_nack;
    }

    // Move the current state of the Client to Data transfer ready
    client->client_ptr->__proto_state = COMM_MGR_PROTO_DATATRANSFER_READY;

    // Drop the msg received since we done using it
    comm_mgr_lib_free_msg(msg); 

    return COMM_MGR_LIB_SUCCESS;
send_nack:
    // We need ask the Communication Manager to send the discovery ACK packet again. Send NACK
     if(comm_mgr_lib_send_ack(client->__clientID, SYS_MGR_SYSTEM_UID_COMM_MANAGER, 
                COMM_MGR_SUBMSG_PROTO_NACK) != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Failed to send NACK PROTO packet to Communication Manager");
    }
    
    // Drop the msg received since we done using it
    comm_mgr_lib_free_msg(msg);

    return COMM_MGR_LIB_ACK_BAD_PACKET;
}

/*
    Learning messages are sent by the Server when it needs to notify the client library
    about something the Server has learnt. These kind of messages can come anytime and
    library needs to honour these messages

    Format :

    msg_type = PROTOCOL | submsg_type = LEARNING | payloadsize = 4 (bytes) | 
               *payload = COMM_MGR_MSG_PROTOCOL_MAGIC (2) | action (2) | dst_uid (2)

*/
static 
COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_learning(COMM_MGR_LIB_CLIENT *client,
                                                  COMM_MGR_MSG *msg) {

    if (msg->hdr.payloadSize != (COMM_MGR_MSG_PROTOCOL_SRV_LEARNING_SIZE)) {
        COMM_MGR_LIB_ERROR("Bad payloadsize received. Discarding"); 
        goto send_nack;
    }

    uint16_t magic;
    memcpy(&magic, &(msg->payload[0]), sizeof(uint16_t));
    if(magic != COMM_MGR_MSG_PROTOCOL_MAGIC) {
        COMM_MGR_LIB_ERROR("Bad payloadsize received. Discarding"); 
        goto send_nack;
    }

    uint16_t action, dest_uid;
    memcpy(&action, &(msg->payload[2]), sizeof(uint16_t));    
    memcpy(&dest_uid, &(msg->payload[4]), sizeof(uint16_t));    

    // Validate the Dest UID received
    if(!__comm_mgr_lib_is_uid_valid(dest_uid)) {
        COMM_MGR_LIB_ERROR("Bad Dest UID received in the Learning protocol packet");
        goto send_nack;
    }
    // Also validate the action message received. 
    if(action >= COMM_MGR_SUBMSG_LEARNING_ACTION_INVALID) {
        COMM_MGR_LIB_ERROR("Bad Action received in the Learning protocol packet");
        goto send_nack;
    }

    if(__comm_mgr_lib_is_uid_static(dest_uid)) {
        uint16_t index = dest_uid - comm_mgr_lib_static_uid_base;
        comm_mgr_lib_static_uid_learning_cache[index] = action;
    } else {
        uint16_t index = dest_uid - comm_mgr_lib_dynamic_uid_base;
        comm_mgr_lib_dynamic_uid_learning_cache[index] = action;      
    }
    COMM_MGR_LIB_DEBUG("Received the Learning message with Action [%d], Dest UID [%d]",
                                                                    action, dest_uid);

    // Drop the msg received since we done using it
    comm_mgr_lib_free_msg(msg);

    return COMM_MGR_LIB_SUCCESS;

send_nack:
    // We need ask the Communication Manager to send the learning packet again. Send NACK
     if(comm_mgr_lib_send_ack(client->__clientID, SYS_MGR_SYSTEM_UID_COMM_MANAGER, 
                COMM_MGR_SUBMSG_PROTO_NACK) != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Failed to send NACK PROTO packet to Communication Manager");
    }

    // Drop the msg received since we done using it
    comm_mgr_lib_free_msg(msg);

    return COMM_MGR_LIB_PROTO_BAD_PACKET;
}

/*
    Ancillary Learning messages are sent by the Communication Manager Server when it
    needs to learn about the Ancillary Channel of this UID (App).

    If this UID doesn't have the Ancillary Channel open or there is no capability then
    send back an Ancillary NACK

    If the Ancillary Channel exists, then send an Ancillary message destined to the 
    Communication Manager for it to know this UIDs Ancillary capability
*/
static
COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_anc_learning(COMM_MGR_LIB_CLIENT *client,
                                                      COMM_MGR_MSG *msg) {
    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;
    // Check if the Ancillary Channel is Open Or if we have the capability
    if(client->client_ptr->__app_property->isAncillaryCapable == FALSE) {
        COMM_MGR_LIB_TRACE("Ancillary Communication Channel doesn't exist for this Client ID [%d]",
                            client->__clientID);
        ret = comm_mgr_lib_send_ack(client->__clientID, SYS_MGR_SYSTEM_UID_COMM_MANAGER, COMM_MGR_SUBMSG_ANC_NACK);
        if(ret != COMM_MGR_LIB_SUCCESS) {
            COMM_MGR_LIB_ERROR("Failed to send ANC NACK PROTO packet to Communication Manager")
        }
        // Drop the msg received since we done using it
        comm_mgr_lib_free_msg(msg);       
        return ret;
    }
    
    // Since the Ancillary channel exist in this app, change the client internally to send response bacl to server
    uint8_t anc_cid = COMM_MGR_LIB_GET_CLIENT_ID(client->client_ptr->__app_property->anc_cid);
    COMM_MGR_LIB_CLIENT *anc_client = &__comm_mgr_lib_clients[anc_cid]; 

    // If the Ancillary Channel exists, then send the Ancillary Message to the Server
    if(__comm_mgr_lib_send_anc_system_info(anc_client, SYS_MGR_SYSTEM_UID_COMM_MANAGER,
                                           NULL, 0) != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Failed to send the Ancillary Learning Messageto the Communication Manager");
    }                               

    // Drop the msg received since we done using it
    comm_mgr_lib_free_msg(msg);

    return COMM_MGR_LIB_SUCCESS;
}                                                  

/*
    This function is the entry point once the client finishes the Discovery stages. 

    Now depending on the Dest UID the packets can be forwarded or dropped

    Format :

    msg_type = PROTOCOL | submsg_type = LEARNING | payloadsize = 6 (bytes) | 
                      *payload = COMM_MGR_MSG_PROTOCOL_MAGIC (2) | Action(2) | Dest UID (2)

    We can get LEARNING Message with some Actions for a Dest UID depeding on whether the Dest UID is
    not learnt or learnt by the Communuication Manager.

    At this point, the Server can send Learning Messages/System Messages etc. But 99% of the time,
    only Learning messages will come here. But Discovery messages should never come again here.
*/
static 
COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_datatransfer_ready(COMM_MGR_LIB_CLIENT *client, 
                                                             COMM_MGR_MSG *msg) {

    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;
    // The sub msg can be either Data Tx Ready or Learning. All others are error cases
    if (msg->hdr.submsg_type == COMM_MGR_SUBMSG_DATATXREADY) {
        // <TODO> Can this message be received from the Server. Investigate / extend new feature
        return COMM_MGR_LIB_PROTO_BAD_PACKET;
    } else if (msg->hdr.submsg_type == COMM_MGR_SUBMSG_LEARNING) {
        ret = __comm_mgr_lib_protocol_learning(client, msg);
    } else {
        // <TODO> For now will ignore other packet types received. Will extend later 
       return COMM_MGR_LIB_PROTO_BAD_PACKET;
    }

    return ret;
}

/*
    This function is used to send Ancillary System Info
*/
static
COMM_MGR_LIB_ERR __comm_mgr_lib_send_anc_system_info(COMM_MGR_LIB_CLIENT *client, uint16_t dst_uid,
                                                    char *data, uint8_t datalen) {

    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;
    COMM_MGR_MSG_HDR hdr;
    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    if(client == NULL) {
        COMM_MGR_LIB_ERROR("Client is Invalid");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR; 
    }

    // Just the dst_uid and msg type is enough
    hdr.msg_type = COMM_MGR_MSG_ANCILLARY;
    hdr.dst_uid = dst_uid;

    // This is like a container, used to hold the user passed pointers. No need to
    // fill other fileds like magic, version etc.
    COMM_MGR_ANC_MSG anc_msg;
    memset(&anc_msg, 0, sizeof(anc_msg));
    anc_msg.hdr.anc_msg_type = COMM_MGR_ANC_MSG_SYSTEM_INFO;
    anc_msg.hdr.num_fd = 0;
    if (datalen == 0) { // If the datalen is 0, reset the num_vec to 0
        anc_msg.hdr.num_vec = 0;
        anc_msg.payloads = NULL;
        anc_msg.nPayloadSize = NULL;
    } else {
        anc_msg.hdr.num_vec = 1;
        anc_msg.payloads = &data;
        anc_msg.nPayloadSize = &datalen;
    }
    anc_msg.fds = NULL;

    ret = __comm_mgr_lib_send_msg(client, &hdr, (void *)&anc_msg, 0);

    return ret;

}

/*
    The lib constructs the map during runtime using the info provided by the 
    Communication Manager.

    During the Discovery Phase of the Protocol, the Communication Manager
    also sends the UID map information.

    If there is any change in the Map info at a later point of time, the 
    Communication Manager can again send via COMM_MGR_MSG_SYSTEM msgs (very rare)

    Data Format of Payload : (each is 2 bytes)        
        payloadsize = 2 * 6
        COMM_MGR_MSG_PROTOCOL_MAGIC | static_uid_max | static_uid_base | dynamic_uid_max | dynamic_uid_base | dst_uid
*/
static 
COMM_MGR_LIB_ERR __comm_mgr_lib_update_local_uid_map(COMM_MGR_MSG *msg) {
    
    if ((msg->hdr.msg_type == COMM_MGR_MSG_PROTOCOL) &&
       (msg->hdr.submsg_type == COMM_MGR_SUBMSG_DISCOVERY)) { // First time
        if (msg->hdr.payloadSize != (COMM_MGR_MSG_PROTOCOL_SRV_DISCOVERY_SIZE)) {
            COMM_MGR_LIB_ERROR("Bad payloadsize received. Discarding"); 
            return COMM_MGR_LIB_BAD_PACKET;
        }
        uint16_t magic;
        memcpy(&magic, &(msg->payload[0]), sizeof(uint16_t));
        if(magic != COMM_MGR_MSG_PROTOCOL_MAGIC) {
            COMM_MGR_LIB_ERROR("Bad magic received. Discarding"); 
            return COMM_MGR_LIB_BAD_PACKET;
        }

        memcpy(&comm_mgr_lib_static_uid_max, &(msg->payload[2]), sizeof(uint16_t));       
        memcpy(&comm_mgr_lib_static_uid_base, &(msg->payload[4]), sizeof(uint16_t));       
        memcpy(&comm_mgr_lib_dynamic_uid_max, &(msg->payload[6]), sizeof(uint16_t));       
        memcpy(&comm_mgr_lib_dynamic_uid_base, &(msg->payload[8]), sizeof(uint16_t));               
    } else if (msg->hdr.msg_type == COMM_MGR_MSG_SYSTEM) { // Update case
        COMM_MGR_LIB_TRACE("Not yet implemented!!!!");
        return COMM_MGR_LIB_BAD_PACKET;
    } else {
        COMM_MGR_LIB_ERROR("Wrong message type");
        return COMM_MGR_LIB_BAD_PACKET; 
    }

    // DO some basic sanity on the values received and decide whether it can be bad.
    if ((comm_mgr_lib_static_uid_base >= comm_mgr_lib_static_uid_max) ||
        (comm_mgr_lib_dynamic_uid_base >= comm_mgr_lib_dynamic_uid_max)) {
        COMM_MGR_LIB_ERROR("Bad UID max/base values received. Discarding");
        return COMM_MGR_LIB_BAD_PACKET;
    }

    // <TODO >Actually make a copy before deleting the current and creating a new map
    // And again copy the map back. But a rare case that, this kind of map changes comes
    // again via COMM_MGR_MSG_SYSTEM
    uint16_t *temp_comm_mgr_lib_static_uid_learning_cache;
    uint16_t *temp_comm_mgr_lib_dynamic_uid_learning_cache;

    // Free te map if it has already been allocated before. (update case : via COMM_MGR_MSG_SYSTEM)
    if (comm_mgr_lib_static_uid_learning_cache) {                
        free(comm_mgr_lib_static_uid_learning_cache);
    }

    if(comm_mgr_lib_dynamic_uid_learning_cache) {
        free(comm_mgr_lib_dynamic_uid_learning_cache);
    }

    uint32_t static_uid_cache_size = sizeof(uint16_t) * (comm_mgr_lib_static_uid_max - comm_mgr_lib_static_uid_base);
    uint32_t dynamic_uid_cache_size = sizeof(uint16_t) * (comm_mgr_lib_dynamic_uid_max - comm_mgr_lib_dynamic_uid_base);

    comm_mgr_lib_static_uid_learning_cache = (uint16_t *)malloc(static_uid_cache_size);
    comm_mgr_lib_dynamic_uid_learning_cache = (uint16_t *)malloc(dynamic_uid_cache_size);

    // By default, all Dest UIDs are not reachable by the library
    memset(comm_mgr_lib_static_uid_learning_cache, COMM_MGR_SUBMSG_LEARNING_ACTION_STOP, static_uid_cache_size);
    memset(comm_mgr_lib_dynamic_uid_learning_cache, COMM_MGR_SUBMSG_LEARNING_ACTION_STOP, dynamic_uid_cache_size);

    return COMM_MGR_LIB_SUCCESS;
}

static boolean __comm_mgr_lib_is_uid_valid(uint16_t uid) {
    if (((uid >= comm_mgr_lib_static_uid_base) &&  
        (uid < comm_mgr_lib_static_uid_max)) ||
        ((uid >= comm_mgr_lib_dynamic_uid_base) &&
        (uid < comm_mgr_lib_dynamic_uid_max))) {
        return TRUE;
    }   
    return FALSE; 
}

// UID should have been validated using __comm_mgr_srv_is_uid_valid
static boolean __comm_mgr_lib_is_uid_static(uint16_t uid) {
    if ((uid >= comm_mgr_lib_static_uid_base) &&  
        (uid < comm_mgr_lib_static_uid_max)) {
        return TRUE;
    }   
    return FALSE;
}

/*
    This function uses epoll based event handling mechanism.

    Refer "https://www.ulduzsoft.com/2014/01/select-poll-epoll-practical-difference-for-system-architects/"
    for pros/cons of using this function
*/
static COMM_MGR_LIB_ERR __comm_mgr_lib_server_communicator_with_epoll(COMM_MGR_LIB_CLIENT_ID id) {

    return COMM_MGR_LIB_SUCCESS;
}

/*
    This function uses select based event handling mechanism.

    'libInactivityTimeOut' in the client property will be set to a default value of '5 sec'.
    This can be be overrided per client in an APP. 
    If it is set to < 0 by the client, then it will forever keep looking for events. This is can be
    helpful only if interested in read event and dont want to timeout (Rare case).

    Recommended to leave at default, unless the app/client knows what it is doing exactly

    Refer "https://www.ulduzsoft.com/2014/01/select-poll-epoll-practical-difference-for-system-architects/"
    for pros/cons of using this function
*/
static COMM_MGR_LIB_ERR __comm_mgr_lib_server_communicator_with_select(COMM_MGR_LIB_CLIENT_ID id) {
    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id);
    fd_set  *working_read_fd;
    fd_set  *working_write_fd;
    struct timeval  timeout;
    int max_sd, rc = 0;
    boolean end_lib = FALSE;
    COMM_MGR_MSG *msg = NULL;
    uint32_t default_select_timeout = COMM_MGR_LIB_DEFAULT_SELECT_TIMEOUT;
    
    COMM_MGR_MSG **recv_msg = NULL;
	uint8_t num_recv_msgs = 0;
    COMM_MGR_CMN_ERR cmn_rc = COMM_MGR_CMN_SUCCESS;

    if(cid > COMM_MGR_LIB_MAX_CLIENTS) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR;
    }

    max_sd = __comm_mgr_lib_clients[cid].client_ptr->__fd;

    COMM_MGR_LIB_DEBUG("Listen FD[%d] for ClientID [%d]", max_sd, cid);

    working_read_fd = &(__comm_mgr_lib_clients[cid].client_ptr->__working_read_fd);
    working_write_fd = &(__comm_mgr_lib_clients[cid].client_ptr->__working_write_fd); 


    // Note : Only one FD per client, where the activity has to be monitored
    /*************************************************************/
    /*Loop waiting for for incoming data on the connected socket */
    /*************************************************************/
    do {
        /*************************************************************/
        /* Initialize the timeval struct to libInactivityTimeOut 	 */
        /* minutes.  If no activity after libInactivityTimeOut 	 	 */
        /* minutes this program will end.           			     */
        /*************************************************************/
        timeout.tv_sec  = __comm_mgr_lib_clients[cid].property->libInactivityTimeOut;
        timeout.tv_usec = 0;

        FD_ZERO(working_read_fd);
        FD_ZERO(working_write_fd);

        /**********************************************************/
        /* Copy the master fd_set over to the working fd_set.     */
        /**********************************************************/
        FD_SET(__comm_mgr_lib_clients[cid].client_ptr->__fd, working_read_fd);	
            
        // Set the write FD only when, there is something to send from SEND_DSID
        if((!utils_ds_queue_is_empty(__comm_mgr_lib_clients[cid].client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO_SEND])) ||
            (!utils_ds_queue_is_empty(__comm_mgr_lib_clients[cid].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_SEND]))){
            COMM_MGR_LIB_DEBUG("Data is available on DSID");
            FD_SET(__comm_mgr_lib_clients[cid].client_ptr->__fd, working_write_fd);	
        }

        /**********************************************************/
        /* Call select() and wait libInactivityTimeOut   	      */
        /**********************************************************/
        if((__comm_mgr_lib_clients[cid].property) && 
            (__comm_mgr_lib_clients[cid].property->libInactivityTimeOut < 1)) { // Forever
            rc = select(max_sd + 1, working_read_fd, working_write_fd, NULL, NULL);
        } else {
            rc = select(max_sd + 1, working_read_fd, working_write_fd, NULL, &timeout);
        }
                
        /**********************************************************/
        /* Check to see if the select call failed.                */
        /**********************************************************/
        if (rc < 0) {
            COMM_MGR_LIB_ERROR("select() failed");
            rc = COMM_MGR_LIB_SELECT_ERR;
            goto cleanup_and_exit;
        }

        // Control comes here when timeouts OR when a activity is found on the fds

        // Now check if the client FD is set
        if (FD_ISSET(__comm_mgr_lib_clients[cid].client_ptr->__fd, working_read_fd)) {
            do {
                if(__comm_mgr_lib_clients[cid].ancillary == FALSE) {
                    cmn_rc = comm_mgr_recv(__comm_mgr_lib_clients[cid].client_ptr->__fd, COMM_MGR_FLAG_MODE_NORMAL, &recv_msg, &num_recv_msgs);
                } else {
                    cmn_rc = comm_mgr_recv(__comm_mgr_lib_clients[cid].client_ptr->__fd, 
                            COMM_MGR_FLAG_MODE_FD | COMM_MGR_FLAG_MODE_VECTOR, &recv_msg, &num_recv_msgs);
                }

                if (cmn_rc == COMM_MGR_CMN_FAILURE) {
                    if ((errno != EAGAIN) && (errno != EWOULDBLOCK))  {
                            COMM_MGR_LIB_ERROR("recv() failed");
                            goto cleanup_and_exit;
                    }
                    break;
                }
                if(cmn_rc == COMM_MGR_CMN_PEER_DOWN) {
                    COMM_MGR_LIB_ERROR("The Communication Manager Server has shutdown. Exiting");
                    goto cleanup_and_exit;
                } else if (cmn_rc != COMM_MGR_CMN_SUCCESS) { // Invalid args etc
                    COMM_MGR_LIB_ERROR("Unknown receive failure");
                    break;
                }

                // Enqueue the received data to proto/data DSID.
				for (uint8_t i = 0; i < num_recv_msgs; i++) { 
                	__comm_mgr_lib_receive_packets(id, recv_msg[i]);
				}
            } while(cmn_rc == COMM_MGR_CMN_SUCCESS);	
        }

        // Check if the FD is writable
        if (FD_ISSET(__comm_mgr_lib_clients[cid].client_ptr->__fd , working_write_fd)) {
            do {
                // Check the send DSID if something is available to be sent. But priotize PROTO packets
                if(!utils_ds_queue_is_empty(__comm_mgr_lib_clients[cid].client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO_SEND])) {
                     msg = (COMM_MGR_MSG *)utils_ds_queue_dequeue( \
                                __comm_mgr_lib_clients[cid].client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO_SEND]);
                } else if (!utils_ds_queue_is_empty(__comm_mgr_lib_clients[cid].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_SEND])) {
                     msg = (COMM_MGR_MSG *)utils_ds_queue_dequeue( \
                                __comm_mgr_lib_clients[cid].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_SEND]);		                   
                } else { // If DSID is empty, abort sending till there is some activity on one of the DSIDs
                    FD_ZERO(working_write_fd);
                    break;                   
                }

                if(msg == NULL) { // If DSID is empty, abort sending till there is some activity on this DSID
                    FD_ZERO(working_write_fd);
                    break;
                }
                
                if(__comm_mgr_lib_clients[cid].ancillary == FALSE) {
                    cmn_rc = comm_mgr_send(__comm_mgr_lib_clients[cid].client_ptr->__fd, COMM_MGR_FLAG_MODE_NORMAL, msg);
                } else {
                    cmn_rc = comm_mgr_send(__comm_mgr_lib_clients[cid].client_ptr->__fd, 
                                            COMM_MGR_FLAG_MODE_FD | COMM_MGR_FLAG_MODE_VECTOR, msg); 
                }
                
                if (cmn_rc == COMM_MGR_CMN_FAILURE) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        COMM_MGR_LIB_TRACE("Communication Manager is not ready right now, try again later");
                        break; // Its okay. But should we enqueue the msg back to queue to try again later
                    } else {
                        COMM_MGR_LIB_ERROR("Error in sending");
                        break; // This is very bad case. Handle it
                    }
                } else if(cmn_rc == COMM_MGR_CMN_PEER_DOWN) {
                    COMM_MGR_LIB_TRACE("Communication Manager cannot accept data right now, try again later");
                    break; // Its okay. But should we enqueue the msg back to queue to try again later
                } else if (cmn_rc != COMM_MGR_CMN_SUCCESS) { // Invalid args etc
                    COMM_MGR_LIB_ERROR("Unknown send failure");
                    break;
                }

                if(cmn_rc == COMM_MGR_CMN_SUCCESS) {
                    COMM_MGR_LIB_DEBUG("CID[%d]: Sent the message, type [%d], subtype [%d] to Communication Manager successfully",
                                            cid, msg->hdr.msg_type, msg->hdr.submsg_type);
                }
            } while(cmn_rc == COMM_MGR_CMN_SUCCESS);
        }

        // Update the library status periodically
        if(utils_ds_queue_is_empty(__comm_mgr_lib_clients[cid].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_RECV])) {
            __comm_mgr_lib_update_status(cid, COMM_MGR_LIB_STATUS_GRP_DATA, COMM_MGR_LIB_DATA_STATUS_EMPTY);
        } else  if(utils_ds_queue_is_full(__comm_mgr_lib_clients[cid].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_RECV])) {
            __comm_mgr_lib_update_status(cid, COMM_MGR_LIB_STATUS_GRP_DATA, COMM_MGR_LIB_DATA_STATUS_FULL);
        } 
        
    } while(end_lib == FALSE);

cleanup_and_exit:
    /*************************************************************/
    /* Clean up the socket which is open                         */
    /*************************************************************/
    close(__comm_mgr_lib_clients[cid].client_ptr->__fd);
    
    return rc;
}

/*
    This function updates various status flags related to the Communication Manager library.

    <TODO> Implement Single Writer-Multiple Reader with Writer Priority

*/
static COMM_MGR_LIB_ERR __comm_mgr_lib_update_status(uint8_t cid, COMM_MGR_LIB_STATUS_GRP grp, uint8_t status) {

    switch(grp) {
        case COMM_MGR_LIB_STATUS_GRP_DATA:
            __comm_mgr_lib_status[cid].comm_mgr_lib_data_recv_status = status;            
            break;
        case COMM_MGR_LIB_STATUS_GRP_GENERIC:
            __comm_mgr_lib_status[cid].comm_mgr_lib_generic_status = status;
            break;
        case COMM_MGR_LIB_STATUS_GRP_ERROR:
            __comm_mgr_lib_status[cid].comm_mgr_lib_error_status = status; 
            break;
        default:
            return COMM_MGR_LIB_UNKNOWN_STATUS_GRP;
    }
    return COMM_MGR_LIB_SUCCESS;
}

