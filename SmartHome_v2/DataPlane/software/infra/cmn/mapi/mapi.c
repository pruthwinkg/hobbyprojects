/*****************************************************************************
    Description: MAPI library

******************************************************************************/

#include "mapi.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <sys/epoll.h> // Include for epoll

boolean mapi_initialized = FALSE;
boolean __mapi_usage_started = FALSE; // Internal flag to check if the usage has started
MAPI_INTERNAL_INFO **mapi_internal_info_map;
uint16_t mapi_src_uid;
uint32_t mapi_src_ip;
uint8_t mapi_max_mids;
uint8_t mapi_curr_mids;
utils_id_mgr_token mapi_id_mgr_token;

static boolean mapi_is_valid_msg(MAPI_MSG *msg, int len);

/*****************************************************************************
                                Function  Defintions
******************************************************************************/
void mapi_init(LOG_LEVEL level, uint8_t max_mids, uint16_t src_uid, uint32_t src_ip) {
    if(mapi_initialized == TRUE) {
        return;
    }

    log_lib_init(NULL, level);
    utils_ds_init(UTILS_DS_LIB_MODE_MIXED, 0); // Need the support of utils data structures library

    if(max_mids > MAPI_MAX_MIDS) {
        MAPI_LOG_ERROR("Invalid max_mids value passed. MAPI lib supports only %d mids per application", MAPI_MAX_MIDS);
        return;
    } 
    mapi_internal_info_map = (MAPI_INTERNAL_INFO **)malloc(sizeof(MAPI_INTERNAL_INFO *) * max_mids);
    memset(mapi_internal_info_map, NULL, sizeof(MAPI_INTERNAL_INFO *) * max_mids);
    mapi_src_uid = src_uid;
    mapi_src_ip = src_ip;
    mapi_max_mids = max_mids;
    mapi_curr_mids = 0;

    utils_id_mgr_init(max_mids, 0, &mapi_id_mgr_token); // Used for id management

    mapi_initialized = TRUE;
}

/*
    The apps can call this function to create MAPI IDs
*/
mapiID mapi_create_mid(MAPI_USER_INFO *user_info) {
    if(mapi_initialized == FALSE) {
        MAPI_LOG_ERROR("MAPI not initialized");
        return MAPI_INVALID_ID;
    }
    __mapi_usage_started = TRUE;

    uint32_t max_packet_size = 0;

    if(user_info == NULL) {
        MAPI_LOG_ERROR("Invalid user info passed");
        return MAPI_INVALID_ID;
    }
    if(mapi_curr_mids >= mapi_max_mids) {
        MAPI_LOG_ERROR("Max MAPI IDs reached. Max supported MAPI IDs for this UID [%d]= %d", mapi_src_uid, mapi_max_mids);
        return MAPI_INVALID_ID;
    }

    if(user_info->num_sub_mids >= MAPI_MAX_SUB_MIDS) {
        MAPI_LOG_ERROR("Invalid num_sub_mids value passed. Supported values are [0-%d]", MAPI_MAX_SUB_MIDS-1);
        return MAPI_INVALID_ID;
    }
    if(user_info->rcv_cb == NULL) {
        MAPI_LOG_ERROR("Receive callback function not set\n");
        return MAPI_INVALID_ID;
    }

    MAPI_INTERNAL_INFO *mapi_internal_info = (MAPI_INTERNAL_INFO *)malloc(sizeof(MAPI_INTERNAL_INFO));
    mapiID mid = (mapiID)utils_id_mgr_alloc(mapi_id_mgr_token);
    if(mid == UTILS_ID_MGR_INVALID_ID) {
        MAPI_LOG_ERROR("Failed to allocate MAPI ID");
        return MAPI_INVALID_ID;
    }
    mapi_internal_info_map[mid] = mapi_internal_info;

    mapi_internal_info->mapi_id = (mapi_src_uid << 16) | mid;
    mapi_internal_info->sock_type = user_info->sock_type;
    mapi_internal_info->num_sub_mids = user_info->num_sub_mids;
    mapi_internal_info->num_ports = user_info->num_ports;
    mapi_internal_info->src_ports = (uint16_t *)malloc(sizeof(uint16_t) * user_info->num_ports);
    memcpy(mapi_internal_info->src_ports, user_info->port_nums, sizeof(uint16_t) * user_info->num_ports);
    mapi_internal_info->nonblockingIO = user_info->nonblockingIO;
    mapi_internal_info->reuseaddr = user_info->reuseaddr;
    mapi_internal_info->internal_fd = mapi_open_internal_socket(mapi_internal_info);
    mapi_internal_info->external_fds = mapi_open_external_sockets(mapi_internal_info);
    mapi_internal_info->internal_max_packet_size = MAPI_DEFAULT_INTERNAL_PKT_SIZE;
    mapi_internal_info->external_max_packet_size = MAPI_DEFAULT_EXTERNAL_PKT_SIZE;
    mapi_internal_info->use_epoll = user_info->use_epoll;
    mapi_internal_info->rcv_cb = user_info->rcv_cb;
    if (user_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_STREAM) {
        mapi_internal_info->stream_info = (MAPI_STREAM_INTERNAL_INFO *)malloc(sizeof(MAPI_STREAM_INTERNAL_INFO));
        memset(mapi_internal_info->stream_info, 0, sizeof(MAPI_STREAM_INTERNAL_INFO));
        // Default stream storage type with unlimited size
        __mapi_set_stream_storage_type(mapi_internal_info, MAPI_STREAM_STORE_LINKEDLIST, 0); 
        
    } else {
        mapi_internal_info->stream_info = NULL; // No need of stream_info for DGRAM type
    }
    //mapi_internal_info->libInactivityTimeOut = MAPI_DEFAULT_SELECT_TIMEOUT * 60;
    mapi_internal_info->libInactivityTimeOut = -1; // Forever
    if(mapi_internal_info->internal_max_packet_size > mapi_internal_info->external_max_packet_size) {
        max_packet_size = mapi_internal_info->internal_max_packet_size;
    } else {
        max_packet_size = mapi_internal_info->external_max_packet_size;
    }
    mapi_internal_info->buffer = malloc(sizeof(char) * max_packet_size);

    mapi_internal_info->adv_config = (void *)__mapi_create_adv_config(mapi_internal_info->mapi_id, user_info->adv_config);

    mapi_curr_mids++;

    return mapi_internal_info->mapi_id;
}

MAPI_LIB_ERR mapi_set_internal_packet_size(mapiID mid, uint16_t size) {
    if((size < 10) || (size > 60 * 1024)) {
        MAPI_LOG_ERROR("Invalid size. Accepted values in the range [10-60k]");
        return MAPI_LIB_INVALID_ARG; 
    }
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];
    mapi_internal_info->internal_max_packet_size = size;
    return MAPI_LIB_SUCCESS;
}

MAPI_LIB_ERR mapi_set_external_packet_size(mapiID mid, uint16_t size) {
    if((size < 10) || (size > 60 * 1024)) {
        MAPI_LOG_ERROR("Invalid size. Accepted values in the range [10-60k]");
        return MAPI_LIB_INVALID_ARG; 
    }
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];
    mapi_internal_info->internal_max_packet_size = size;
    return MAPI_LIB_SUCCESS;
}

/*
    Apps needs to call this function preferably in a seperate thread to start the MAPI ID,
    so that it can send/receive on this MAPI ID
*/
MAPI_LIB_ERR mapi_start_mid(mapiID mid) {
    MAPI_LIB_ERR rc;
    if(mapi_initialized == FALSE) {
        MAPI_LOG_ERROR("MAPI not initialized");
        return MAPI_LIB_INIT_FAILURE;
    }

   rc = mapi_communicator(mapi_internal_info_map[MAPI_GET_MID(mid)]);
}

/*
    This function will open an internal or external stream depending on the 
    information provided in the dst_info

    dst_ip       dst_port   stream type
     0             X        internal
     localhost     0        internal
     localhost     >0       external
     <ip>          X        external
*/
MAPI_LIB_ERR mapi_start_stream(mapiID mid, MAPI_DEST_INFO *dst_info) {

    if(mapi_initialized == FALSE) {
        MAPI_LOG_ERROR("MAPI not initialized");
        return MAPI_LIB_INIT_FAILURE;
    }

    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];
    if(mapi_internal_info == NULL) {
        MAPI_LOG_ERROR("Invalid MAPI ID passed");
        return MAPI_LIB_INVALID_ARG;
    }

    // Always open an internal stream
    if(dst_info->dst_ip == 0) {
        if(mapi_open_internal_stream(mid, (struct __mapi_dest_info *)dst_info) < 0) {
            MAPI_LOG_ERROR("Failed open internal stream for MAPI ID = %d", mid);
            return MAPI_LIB_STREAM_START_ERR;
        }       
    } else if(dst_info->dst_ip == MAPI_LOCALHOST) { // Open an internal stream
        if(dst_info->dst_port == 0) {
            if(mapi_open_internal_stream(mid, (struct __mapi_dest_info *)dst_info) < 0) {
                MAPI_LOG_ERROR("Failed open internal stream for MAPI ID = %d", mid);
                return MAPI_LIB_STREAM_START_ERR;
            }
        } else { // By setting port num to non-zero on local-host external stream could be opened to it
            if(mapi_open_external_stream(mid, (struct __mapi_dest_info *)dst_info) < 0) {
                MAPI_LOG_ERROR("Failed open external stream for MAPI ID = %d", mid);
                return MAPI_LIB_STREAM_START_ERR;
            }
        }
    } else { // Open an external stream 
        if(mapi_open_external_stream(mid, (struct __mapi_dest_info *)dst_info) < 0) {
            MAPI_LOG_ERROR("Failed open external stream for MAPI ID = %d", mid);
            return MAPI_LIB_STREAM_START_ERR;
        }
    }
    
    mapi_internal_info->stream_info->num_streams++;

    return MAPI_LIB_SUCCESS;
}

/*
    Stop internal/external stream for this dst_info using the same rule used while
    starting the stream
*/
MAPI_LIB_ERR mapi_stop_stream(mapiID mid, MAPI_DEST_INFO *dst_info) {
    if(mapi_initialized == FALSE) {
        MAPI_LOG_ERROR("MAPI not initialized");
        return MAPI_LIB_INIT_FAILURE;
    }

    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];
    if(mapi_internal_info == NULL) {
        MAPI_LOG_ERROR("Invalid MAPI ID passed");
        return MAPI_LIB_INVALID_ARG;
    }

    if(dst_info->dst_ip == 0) {
        if(mapi_close_internal_stream(mid, (struct __mapi_dest_info *)dst_info) < 0) {
            MAPI_LOG_ERROR("Failed close internal stream for MAPI ID = %d", mid);
            return MAPI_LIB_STREAM_STOP_ERR;
        }
    } else if(dst_info->dst_ip == MAPI_LOCALHOST) {
        if(dst_info->dst_port == 0) {
            if(mapi_close_internal_stream(mid, (struct __mapi_dest_info *)dst_info) < 0) {
                MAPI_LOG_ERROR("Failed close internal stream for MAPI ID = %d", mid);
                return MAPI_LIB_STREAM_STOP_ERR;
            }
        } else {
            if(mapi_close_external_stream(mid, (struct __mapi_dest_info *)dst_info) < 0) {
                MAPI_LOG_ERROR("Failed close external stream for MAPI ID = %d", mid);
                return MAPI_LIB_STREAM_STOP_ERR;
            }
        }
    } else {
        if(mapi_close_external_stream(mid, (struct __mapi_dest_info *)dst_info) < 0) {
            MAPI_LOG_ERROR("Failed close external stream for MAPI ID = %d", mid);
            return MAPI_LIB_STREAM_STOP_ERR;
        }
    }

    mapi_internal_info->stream_info->num_streams--;

    return MAPI_LIB_SUCCESS;
}

MAPI_LIB_ERR mapi_set_stream_store_type(mapiID mid, uint8_t type, uint16_t size) {
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];

    if(mapi_internal_info == NULL) {
        MAPI_LOG_ERROR("Invalid MAPI ID passed");
        return MAPI_LIB_INVALID_ARG;
    }

    if(__mapi_set_stream_storage_type(mapi_internal_info, type, size) == -1) {
        MAPI_LOG_ERROR("Failed to change the stream storage type for the MAPI ID");
        return MAPI_LIB_STREAM_STORE_TYPE_ERR; 
    }

    return MAPI_LIB_SUCCESS;
}

/*
    This function will decide whether to send via internal or external fd
    based on the dst_ip, dst_port, dst_uid
*/
MAPI_LIB_ERR mapi_send(mapiID mid, MAPI_DEST_INFO *dst_info, uint32_t messageCode, char *msg, uint32_t len, MAPI_SEND_OPTIONS *options) {                       
    if(mapi_initialized == FALSE) {
        MAPI_LOG_ERROR("MAPI not initialized");
        return MAPI_LIB_INIT_FAILURE;
    }

    struct sockaddr_in inremaddr; /* remote address */
    struct sockaddr_un unremaddr; /* remote address */
    struct sockaddr *addr;
    socklen_t addrlen;            /* length of addresses */
    int send_count = 0;
    int send_fd;
    int16_t src_port; //This will be set depending on what the user provided.
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];
    
    if(mapi_internal_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_STREAM) {
        addrlen = sizeof(inremaddr);
        send_fd = __mapi_get_stream_fd(mid, (struct __mapi_dest_info *)dst_info); 
        if(send_fd < 0) {
            return MAPI_LIB_SEND_ERR;
        }
        addr = NULL; // For connected sockets when using sendto()
        addrlen = 0; // For connected sockets when using sendto()
    } else if(mapi_internal_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_DGRAM) {
        // Check if it is internal or external destination
        if((dst_info->dst_ip == MAPI_LOCALHOST) || (dst_info->dst_ip == 0)) {
            __mapi_get_internal_uds_file(MAPI_GET_UID(dst_info->dst_mid), dst_info->dst_sub_mid, unremaddr.sun_path);
            unremaddr.sun_family = AF_UNIX;
            addrlen = sizeof(unremaddr);
            send_fd = mapi_internal_info->internal_fd;
            addr = (struct sockaddr *)&unremaddr;
            src_port = 0; // Internal communication, no port needed
        } else {
            // If a src port is specified, use it. Else we let the library chose it.
            if(options && (options->src_port != 0))
            {
                //TODO check if it is a valid port, else return error.
                src_port = options->src_port;
                
                // Check if the port is in the list of the allocated ports.
                if(utils_is_int_in_array(options->src_port, mapi_internal_info->src_ports, mapi_internal_info->num_ports) == FALSE)
                {
                    MAPI_LOG_ERROR("The port %d is not a valid source port for this MAPI ID", options->src_port);
                    return MAPI_LIB_INVALID_ARG;
                }
                //TODO: Check if the port is being used.
                for(int j = 0; j < mapi_internal_info->num_ports; j++) {
                    if(mapi_internal_info->src_ports[j] == options->src_port) {
                        send_fd = mapi_internal_info->external_fds[j];
                        break;
                    }
                }
            } else {
                send_fd = __mapi_get_dgram_external_fd_for_sending(mapi_internal_info, dst_info);
                if(send_fd == -1) {
                    MAPI_LOG_ERROR("No external fd available for %d", dst_info->dst_port);
                    return MAPI_LIB_INVALID_ARG;
                }
            }

            // External destination (UDP)
            memset(&inremaddr, 0, sizeof(inremaddr));
            inremaddr.sin_family = AF_INET;
            inremaddr.sin_port = htons(dst_info->dst_port);
            inremaddr.sin_addr.s_addr = dst_info->dst_ip;

            addrlen = sizeof(inremaddr);
            addr = (struct sockaddr *)&inremaddr;
        }
    }

    uint32_t buflen = mapi_create_msg(mapi_internal_info, dst_info, options, messageCode, msg, len);

    send_count = sendto(send_fd, mapi_internal_info->buffer, buflen, 0, addr, addrlen);
    if(send_count < 0) {
        return MAPI_LIB_SEND_ERR; 
    } else if (send_count == 0) {
        return MAPI_LIB_PEER_DOWN;
    }
    
    return MAPI_LIB_SUCCESS;
}

void mapi_destroy(mapiID mid) {
    if(mapi_initialized == FALSE) {
        MAPI_LOG_ERROR("MAPI not initialized");
        return;
    }
    char socketfile[512];
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];
    __mapi_get_internal_uds_file(mapi_src_uid, MAPI_GET_MID(mid), socketfile);
    unlink(socketfile);
    close(mapi_internal_info->internal_fd);
    for(int i = 0; i < mapi_internal_info->num_ports; i++) {
        if(mapi_internal_info->external_fds[i] >= 0) {
            close(mapi_internal_info->external_fds[i]); // Close each valid fd
        }
    }
    free(mapi_internal_info->external_fds);
    free(mapi_internal_info->src_ports);
    if(mapi_internal_info->stream_info != NULL) {
        if(mapi_internal_info->stream_info->__DSID != 0) {
            utils_ds_queue_destroy(mapi_internal_info->stream_info->__DSID, TRUE);
        }         
        free(mapi_internal_info->stream_info);
    }

    free(mapi_internal_info->buffer);

    __mapi_delete_adv_config(mid);   
    free(mapi_internal_info);

    // This should be the last step
    utils_id_mgr_free(mapi_id_mgr_token, MAPI_GET_MID(mid)); // free up the ID    
    if(mapi_internal_info == NULL) {
        MAPI_LOG_ERROR("Invalid MAPI ID passed");            
        return;
    }

    mapi_curr_mids--;
    return;
}


/***********************************************************************************/
/*                          Internal Functions                                     */
/***********************************************************************************/
int mapi_open_internal_socket(MAPI_INTERNAL_INFO *mapi_internal_info) {
    int mapi_fd;
    mapiID mid = mapi_internal_info->mapi_id;
    int opt = TRUE;
    int rc;
    struct sockaddr_un un_addr;
    char socketfile[512];

    switch(mapi_internal_info->sock_type) {
        case MAPI_LIB_SOCK_TYPE_SOCK_DGRAM:        
            mapi_fd = socket(AF_UNIX, SOCK_DGRAM, 0); 
            break;
        case MAPI_LIB_SOCK_TYPE_SOCK_STREAM:
            mapi_fd = socket(AF_UNIX, SOCK_STREAM, 0);        
           break;
        default:
            MAPI_LOG_ERROR("Invalid sock type");
            return -1;               
    }
    
    if(mapi_internal_info->reuseaddr) {
        rc = setsockopt(mapi_fd, SOL_SOCKET,  SO_REUSEADDR,
                    (char *)&opt, sizeof(opt));
        if (rc < 0) {
            close(mapi_fd);
            return -1;
        }
    }

    if(mapi_internal_info->nonblockingIO == TRUE) {
        if(mapi_set_non_blocking_io(mapi_fd) != MAPI_LIB_SUCCESS) {
            MAPI_LOG_TRACE("Setting the socket %d in blocking mode", mapi_fd);
        }
    }

    __mapi_get_internal_uds_file(mapi_src_uid, MAPI_GET_MID(mid), socketfile);

    memset(&un_addr, 0, sizeof(un_addr));
    un_addr.sun_family = AF_UNIX;
    strcpy(un_addr.sun_path, socketfile);

    unlink(socketfile);

    rc = bind(mapi_fd, (struct sockaddr *)&un_addr, sizeof(un_addr));
    if (rc < 0) {
        close(mapi_fd);
        unlink(socketfile);
        return -1;
    }

    if(mapi_internal_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_STREAM) {
        rc = listen(mapi_fd, MAPI_SOCK_BACKLOG);
        if (rc < 0) {
            close(mapi_fd);
            unlink(socketfile);
            return -1;
        }
    }
   
    return mapi_fd;
}

int *mapi_open_external_sockets(MAPI_INTERNAL_INFO *mapi_internal_info) {
    int mapi_fd;
    mapiID mid = mapi_internal_info->mapi_id;
    int opt = TRUE;
    int rc;
    struct sockaddr_in in_addr;

    int *mapi_external_fds = (int *)malloc(sizeof(int) * mapi_internal_info->num_ports); // Allocate array of fds
    memset(mapi_external_fds, -1, sizeof(int) * mapi_internal_info->num_ports); // Initialize to invalid

    for(int i = 0; i < mapi_internal_info->num_ports; i++) {        
        switch(mapi_internal_info->sock_type) {
            case MAPI_LIB_SOCK_TYPE_SOCK_DGRAM:        
                mapi_fd = socket(AF_INET, SOCK_DGRAM, 0); 
                break;
            case MAPI_LIB_SOCK_TYPE_SOCK_STREAM:
                mapi_fd = socket(AF_INET, SOCK_STREAM, 0);        
            break;
            default:
                MAPI_LOG_ERROR("Invalid sock type");
                return -1;               
        }
        
        if(mapi_internal_info->reuseaddr) {
            rc = setsockopt(mapi_fd, SOL_SOCKET,  SO_REUSEADDR,
                        (char *)&opt, sizeof(opt));
            if (rc < 0) {
                close(mapi_fd);
                return -1;
            }
        }

        if(mapi_internal_info->nonblockingIO == TRUE) {
            if(mapi_set_non_blocking_io(mapi_fd) != MAPI_LIB_SUCCESS) {
                MAPI_LOG_TRACE("Setting the socket %d in blocking mode", mapi_fd);
            }
        }

        memset(&in_addr, 0, sizeof(in_addr));
        in_addr.sin_family = AF_INET;
        in_addr.sin_port = htons(mapi_internal_info->src_ports[i]);
        in_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        rc = bind(mapi_fd, (struct sockaddr *)&in_addr, sizeof(in_addr));
        if (rc < 0) {
            MAPI_LOG_ERROR("Failed to open external socket for port = %d", mapi_internal_info->src_ports[i]);
            close(mapi_fd);
            return -1;
        }

        if(mapi_internal_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_STREAM) {
            rc = listen(mapi_fd, MAPI_SOCK_BACKLOG);
            if (rc < 0) {
                MAPI_LOG_ERROR("Failed to open external socket for port = %d", mapi_internal_info->src_ports[i]);
                close(mapi_fd);
                return -1;
            }
        }
        mapi_external_fds[i] = mapi_fd;
    }
   
    return mapi_external_fds;  
}

int mapi_open_internal_stream(mapiID mid, struct __mapi_dest_info *dst_info) {
    struct sockaddr_un un_addr;
    int fd;
    char socketfile[512];

    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];

    if(mapi_internal_info->sock_type != MAPI_LIB_SOCK_TYPE_SOCK_STREAM) {
        MAPI_LOG_ERROR("Source MAPI ID is not of the STREAM type. Cannot start a stream");
        return MAPI_LIB_STREAM_START_ERR;
    }

    if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        MAPI_LOG_ERROR("Socket creation error");
        return -1;
    }
    if(__mapi_add_stream_fd(mid, (struct __mapi_dest_info *)dst_info, fd) == -1) {
        MAPI_LOG_ERROR("Failed to add the stream fd to the MAPI ID %d\n", mid);
        close(fd);
        return -1;
    }

    if(mapi_internal_info->nonblockingIO == TRUE) {
        if(mapi_set_non_blocking_io(fd) != MAPI_LIB_SUCCESS) {
            MAPI_LOG_TRACE("Setting the socket %d in blocking mode", fd);
        }
    }

    __mapi_get_internal_uds_file(dst_info->dst_uid, dst_info->dst_sub_mid, socketfile);
    memset(&un_addr, 0, sizeof(un_addr));
    un_addr.sun_family = AF_UNIX;
    strcpy(un_addr.sun_path, socketfile);

    if (connect(fd, (struct sockaddr*)&un_addr, sizeof(un_addr)) == -1) {
        MAPI_LOG_ERROR("Socket connect error");
        __mapi_del_stream_fd(mid, (struct __mapi_dest_info *)dst_info);
        close(fd);        
        return -1;
    }
    return fd;
}

int mapi_open_external_stream(mapiID mid, struct __mapi_dest_info *dst_info) {
    struct sockaddr_in in_addr;
    int fd;

    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];

    if(mapi_internal_info->sock_type != MAPI_LIB_SOCK_TYPE_SOCK_STREAM) {
        MAPI_LOG_ERROR("Source MAPI ID is not of the STREAM type. Cannot start a stream");
        return -1;
    }

    if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        MAPI_LOG_ERROR("Socket creation error");
        return -1;
    }
    if(__mapi_add_stream_fd(mid, (struct __mapi_dest_info *)dst_info, fd) == -1) {
        MAPI_LOG_ERROR("Failed to add the stream fd to the MAPI ID %d\n", mid);
        close(fd);
        return -1;
    }

    if(mapi_internal_info->nonblockingIO == TRUE) {
        if(mapi_set_non_blocking_io(fd) != MAPI_LIB_SUCCESS) {
            MAPI_LOG_TRACE("Setting the socket %d in blocking mode", fd);
        }
    }

    memset(&in_addr, 0, sizeof(in_addr));
    in_addr.sin_family = AF_INET;
    in_addr.sin_addr.s_addr = dst_info->dst_ip;
    in_addr.sin_port = htons(dst_info->dst_port);
    MAPI_LOG_DEBUG("Opening a stream to address : %s : %d",
            inet_ntoa(in_addr.sin_addr), dst_info->dst_port);

    if (connect(fd, (struct sockaddr*)&in_addr, sizeof(in_addr)) == -1) {
        MAPI_LOG_ERROR("Socket connect error");
        __mapi_del_stream_fd(mid, (struct __mapi_dest_info *)dst_info);
        close(fd);        
        return -1;
    }
    return fd;
}

int mapi_close_internal_stream(mapiID mid, struct __mapi_dest_info *dst_info) {
    struct sockaddr_un un_addr;
    int fd;
    char socketfile[512];

    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];

    if(mapi_internal_info->sock_type != MAPI_LIB_SOCK_TYPE_SOCK_STREAM) {
        MAPI_LOG_ERROR("Source MAPI ID is not of the STREAM type. Cannot stop the stream");
        return MAPI_LIB_STREAM_STOP_ERR;
    }

    fd = __mapi_del_stream_fd(mid, (struct __mapi_dest_info *)dst_info);
    if(fd == -1) {
        MAPI_LOG_ERROR("Failed to delete the stream fd to the MAPI ID %d\n", mid);        
        return -1;
    }
    close(fd);

    return 0;
}

int mapi_close_external_stream(mapiID mid, struct __mapi_dest_info *dst_info) {
    struct sockaddr_in in_addr;
    int fd;

    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];

    if(mapi_internal_info->sock_type != MAPI_LIB_SOCK_TYPE_SOCK_STREAM) {
        MAPI_LOG_ERROR("Source MAPI ID is not of the STREAM type. Cannot stop the stream");
        return -1;
    }

    fd = __mapi_del_stream_fd(mid, (struct __mapi_dest_info *)dst_info);
    if(fd == -1) {
        MAPI_LOG_ERROR("Failed to delete the stream fd to the MAPI ID %d\n", mid);        
        return -1;
    }
    close(fd);

    return 0;
}

MAPI_LIB_ERR mapi_set_non_blocking_io(int socket_fd) {
    int rc = 0;
    rc = fcntl(socket_fd, F_SETFL, (fcntl(socket_fd, F_GETFL, 0) | O_NONBLOCK));
    if (rc < 0) {
        MAPI_LOG_ERROR("Failed to set the socket %d to Non-blocking mode", socket_fd);
        return MAPI_LIB_INIT_FAILURE;
    }
    return MAPI_LIB_SUCCESS;
}

MAPI_LIB_ERR mapi_communicator(MAPI_INTERNAL_INFO *mapi_internal_info) {
    if(mapi_internal_info->use_epoll) {
        MAPI_LOG_DEBUG("Using the epoll based event handling mechansim");
        return __mapi_communicator_with_epoll(mapi_internal_info);
    } else {
        MAPI_LOG_DEBUG("Using the select based event handling mechansim");
        return __mapi_communicator_with_select(mapi_internal_info);
    }
    return MAPI_LIB_SUCCESS;
}


MAPI_LIB_ERR __mapi_communicator_with_epoll(MAPI_INTERNAL_INFO *mapi_internal_info) {
    int epoll_fd, num_events, i;
    struct epoll_event event, *events;
    int listen_internal_fd = mapi_internal_info->internal_fd;
    int *listen_external_fds = mapi_internal_info->external_fds;
    MAPI_LIB_ERR cmn_rc = MAPI_LIB_SUCCESS;
    boolean end_server = FALSE;

    // 1. Create the epoll instance
    epoll_fd = epoll_create1(0); // Use epoll_create1 for modern kernels
    if (epoll_fd == -1) {
        MAPI_LOG_ERROR("epoll_create1 failed: %s", strerror(errno));
        return MAPI_LIB_EPOLL_CREATE_ERR;
    }

    // 2. Prepare the event array
    events = calloc(MAPI_MAX_MIDS * 2, sizeof(struct epoll_event)); // Assuming a reasonable max number of connections
    if (events == NULL) {
        MAPI_LOG_ERROR("calloc for epoll events failed");
        close(epoll_fd);
        return MAPI_LIB_MEM_ALLOC_FAILURE;
    }

    // 3. Add the listening sockets to the epoll set
    if (listen_internal_fd >= 0) {
        event.data.fd = listen_internal_fd;
        event.events = EPOLLIN; // Watch for read events
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_internal_fd, &event) == -1) {
            MAPI_LOG_ERROR("epoll_ctl (internal_fd) failed: %s", strerror(errno));
            free(events);
            close(epoll_fd);
            return MAPI_LIB_EPOLL_CTL_ERR;
        }
    }

    for (i = 0; i < mapi_internal_info->num_ports; i++) {
        if (listen_external_fds[i] >= 0) {
            event.data.fd = listen_external_fds[i];
            event.events = EPOLLIN; // Watch for read events
            if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_external_fds[i], &event) == -1) {
                MAPI_LOG_ERROR("epoll_ctl (external_fd) failed: %s", strerror(errno));
                free(events);
                close(epoll_fd);
                return MAPI_LIB_EPOLL_CTL_ERR;
            }
        }
    }

    // 4. Event Loop
    while (!end_server) {
        // Wait for events
        num_events = epoll_wait(epoll_fd, events, MAPI_MAX_MIDS * 2, MAPI_DEFAULT_EPOLL_TIMEOUT * 60 *1000); // Timeout in milliseconds
        if (num_events == -1) {
            MAPI_LOG_ERROR("epoll_wait failed: %s", strerror(errno));
            break; // Exit on error
        }

        if(num_events == 0){
            MAPI_LOG_DEBUG("epoll_wait timed out. End program.");
            cmn_rc = MAPI_LIB_SERVER_TIMEOUT;
            goto cleanup_and_exit;
        }

        // Handle events
        for (i = 0; i < num_events; i++) {
            int current_fd = events[i].data.fd;

            // Handle Errors
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP)) {
                MAPI_LOG_ERROR("epoll event error on fd: %d", current_fd);
                 if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, current_fd, NULL) == -1) {
                    MAPI_LOG_ERROR("epoll_ctl del failed for fd %d : %s", current_fd, strerror(errno));
                 }
                close(current_fd);
                continue; // Go to the next event
            }

            //Check for readable event
            if(events[i].events & EPOLLIN) {
                if (__mapi_is_listening_socket(current_fd, listen_internal_fd, listen_external_fds, mapi_internal_info->num_ports)) {
                    // Handle new connections
                    if(mapi_internal_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_STREAM){
                       int new_fd;
                       do{
                            new_fd = accept(current_fd, NULL, NULL);
                            if (new_fd == -1) {
                                if (errno != EWOULDBLOCK && errno != EAGAIN) {
                                    MAPI_LOG_ERROR("accept failed: %s", strerror(errno));
                                }
                                break;
                            }

                            //set socket as non blocking if required
                            if(mapi_internal_info->nonblockingIO) {
                                if(mapi_set_non_blocking_io(new_fd) != MAPI_LIB_SUCCESS) {
                                    MAPI_LOG_TRACE("Setting the socket %d in blocking mode", new_fd);
                                }
                            }

                            // Add new fd to epoll list
                            event.data.fd = new_fd;
                            event.events = EPOLLIN | EPOLLHUP | EPOLLERR; // Watch for read events, hangup and error
                            if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_fd, &event) == -1) {
                                MAPI_LOG_ERROR("epoll_ctl (new_fd) failed: %s", strerror(errno));
                                close(new_fd);
                            }
                       } while(new_fd != -1);

                    } else if(mapi_internal_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_DGRAM) {
                        cmn_rc = mapi_lib_recv(current_fd, mapi_internal_info);
                         if(cmn_rc == MAPI_LIB_RECV_ERR) {
                            MAPI_LOG_ERROR("recv() failed");
                         }
                    }

                } else {
                    // Handle data on existing connection
                    boolean close_conn = FALSE;
                     do {
                        cmn_rc = mapi_lib_recv(current_fd, mapi_internal_info);
                        if(cmn_rc == MAPI_LIB_RECV_ERR) {
                            if (errno != EWOULDBLOCK && errno != EAGAIN) {
                                MAPI_LOG_ERROR("recv() failed on fd %d : %s", current_fd, strerror(errno));
                                close_conn = TRUE;
                            }
                            break;
                        }

                        if(cmn_rc == MAPI_LIB_PEER_DOWN) {
                            MAPI_LOG_TRACE("Peer connection closed on fd: %d", current_fd);
                            close_conn = TRUE;
                            break;
                        }
                    } while(TRUE);

                     if(close_conn) {
                        if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, current_fd, NULL) == -1) {
                            MAPI_LOG_ERROR("epoll_ctl del failed for fd %d : %s", current_fd, strerror(errno));
                        }
                        close(current_fd);
                     }
                }
            }
           
        }
    }

cleanup_and_exit:
    // 5. Cleanup
    free(events);
    close(epoll_fd);
    return cmn_rc;
}

MAPI_LIB_ERR __mapi_communicator_with_select(MAPI_INTERNAL_INFO *mapi_internal_info) {
    fd_set  *working_read_fd, master_set;
    struct timeval  timeout;
    int new_fd, rc = 0, i = 0, close_conn;
    int listen_internal_fd = mapi_internal_info->internal_fd;
    int *listen_external_fds = mapi_internal_info->external_fds;
    uint32_t default_select_timeout = MAPI_DEFAULT_SELECT_TIMEOUT;
    boolean end_lib = FALSE;
    int desc_ready;
    MAPI_LIB_ERR cmn_rc = MAPI_LIB_SUCCESS;
    boolean end_server = FALSE;

    // Find the max fd
    mapi_internal_info->max_fd = __mapi_get_max_fd(mapi_internal_info);

    working_read_fd = &mapi_internal_info->__working_read_fd;
    FD_ZERO(&master_set);
    if(mapi_internal_info->internal_fd >= 0) {
        listen_internal_fd = mapi_internal_info->internal_fd;
        FD_SET(listen_internal_fd, &master_set);
    }
    for (int j = 0; j < mapi_internal_info->num_ports; j++) {
        if (listen_external_fds[j] >= 0) {
            FD_SET(listen_external_fds[j], &master_set);
        }
    }   

    timeout.tv_sec  = mapi_internal_info->libInactivityTimeOut;
    timeout.tv_usec = 0;
    do {
        FD_ZERO(working_read_fd);
        memcpy(working_read_fd, &master_set, sizeof(master_set));
        
        if(mapi_internal_info->libInactivityTimeOut < 0) { // Forever
            rc = select(mapi_internal_info->max_fd + 1, working_read_fd, NULL, NULL, NULL);
        } else {
            rc = select(mapi_internal_info->max_fd + 1, working_read_fd, NULL, NULL, &timeout);
        }

        if(rc < 0) {
            MAPI_LOG_ERROR("select() failed");
            rc = MAPI_LIB_SELECT_ERR;
            goto cleanup_and_exit;
        }
        if(rc == 0) {
            MAPI_LOG_ERROR("select() timed out.  End program.");
            rc = MAPI_LIB_SERVER_TIMEOUT;
            goto cleanup_and_exit;
        }

        desc_ready = rc;
        for (i=0; i <= mapi_internal_info->max_fd && desc_ready > 0; ++i) {
            if (FD_ISSET(i, working_read_fd)) {
                desc_ready -= 1;
                //Check if it is a listening socket
                if (__mapi_is_listening_socket(i, listen_internal_fd, listen_external_fds, mapi_internal_info->num_ports)) {
                    if(mapi_internal_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_STREAM) {
                        MAPI_LOG_TRACE("Listening socket is readable");                        
                        rc = __mapi_communicator_with_select_accept(&master_set, i, mapi_internal_info);
                        if(rc == MAPI_LIB_SOCKET_ACCEPT_ERR) {
                            MAPI_LOG_ERROR("accept() failed");
                            end_server = TRUE;
                        }
                    } else if(mapi_internal_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_DGRAM) {
                        cmn_rc = mapi_lib_recv(i, mapi_internal_info);
                        if(cmn_rc == MAPI_LIB_RECV_ERR) {
                            MAPI_LOG_ERROR("recv() failed");
                        }
                    }
                } else {
                    MAPI_LOG_DEBUG("Descriptor %d is readable", i);
                    close_conn = FALSE;
                    do {
                        cmn_rc = mapi_lib_recv(i, mapi_internal_info);
                        if(cmn_rc == MAPI_LIB_RECV_ERR) {
                            if (errno != EWOULDBLOCK) {
                                MAPI_LOG_ERROR("recv() failed");
                                close_conn = TRUE;
                            }
                            break;
                        }

                        if(cmn_rc == MAPI_LIB_PEER_DOWN) {
                            MAPI_LOG_TRACE("Peer connection closed");
                            close_conn = TRUE;
                            break;
                        }
                    } while(TRUE);

                    if(close_conn) {
                        close(i);
                        FD_CLR(i, &master_set);
                        if (i == mapi_internal_info->max_fd) {
                            while (FD_ISSET(mapi_internal_info->max_fd, &master_set) == FALSE) {
                                mapi_internal_info->max_fd -= 1;
                            }
                        }
                    }
                }
            } /* End of if (FD_ISSET(i, &working_read_fd)) */
        } /* End of loop through selectable descriptors */        
    } while(end_server == FALSE);
    
cleanup_and_exit:
    for (i=0; i <= mapi_internal_info->max_fd; ++i) {
        if (FD_ISSET(i, &master_set)) {
            close(i);
        }
    }
    return rc;
}

MAPI_LIB_ERR __mapi_communicator_with_select_accept(fd_set *master_set, int listen_fd, 
                                                    MAPI_INTERNAL_INFO *mapi_internal_info) {
    int new_fd;
    MAPI_LIB_ERR rc = MAPI_LIB_SUCCESS;

    do {
        new_fd = accept(listen_fd, NULL, NULL);
        if(new_fd < 0) {
            if(errno != EWOULDBLOCK) {
                MAPI_LOG_ERROR("accept() failed");
                rc = MAPI_LIB_SOCKET_ACCEPT_ERR;
            }
            break;
        }
        if(mapi_internal_info->nonblockingIO == TRUE) {
            if(mapi_set_non_blocking_io(new_fd) != MAPI_LIB_SUCCESS) {
                MAPI_LOG_TRACE("Setting the socket %d in blocking mode", new_fd);
            }                               
        }
        MAPI_LOG_DEBUG("New incoming connection - %d", new_fd);
        FD_SET(new_fd, master_set);
        if(new_fd > mapi_internal_info->max_fd) {
            mapi_internal_info->max_fd = new_fd;
        }
    } while(new_fd != -1);
    return rc;
}

MAPI_LIB_ERR mapi_lib_recv(int fd, MAPI_INTERNAL_INFO *mapi_internal_info) {
    struct sockaddr_in remaddr; /* remote address */
    socklen_t addrlen = sizeof(remaddr);            /* length of addresses */
    int recvlen;                    /* # bytes received */

    if(mapi_internal_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_STREAM) {
        recvlen = recv(fd, mapi_internal_info->buffer, mapi_internal_info->internal_max_packet_size, 0);        
    } else if (mapi_internal_info->sock_type == MAPI_LIB_SOCK_TYPE_SOCK_DGRAM) {
        recvlen = recvfrom(fd, mapi_internal_info->buffer, mapi_internal_info->internal_max_packet_size, 0, 
                            (struct sockaddr *)&remaddr, &addrlen);       
    }                            

    if(recvlen > 0) {
        if(mapi_is_valid_msg((MAPI_MSG *)mapi_internal_info->buffer, recvlen) == FALSE) {
            MAPI_LOG_ERROR("Received invalid MAPI packet");
            return MAPI_LIB_BAD_MSG;
        }       
        mapi_internal_info->rcv_cb(mapi_internal_info->buffer, recvlen);
    } else if(recvlen == 0) {
        return MAPI_LIB_PEER_DOWN;
    } else {
        return MAPI_LIB_RECV_ERR;
    }

    return MAPI_LIB_SUCCESS;    
}

uint32_t mapi_create_msg(MAPI_INTERNAL_INFO *mapi_internal_info,
                          MAPI_DEST_INFO *dst_info, MAPI_SEND_OPTIONS *options,
                          uint32_t messageCode, char *msg, uint32_t len) {
    MAPI_MSG *mapi_msg = (MAPI_MSG *)mapi_internal_info->buffer;
    if(mapi_msg == NULL) {
        MAPI_LOG_ERROR("Failed to create the MAPI message");
        return 0;
    }
    memset(mapi_msg, 0, sizeof(MAPI_MSG));

    mapi_msg->hdr.magic = MAPI_MSG_HDR_MAGIC;
    mapi_msg->hdr.major_ver = MAPI_MSG_HDR_MAJOR_VER;
    mapi_msg->hdr.minor_ver = MAPI_MSG_HDR_MINOR_VER;
    mapi_msg->hdr.dst_ip = dst_info->dst_ip;
    mapi_msg->hdr.src_ip = mapi_src_ip;
    mapi_msg->hdr.dst_port = dst_info->dst_port;
    if(mapi_internal_info->num_ports > 0) { // In mapi send api, if the src port is not specified, use the first port
        mapi_msg->hdr.src_port = mapi_internal_info->src_ports[0]; // By default use the first port
    } else {
        mapi_msg->hdr.src_port = 0;
    }
    mapi_msg->hdr.dst_mid = dst_info->dst_mid;
    mapi_msg->hdr.dst_sub_mid = dst_info->dst_sub_mid;
    mapi_msg->hdr.src_mid = mapi_internal_info->mapi_id;
    mapi_msg->hdr.src_sub_mid = 0;

    mapi_msg->hdr.messageCode = messageCode;
    mapi_msg->hdr.payloadSize = len;

    if(mapi_msg->hdr.payloadSize > 0) {
        memcpy(mapi_internal_info->buffer + sizeof(MAPI_MSG_HDR), msg, mapi_msg->hdr.payloadSize);
    } 

    // Set the options if any
    if(options) {
        mapi_msg->hdr.src_port = options->src_port;
        if(options->messageCode != 0) {
            mapi_msg->hdr.messageCode = options->messageCode;
        }
        if(options->src_sub_mid != 0) {
            mapi_msg->hdr.src_sub_mid = options->src_sub_mid;
        }
        if(options->dst_mid != 0) {
            mapi_msg->hdr.dst_mid = options->dst_mid;
        }
        if(options->dst_sub_mid != 0) {
            mapi_msg->hdr.dst_sub_mid = options->dst_sub_mid;
        }
    }

    return (sizeof(MAPI_MSG_HDR)+mapi_msg->hdr.payloadSize);
}                          

static boolean mapi_is_valid_msg(MAPI_MSG *msg, int len) {
    if(msg == NULL) return FALSE;
    if((msg->hdr.magic != MAPI_MSG_HDR_MAGIC)) return FALSE;
    if(len != MAPI_MSG_SIZE(msg)) return FALSE;
    return TRUE;
}

int __mapi_get_stream_fd(mapiID mid, struct __mapi_dest_info *dst_info) {
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)]; 
    MAPI_STREAM_INTERNAL_INFO *stream_info = mapi_internal_info->stream_info; 
    MAPI_STREAM_INTERNAL_ENTRY stream_entry;
    memset(&stream_entry, 0, sizeof(MAPI_STREAM_INTERNAL_ENTRY));

    stream_entry.dst_sub_mid = dst_info->dst_sub_mid; 
    stream_entry.dst_uid = dst_info->dst_uid;

    if((dst_info->dst_ip == MAPI_LOCALHOST) || (dst_info->dst_ip == 0)) {
        stream_entry.dst_port = 0;
        stream_entry.dst_ip = MAPI_LOCALHOST;
    } else {
        stream_entry.dst_port = dst_info->dst_port;
        stream_entry.dst_ip = dst_info->dst_ip;
    }

    switch(stream_info->stream_storage_type) {
        case MAPI_STREAM_STORE_TREE:

            break;
        case MAPI_STREAM_STORE_LINKEDLIST:
            return __mapi_get_stream_fd_linkedlist(stream_info, &stream_entry);
        case MAPI_STREAM_STORE_HASH:
            break;
        case MAPI_STREAM_STORE_QUEUE:
            return __mapi_get_stream_fd_queue(stream_info, &stream_entry);                
            break;                
        default:
            return -1;
    }

    return -1;
}

int __mapi_get_stream_fd_linkedlist(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry) {
    return -1;
}

int __mapi_get_stream_fd_queue(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry) {    
    MAPI_STREAM_INTERNAL_ENTRY *queue_entry;

    for (int i = 0; i < stream->stream_storage_size; i++) {
        queue_entry = utils_ds_queue_lookup_at_pos(stream->__DSID, i);
        if(__mapi_is_stream_entry_match(queue_entry, entry)) {
            if(queue_entry->status_flag & MAPI_STREAM_STATUS_READY) {
                return queue_entry->stream_fd;
            }
        }
    }
    return -1;
}

/*
    Stream FDs are arranged/organized for a faster access using certain rules.
    This helps to get the correct stream fd faster while using the send api

    This is maintained in the form of a tree (So only two memory access is required always to get an fd)

            [mid]
        /     /    \    \
     UID0    UID3  UID5 UID2
   /   \       \       \
 subM0 subM1  subM0   subM1
 (fd)   (fd)   (fd)   (fd)

 Use case: When there are many number of mids per application. 
 Cons : Consumes little extra memory for maintaining the pointers for ALL available UIDs in the system

    OR

    using a linked list with a small built-in cache for faster access

 

 UID0   ->  UID0 ->  UID3 ->  UID5  -> UID2 .......
 subM0     subM1     subM0    subM0    subM1

Have a cache of max 5 nodes with pointers to those nodes. This relying on the fact that usually,
when we need to send data to a UID, the next send will most likely to be the same UID

    Use case: When the number of mids used in an application is less. And when we need to send lot of messages continusoly to
        a particular destination by repetedly calling the send api. (To make use of cache)
    Cons: Long Linear search of the UIDs in case of cache hit miss. If the cache is made larger, even that will result in longer
        linear search

   OR

 Build a hash table with key as UID + sub_mid

    TODO: To be implemented    

 Use case: Most efficient.
 Cons : Difficult implemenation. 

*/
int __mapi_add_stream_fd(mapiID mid, struct __mapi_dest_info *dst_info, int fd) {
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)]; 
    MAPI_STREAM_INTERNAL_INFO *stream_info = mapi_internal_info->stream_info; 
    MAPI_STREAM_INTERNAL_ENTRY *stream_entry = (MAPI_STREAM_INTERNAL_ENTRY *)malloc(sizeof(MAPI_STREAM_INTERNAL_ENTRY));
    memset(stream_entry, 0, sizeof(MAPI_STREAM_INTERNAL_ENTRY));

    stream_entry->dst_sub_mid = dst_info->dst_sub_mid; 
    stream_entry->dst_uid = dst_info->dst_uid;
    stream_entry->stream_fd = fd;

    if((dst_info->dst_ip == MAPI_LOCALHOST) || (dst_info->dst_ip == 0)) {
        stream_entry->dst_port = 0;
        stream_entry->dst_ip = MAPI_LOCALHOST;
    } else {
        stream_entry->dst_port = dst_info->dst_port;
        stream_entry->dst_ip = dst_info->dst_ip;
    }
    stream_entry->status_flag |= MAPI_STREAM_STATUS_READY;

    switch(stream_info->stream_storage_type) {
        case MAPI_STREAM_STORE_TREE:

            break;
        case MAPI_STREAM_STORE_LINKEDLIST:
            return __mapi_add_stream_fd_linkedlist(stream_info, stream_entry);
        case MAPI_STREAM_STORE_HASH:
            break;
        case MAPI_STREAM_STORE_QUEUE:                
            return __mapi_add_stream_fd_queue(stream_info, stream_entry);
            break;                
        default:
            return -1;
    }
    return -1;
}

int __mapi_add_stream_fd_linkedlist(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry) {

}

/*
    We will be using the static queues from the utils library. The static queues cannot be enqueued further,
    even if some element is dequeued. So it has a peculiar behaviour.

    Because of the above reason, when stream FDs uses queues, it will allow the user only to start and stop a set of 
    streams till the queue is full. Even if a stream is stopped, user cannot start a new stream since static queues
    doesnt allow enqueue after reaching max limit once.

    So with queues, the stream FDs can be started and stopped in batches per mid. Once all streams are stopped, a new
    batch can be created
*/
int __mapi_add_stream_fd_queue(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry) {
    if(stream->__DSID == 0) { // Create the queue
        UTILS_QUEUE queue;
        queue.type = UTILS_QUEUE_STATIC; // Static Queues are peculiar. Read the above notes
        if(stream->stream_storage_size == 0) {
            stream->stream_storage_size = MAPI_STREAM_STORE_QUEUE_DEFAULT_MAX_SIZE;
            queue.size = MAPI_STREAM_STORE_QUEUE_DEFAULT_MAX_SIZE;
        } else {
            queue.size = stream->stream_storage_size;
        }            
        queue.isPriority = FALSE;
        queue.isProtected = FALSE;
        stream->__DSID = utils_ds_queue_create(&queue); 
    }

    return utils_ds_queue_enqueue(stream->__DSID, (void *)entry);    
}

/*
    This function deletes the stream entry matching the dst_info and return the
    corresponding stream fd for the deleted entry.

    In case of any failure, it will return -1
*/
int __mapi_del_stream_fd(mapiID mid, struct __mapi_dest_info *dst_info) {
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)]; 
    MAPI_STREAM_INTERNAL_INFO *stream_info = mapi_internal_info->stream_info; 
    MAPI_STREAM_INTERNAL_ENTRY stream_entry;
    memset(&stream_entry, 0, sizeof(MAPI_STREAM_INTERNAL_ENTRY));

    stream_entry.dst_sub_mid = dst_info->dst_sub_mid; 
    stream_entry.dst_uid = dst_info->dst_uid;

    if((dst_info->dst_ip == MAPI_LOCALHOST) || (dst_info->dst_ip == 0)) {
        stream_entry.dst_port = 0;
        stream_entry.dst_ip = MAPI_LOCALHOST;
    } else {
        stream_entry.dst_port = dst_info->dst_port;
        stream_entry.dst_ip = dst_info->dst_ip;
    }

    switch(stream_info->stream_storage_type) {
        case MAPI_STREAM_STORE_TREE:

            break;
        case MAPI_STREAM_STORE_LINKEDLIST:
            return __mapi_del_stream_fd_linkedlist(stream_info, &stream_entry);
        case MAPI_STREAM_STORE_HASH:
            break;
        case MAPI_STREAM_STORE_QUEUE:
            return __mapi_del_stream_fd_queue(stream_info, &stream_entry);                
            break;                
        default:
            return -1;
    }

    return -1;

}

int __mapi_del_stream_fd_linkedlist(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry) {
    return -1;
}

int __mapi_del_stream_fd_queue(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry) {
    MAPI_STREAM_INTERNAL_ENTRY *queue_entry;
    int prev_stream_fd = -1;

    for (int i = 0; i < stream->stream_storage_size; i++) {
        queue_entry = utils_ds_queue_lookup_at_pos(stream->__DSID, i);
        if(queue_entry && __mapi_is_stream_entry_match(queue_entry, entry)) {
            if(queue_entry->status_flag & MAPI_STREAM_STATUS_READY) {
                prev_stream_fd = queue_entry->stream_fd;
                free(queue_entry);
                queue_entry = NULL;
                break;
            }
        }
    }
    return prev_stream_fd;
}

int __mapi_set_stream_storage_type(MAPI_INTERNAL_INFO *mapi_internal_info, uint8_t type, uint16_t size) {

    // Cannot change the stream type if there is an active stream
    if(mapi_internal_info->stream_info->num_streams != 0) {
        return -1;
    }

    // Software limit to  allow changing the stream storage only once per mid
    if(mapi_internal_info->stream_info->stream_storage_initialized >= 2) {
        return -1;
    }

    mapi_internal_info->stream_info->stream_storage_type = type;
    mapi_internal_info->stream_info->stream_storage_size = size;
    mapi_internal_info->stream_info->stream_storage_initialized++;
    return 0;
}

boolean __mapi_is_stream_entry_match(MAPI_STREAM_INTERNAL_ENTRY *e1, MAPI_STREAM_INTERNAL_ENTRY *e2) {    
    if((e1->dst_sub_mid == e2->dst_sub_mid) &&
       (e1->dst_uid == e2->dst_uid) &&
       (e1->dst_port == e2->dst_port) &&
       (e1->dst_ip == e2->dst_ip)) {
        return TRUE;
    }
    return FALSE;
}

boolean __mapi_is_listening_socket(int current_fd, int listen_internal_fd, int *listen_external_fds, int num_ports) {
    if (current_fd == listen_internal_fd) {
        return TRUE;
    }

    return utils_is_int_in_array(current_fd, listen_external_fds, num_ports);
}

int __mapi_get_max_fd(MAPI_INTERNAL_INFO *mapi_internal_info) {
    int max_fd = utils_get_max_int_in_array(mapi_internal_info->external_fds, mapi_internal_info->num_ports);

    if (mapi_internal_info->internal_fd > max_fd) {
        max_fd = mapi_internal_info->internal_fd;
    }
    return max_fd;
}

// TODO: If ADVANCED_CONFIG is enabled, use the advanced config to get the correct external fd
int __mapi_get_dgram_external_fd_for_sending(MAPI_INTERNAL_INFO *mapi_internal_info, MAPI_DEST_INFO *dst_info) {
    if(mapi_internal_info->num_ports == 0) {
        return -1;
    }
    if(mapi_internal_info->num_ports == 1) {
        if (mapi_internal_info->external_fds[0] >= 0) {
           return mapi_internal_info->external_fds[0]; // Return the valid fd
        } else {
            return -1; // No valid external fd.
        }
    }

    for(int j = 0; j < mapi_internal_info->num_ports; j++) {
        if (mapi_internal_info->external_fds[j] >= 0) {
            return mapi_internal_info->external_fds[j]; // Return the first valid fd
        }
    }
    return -1; // No valid external fd.
}
