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
static uint16_t *comm_mgr_lib_static_uid_map = NULL;
static uint16_t *comm_mgr_lib_dynamic_uid_map = NULL;

static uint16_t comm_mgr_lib_src_uid = 0;

boolean comm_mgr_lib_initialized = FALSE;

COMM_MGR_LIB_ERR comm_mgr_lib_init(LOG_LEVEL level, uint16_t src_uid) {
    log_lib_init(NULL, level);

    for (uint16_t i = 0; i < COMM_MGR_LIB_MAX_CLIENTS; i++) {
        __comm_mgr_lib_clients[i].client_ptr = NULL; // This indicates Invalid client
    }
    comm_mgr_lib_src_uid = src_uid;

    comm_mgr_lib_initialized = TRUE;
    return COMM_MGR_LIB_SUCCESS; 
}

COMM_MGR_LIB_ERR comm_mgr_lib_destroy() {
    COMM_MGR_LIB_TRACE("Not yet implemented");

    for (uint16_t i = 0; i < COMM_MGR_LIB_MAX_CLIENTS; i++) {
        __comm_mgr_lib_clients[i].client_ptr = NULL; // This indicates Invalid client
        free(&__comm_mgr_lib_clients[i]);
    }

    comm_mgr_lib_initialized = FALSE;
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
                strcpy(un_addr.sun_path, SOCKET_FILE_PATH); 

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
    __comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO] = utils_ds_queue_create(&queue);
    if (__comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO] == 0) {
        COMM_MGR_LIB_ERROR("Failed to create COMM_MGR_LIB_DSID_PROTO");
        goto cleanup;
    }



    if(__comm_mgr_lib_clients[id].property == NULL) {
        queue.size = COMM_MGR_LIB_RECV_QUEUE_SIZE;
    } else {
        queue.size = __comm_mgr_lib_clients[id].property->comm_mgr_lib_recv_queue_size;
    }
    __comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_RECV] = utils_ds_queue_create(&queue);
    if (__comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_RECV] == 0) {
        COMM_MGR_LIB_ERROR("Failed to create COMM_MGR_LIB_DSID_DATA_RECV");
        goto cleanup;
    }

    if(__comm_mgr_lib_clients[id].property == NULL) {
        queue.size = COMM_MGR_LIB_SEND_QUEUE_SIZE;
    } else {
        queue.size = __comm_mgr_lib_clients[id].property->comm_mgr_lib_send_queue_size;
    }
    __comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_SEND] = utils_ds_queue_create(&queue);
    if (__comm_mgr_lib_clients[id].client_ptr->__DSID[COMM_MGR_LIB_DSID_DATA_SEND] == 0) {
        COMM_MGR_LIB_ERROR("Failed to create COMM_MGR_LIB_DSID_DATA_SEND");
        goto cleanup;
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
          Communication Manager.

          It relies on the below DSIDs for receving/sending protocol/data/ack
          COMM_MGR_LIB_DSID_PROTO - DSID for sending protocols/ack      
          COMM_MGR_LIB_DSID_DATA_RECV - DSID for receiving the Data/ack
          COMM_MGR_LIB_DSID_DATA_SEND - DSID for sending the Data/ack

          All these DSIDs are per client
*/
COMM_MGR_LIB_ERR comm_mgr_lib_server_communicator(COMM_MGR_LIB_CLIENT_ID id) {
	uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id);
    fd_set  working_read_fd;
    fd_set  working_write_fd;
	struct timeval	timeout;
	int max_sd, rc = 0;
	boolean end_lib = FALSE;
	boolean is_send_ready = FALSE;
	char recv_buffer[8096];
	int recv_count = 0;

    if(cid > COMM_MGR_LIB_MAX_CLIENTS) {
        COMM_MGR_LIB_ERROR("Invalid client");
        return COMM_MGR_LIB_INVALID_CLIENT_ERR;
    }

   	max_sd = __comm_mgr_lib_clients[cid].client_ptr->__fd;

   	/*************************************************************/
   	/* Initialize the timeval struct to libInactivityTimeOut 	 */
	/* minutes.  If no activity after libInactivityTimeOut 	 	 */
	/* minutes this program will end.           			     */
   	/*************************************************************/
	if (__comm_mgr_lib_clients[cid].property) {
	   	timeout.tv_sec  = __comm_mgr_lib_clients[cid].property->libInactivityTimeOut * 60;
   		timeout.tv_usec = 0;
	}

	// Note : Only one FD per client, where the activity has to be monitored
	/*************************************************************/
   	/*Loop waiting for for incoming data on the connected socket */
   	/*************************************************************/
	do {
	    FD_ZERO(&working_read_fd);
    	FD_ZERO(&working_write_fd);

    	/**********************************************************/
      	/* Copy the master fd_set over to the working fd_set.     */
      	/**********************************************************/
		FD_SET(__comm_mgr_lib_clients[cid].client_ptr->__fd, &working_read_fd);	
	
		// Set the write FD only when, there is something to send from SEND_DSID
		if(is_send_ready == TRUE) {
			FD_SET(__comm_mgr_lib_clients[cid].client_ptr->__fd, &working_write_fd);	
		}

		/**********************************************************/
      	/* Call select() and wait libInactivityTimeOut   	      */
      	/**********************************************************/
      	COMM_MGR_LIB_DEBUG("Waiting on select()...");
		if (__comm_mgr_lib_clients[cid].property == NULL) { // Forever
	      	rc = select(max_sd + 1, &working_read_fd, &working_write_fd, NULL, NULL);
		} else {
			if(__comm_mgr_lib_clients[cid].property->libInactivityTimeOut < 1) { // Forever
				rc = select(max_sd + 1, &working_read_fd, &working_write_fd, NULL, NULL);
			} else {
				rc = select(max_sd + 1, &working_read_fd, &working_write_fd, NULL, &timeout);
			}
		}
      	
		/**********************************************************/
      	/* Check to see if the select call failed.                */
      	/**********************************************************/
      	if (rc < 0) {
        	COMM_MGR_LIB_ERROR("select() failed");
			rc = COMM_MGR_LIB_SELECT_ERR;
         	goto cleanup_and_exit;
      	}
      	/**********************************************************/
      	/* Check to see if the libInactivityTimeOut minute time   */
		/* out expired.         								  */
      	/**********************************************************/
      	if (rc == 0) {
        	COMM_MGR_LIB_ERROR("select() timed out.  End program.");
			rc = COMM_MGR_LIB_CLIENT_TIMEOUT;
         	goto cleanup_and_exit;
      	}

		// Now check if the client FD is set
		if (FD_ISSET(__comm_mgr_lib_clients[cid].client_ptr->__fd, &working_read_fd)) {
			do {
				recv_count = recv(__comm_mgr_lib_clients[cid].client_ptr->__fd, 
												recv_buffer, sizeof(recv_buffer), MSG_DONTWAIT);
				if (recv_count < 0) {
					if (errno != EWOULDBLOCK) {
						COMM_MGR_LIB_ERROR("recv() failed");
						goto cleanup_and_exit;
					}
					break;
				}
				// Enqueue the received data to proto/data DSID. 
				__comm_mgr_lib_receive_packets(id, recv_buffer, recv_count);
			} while(recv_count > 0);	
		}

#if 0
		// Check if the FD is writable
		if (FD_ISSET(__comm_mgr_lib_clients[cid].client_ptr->__fd , &working_write_fd)) {
			// Check the send DSID if something is available to be sent
		    (COMM_MGR_LIB_MSG *)utils_ds_queue_dequeue(__comm_mgr_lib_clients[cid].client_ptr->__DSID[COMM_MGR_LIB_DSID_SEND]);		
			
			do {

			} while(); // Keep sending till the SEND_DSID is empty
		}
#endif
		

	} while(end_lib == FALSE);

cleanup_and_exit:
   	/*************************************************************/
   	/* Clean up the socket which is open                         */
   	/*************************************************************/
	close(__comm_mgr_lib_clients[cid].client_ptr->__fd);
	
	return rc;
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

    ret = __comm_mgr_lib_send_msg(&__comm_mgr_lib_clients[cid], &hdr, msg, len);

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

int comm_mgr_lib_recv_data(COMM_MGR_LIB_CLIENT_ID id, char *msg, int len) {
    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id);

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

    struct hostent *server = &(__comm_mgr_lib_clients[cid].server);
    ssize_t out_len = 0;

    out_len = recv(__comm_mgr_lib_clients[cid].client_ptr->__fd, msg, len, 0);
    if (out_len < 0) {
        COMM_MGR_LIB_ERROR("Receive error\n");
        return -1;        
    }

    return out_len;
}

/******************************************************************************
                            Internal Functions
******************************************************************************/
static uint16_t __comm_mgr_lib_get_free_client() {
    for (uint16_t i = 0; i < COMM_MGR_LIB_MAX_CLIENTS; i++) {
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
static COMM_MGR_LIB_ERR  __comm_mgr_lib_receive_packets(COMM_MGR_LIB_CLIENT_ID id, char *msg, uint16_t len) {
	COMM_MGR_MSG *comm_mgr_msg;
    uint8_t cid = COMM_MGR_LIB_GET_CLIENT_ID(id); 

	comm_mgr_msg = comm_mgr_get_msg(msg, len);

    if (comm_mgr_msg == NULL) {
        COMM_MGR_LIB_ERROR("Received bad packet from Communication Manager");
        return COMM_MGR_LIB_BAD_PACKET;
    }

    switch(comm_mgr_msg->hdr.msg_type) {
        case COMM_MGR_MSG_PROTOCOL:
            __comm_mgr_lib_protocol_handler(&__comm_mgr_lib_clients[cid], comm_mgr_msg);
            break;
        case COMM_MGR_MSG_ACK:
            __comm_mgr_lib_ack_handler(&__comm_mgr_lib_clients[cid], comm_mgr_msg);
            break;
        case COMM_MGR_MSG_DATA:

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
                                      char *msg, int len) {
    struct hostent *server = &(client->server);
    uint32_t comm_msg_size = 0; 
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

    COMM_MGR_MSG *comm_mgr_msg = comm_mgr_create_msg(client->client_ptr->__src_uid, 
                                    hdr->dst_uid, hdr->msg_type, msg, len);
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
    // If its a Protocol packet OR an ACK related to Protocol, enqueue in Protocol DSID
    if ((comm_mgr_msg->hdr.msg_type == COMM_MGR_MSG_PROTOCOL) ||
        ((comm_mgr_msg->hdr.msg_type == COMM_MGR_MSG_ACK) && 
        ((comm_mgr_msg->hdr.submsg_type == COMM_MGR_SUBMSG_PROTO_ACK) || 
        (comm_mgr_msg->hdr.submsg_type == COMM_MGR_SUBMSG_PROTO_NACK)))) {
        if(utils_ds_queue_enqueue(client->client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO], (void *)comm_mgr_msg) < 0) {
            COMM_MGR_LIB_ERROR("Failed to insert the Protocol packet to DSID 0x%0x", 
                                                client->client_ptr->__DSID[COMM_MGR_LIB_DSID_PROTO]);
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

    ret = __comm_mgr_lib_send_msg(client, &hdr, payload, payloadsize);

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
        - Create a new protocol comm msg with same state and respond with apps UID
        - Once it gets gets the ACK packet, should change the client state tp DISCOVERY_DONE
        - Discard any user packets
*/
static 
COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_discovery_start(COMM_MGR_LIB_CLIENT *client, 
                                                         COMM_MGR_MSG *msg) {

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

    //Create a new protocol comm msg with same state and respond with apps UID
    if(__comm_mgr_lib_send_protocol(client, COMM_MGR_SUBMSG_DISCOVERY, 
                                   (char *)&(client->client_ptr->__src_uid), 
                 sizeof(client->client_ptr->__src_uid)) != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Failed to send ACK PROTO packet to Communication Manager");
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

    return COMM_MGR_LIB_SUCCESS;
send_nack:
    // We need ask the Communication Manager to send the discovery ACK packet again. Send NACK
     if(comm_mgr_lib_send_ack(client->__clientID, SYS_MGR_SYSTEM_UID_COMM_MANAGER, 
                COMM_MGR_SUBMSG_PROTO_NACK) != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Failed to send NACK PROTO packet to Communication Manager");
    }
    return COMM_MGR_LIB_ACK_BAD_PACKET;
}

/*
    Learning happens only when the dest UID in which the app is interested is not
    Discovered yet. The lib will drop all the user packets to the dest UID till it is
    data transfer ready

    Format :

    msg_type = PROTOCOL | submsg_type = LEARNING | payloadsize = 5 (bytes) | 
                         *payload = COMM_MGR_MSG_PROTOCOL_MAGIC (16) | Dest UID (16)


*/
static 
COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_learning(COMM_MGR_LIB_CLIENT *client,
                                                  COMM_MGR_MSG *msg,
                                                  uint8_t isLearnt) {

    if (msg->hdr.payloadSize != (16*5)) {
        COMM_MGR_LIB_ERROR("Bad payloadsize received. Discarding"); 
        goto send_nack;
    }

    uint16_t magic;
    memcpy(&magic, &(msg->payload[0]), sizeof(uint16_t));
    if(magic != COMM_MGR_MSG_PROTOCOL_MAGIC) {
        COMM_MGR_LIB_ERROR("Bad payloadsize received. Discarding"); 
        goto send_nack;
    }

    uint16_t dest_uid;
    memcpy(&dest_uid, &(msg->payload[2]), sizeof(uint16_t));    

    // Validate the Dest UID received
    if((dest_uid >= comm_mgr_lib_static_uid_base) && (dest_uid < comm_mgr_lib_static_uid_max)) {
        uint16_t index = dest_uid - comm_mgr_lib_static_uid_base;
        comm_mgr_lib_static_uid_map[index] = isLearnt;
    } else if((dest_uid >= comm_mgr_lib_dynamic_uid_base) && (dest_uid < comm_mgr_lib_dynamic_uid_max)) {
        uint16_t index = dest_uid - comm_mgr_lib_dynamic_uid_base;
        comm_mgr_lib_dynamic_uid_map[index] = isLearnt;      
    } else {
        COMM_MGR_LIB_ERROR("Bad Dest UID received in the Learning protocol packet");
        goto send_nack;
    }

    return COMM_MGR_LIB_SUCCESS;

send_nack:
    // We need ask the Communication Manager to send the learning packet again. Send NACK
     if(comm_mgr_lib_send_ack(client->__clientID, SYS_MGR_SYSTEM_UID_COMM_MANAGER, 
                COMM_MGR_SUBMSG_PROTO_NACK) != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Failed to send NACK PROTO packet to Communication Manager");
    }
    return COMM_MGR_LIB_PROTO_BAD_PACKET;
}


/*
    This function is the entry point once the client finishes the Discovery stages. 

    Now depending on the Dest UID the packets can be forwarded or dropped

    Format :

    msg_type = PROTOCOL | submsg_type = LEARNING | payloadsize = 5 (bytes) | 
                         *payload = COMM_MGR_MSG_PROTOCOL_MAGIC (16) | Dest UID (16)


    We can get LEARNING/DATATXREADY for a Dest UID depeding on whether the Dets UID is
    not learnt or learnt by the Communuication Manager
*/
static 
COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_datatransfer_ready(COMM_MGR_LIB_CLIENT *client, 
                                                             COMM_MGR_MSG *msg) {

    COMM_MGR_LIB_ERR ret = COMM_MGR_LIB_SUCCESS;
    // The sub msg can be either Data Tx Ready or Learning. All others are error cases
    if (msg->hdr.submsg_type == COMM_MGR_SUBMSG_DATATXREADY) {
        ret = __comm_mgr_lib_protocol_learning(client, msg, 1);
    } else if (msg->hdr.submsg_type == COMM_MGR_SUBMSG_LEARNING) {
        ret = __comm_mgr_lib_protocol_learning(client, msg, 0);
    } else {
        // Will just ignore the other protcol packets
        // <TODO> Can Communiation Manager forecfully send the Discovery again, to ask the client
        // to be discovered again ???/ Will handle the case later
        return COMM_MGR_LIB_PROTO_BAD_PACKET;
    }

    return ret;
}


/*
    The lib constructs the map during runtime using the info provided by the 
    Communication Manager.

    During the Discovery Phase of the Protocol, the Communication Manager
    also sends the UID map information.

    If there is any change in the Map info at a later point of time, the 
    Communication Manager can again send via COMM_MGR_MSG_SYSTEM msgs (very rare)

    Data Format of Payload : (each is 16 bit)        
        payloadsize = 16 * 5
        COMM_MGR_MSG_PROTOCOL_MAGIC | static_uid_max | static_uid_base | dynamic_uid_max | dynamic_uid_base
*/
static 
COMM_MGR_LIB_ERR __comm_mgr_lib_update_local_uid_map(COMM_MGR_MSG *msg) {
    
    if ((msg->hdr.msg_type == COMM_MGR_MSG_PROTOCOL) &&
       (msg->hdr.submsg_type == COMM_MGR_SUBMSG_DISCOVERY)) { // First time
        if (msg->hdr.payloadSize != (16*5)) {
            COMM_MGR_LIB_ERROR("Bad payloadsize received. Discarding"); 
            return COMM_MGR_LIB_BAD_PACKET;
        }
        uint16_t magic;
        memcpy(&magic, &(msg->payload[0]), sizeof(uint16_t));
        if(magic != COMM_MGR_MSG_PROTOCOL_MAGIC) {
            COMM_MGR_LIB_ERROR("Bad payloadsize received. Discarding"); 
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
    uint16_t *temp_comm_mgr_lib_static_uid_map;
    uint16_t *temp_comm_mgr_lib_dynamic_uid_map;

    // Free te map if it has already been allocated before. (update case : via COMM_MGR_MSG_SYSTEM)
    if (comm_mgr_lib_static_uid_map) {                
        free(comm_mgr_lib_static_uid_map);
    }

    if(comm_mgr_lib_dynamic_uid_map) {
        free(comm_mgr_lib_dynamic_uid_map);
    }

    uint32_t static_uid_map_size = sizeof(uint16_t) * (comm_mgr_lib_static_uid_max - comm_mgr_lib_static_uid_base);
    uint32_t dynamic_uid_map_size = sizeof(uint16_t) * (comm_mgr_lib_dynamic_uid_max - comm_mgr_lib_dynamic_uid_base);

    comm_mgr_lib_static_uid_map = (uint16_t *)malloc(static_uid_map_size);
    comm_mgr_lib_dynamic_uid_map = (uint16_t *)malloc(dynamic_uid_map_size);

    memset(comm_mgr_lib_static_uid_map, 0, static_uid_map_size);
    memset(comm_mgr_lib_dynamic_uid_map, 0, dynamic_uid_map_size);

    return COMM_MGR_LIB_SUCCESS;
}



