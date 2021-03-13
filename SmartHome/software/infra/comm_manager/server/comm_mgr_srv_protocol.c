/****************************************************************************
  Description : This file handles all the communication manager protocol   
          related functionalities. The protocol is common for all different
          types of Master instances. Every master instance needs to follow this
          set of protocols for reliable-data communication


        There are certain rules for the Communication Manager and the client
        which wishes to communicate with other clients in the system using
        Communication Manager directly or any of Commuication Manager's
        inherited communication system, should follow this protocol. Else
        the Communication manager will drop those packets.

    Each Master Instances will have a single global protocol queue. But each
    Master Instance will be responsible for serving only the UIDs under them

    For exact details about the protocol, refer the Software Design Specification

    Rules/Restricitons/Features :
        1) The Protocol is always initiated by the Communication Manager. If a
          client tries to initiate on its own, the Communication Manager will
          drop all requests from that client.
        2) The Communication Manager can apply various policies on the client.
          These policies vary from asking the client not to send packets/ 
          controlling the rate of packet send etc.
        3) For various supplimentary features of Communication Manager refer
         Software Design Specification
        
         


*****************************************************************************/
#include "comm_mgr_srv.h"
#include "comm_mgr_cmn.h"
#include "comm_mgr_srv_protocol.h"
#include "utils.h"
#include "system_mgr.h"


uint16_t comm_mgr_srv_static_uid_map_base = 0;
uint16_t comm_mgr_srv_static_uid_map_max = 0;
uint16_t comm_mgr_srv_dynamic_uid_map_base = 0;
uint16_t comm_mgr_srv_dynamic_uid_map_max = 0;

UTILS_DS_ID comm_mgr_srv_protocol_dsid = 0;

boolean comm_mgr_srv_protocol_initialized = FALSE;

// Two <UID, uid_ptr> tables are created. One for Static UIDs and another for dynamic. 
// The tables are indexed with the UIDs. Since the static and dynamic UID ranges 
//are different two tables are required (Saves memory as well)
COMM_MGR_SRV_UID_MAP **comm_mgr_srv_protocol_static_uid_tbl; // For ALL infra modules and some user apps
COMM_MGR_SRV_UID_MAP **comm_mgr_srv_protocol_dynamic_uid_tbl; // For ALL user apps

/*
    Mapping format :
        (UID Map)               (COMM_MGR_SRV_PROTO_TBL)
        UID1 , uid_ptr            uid_ptr -----> proto_tbl (for UID1) (M1 Master ID)
        UID2 , uid_ptr            uid_ptr -----> proto_tbl (for UID2) (M2)
        UID3 , uid_ptr            uid_ptr -----> proto_tbl (for UID3) (M1)
        
        Interest table:
            UID  - static_uid_tbl  : 010110.........MAX => Indicates that static UIDs 1,3,4 are interested in UID
                 - dynamic_uid_tbl : 00101..........MAX => Indicates that static UIDs 2,4 are interested in UID

    Queues Used:
      COMM_MGR_SRV_DSID_RECV            One receive queue per Master instance (For receving the data from clients)
      COMM_MGR_SRV_DSID_PROTO           One protocol queue per Master instance(Similar to dst queue, but for protocols only)
      COMM_MGR_SRV_DSID_SEND            One send data queue per Master instance (For sending the data to clients)
*/

/***********************************************************
    @brief This function initializes some of the basic tables
    needed for the Communication Manager Protocol to work.
    This function must be called only once.

***********************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_init() {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;

    if (comm_mgr_srv_protocol_initialized == TRUE) {
        COMM_MGR_SRV_ERROR("Communication Manager Protocol is already initialized");
        return COMM_MGR_SRV_PROTO_INIT_ERR;
    }

    comm_mgr_srv_static_uid_map_base = SYS_MGR_SYSTEM_STATIC_UID_BASE;
    comm_mgr_srv_static_uid_map_max = SYS_MGR_SYSTEM_STATIC_UID_MAX;
    comm_mgr_srv_dynamic_uid_map_base = SYS_MGR_SYSTEM_DYNAMIC_UID_BASE;
    comm_mgr_srv_dynamic_uid_map_max = SYS_MGR_SYSTEM_DYNAMIC_UID_MAX;
    
    comm_mgr_srv_protocol_static_uid_tbl = 
                  __comm_mgr_srv_protocol_create_uid_tbl(comm_mgr_srv_static_uid_map_base,
                                                         comm_mgr_srv_static_uid_map_max);

    if(comm_mgr_srv_protocol_static_uid_tbl == NULL) {
        COMM_MGR_SRV_ERROR("Failed to create the static uid table");
        return COMM_MGR_SRV_PROTO_INIT_ERR;
    }

    comm_mgr_srv_protocol_dynamic_uid_tbl = 
                  __comm_mgr_srv_protocol_create_uid_tbl(comm_mgr_srv_dynamic_uid_map_base,
                                                         comm_mgr_srv_dynamic_uid_map_max);

    if(comm_mgr_srv_protocol_dynamic_uid_tbl == NULL) {
        COMM_MGR_SRV_ERROR("Failed to create the dynamic uid table");
        return COMM_MGR_SRV_PROTO_INIT_ERR;
    }

    comm_mgr_srv_protocol_initialized = TRUE;

    return COMM_MGR_SRV_SUCCESS;
}

/***********************************************************
    @brief This function initializes the protocol needed
           for communication manager. This function is called for
           every Master instance

***********************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_master_init(COMM_MGR_SRV_MASTER *master) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;

    if (comm_mgr_srv_protocol_initialized == FALSE) {
        COMM_MGR_SRV_ERROR("Communication Manager Protocol is not yet initialized");
        return COMM_MGR_SRV_PROTO_INIT_ERR;
    }

    /* Create a Queue dedicated for Protocol packets
       Currently the size is 1024 which is good enough. If more than 1024 UIDs
       participate in the protocol AT the SAME time, then we will see drops for those
       UIDs. But when the queue frees up, it will be taken care of again. The comm mgr 
       will inform the client to delay the packet send for some time in such cases
     <TODO> Can enhance it to priority based queue, once utils lib supports it        
    */
    UTILS_QUEUE comm_mgr_srv_protocol_queue;
    comm_mgr_srv_protocol_queue.type = UTILS_QUEUE_CIRCULAR;
    comm_mgr_srv_protocol_queue.size = COMM_MGR_SRV_PROTOCOL_QUEUE_SIZE; 
    comm_mgr_srv_protocol_queue.isPriority = FALSE;
    comm_mgr_srv_protocol_queue.isProtected = FALSE;
    master->__DSID[COMM_MGR_SRV_DSID_PROTO] = utils_ds_queue_create(&comm_mgr_srv_protocol_queue);
    if (master->__DSID[COMM_MGR_SRV_DSID_PROTO] == 0) {
        COMM_MGR_SRV_ERROR("Failed to create Protocol queue");
        return COMM_MGR_SRV_PROTO_INIT_ERR;
    }

    COMM_MGR_SRV_DEBUG("Successfully intialized the protocol for the Master ID [%d], Proto DSID [0x%0x]",
                                        master->__masterID, master->__DSID[COMM_MGR_SRV_DSID_PROTO]);

    return ret;
}

/*
    @brief This function maintains a statemachine of the protocol
           required for a reliable data exchange. It describes a
           series of steps leading to a successful connection
           between any apps
    @param state Current state of the UID
    @param uid UID for which statemachine is run

    The Protocol packets uses one dedicated queue for ALL UIDs.
    Once the new protocol packet is added to the queue, a high priority
    event will be sent to response handler (static/dynamic) to send the
    packets to clients
*/
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_statemachine(COMM_MGR_PROTO_STATES state, 
                                                    uint16_t uid, COMM_MGR_SRV_MSG *srv_msg) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;                                                    
    switch(state) {
        case COMM_MGR_PROTO_DISCOVERY_START:
            ret = __comm_mgr_srv_protocol_discovery_start(uid, srv_msg); 
            break;
        case COMM_MGR_PROTO_DISCOVERY_DONE:
            ret = __comm_mgr_srv_protocol_discovery_done(uid, srv_msg); 
            break;
        case COMM_MGR_PROTO_DATATRANSFER_READY:
            ret = __comm_mgr_srv_protocol_datattransfer_ready(uid, srv_msg);
            break;
        default:
            COMM_MGR_SRV_ERROR("Invalid protocol state");
            return COMM_MGR_SRV_PROTO_INVALID_STATE;
    }

    // If an error occurs when in protocol states
    // Return the correct error code, so that Master instance will decide what to do next
    if (ret != COMM_MGR_SRV_SUCCESS) {
        COMM_MGR_SRV_ERROR("Error occurred for the UID [%d] during protocol", uid);
        return COMM_MGR_SRV_PROTO_ERR; // Return a common error code
    }

    return COMM_MGR_SRV_SUCCESS;
}

/*
    This function needs to be called by the Communication Manager Master
    instances whenever it receives a packet.
 
   <TODO> Also should we use another thread or use the response handler ???

*/
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_process_packet(COMM_MGR_SRV_MSG *srv_msg) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    if (srv_msg == NULL) {
        COMM_MGR_SRV_DEBUG("comm msg is NULL");
        return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }
    if (srv_msg->msg->hdr.magic != COMM_MGR_MSG_HDR_MAGIC) {
        COMM_MGR_SRV_DEBUG("Invalid comm msg. Wrong magic");
        return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }
    if ((!__comm_mgr_srv_is_uid_valid(srv_msg->msg->hdr.src_uid)) || 
        (!__comm_mgr_srv_is_uid_valid(srv_msg->msg->hdr.dst_uid))) {
        COMM_MGR_SRV_DEBUG("Invalid comm msg. Wrong UID");
        return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }

    // <TODO> Might need to check for compatible version (major/minor) when
    // inter-systems comes in future

    // If basic sanity passes, process the received packet and take action
    switch(srv_msg->msg->hdr.msg_type) {
        case COMM_MGR_MSG_PROTOCOL:
            ret =__comm_mgr_srv_protocol_process_proto_packet(srv_msg);
            break;
        case COMM_MGR_MSG_ACK:
            ret =__comm_mgr_srv_protocol_process_ack_packet(srv_msg);
            break;
        case COMM_MGR_MSG_DATA:
        case COMM_MGR_MSG_ANCILLARY:
            ret =__comm_mgr_srv_protocol_process_data_packet(srv_msg);
            break;            
        default:
            COMM_MGR_SRV_DEBUG("Invalid comm msg type");
            return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }
    return ret; 
}

/*
    This function handles various events associated with a client
*/
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_client_event(uint8_t ev, void *arg) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    switch(ev) {
        case COMM_MGR_SRV_HOUSEKEEP_EVENT_CLIENT_DOWN:
        {
            if (arg == NULL) {
                return COMM_MGR_SRV_INVALID_ARG;
            }
            uint32_t server_fd = *(uint32_t *)arg;
            uint16_t uid;
            COMM_MGR_SRV_PROTO_TBL *proto_tbl;
            boolean found_fd = FALSE;
            /*
                Search the UID map which has this server_fd and then remove the client data
                Currently the search mechasim is just a linear search. This is a very slow process.
                Might need to optimize in future <TODO>
            */
            for (uint16_t i = comm_mgr_srv_static_uid_map_base; i < comm_mgr_srv_static_uid_map_max; i++) {
                proto_tbl = __comm_mgr_srv_protocol_uid_map_get(i);
                if((proto_tbl) && (proto_tbl->server_fd == server_fd)) {
                    uid = proto_tbl->UID;
                    found_fd = TRUE;
                    break;
                }
            }

            if(found_fd == FALSE) {
                for (uint16_t i = 0; i < (comm_mgr_srv_dynamic_uid_map_max-comm_mgr_srv_dynamic_uid_map_base); i++) {
                    proto_tbl = __comm_mgr_srv_protocol_uid_map_get(i);
                    if((proto_tbl) && (proto_tbl->server_fd == server_fd)) {
                        uid = proto_tbl->UID;
                        found_fd = TRUE;
                        break;
                    }
                }
            }

            if (found_fd == TRUE) {
                COMM_MGR_SRV_DEBUG("Found the client with Server FD [%d], UID [%d], deleting from the protocol table",
                                server_fd, uid);            
                ret = __comm_mgr_srv_protocol_uid_map_remove(uid);
            } else {
                COMM_MGR_SRV_ERROR("Couldn't find the UID corresponding to the Server FD [%d]", server_fd);
                return COMM_MGR_SRV_BAD_SERVER;
            }
        }   
            break;
        default:
            return COMM_MGR_SRV_UNKNOWN_EVENT; 
    }
    return ret;
}

void comm_mgr_srv_msg_action(COMM_MGR_SRV_MSG *srv_msg) {
    if(srv_msg == NULL) {
        return;
    }
    
    switch(srv_msg->action) {
        case COMM_MGR_SRV_MSG_ACTION_DROP:
            comm_mgr_destroy_msg(srv_msg->msg);
            free(srv_msg);
            break;
        default:
            COMM_MGR_SRV_ERROR("Unsupported Server Message action [%d]", srv_msg->action);
            break;
    }
}

/******************************************************************************
                             Internal Functions
******************************************************************************/
static COMM_MGR_SRV_UID_MAP** __comm_mgr_srv_protocol_create_uid_tbl(uint32_t base, 
                                                                    uint32_t max) {
    uint32_t total_size = (max-base) * sizeof(COMM_MGR_SRV_PROTO_TBL);
    COMM_MGR_SRV_UID_MAP **uid_tbl = 
                        (COMM_MGR_SRV_UID_MAP**)malloc(total_size * sizeof(COMM_MGR_SRV_UID_MAP*));

    for (uint16_t i = 0; i < (max-base); i++) {
        uid_tbl[i] = (COMM_MGR_SRV_UID_MAP*)malloc(sizeof(COMM_MGR_SRV_UID_MAP));
        uid_tbl[i]->UID = i + base;
        uid_tbl[i]->uid_ptr = NULL;
        uid_tbl[i]->interest_tbl = __comm_mgr_srv_protocol_create_interest_tbl();
    }

    return uid_tbl;
}

/*
    Note : Interest tables are created for every UID exisiting in this system at the init time
           These interest tables can be accessed via the static/dynamic UID maps
*/
static COMM_MGR_SRV_INTEREST_TBL* __comm_mgr_srv_protocol_create_interest_tbl(void) {
    uint32_t static_tbl_size = ((comm_mgr_srv_static_uid_map_max - comm_mgr_srv_static_uid_map_base) / 32) + 1;
    uint32_t dynamic_tbl_size = ((comm_mgr_srv_dynamic_uid_map_max - comm_mgr_srv_dynamic_uid_map_base) / 32) + 1;
    COMM_MGR_SRV_INTEREST_TBL *interest_tbl = 
                                (COMM_MGR_SRV_INTEREST_TBL*)malloc(sizeof(COMM_MGR_SRV_INTEREST_TBL));
    interest_tbl->static_uid_tbl = (uint32_t *)malloc(sizeof(uint32_t) * static_tbl_size);
    interest_tbl->dynamic_uid_tbl = (uint32_t *)malloc(sizeof(uint32_t) * dynamic_tbl_size);
    memset(interest_tbl->static_uid_tbl, 0, sizeof(uint32_t) * static_tbl_size);
    memset(interest_tbl->dynamic_uid_tbl, 0, sizeof(uint32_t) * dynamic_tbl_size);

    return interest_tbl;
}                                            

/*
    How interest tables work :
        Say A, B, C are the 3 processes. Lets say A & B wants to send data to C
        Now A & B will be discovered by the Server Instance and lets say C is not yet learnt
        We will add A & B UIDs to the interest table of C first, to indicate when C is learnt, notify A & B.
        Also when A & B are discovered, their own interest tables are checked to see, if anybody is 
        interested in them.

    interest_tbl : This table belongs to the Dest UID
    uid : src UID which wants to talk to dest UID
    add : add/del the interest

    uid param will be evaluated and checked whether it belongs to static or dynamic range

    Note : A client can always implement its own logic to keep polling for the Server Instance to check
        if a dest UID has been learnt. By its efficient to use the notification mechanism
*/
static void 
__comm_mgr_srv_protocol_interest_tbl_update_uid(COMM_MGR_SRV_INTEREST_TBL *interest_tbl, uint16_t uid,
                                                boolean add) {
    if ((interest_tbl == NULL) || (!__comm_mgr_srv_is_uid_valid(uid))) {
        return;
    }
    uint16_t row, shift;

    if(__comm_mgr_srv_is_uid_static(uid)) {
        row = (uid-comm_mgr_srv_static_uid_map_base) / 32;
        shift = (uid-comm_mgr_srv_static_uid_map_base) % 32;

        if(add) {
            interest_tbl->static_uid_tbl[row] |= (1 << shift);
        } else {
            interest_tbl->static_uid_tbl[row] &= ~(1 << shift);
        }
    } else {
        row = (uid-comm_mgr_srv_dynamic_uid_map_base) / 32;
        shift = (uid-comm_mgr_srv_dynamic_uid_map_base) % 32;
   
        if(add) {
            interest_tbl->dynamic_uid_tbl[row] |= (1 << shift);
        } else {
            interest_tbl->dynamic_uid_tbl[row] &= ~(1 << shift);
        }
    }

    COMM_MGR_SRV_DEBUG("Updated the interest table for UID [%d], add [%s], row [%d], shift[%d]", 
                                    uid, add ? "True":"False", row, shift);
}

/*
    This function will send a learning message to all the UIDs present in the interest table.
    No ACK is required by the learing message.

    Note : This function is both compute intensive (always) and network intensive (depending on the number of
    apps in the system). So need to limit the invocation of this function as much as possible
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_interest_tbl_notify(uint16_t uid) {
    COMM_MGR_SRV_ERR rc = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_SRV_INTEREST_TBL* interest_tbl = __comm_mgr_srv_protocol_get_interest_tbl(uid);

    if(interest_tbl == NULL) {
        COMM_MGR_SRV_ERROR("Unable to find the interest table for uid [%d]", uid);
        return COMM_MGR_SRV_NOT_INITIALIZED; 
    }

    // Send the learning message to all the UIDs present in the interest_tbl
    // Search both static and dynamic tables
    uint32_t static_tbl_size = ((comm_mgr_srv_static_uid_map_max - comm_mgr_srv_static_uid_map_base) / 32) + 1;
    uint32_t dynamic_tbl_size = ((comm_mgr_srv_dynamic_uid_map_max - comm_mgr_srv_dynamic_uid_map_base) / 32) + 1;
  
    // First check the static table (To check if any static UIDs are interested in uid)
    if (interest_tbl->static_uid_tbl) {
        for (uint32_t i = 0; i < static_tbl_size; i++) {
            for (uint8_t j = 0; j < 32; j++) {
                if((interest_tbl->static_uid_tbl[i] >> j) & 0x01) {
                    __comm_mgr_srv_protocol_learning((i*32 + j), COMM_MGR_SUBMSG_LEARNING_ACTION_START, uid); 
                }
            }
        }
    }

    // Now check if any dynamic UIDs are interested
    if (interest_tbl->dynamic_uid_tbl) {
        for (uint32_t i = 0; i < dynamic_tbl_size; i++) {
            for (uint8_t j = 0; j < 32; j++) {
                if((interest_tbl->dynamic_uid_tbl[i] >> j) & 0x01) {
                    __comm_mgr_srv_protocol_learning((i*32 + j), COMM_MGR_SUBMSG_LEARNING_ACTION_START, uid); 
                }
            }
        }
    }

    return rc;
}

static COMM_MGR_SRV_INTEREST_TBL* __comm_mgr_srv_protocol_get_interest_tbl(uint16_t uid) {
    if(!__comm_mgr_srv_is_uid_valid(uid)) {
        return NULL;
    }
    if(__comm_mgr_srv_is_uid_static(uid) == TRUE) {
        return comm_mgr_srv_protocol_static_uid_tbl[uid]->interest_tbl;
    }
    return comm_mgr_srv_protocol_dynamic_uid_tbl[uid]->interest_tbl;
}

/*
    Note : The protocol is always intiated by Communication Manager. In case a client
    tries to initiate protocol on its own drop such packets
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_proto_packet(COMM_MGR_SRV_MSG *srv_msg) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    
    // If Protocol packet is received, the client src uid should already be present in the UID map
    // And, the current state should be in one of the protocol states for that client
    // Else, it means the client tried to start the protocol on its own => drop the packet
    COMM_MGR_SRV_PROTO_TBL *proto_tbl = __comm_mgr_srv_protocol_uid_map_get(srv_msg->msg->hdr.src_uid);
    if (proto_tbl == NULL) {
        COMM_MGR_SRV_DEBUG("Client UID [%d] tried to initiate the protocol. Discarding", srv_msg->msg->hdr.src_uid);
        return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }

    // Check the current protocol state of the UID
    switch(proto_tbl->proto_state) {
        case COMM_MGR_PROTO_DISCOVERY_START:
        {
            // When the server is in this state for the UID, it expects two things
            // - The proto_sub_state has to be 1
            // - The received message should be Discovery message with src_uid in its payload
            // Else we will discard the packet
            if (proto_tbl->proto_sub_state != 1) { // Check for sub-state
                goto drop_packet;
            }
            if ((srv_msg->msg->hdr.msg_type != COMM_MGR_MSG_PROTOCOL) || // Check for msg and submsg type
                (srv_msg->msg->hdr.submsg_type != COMM_MGR_SUBMSG_DISCOVERY)){
                goto drop_packet;
            }            
            if(srv_msg->msg->hdr.payloadSize != COMM_MGR_MSG_PROTOCOL_LIB_DISCOVERY_SIZE) { // Magic, Dst_uid
                goto drop_packet;
            } 
            if(srv_msg->msg->payload) {
                uint16_t magic, __dst_uid;
                memcpy(&magic, &(srv_msg->msg->payload[0]), sizeof(uint16_t));
                memcpy(&__dst_uid, &(srv_msg->msg->payload[2]), sizeof(uint16_t));
                if(magic != COMM_MGR_MSG_PROTOCOL_MAGIC) {
                    COMM_MGR_SRV_DEBUG("Bad magic received. Discarding");
                    goto drop_packet;
                }
                // Over write the dst_uid field in srv_msg with the dst_uid received in the Discovery message
                srv_msg->msg->hdr.dst_uid = __dst_uid; // Used for interest tables
            }
            proto_tbl->proto_state = COMM_MGR_PROTO_DISCOVERY_DONE; // Move the state to Discovery Done
            break;        
        }
        default:
            // Note : Execpt when the proto_state of the client is in COMM_MGR_PROTO_DISCOVERY_START,
            // we should not receive any protocol packets from that client.
            return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }

    ret = comm_mgr_srv_protocol_statemachine(proto_tbl->proto_state, srv_msg->msg->hdr.src_uid, srv_msg); 

    return ret;

drop_packet:
    srv_msg->action |= COMM_MGR_SRV_MSG_ACTION_DROP;
    return COMM_MGR_SRV_SUCCESS;
}

/*
    This function handles the ack/nack for data/protocol packets.
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_ack_packet(COMM_MGR_SRV_MSG *srv_msg) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_SRV_PROTO_TBL *proto_tbl = __comm_mgr_srv_protocol_uid_map_get(srv_msg->msg->hdr.src_uid);

    if (proto_tbl == NULL) { // New UID
        // A client cannot send the ACK, unless it is already discovered by the Comm Server
        // Discard all ack/nacks
        COMM_MGR_SRV_DEBUG("Client UID [%d] sent a ack packet even before it is discovered. Dropping",
                            srv_msg->msg->hdr.src_uid);
        srv_msg->action |= COMM_MGR_SRV_MSG_ACTION_DROP;
        return COMM_MGR_SRV_SUCCESS;       
    }

    // Check the current protocol state for the src UID
    switch (proto_tbl->proto_state) {
        // When the server is in Discovery Start state, it expects an PROTO_ACK packet
        // from client before receving the Discovery message from the client
        case COMM_MGR_PROTO_DISCOVERY_START:
            if((srv_msg->msg->hdr.msg_type != COMM_MGR_MSG_ACK) || 
                (srv_msg->msg->hdr.submsg_type != COMM_MGR_SUBMSG_PROTO_ACK)) {
                goto drop_packet;
            }
            // Indicates that a PROTO_ACK is received
            proto_tbl->proto_sub_state = 1;
            break;

    }

    return COMM_MGR_SRV_SUCCESS; // <TODO> Should the packet be dropped in success case ?

drop_packet:
    srv_msg->action |= COMM_MGR_SRV_MSG_ACTION_DROP;
    return COMM_MGR_SRV_SUCCESS;       
}

/*
    Please refer the Software Design Specification to know about the Protocol
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_data_packet(COMM_MGR_SRV_MSG *srv_msg) {
    /* <TODO> We need to maintain a data queue per dest UID
       <TODO> Also we need a seperate data queue per src UID. This is used only when dest UID is not
            learnt. We will register for a new event, when we are waiting on some dest UID to 
            be discovered and learnt. Once the dest UID is learnt , we will dequeue from this queue 
           and insert to the dest UID queue.
       <TODO> We will have two threads for sending data. One dedicated for Dest as Static UID and 
            another for Dynamic Dest UID. These threads will be per Master Instances
    */
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_SRV_PROTO_TBL *proto_tbl = __comm_mgr_srv_protocol_uid_map_get(srv_msg->msg->hdr.src_uid);
    if (proto_tbl == NULL) { //  case 1 : New UID discovered
        // If an Ancillary message comes without a pre-exisitng entry in protocol table, drop it
        if(srv_msg->msg->hdr.msg_type == COMM_MGR_MSG_ANCILLARY) {
            COMM_MGR_SRV_ERROR("Received Ancillary message before the UID [%d] was discovered",srv_msg->msg->hdr.src_uid);
            return COMM_MGR_SRV_PROTO_BAD_PACKET;
        }

        COMM_MGR_SRV_DEBUG("Client UID [%d] connecting to the Communication Manager for the first time (dst_uid [%d])",
                                                srv_msg->msg->hdr.src_uid, srv_msg->msg->hdr.dst_uid);
        proto_tbl = __comm_mgr_srv_protocol_uid_map_insert(srv_msg->msg->hdr.src_uid, srv_msg->server_fd); 
        
        // Start the Protocol State Machine (current state = COMM_MGR_PROTO_DISCOVERY_START) 
        ret = comm_mgr_srv_protocol_statemachine(proto_tbl->proto_state, srv_msg->msg->hdr.src_uid, srv_msg);

        return ret;
    }

    // Check the current protocol status for the src UID
    // This indicates that the Discovery has just been completed for the client and client library
    // has sent the data again for sending
    if (proto_tbl->proto_state == COMM_MGR_PROTO_DISCOVERY_DONE) {
        proto_tbl->proto_state = COMM_MGR_PROTO_DATATRANSFER_READY;
    }

    if(proto_tbl->proto_state != COMM_MGR_PROTO_DATATRANSFER_READY) {
        // If the src UID is not yet Discovered, should drop this data packet.
        COMM_MGR_SRV_DEBUG("Client UID [%d] sent a data packet while in protocol state [%d]",
                            srv_msg->msg->hdr.src_uid, proto_tbl->proto_state);
        srv_msg->action |= COMM_MGR_SRV_MSG_ACTION_DROP;
        return COMM_MGR_SRV_SUCCESS;
    }

    // If the control comes here, it means that src uid has been Discovered.
    // Call the state machine with COMM_MGR_PROTO_DATATRANSFER_READY state
    // Also, if it is an Ancillary message, add the Server FD of Ancillary Channel to the protcol table for the UID
    if(srv_msg->msg->hdr.msg_type == COMM_MGR_MSG_ANCILLARY) {
        if (proto_tbl->server_anc_fd == -1) { // If Not yet updated, update it
            proto_tbl->server_anc_fd = srv_msg->server_fd;
        }

        // If the Dest UID is of Communication Manager, then no need to forward the packet. This happens when the 
        // src_uid has sent an response to an Ancillary Learning message request from Communication Manager
        // Just drop this packet and start processing any pending previous messages. Now they can be forwarded
        if(srv_msg->msg->hdr.dst_uid == SYS_MGR_SYSTEM_UID_COMM_MANAGER) {
            COMM_MGR_ANC_MSG *anc_msg = COMM_MGR_GET_ANC_MSG(srv_msg->msg); 
            // Check who is Master instance of this task
            COMM_MGR_SRV_MASTER *master = comm_mgr_srv_protocol_get_master(COMM_MGR_SRV_MASTER_CONFLICT_MSG, (void *)srv_msg);
           
            if(anc_msg->hdr.anc_msg_type == COMM_MGR_ANC_MSG_SYSTEM_INFO) {
                srv_msg->action |= COMM_MGR_SRV_MSG_ACTION_DROP; // We are done using this. Drop it

                // Now we need to ask the Master instance to process the previously saved messages again
                // We will ask the Housekeeper to move all the Ancillary destined to this Dest UID to be moved
                // from Transit DSID to Send DSID and finally send an event to the response handler
                if (master->__dsid_cb[COMM_MGR_SRV_DSID_HOUSEKEEP]) {
                    COMM_MGR_SRV_HK_JOB *hk_job = (COMM_MGR_SRV_HK_JOB*)malloc(sizeof(COMM_MGR_SRV_HK_JOB));
                    COMM_MGR_SRV_TRANSIT_ENTRY *transit_entry = (COMM_MGR_SRV_TRANSIT_ENTRY*)malloc(sizeof(COMM_MGR_SRV_TRANSIT_ENTRY));
                    hk_job->event = COMM_MGR_SRV_HOUSEKEEP_EVENT_FWD_ANC_TRANSIT;
                    transit_entry->masterID = master->__masterID; 
                    transit_entry->which_dst = COMM_MGR_SRV_TRANSIT_SELECT_SPECIFIC;
                    transit_entry->dst_uid = srv_msg->msg->hdr.src_uid; //copy the src UID. This will be dest for transit
                    transit_entry->which_src = COMM_MGR_SRV_TRANSIT_SELECT_NONE;
                    transit_entry->src_uid = 0;
                    hk_job->eventData = (void *)transit_entry;
                    master->__dsid_cb[COMM_MGR_SRV_DSID_HOUSEKEEP](master->__DSID[COMM_MGR_SRV_DSID_HOUSEKEEP], (void *)hk_job, NULL, NULL);
                } else {
                    COMM_MGR_SRV_ERROR("DSID [%s] Callback not set. Not sending the house keeping job to Master ID %d",
                                             DECODE_ENUM(COMM_MGR_SRV_DSID, COMM_MGR_SRV_DSID_HOUSEKEEP), master->__masterID); 
                }

                return COMM_MGR_SRV_SUCCESS;
            }
            return COMM_MGR_SRV_PROTO_BAD_PACKET; // Currently there is no other use case where it should come here.
        }
    }

    ret = comm_mgr_srv_protocol_statemachine(proto_tbl->proto_state, srv_msg->msg->hdr.src_uid, srv_msg);

    return ret;
}

/*
    Along with the Discovery message, server also sends the system wide UID map
    information to the client int its payload

    Once the Discovery message is sent to the client, the server should wait for
    an PROTO_ACK from the client.

    Followed by a PROTO_ACK, the server will receive the Discovery message from the
    client with src_uid filled in its payload
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_discovery_start(uint16_t uid, COMM_MGR_SRV_MSG *srv_msg) {
    // Send a discovery start msg to the UID by adding to protocol queue
    // and sending a high priority event to response handlers
    uint16_t payload[COMM_MGR_MSG_PROTOCOL_SRV_DISCOVERY_SIZE/2];
    payload[0] = COMM_MGR_MSG_PROTOCOL_MAGIC;
    payload[1] = comm_mgr_srv_static_uid_map_max; 
    payload[2] = comm_mgr_srv_static_uid_map_base;
    payload[3] = comm_mgr_srv_dynamic_uid_map_max;
    payload[4] = comm_mgr_srv_dynamic_uid_map_base;
    payload[5] = srv_msg->msg->hdr.dst_uid; 

    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_MSG_HDR hdr;

    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    hdr.src_uid = SYS_MGR_SYSTEM_UID_COMM_MANAGER;
    hdr.dst_uid = uid;
    hdr.msg_type = COMM_MGR_MSG_PROTOCOL;
    hdr.submsg_type = COMM_MGR_SUBMSG_DISCOVERY;    
    hdr.priority = COMM_MGR_MSG_PRIORITY_HIGH;
    hdr.ack_required = TRUE;
    hdr.payloadSize = sizeof(payload);    

    ret = __comm_mgr_srv_send_msg(&hdr, (char *)payload);

    COMM_MGR_SRV_DEBUG("Discovery started for UID [%d]", uid);

    return ret;
}

/*    
    Once the Discovery message is received from the src UID, an PROTO_ACK has to be
    sent to that Client, so that the client knows it has been successfully discovered 
    by the Server and it is ready to send data

    Note : The proto_state for the client is not changed to "COMM_MGR_PROTO_DATATRANSFER_READY"
    right after PROTO_ACK for Discovery message is sent in Discovery Done state

    The client library sends the data packet again. The proto_state will be chnaged to
    "COMM_MGR_PROTO_DATATRANSFER_READY" at that time. This will also make sure that,
    the ACK for the Discovery Done has been actually received by the client
   
    Also, we will update the interest tables for the dest UID and also notify any UIDs waiting 
    in the interest table of src UID
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_discovery_done(uint16_t uid, COMM_MGR_SRV_MSG *srv_msg) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_MSG_HDR hdr;

    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    hdr.src_uid = SYS_MGR_SYSTEM_UID_COMM_MANAGER;
    hdr.dst_uid = uid;
    hdr.msg_type = COMM_MGR_MSG_ACK;
    hdr.submsg_type = COMM_MGR_SUBMSG_PROTO_ACK;
    hdr.priority = COMM_MGR_MSG_PRIORITY_HIGH;
    hdr.ack_required = FALSE;
    hdr.payloadSize = 0;    

    ret = __comm_mgr_srv_send_msg(&hdr, NULL);

    // Update the interest table of Dest UID, saying src_uid is interested.
    COMM_MGR_SRV_INTEREST_TBL *interest_tbl = __comm_mgr_srv_protocol_get_interest_tbl(srv_msg->msg->hdr.dst_uid);
    __comm_mgr_srv_protocol_interest_tbl_update_uid(interest_tbl, uid, TRUE); 
    
    // Now notify all interested UIDs in the interest table of src_uid
    ret = __comm_mgr_srv_protocol_interest_tbl_notify(uid);

    COMM_MGR_SRV_DEBUG("Discovery is done for UID [%d]", uid);

    return ret;
}

/*
    This function sends learning messages to the UID

    @param action : This optional parameter specifes action which the receiver has
    to take upon receving the learning message. 
    
    The learning messages can be overrided to be used for purposes like sending 
    messages to the receiver to start, stop, abort, throttle etc

    This function can be called at any point of time.
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_learning(uint16_t uid, 
                                           COMM_MGR_SUBMSG_LEARNING_ACTION_TYPE action, uint16_t dst_uid) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_MSG_HDR hdr;
    uint16_t payload[COMM_MGR_MSG_PROTOCOL_SRV_LEARNING_SIZE/2];

    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    COMM_MGR_SRV_PROTO_TBL *proto_tbl = __comm_mgr_srv_protocol_uid_map_get(uid);
    if(proto_tbl == NULL) { // This should NEVER happen
        COMM_MGR_SRV_ERROR("Unable to find protocol table for uid [%d]", uid); 
        return COMM_MGR_SRV_PROTO_ERR;
    }

    hdr.src_uid = SYS_MGR_SYSTEM_UID_COMM_MANAGER;
    hdr.dst_uid = uid;
    hdr.msg_type = COMM_MGR_MSG_PROTOCOL;
    hdr.submsg_type = COMM_MGR_SUBMSG_LEARNING;
    hdr.priority = COMM_MGR_MSG_PRIORITY_HIGH;
    hdr.ack_required = FALSE;
    hdr.payloadSize = sizeof(payload);    

    payload[0] = COMM_MGR_MSG_PROTOCOL_MAGIC;
    payload[1] = action;
    payload[2] = dst_uid;

    COMM_MGR_SRV_DEBUG("Sending learning message for UID [%d], action [%d], dst_uid [%d]", uid, action, dst_uid);

    ret = __comm_mgr_srv_send_msg(&hdr, (char *)payload);
    return ret;
}

/*
    This function is used to send Ancillary Learning message to Dest UID
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_anc_learning(uint16_t dst_uid) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_MSG_HDR hdr;
    COMM_MGR_SRV_PROTO_TBL *proto_tbl = __comm_mgr_srv_protocol_uid_map_get(dst_uid);

    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    if(proto_tbl == NULL) { // This should NEVER happen
        COMM_MGR_SRV_ERROR("Unable to find protocol table for uid [%d]", dst_uid); 
        return COMM_MGR_SRV_PROTO_ERR;
    }

    hdr.src_uid = SYS_MGR_SYSTEM_UID_COMM_MANAGER;
    hdr.dst_uid = dst_uid;
    hdr.msg_type = COMM_MGR_MSG_PROTOCOL;
    hdr.submsg_type = COMM_MGR_SUBMSG_ANC_LEARNING;
    hdr.priority = COMM_MGR_MSG_PRIORITY_HIGH;
    hdr.ack_required = FALSE;
    hdr.payloadSize = 0;

    COMM_MGR_SRV_DEBUG("Sending Ancillary learning message for UID [%d]", dst_uid);

    ret = __comm_mgr_srv_send_msg(&hdr, NULL);
    return ret;
}
                                                

/*
    This function decides if the messages can be forwarded to the dest UID or not.
    
    In case if the dest UID is not yet discovered it sends a learning message with NULL<dst_uid> in payload

*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_datattransfer_ready(uint16_t uid, COMM_MGR_SRV_MSG *srv_msg) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_MSG_HDR hdr;
    uint16_t payload[2];

    memset(&hdr, 0, sizeof(COMM_MGR_MSG_HDR));

    // Now check if the dest UID for the data packet is Discovered/Learnt already
    COMM_MGR_SRV_PROTO_TBL *dest_proto_tbl = __comm_mgr_srv_protocol_uid_map_get(srv_msg->msg->hdr.dst_uid);

    if (dest_proto_tbl == NULL) { //  case 1 : Dest UID not discovered yet

        // If it is an Ancillary message, one pre-requisite is, the Dest UID should have been discovered.
        // The src UID needs to try again later, send a learning action message with Ancillary Stop:        
        if(srv_msg->msg->hdr.msg_type == COMM_MGR_MSG_ANCILLARY) {
            COMM_MGR_SRV_ERROR("Dest UID [%d] is not yet discovered. So dropping the Ancillary message from Src UID [%d]",
                                       srv_msg->msg->hdr.dst_uid, srv_msg->msg->hdr.src_uid);
            ret = __comm_mgr_srv_protocol_learning(uid, COMM_MGR_SUBMSG_LEARNING_ACTION_ANC_STOP, srv_msg->msg->hdr.dst_uid);
        } else {
            // Notify the client not to send any more data packets till a learning message with start is sent
            ret = __comm_mgr_srv_protocol_learning(uid, COMM_MGR_SUBMSG_LEARNING_ACTION_STOP, srv_msg->msg->hdr.dst_uid);
        }
    } else { // Dest UID is already discovered/learnt
        
        // If its an Ancillary message, check if the Ancillary Channel Server FD exists.
        // If not, need to send a Ancillary Learning message to dest UID
        if (srv_msg->msg->hdr.msg_type == COMM_MGR_MSG_ANCILLARY) {
            if(dest_proto_tbl->server_anc_fd == -1) { // Dest UIDs Ancillary channel Server FD not yet learnt
                ret = __comm_mgr_srv_protocol_anc_learning(srv_msg->msg->hdr.dst_uid);
                if(ret == COMM_MGR_SRV_SUCCESS) {
                    srv_msg->action |= COMM_MGR_SRV_MSG_ACTION_HOLD; // Ask the Master instance to hold the packet
                    return COMM_MGR_SRV_SUCCESS;
                }
                return ret;
            }
        }

        // We dont have to notify the src UID here. Simply forward the data to dest UID
        COMM_MGR_SRV_DEBUG("FINALLY THE PACKETS ARE ACTUALLY GOING TO THE DESTINATION APP!!!!");
        
        // Since the data is now ready to be forwarded, put the dest fd in the srv_msg
        // This actually does the magic of forwarding
        if(srv_msg->msg->hdr.msg_type == COMM_MGR_MSG_ANCILLARY) {
            srv_msg->server_fd = dest_proto_tbl->server_anc_fd; // Use the Server FD of Dest UID Ancillary Channel
        } else {
            srv_msg->server_fd = dest_proto_tbl->server_fd; // Use the Server FD of Dest UID Normal Channel
        }

        ret = __comm_mgr_srv_forward_data(srv_msg); // Forward the original received message
    }
    return ret;
}

/*
    This function is desgined to light weight with it acting as a passthrough.
    Once the protocol stages are done, this function should be used always. There are
    no memory allocations also done by this function

    There is always a possiblity that data packets can be dropped while using this
    fnction (best effort)
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_forward_data(COMM_MGR_SRV_MSG *srv_msg) {
    if (srv_msg == NULL) {
        COMM_MGR_SRV_ERROR("Bad server message");
        return COMM_MGR_SRV_SEND_ERR; 
    }

    // Check who is Master instance of this task
    COMM_MGR_SRV_MASTER *master = comm_mgr_srv_protocol_get_master(COMM_MGR_SRV_MASTER_CONFLICT_MSG, (void *)srv_msg);

    // Only data packets goes into the COMM_MGR_SRV_DSID_SEND
    if ((srv_msg->msg->hdr.msg_type == COMM_MGR_MSG_DATA) ||
        (srv_msg->msg->hdr.submsg_type == COMM_MGR_SUBMSG_DATA_ACK) ||
        (srv_msg->msg->hdr.submsg_type == COMM_MGR_SUBMSG_DATA_NACK) ||
        (srv_msg->msg->hdr.msg_type == COMM_MGR_MSG_ANCILLARY)) {
        // Insert the msg to the data queue and send event
        if(master->__dsid_cb[COMM_MGR_SRV_DSID_SEND](master->__DSID[COMM_MGR_SRV_DSID_SEND], 
                                                       (void *)srv_msg, NULL, NULL) != COMM_MGR_SRV_SUCCESS) {
            COMM_MGR_SRV_ERROR("Failed to insert the data to DSID 0x%0x", master->__DSID[COMM_MGR_SRV_DSID_SEND]);
            return COMM_MGR_SRV_UTILS_DSID_ERR;
        }
    }
    return COMM_MGR_SRV_SUCCESS;
}

/*
    This function is little heavier with lot of memory allocations and validations.
    This is mainly used during protocol stages to be very reliant
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_send_msg(COMM_MGR_MSG_HDR *hdr, char *payload) {

    COMM_MGR_MSG *msg = comm_mgr_create_msg(hdr->src_uid, hdr->dst_uid,
                                            hdr->msg_type, (char *)payload, hdr->payloadSize);

    if (msg == NULL) {
        COMM_MGR_SRV_ERROR("There is no memory left to process the packet, dst uid[%d]", hdr->dst_uid);
        return COMM_MGR_SRV_OUT_OF_MEMORY;
    }

    // Get the protocol tbl for this UID
    COMM_MGR_SRV_PROTO_TBL *proto_tbl = __comm_mgr_srv_protocol_uid_map_get(hdr->dst_uid);
    if (proto_tbl == NULL) { // This is an error case. Abort the protocol for this UID
        COMM_MGR_SRV_ERROR("Failed to get the protocol table for UID [%d], in Discovery state", hdr->dst_uid);
        return COMM_MGR_SRV_PROTO_ERR;
    }
    
    // Also get the Master instance for this UID
    COMM_MGR_SRV_MASTER *master = comm_mgr_srv_get_master(proto_tbl->masterID);
    if (master == NULL) {
        COMM_MGR_SRV_ERROR("Unable to get the Master instance for the UID [%d], master ID [%d]",
                                    hdr->dst_uid, proto_tbl->masterID);
        return COMM_MGR_SRV_PROTO_ERR;
    }

    msg->hdr.priority = hdr->priority;    
    msg->hdr.submsg_type = hdr->submsg_type;
    msg->hdr.ack_required = hdr->ack_required;

    COMM_MGR_SRV_DEBUG("Sending msg_type [%d] submsg_type [%d] to UID [%d] with fd [%d]", 
                            hdr->msg_type, hdr->submsg_type, hdr->dst_uid, proto_tbl->server_fd);

    COMM_MGR_SRV_MSG *comm_mgr_srv_msg = (COMM_MGR_SRV_MSG *)malloc(sizeof(COMM_MGR_SRV_MSG));
    comm_mgr_srv_msg->server_fd = proto_tbl->server_fd;
    comm_mgr_srv_msg->msg = msg;

    // Only protocol and proto ack/nacks goes into the COMM_MGR_SRV_DSID_PROTO
    if ((hdr->msg_type == COMM_MGR_MSG_PROTOCOL) ||
        (hdr->submsg_type == COMM_MGR_SUBMSG_PROTO_ACK) ||
        (hdr->submsg_type == COMM_MGR_SUBMSG_PROTO_NACK)) {
        // Insert the msg to the protocol queue and send event
        if(master->__dsid_cb[COMM_MGR_SRV_DSID_PROTO](master->__DSID[COMM_MGR_SRV_DSID_PROTO], 
                                            (void *)comm_mgr_srv_msg, NULL, NULL) != COMM_MGR_SRV_SUCCESS) {
            COMM_MGR_SRV_ERROR("Failed to insert the data to DSID 0x%0x", master->__DSID[COMM_MGR_SRV_DSID_PROTO]);
            return COMM_MGR_SRV_UTILS_DSID_ERR;
        }
    }

    return COMM_MGR_SRV_SUCCESS;
}

static boolean __comm_mgr_srv_is_uid_valid(uint16_t uid) {
    if (((uid >= comm_mgr_srv_static_uid_map_base) && 
        (uid < comm_mgr_srv_static_uid_map_max)) ||
        ((uid >= comm_mgr_srv_dynamic_uid_map_base) &&
        (uid < comm_mgr_srv_dynamic_uid_map_max))) {
        return TRUE;
    }
    return FALSE; 
}

// UID should have been validated using __comm_mgr_srv_is_uid_valid
static boolean __comm_mgr_srv_is_uid_static(uint16_t uid) {
    if ((uid >= comm_mgr_srv_static_uid_map_base) && 
        (uid < comm_mgr_srv_static_uid_map_max)) {
        return TRUE;
    }
    return FALSE;
}

// UID should have been validated using __comm_mgr_srv_is_uid_valid
static COMM_MGR_SRV_PROTO_TBL* __comm_mgr_srv_protocol_uid_map_get(uint16_t uid) {
    if(__comm_mgr_srv_is_uid_static(uid) == TRUE) {
        if (comm_mgr_srv_protocol_static_uid_tbl[uid]->UID == COMM_MGR_SRV_INVALID_UID) {
            return NULL;
        }
        return comm_mgr_srv_protocol_static_uid_tbl[uid]->uid_ptr;
    }
    if (comm_mgr_srv_protocol_dynamic_uid_tbl[uid]->UID == COMM_MGR_SRV_INVALID_UID) {
        return NULL;
    }
    return comm_mgr_srv_protocol_dynamic_uid_tbl[uid]->uid_ptr;
}

static COMM_MGR_SRV_PROTO_TBL* __comm_mgr_srv_protocol_uid_map_insert(uint16_t uid, uint32_t fd) {
    COMM_MGR_SRV_PROTO_TBL *proto_entry = NULL;

    proto_entry = (COMM_MGR_SRV_PROTO_TBL *)malloc(sizeof(COMM_MGR_SRV_PROTO_TBL));
    memset(proto_entry, 0, sizeof(COMM_MGR_SRV_PROTO_TBL));

    proto_entry->UID = uid;
    proto_entry->server_fd = fd;
    proto_entry->server_anc_fd = -1; // This will be updated later using COMM_MGR_SUBMSG_ANC_LEARNING
    proto_entry->proto_state = COMM_MGR_PROTO_DISCOVERY_START;
    proto_entry->proto_sub_state = 0; // Ack not yet received

    // Check who is Master instance of this task
    COMM_MGR_SRV_MASTER *master = comm_mgr_srv_protocol_get_master(COMM_MGR_SRV_MASTER_CONFLICT_FIRST, NULL);

    if(master == NULL) {
        COMM_MGR_SRV_ERROR("Not to able to identify the Master for the UID [%d]", uid);
        return NULL;
    }

    proto_entry->masterID = master->__masterID;

    // Add the entry to the UID map
    if(__comm_mgr_srv_is_uid_static(uid)) {
        comm_mgr_srv_protocol_static_uid_tbl[uid]->uid_ptr = proto_entry;
    } else {
        comm_mgr_srv_protocol_dynamic_uid_tbl[uid]->uid_ptr = proto_entry;
    }

    COMM_MGR_SRV_DEBUG("Mapped UID [%d] to server fd [%d] in the [%s] UID table", 
                                        uid, fd, __comm_mgr_srv_is_uid_static(uid) ? "Static":"Dynamic");

    return proto_entry;
}

/*
    This function removes an UID from the UID map

    It cleans up only the uid_ptr in the map. The entry for that UID in the
    UID Map remains always along with the interest table.
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_uid_map_remove(uint16_t uid) {
    
    COMM_MGR_SRV_PROTO_TBL *proto_tbl = __comm_mgr_srv_protocol_uid_map_get(uid);

    if (proto_tbl == NULL) {
        COMM_MGR_SRV_ERROR("Unable to find the UID [%d] in the protocol table", uid);
        return COMM_MGR_SRV_PROTO_ERR;
    }

    if(proto_tbl->property) {
        free(proto_tbl->property);
    }   

    free(proto_tbl);

    // Delete the entry from the UID map
    if(__comm_mgr_srv_is_uid_static(uid)) {
        comm_mgr_srv_protocol_static_uid_tbl[uid]->uid_ptr = NULL;
    } else {
        comm_mgr_srv_protocol_dynamic_uid_tbl[uid]->uid_ptr = NULL;
    }

    return COMM_MGR_SRV_SUCCESS;
}

/*
    This function can be called by any Task, to get it Master Information

    Very useful say when we have a common function which is run by two tasks
    belonging to two Master instances, then we need to identify the Master in
    some cases to make some decisions like which DSID to use etc

    Refer the UTILS task handler lib and its sample test example to get to know
    about the API

    Note: In a multi master case, when load sharing is enabled, a single task can 
    be owned by multiple master instances. In such cases for a task to determine
    who is my master, it becomes ambigous. In such cases, conflict are resolved
    using a conflict vector which will be implmeneted by the type of Master instance.
    For example in UDS type of Master instances, a vector needs to be implemented which
    will be very specific for that type of Master.
*/
COMM_MGR_SRV_MASTER* comm_mgr_srv_protocol_get_master(COMM_MGR_SRV_MASTER_CONFLICT_TYPE type, void *arg) {
    UTILS_TASK_HANDLER_STATUS *task_st = utils_task_handler_get_taskInfo();

    if ((task_st == NULL) || 
        (task_st->__task == NULL) || 
        (task_st->__task->arg == NULL)) {
        return NULL;
    }
    // This should have been set during the Master instance creation
    uint16_t masterID = 0;
    COMM_MGR_SRV_WORKER_ARG *workerArg = (COMM_MGR_SRV_WORKER_ARG *)task_st->__task->arg;
    if(workerArg == NULL) {
        return NULL;
    }

    // Check if its a multi-master case with load sharing enabled scenerio.
    if((workerArg->num_masterFDs > 0) && (workerArg->isLoadSharingEn)) {
        masterID = workerArg->resolver(type, arg, (void *)workerArg);
    }        

    return comm_mgr_srv_get_master(masterID);
}


