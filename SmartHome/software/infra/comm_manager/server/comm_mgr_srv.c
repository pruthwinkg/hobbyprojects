/*****************************************************************************
    Description : This is the core of Communication Manager. This doesn't do
            anything on its own. An instance of Communication Manager needs
            to be created to use this. Multiple Master instances can be 
            supported by this module. Currently there is a soft-limit of max 5
            master instances. All the Master instances run in the context of
            Communication Manager (same process). They can be thought of as 
            logical masters. 
            Example : UDS master
                It takes care of Unix Domain Sockets, which is effective for
            communication inside a system. Even multiple UDS masters can be
            created. Use case will be to handle a set of UIDs by one UDS master.

            It is recommneded to use a event driven system for the Master instance
            using the utils task_handler library.

            Also, this Module enforces a custom protocol for the reliable data
            connection between the Master instances and its clients.
            Refer Software Design Specifications for the details about the protocol.

            This module also provides facility to create custom messaging protocols.
            One of the example is SCOM (Smart Communication Messages) which have
            rich feature set for message passing.
******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h> 

#include "comm_mgr_srv.h"
#include "system_mgr.h"
#include "utils.h"
#include "comm_mgr_srv_protocol.h"
#include "comm_mgr_srv_uds.h"

// Resource :
// https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/

// https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzab6/xnonblock.htm


static uint16_t *__comm_mgr_srv_master_id_array;
COMM_MGR_SRV_MASTER *comm_mgr_srv_masters;
boolean comm_mgr_srv_initialized = FALSE;
UTILS_SHM_OBJ *sysmgr_shm_obj;

uint16_t comm_mgr_reg_apps_num = 0; // Total number of valid registered apps
COMM_MGR_SRV_REG_APPS *comm_mgr_reg_apps_list;

char datastream[COMM_MGR_PACKET_MAX_SIZE]; // Used while sending data. Statically allocted to avoid frequent
                                           // mallocs which can result in lot of fragmentation

COMM_MGR_SRV_ERR comm_mgr_srv_init() {
	if (comm_mgr_srv_initialized == TRUE) {
		COMM_MGR_SRV_ERROR("comm_mgr_srv already initialized");
		return COMM_MGR_SRV_ALREADY_INITIALIZED;
	}
    COMM_MGR_SRV_TRACE("Initializing the %s", COMM_MGR_SRV_APP_NAME);

    int shm_obj_size = SYS_MGR_CLIENT_MAX_CLIENTS * sizeof(SYS_MGR_CLIENT_SHM_TBL_ENTRY);

	comm_mgr_srv_masters = (COMM_MGR_SRV_MASTER *)malloc(sizeof(COMM_MGR_SRV_MASTER) * COMM_MGR_SRV_MAX_MASTERS);
	__comm_mgr_srv_init_master_id();

    // Access the system managers client table shm obj as read only
    // This will be used to identify the sub-systems which are registered
    // with system manager and to exclude apps which are not registered.
    // Unregistered apps cannot use comm_mgr for communication
    sysmgr_shm_obj = utils_create_shared_obj(SYS_MGR_SHM_ID_SYS_MANAGER_CLIENT_TBL, 
                                             shm_obj_size,
                                             UTILS_SHM_FLAGS_RDONLY | UTILS_SHM_FLAGS_SHARED);

    if(sysmgr_shm_obj == NULL) {
        COMM_MGR_SRV_ERROR("Couldn't get the system manager client table shm obj");
        return COMM_MGR_SRV_BAD_SHM_OBJ;
    }
    // Note : No need to check for the SYS_MGR_SHM_OBJ_USERDEFINED_CREATED, since it is
    // guranteed that comm_manager is started post shm obj creation by sys manager
    // It might be required in the case where comm_manager is started independent of sys manager

    if (comm_mgr_create_registered_apps_list() != COMM_MGR_SRV_SUCCESS) {
        COMM_MGR_SRV_ERROR("Unable to get the registered apps list");
        utils_destroy_shared_obj(sysmgr_shm_obj, FALSE);
        return COMM_MGR_SRV_INIT_FAILURE;
    }

    if(comm_mgr_srv_protocol_init() != COMM_MGR_SRV_SUCCESS) {
        COMM_MGR_SRV_ERROR("Failed to initialize the protocol");
        return COMM_MGR_SRV_INIT_FAILURE;
    }

	comm_mgr_srv_initialized = TRUE;
	return COMM_MGR_SRV_SUCCESS;
}

COMM_MGR_SRV_ERR comm_mgr_srv_destroy() {
	if (comm_mgr_srv_initialized == FALSE) {
		COMM_MGR_SRV_ERROR("Comm_mgr_srv already destroyed or not yet initialized");
		return COMM_MGR_SRV_DESTROY_FAILURE;
	}

	free(comm_mgr_srv_masters);
	free(__comm_mgr_srv_master_id_array);
	
	comm_mgr_srv_initialized = FALSE;
	return COMM_MGR_SRV_SUCCESS;
}

static
COMM_MGR_SRV_ERR comm_mgr_set_non_blocking_io(int socket_fd) {
    int rc = 0;
    rc = fcntl(socket_fd, F_SETFL, (fcntl(socket_fd, F_GETFL, 0) | O_NONBLOCK));
    if (rc < 0) {
       COMM_MGR_SRV_ERROR("Failed to set the socket %d to Non-blocking mode", socket_fd);
       return COMM_MGR_SRV_FCNTL_NON_BLOCK_ERR;
    }
    return COMM_MGR_SRV_SUCCESS;
}

COMM_MGR_SRV_ERR comm_mgr_srv_init_master(COMM_MGR_SRV_MASTER *master) {
    if (master == NULL) {
        return COMM_MGR_SRV_INVALID_ARG;
    }

	if (comm_mgr_srv_initialized == FALSE) {
		COMM_MGR_SRV_ERROR("Comm_mgr is not yet initialized");
		return COMM_MGR_SRV_NOT_INITIALIZED;
	}

    master->__masterReady = FALSE;
    
	int opt = TRUE;
	int rc;
	struct sockaddr_un un_addr; 
	//struct sockaddr_in in_addr; 

    switch(master->masterAf) {
        case COMM_MGR_SRV_IPC_AF_UNIX_SOCK_STREAM:
		   	/*************************************************************/
		   	/* Create an COMM_MGR_SRV_IPC_AF_UNIX stream socket to 	    */
		   	/* receive incoming connections on                         */
		   	/*************************************************************/
			master->__masterFd = socket(AF_UNIX, SOCK_STREAM, 0);
		   	if (master->__masterFd < 0) {			  
				return COMM_MGR_SRV_SOCKET_CREATE_ERR;
		   	}

		   	/*************************************************************/
		   	/* Allow socket descriptor to be reuseable                   */
		   	/*************************************************************/
			if (master->reuseaddr == TRUE) {
		   		rc = setsockopt(master->__masterFd, SOL_SOCKET,  SO_REUSEADDR,
						   (char *)&opt, sizeof(opt));
		   		if (rc < 0) {
			  		close(master->__masterFd);
					return COMM_MGR_SRV_SOCKET_OPT_ERR;
		   		}
			}
			
		    /*************************************************************/
		    /* Set socket to be nonblocking using fcntl() for portability*/
            /* purpose. The incoming sockets doesn't inherit from this   */
            /* listening sokcet.Refer https://linux.die.net/man/2/accept4*/
		    /*************************************************************/			
			if (master->nonblockingIO == TRUE) {
                if( comm_mgr_set_non_blocking_io(master->__masterFd) != COMM_MGR_SRV_SUCCESS) {
                    COMM_MGR_SRV_TRACE("Setting the socket %d in blocking mode", master->__masterFd);
                }
			}

		    /*************************************************************/
		    /* Bind the socket                                           */
		    /*************************************************************/
			memset(&un_addr, 0, sizeof(un_addr));
			un_addr.sun_family = AF_UNIX;   
			strcpy(un_addr.sun_path, SOCKET_FILE_PATH); 

    		unlink(SOCKET_FILE_PATH);

		    rc = bind(master->__masterFd,
			 		 (struct sockaddr *)&un_addr, sizeof(un_addr));
		    if (rc < 0) {
			  	close(master->__masterFd);
				return COMM_MGR_SRV_SOCKET_BIND_ERR;
		   	}

   			/*************************************************************/
   			/* Set the listen back log                                   */
   			/*************************************************************/
   			rc = listen(master->__masterFd, COMM_MGR_SRV_BACKLOG);
   			if (rc < 0) {
      			close(master->__masterFd);
				return COMM_MGR_SRV_SOCKET_LISTEN_ERR;
   			}		
            break;
        case COMM_MGR_SRV_IPC_AF_INET_SOCK_STREAM:

            break;
        default:            
            return COMM_MGR_SRV_UNKNOWN_AF_TYPE;
    }
	
	master->__masterID = __comm_mgr_srv_get_next_free_master_id(master->masterAf);
    master->__masterReady = TRUE;

	memcpy(&comm_mgr_srv_masters[COMM_MGR_SRV_GET_MASTER_INDEX(master->__masterID)], master, 
							sizeof(COMM_MGR_SRV_MASTER));

	if (master->masterAf == COMM_MGR_SRV_IPC_AF_UNIX_SOCK_STREAM) {
		COMM_MGR_SRV_TRACE("Created a %s with "
					    ", Master ID : %d, UDS File : %s successfully", 
						COMM_MGR_SRV_APP_NAME,
						master->__masterID, SOCKET_FILE_PATH);
	} else if (master->masterAf == COMM_MGR_SRV_IPC_AF_INET_SOCK_STREAM) {
		COMM_MGR_SRV_TRACE("Created a %s with "
					    ", Master ID : %d, Port : %d successfully", 
						COMM_MGR_SRV_APP_NAME,
						master->__masterID, master->portNum);
	}

	COMM_MGR_SRV_TRACE("%s, Master ID [%d] started to listen", COMM_MGR_SRV_APP_NAME, master->__masterID);

    // Call the protocol init function for the specific master 
    if(comm_mgr_srv_protocol_master_init(master) != COMM_MGR_SRV_SUCCESS) {
        COMM_MGR_SRV_ERROR("%s failed to initialize the protocol for the Master ID [%d]", COMM_MGR_SRV_APP_NAME, master->__masterID);
        return COMM_MGR_SRV_PROTO_INIT_ERR;
    }


    return COMM_MGR_SRV_SUCCESS;
}


/************************************************************************
	Note: In a multi-master system call the below function in different
		threads. Maintain different comm_mgr_srv data buffers for each
		thread and write to it seperatly. And each of these threads should  
		run indefinetly accpeting connections.

		Upon any mal-function of this thread ,the main-thread should 
		destroy the sepecific thread and spawn it again. Also any data 
		which was left unprocessed must be replayed, so that there is 
		very minimal mis-communication

		This function is capable of accpeting multiple simultaneous clients 
		in a single server. (Because of select() call)
************************************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_accept_clients(uint16_t masterID) {
	fd_set	master_set, working_set;
	int	listen_sd, max_sd, new_sd;
	int desc_ready, end_server = FALSE;
	struct timeval	timeout;
	int i = 0, rc, close_conn, len;
	int masterIndex = COMM_MGR_SRV_GET_MASTER_INDEX(masterID);
    COMM_MGR_SRV_MASTER *master = &comm_mgr_srv_masters[masterIndex];

	char buffer[4096]; // Delete it

	if (master->__masterReady == FALSE) {
		COMM_MGR_SRV_ERROR("Master ID [%d] not yet ready", masterID);
		return COMM_MGR_SRV_MASTER_NOT_READY;
	}

	listen_sd = master->__masterFd;

   	/*************************************************************/
   	/* Initialize the master fd_set                              */
   	/*************************************************************/
   	FD_ZERO(&master_set);
   	max_sd = listen_sd;
   	FD_SET(listen_sd, &master_set);	

   	/*************************************************************/
   	/* Initialize the timeval struct to srvInactivityTimeOut 	 */
	/* minutes.  If no activity after srvInactivityTimeOut 	 	 */
	/* minutes this program will end.           			     */
   	/*************************************************************/
   	timeout.tv_sec  = master->srvInactivityTimeOut * 60;
   	timeout.tv_usec = 0;

	/*************************************************************/
   	/* Loop waiting for incoming connects or for incoming data   */
   	/* on any of the connected sockets.                          */
   	/*************************************************************/
   	do {
    	/**********************************************************/
      	/* Copy the master fd_set over to the working fd_set.     */
      	/**********************************************************/
      	memcpy(&working_set, &master_set, sizeof(master_set));

      	/**********************************************************/
      	/* Call select() and wait srvInactivityTimeOut   	      */
      	/**********************************************************/
      	COMM_MGR_SRV_DEBUG("Waiting on select()...");
		if (master->srvInactivityTimeOut < 1) {
	      	rc = select(max_sd + 1, &working_set, NULL, NULL, NULL);
		} else {
			rc = select(max_sd + 1, &working_set, NULL, NULL, &timeout);
		}

      	/**********************************************************/
      	/* Check to see if the select call failed.                */
      	/**********************************************************/
      	if (rc < 0) {
        	COMM_MGR_SRV_ERROR("select() failed");
			rc = COMM_MGR_SRV_SELECT_ERR;
         	goto cleanup_and_exit;
      	}

      	/**********************************************************/
      	/* Check to see if the srvInactivityTimeOut minute time   */
		/* out expired.         								  */
      	/**********************************************************/
      	if (rc == 0) {
        	COMM_MGR_SRV_ERROR("select() timed out.  End program.");
			rc = COMM_MGR_SRV_SERVER_TIMEOUT;
         	goto cleanup_and_exit;
      	}

      	/**********************************************************/
      	/* One or more descriptors are readable.  Need to         */
      	/* determine which ones they are.                         */
      	/**********************************************************/
      	desc_ready = rc;
      	for (i=0; i <= max_sd  &&  desc_ready > 0; ++i) {
        	/*******************************************************/
         	/* Check to see if this descriptor is ready            */
         	/*******************************************************/
         	if (FD_ISSET(i, &working_set)) {
				/****************************************************/
				/* A descriptor was found that was readable - one   */
				/* less has to be looked for.  This is being done   */
				/* so that we can stop looking at the working set   */
				/* once we have found all of the descriptors that   */
				/* were ready.                                      */
				/****************************************************/
				desc_ready -= 1;

				/****************************************************/
				/* Check to see if this is the listening socket     */
				/****************************************************/
				if (i == listen_sd) {
					COMM_MGR_SRV_DEBUG("Listening socket is readable");
					/*************************************************/
					/* Accept all incoming connections that are      */
					/* queued up on the listening socket before we   */
					/* loop back and call select again.              */
					/*************************************************/
					do {
						/**********************************************/
						/* Accept each incoming connection.  If       */
						/* accept fails with EWOULDBLOCK, then we     */
						/* have accepted all of them.  Any other      */
						/* failure on accept will cause us to end the */
						/* server.                                    */
						/**********************************************/
						new_sd = accept(listen_sd, NULL, NULL);
						if (new_sd < 0) {
							if (errno != EWOULDBLOCK) {
								COMM_MGR_SRV_ERROR("accept() failed");
								end_server = TRUE;
								rc = COMM_MGR_SRV_SOCKET_ACCEPT_ERR;
							}
							break;
						}

                        /*************************************************************/
                        /* Set socket to be nonblocking using fcntl() for portability*/
                        /* purpose. The incoming sockets doesn't inherit from this   */
                        /* listening sokcet.Refer https://linux.die.net/man/2/accept4*/
                        /*************************************************************/			
                        if (master->nonblockingIO == TRUE) {
                            if( comm_mgr_set_non_blocking_io(new_sd) != COMM_MGR_SRV_SUCCESS) {
                                COMM_MGR_SRV_TRACE("Setting the socket %d in blocking mode", new_sd);
                            }
                        }

						/**********************************************/
						/* Add the new incoming connection to the     */
						/* master read set                            */
						/**********************************************/
						COMM_MGR_SRV_DEBUG("New incoming connection - %d", new_sd);
						FD_SET(new_sd, &master_set);
						if (new_sd > max_sd) {
							max_sd = new_sd;
						}

						/**********************************************/
						/* Loop back up and accept another incoming   */
						/* connection                                 */
						/**********************************************/
					} while (new_sd != -1);
				}
				/****************************************************/
				/* This is not the listening socket, therefore an   */
				/* existing connection must be readable             */
				/****************************************************/
				else {
					COMM_MGR_SRV_DEBUG("Descriptor %d is readable", i);
					close_conn = FALSE;
					/*************************************************/
					/* Receive all incoming data on this socket      */
					/* before we loop back and call select again.    */
					/*************************************************/
					do {
						/**********************************************/
						/* Receive data on this connection until the  */
						/* recv fails with EWOULDBLOCK.  If any other */
						/* failure occurs, we will close the          */
						/* connection.                                */
						/**********************************************/
						rc = recv(i, buffer, sizeof(buffer), 0);
						if (rc < 0) {
							if (errno != EWOULDBLOCK) {
								COMM_MGR_SRV_ERROR("recv() failed");
								close_conn = TRUE;
							}
							break;
						}

						/**********************************************/
						/* Check to see if the connection has been    */
						/* closed by the client                       */
						/**********************************************/
						if (rc == 0) {
							COMM_MGR_SRV_TRACE("Connection closed");
							close_conn = TRUE;
                            
                            // Add this event to the HouseKeeping DSID
                            if (master->__dsid_cb[COMM_MGR_SRV_DSID_HOUSEKEEP]) {
                                COMM_MGR_SRV_UDS_HK_JOB *hk_job = (COMM_MGR_SRV_UDS_HK_JOB*)malloc(sizeof(COMM_MGR_SRV_UDS_HK_JOB));
                                hk_job->event = COMM_MGR_SRV_HOUSEKEEP_EVENT_CLIENT_DOWN;
                                hk_job->eventData = (uint32_t *)malloc(sizeof(uint32_t));
                                *(uint32_t *)(hk_job->eventData) = i; // copy the server fd
                                master->__dsid_cb[COMM_MGR_SRV_DSID_HOUSEKEEP](master->__DSID[COMM_MGR_SRV_DSID_HOUSEKEEP], NULL, 0, (void *)hk_job);
                            } else {
                                COMM_MGR_SRV_ERROR("DSID [%s] Callback not set. Not sending the data to Master ID %d", 
                                                    DECODE_ENUM(COMM_MGR_SRV_DSID, COMM_MGR_SRV_DSID_HOUSEKEEP), master->__masterID);
                            }
							break;
						}

						/**********************************************/
						/* Data was received                          */
						/**********************************************/
						len = rc;
                       
						//COMM_MGR_SRV_DEBUG("Data received : %s, len : %d", buffer, len);
                        if (master->__dsid_cb[COMM_MGR_SRV_DSID_RECV]) {
                            master->__dsid_cb[COMM_MGR_SRV_DSID_RECV](master->__DSID[COMM_MGR_SRV_DSID_RECV], buffer, len, (void *)&i);
                        } else {
                            COMM_MGR_SRV_ERROR("DSID [%s] Callback not set. Not sending the data to Master ID %d", 
                                                DECODE_ENUM(COMM_MGR_SRV_DSID, COMM_MGR_SRV_DSID_RECV), master->__masterID);
                            close_conn = TRUE;
                            break;
                        }

#if 0 // TODO : Enable it Later
						/**********************************************/
						/* Echo the data back to the client           */
						/**********************************************/
						rc = send(i, buffer, len, 0);
						if (rc < 0) {
							COMM_MGR_SRV_ERROR("  send() failed");
							close_conn = TRUE;
						 break;
						}
#endif
                        
					} while (TRUE);

					/*************************************************/
					/* If the close_conn flag was turned on, we need */
					/* to clean up this active connection.  This     */
					/* clean up process includes removing the        */
					/* descriptor from the master set and            */
					/* determining the new maximum descriptor value  */
					/* based on the bits that are still turned on in */
					/* the master set.                               */
					/*************************************************/
					if (close_conn) {
						close(i);
						FD_CLR(i, &master_set);
						if (i == max_sd) {
							while (FD_ISSET(max_sd, &master_set) == FALSE) {
								max_sd -= 1;
							}
						}
					}
				} /* End of existing connection is readable */
      		} /* End of if (FD_ISSET(i, &working_set)) */
    	} /* End of loop through selectable descriptors */
	} while (end_server == FALSE);

cleanup_and_exit:
   	/*************************************************************/
   	/* Clean up all of the sockets that are open                 */
   	/*************************************************************/
   	for (i=0; i <= max_sd; ++i) {
    	if (FD_ISSET(i, &master_set)) {
        	close(i);
		}
   	}
	return rc;
}



/************************************************************************
    @brief  This function is used to send data outbound from Communication
            Manager.

*************************************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_send_data(COMM_MGR_SRV_MASTER *master, 
                                        COMM_MGR_SRV_MSG *srv_msg) {
    int rc = 0;
    if ((srv_msg == NULL) || (master == NULL) || (srv_msg->msg == NULL)) {
        COMM_MGR_SRV_ERROR("Received invalid argument");
        return COMM_MGR_SRV_INVALID_ARG;
    } 

    if (srv_msg->server_fd == 0) {
        COMM_MGR_SRV_ERROR("Server fd is 0 for UID [%d]. Aborting the send", srv_msg->msg->hdr.dst_uid);
    }

    uint32_t len = 0;
    len = sizeof(COMM_MGR_MSG_HDR) + (srv_msg->msg->hdr.payloadSize);
    memset(datastream, 0, sizeof(datastream));
    memcpy(datastream, srv_msg->msg, sizeof(COMM_MGR_MSG_HDR));
    memcpy(datastream + sizeof(COMM_MGR_MSG_HDR), srv_msg->msg->payload, (srv_msg->msg->hdr.payloadSize));

    rc = send(srv_msg->server_fd, datastream, len, 0);

    if (rc < 0) {
        COMM_MGR_SRV_ERROR("  send() failed");
        return COMM_MGR_SRV_SEND_ERR;
    }

    return COMM_MGR_SRV_SUCCESS;
}

/************************************************************************
    @brief  This function gets the list of registered sub-systems 
            from the system manager. These sub-systems will have full-access
            to the functionalties of communication manager and any of its
            inherited communication systems (example SCOM).

            The user apps are not part of registered apps. They are 
            maintained by app manager. They will have restricted access,
            and its upto the descrection of communication manager to
            grant resources/access to the communication.

            Also, the sys manager can revoke the special status of infra
            modules in case it feels to do. Then sys manager will send
            a message to the comm_manager via UDS, asking it to read the
            table again to get the updated list. This is applicable even
            in case of addition of new modules/restart of a module. The comm_manager
            then has to call this function again and update it local list
*************************************************************************/
COMM_MGR_SRV_ERR comm_mgr_create_registered_apps_list() {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    SYS_MGR_CLIENT_SHM_TBL_ENTRY *sysmgr_shm_obj_entry;

    UTILS_SHM_OBJ_HDR *shm_obj_hdr;
    
    shm_obj_hdr = utils_get_shared_obj_hdr(sysmgr_shm_obj->addr);
    COMM_MGR_SRV_TRACE("shm obj header : magic = 0x%x, refcount = %d, obj_id = %d\n",
            shm_obj_hdr->magic, shm_obj_hdr->refcount, shm_obj_hdr->obj_id);
    
    // Logic : This shm obj should already be created by the system manager.
    // So check for ref count along with the magic number just to be sure.
    if(shm_obj_hdr->magic != UTILS_SHM_OBJ_MAGIC_NUM) { 
        COMM_MGR_SRV_ERROR("Inconsistent shm obj (sysmgr client tbl shm obj). Magic = 0x%x",
                            shm_obj_hdr->magic);
        return COMM_MGR_SRV_BAD_SHM_OBJ;
    }

    // sysmgr sets userdefined with 0x01 when the table is ready to be read.
    // Wait till then. Should we have a timeout for this ??
    // 99% of the time, it is always ready for use
    while(!(shm_obj_hdr->userdefined.field1 & SYS_MGR_SHM_OBJ_USERDEFINED_READY)) {
        sleep(2);
    }
   
    COMM_MGR_SRV_TRACE("System Manager client shm tbl is ready for read");

    // Free the local list if it is allocated before. (For update case)
    if (comm_mgr_reg_apps_list) {
        free(comm_mgr_reg_apps_list);
    }

    comm_mgr_reg_apps_num = shm_obj_hdr->userdefined.field2; // Get the number of valid registered apps
    //copy the registered apps into a local copy for easier access. Copy only valid apps
    comm_mgr_reg_apps_list = (COMM_MGR_SRV_REG_APPS*)malloc(
                        comm_mgr_reg_apps_num * sizeof(COMM_MGR_SRV_REG_APPS));


    sysmgr_shm_obj_entry = (SYS_MGR_CLIENT_SHM_TBL_ENTRY *)sysmgr_shm_obj->addr;
    // First iterate over the shm obj to get the number of valid clients.
    COMM_MGR_SRV_DEBUG("System Manager Registered apps total : %d", comm_mgr_reg_apps_num);
    int index = 0;
    for (uint16_t i = 0; i < SYS_MGR_CLIENT_MAX_CLIENTS; i++) {
        if (sysmgr_shm_obj_entry->valid == FALSE) {
            sysmgr_shm_obj_entry++;
            continue;
        }

        COMM_MGR_SRV_DEBUG("    - UID : %d, clientID : %d", 
                                                    sysmgr_shm_obj_entry->UID,
                                                    sysmgr_shm_obj_entry->clientID);

        comm_mgr_reg_apps_list[index].UID = sysmgr_shm_obj_entry->UID;
        comm_mgr_reg_apps_list[index].clientID = sysmgr_shm_obj_entry->clientID;
        comm_mgr_reg_apps_list[index].priority = 0; // Will come back here later

        index++;
        sysmgr_shm_obj_entry++;
    }

    return ret;
}

COMM_MGR_SRV_MASTER* comm_mgr_srv_get_master(uint16_t masterID) {
	int masterIndex = COMM_MGR_SRV_GET_MASTER_INDEX(masterID);
    return &comm_mgr_srv_masters[masterIndex];
}

/************************************************************************/
/*			Internal helper functions						    		*/
/************************************************************************/

static void __comm_mgr_srv_init_master_id() {
	__comm_mgr_srv_master_id_array = (uint16_t *)malloc(sizeof(uint16_t) * COMM_MGR_SRV_MAX_MASTERS);

	for (uint8_t i = 0; i < COMM_MGR_SRV_MAX_MASTERS; i++) {
		__comm_mgr_srv_master_id_array[i] = 0xFFFF;
	}
}

static uint16_t __comm_mgr_srv_get_next_free_master_id(COMM_MGR_SRV_IPC_AF af) {
	for (uint8_t i = 0; i < COMM_MGR_SRV_MAX_MASTERS; i++) {
		if (__comm_mgr_srv_master_id_array[i] == 0xFFFF) {
			__comm_mgr_srv_master_id_array[i] = (af << 12) | i;
			return __comm_mgr_srv_master_id_array[i];
		}
	}
	COMM_MGR_SRV_ERROR("Exhausted all the Master IDs");
	return 0xFFFF;
}

static void __comm_mgr_srv_free_master_id(uint16_t masterID) {
	uint16_t index = COMM_MGR_SRV_GET_MASTER_INDEX(masterID);

	if (masterID == 0xFFFF) {
		return; // Error condition
	}
	__comm_mgr_srv_master_id_array[index] = 0xFFFF; // Free it
}


int main() {
    COMM_MGR_SRV_TRACE("Starting the %s...", COMM_MGR_SRV_APP_NAME);
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;

    log_lib_init(NULL, LOG_LVL_DEBUG); // Initialize logger
    utils_ds_init(); // Initialize utils data structure library

	if(comm_mgr_srv_init() != COMM_MGR_SRV_SUCCESS) {
        return -1;
    }

    // Create each master instance. If multiple master instances needs to be created
    // call create for each first
    uint16_t uds_masterID = 0;
    ret = comm_mgr_srv_create_uds_master(&uds_masterID, COMM_MGR_SRV_MASTER_DEFAULT_UDS);
    if (ret != COMM_MGR_SRV_SUCCESS) {
        __comm_mgr_srv_free_master_id(uds_masterID);
    }
   
    // Now start the various masters
    if(utils_task_handlers_create(COMM_MGR_SRV_TASK_ID_MAX, comm_mgr_srv_workers, 
                                COMM_MGR_SRV_LOCAL_EVENT_MAX, COMM_MGR_SRV_GLOBAL_EVENT_MAX) < 0) {
        goto err;
    }

    // Wait for all the master instances to finish their tasks
    utils_task_handlers_wait(COMM_MGR_SRV_TASK_ID_MAX, comm_mgr_srv_workers);
err:
	comm_mgr_srv_destroy();
    return 0;
}


