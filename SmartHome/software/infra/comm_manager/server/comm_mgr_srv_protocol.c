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

// Two <UID, uid_ptr> tables are created. One for Static UIDs and another for dynamic. 
// The tables are indexed with the UIDs. Since the static and dynamic UID ranges 
//are different two tables are required (Saves memory as well)
COMM_MGR_SRV_UID_MAP *comm_mgr_srv_protocol_static_uid_tbl; // For ALL infra modules and some user apps
COMM_MGR_SRV_UID_MAP *comm_mgr_srv_protocol_dynamic_uid_tbl; // For ALL user apps
/*
    Mapping format :
        (UID Map)               (COMM_MGR_SRV_PROTO_TBL)
        UID1 , uid_ptr            uid_ptr -----> proto_tbl (for UID1)
        UID2 , uid_ptr            uid_ptr -----> proto_tbl (for UID2)
        UID3 , uid_ptr            uid_ptr -----> proto_tbl (for UID3)

    Queues Used:
      comm_mgr_srv_protocol_dsid        One queue for all UIDs (Similar to dst queue, but for protocols only)
      comm_mgr_srv_src_uid_dsid[uid]    One queue for each src UID (During discovery phase and when dst is not learnt)
      comm_mgr_srv_dst_uid_dsid[uid]    One queue for each dst UID (For data tx purpose)
*/

/***********************************************************
    @brief This function initializes the protocol needed
           for communication manager

            Only static tbl is created during the init time.
            For the dynamic tbl creation, the app manager has to
            request the communication manager.
***********************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_init() {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;

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

    if(comm_mgr_srv_protocol_static_uid_tbl == NULL) {
        COMM_MGR_SRV_ERROR("Failed to create the static uid table");
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
    comm_mgr_srv_protocol_dsid = utils_ds_queue_create(&comm_mgr_srv_protocol_queue);
    if (comm_mgr_srv_protocol_dsid == 0) {
        COMM_MGR_SRV_ERROR("Failed to create Protocol queue");
        return COMM_MGR_SRV_PROTO_INIT_ERR;
    }

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
                                                    uint16_t uid) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;                                                    
    switch(state) {
        case COMM_MGR_PROTO_DISCOVERY_START:
            ret = __comm_mgr_srv_protocol_discovery_start(uid); 
            break;
        case COMM_MGR_PROTO_DISCOVERY_DONE:
            ret = __comm_mgr_srv_protocol_discovery_done(); 
            break;
        case COMM_MGR_PROTO_LEARNING_START:
            ret = __comm_mgr_srv_protocol_learning_start(); 
            break;
        case COMM_MGR_PROTO_LEARNING_DONE:
            ret = __comm_mgr_srv_protocol_learning_start();
            break;
        case COMM_MGR_PROTO_DATATRANSFER_READY:
            ret = __comm_mgr_srv_protocol_datattransfer_ready();
            break;
        default:
            COMM_MGR_SRV_ERROR("Invalid protocol state");
            return COMM_MGR_SRV_PROTO_INVALID_STATE;
    }
    return COMM_MGR_SRV_SUCCESS;
}

/*
    This function needs to be called by the Communication Manager Master
    instances whenever it receives a packet.

    
   <TODO> Should be ask the Master instance to discard the packet upon error
   <TODO> Also should we use another thread or use the response handler ???

*/
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_process_packet(COMM_MGR_MSG *msg) {
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    if (msg == NULL) {
        COMM_MGR_SRV_DEBUG("comm msg is NULL");
        return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }
    if (msg->magic != COMM_MGR_MSG_HDR_MAGIC) {
        COMM_MGR_SRV_DEBUG("Invalid comm msg. Wrong magic");
        return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }
    if (__comm_mgr_srv_is_uid_valid(msg->hdr.src_uid) && 
        __comm_mgr_srv_is_uid_valid(msg->hdr.dst_uid)) {
        COMM_MGR_SRV_DEBUG("Invalid comm msg. Wrong UID");
        return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }

    // <TODO> Might need to check for compatible version (major/minor) when
    // inter-systems comes in future

    // If basic sanity passes, process the received packet and take action
    switch(msg->msg_type) {
        case COMM_MGR_MSG_PROTOCOL:
            ret =__comm_mgr_srv_protocol_process_proto_packet(msg);
            break;
        case COMM_MGR_MSG_ACK:
            ret =__comm_mgr_srv_protocol_process_ack_packet(msg);
            break;
        case COMM_MGR_MSG_DATA:
            ret =__comm_mgr_srv_protocol_process_data_packet(msg);
            break;
        default:
            COMM_MGR_SRV_DEBUG("Invalid comm msg type");
            return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }
    return ret; 
}

/******************************************************************************
                             Internal Functions
******************************************************************************/
static *COMM_MGR_SRV_UID_MAP __comm_mgr_srv_protocol_create_uid_tbl(uint32_t base, 
                                                                    uint32_t max) {
    uint32_t total_size = (max-base) * sizeof(COMM_MGR_SRV_PROTO_TBL);
    COMM_MGR_SRV_UID_MAP *uid_tbl = 
                        (COMM_MGR_SRV_UID_MAP*)malloc(total_size);

    for (uint16_t i = 0; i < total_size; i++) {
        uid_tbl->UID = COMM_MGR_SRV_INVALID_UID;
        uid_tbl->uid_ptr = NULL;
    }

    return uid_tbl;
}

/*
    Note : The protocol is always intiated by Communication Manager. In case a client
    tries to initiate protocol on its own drop such packets
*/
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_proto_packet(COMM_MGR_MSG *msg) {
    // If Protocol packet is received, the client src uid should already be present in the UID map
    // And, the current state should be in one of the protocol states for that client
    // Else, it means the client tried to start the protocol on its own => drop the packet
    COMM_MGR_SRV_PROTO_TBL *proto_tbl = __comm_mgr_srv_protocol_uid_map_get(msg->hdr.src_uid);
    if (proto_tbl == NULL) {
        COMM_MGR_SRV_DEBUG("Client UID [%d] tried to initiate the protocol. Discarding", msg->hdr.src_uid);
        return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }

    // Check the current protocol state of the UID
    switch(proto_tbl->proto_state) {
        case COMM_MGR_PROTO_DISCOVERY_START:
        case COMM_MGR_PROTO_DISCOVERY_DONE:
        case COMM_MGR_PROTO_LEARNING_START:
        case COMM_MGR_PROTO_LEARNING_DONE:
            // These are correct proto states for a proto packet received from client
            break;
        default:
            // Note : Even when the current state for the UID is COMM_MGR_PROTO_DATATRANSFER_READY,
            // we should not receive any protocol packets from that client.
            return COMM_MGR_SRV_PROTO_BAD_PACKET;
    }

    // <TODO> <NOT YET IMPLEMENTED>
 
}

static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_ack_packet(COMM_MGR_MSG *msg) {

}

static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_data_packet(COMM_MGR_MSG *msg) {
    // If a Data Packet is received, check the UID map table for the current state of
    // the UID. If the UID is present with the current state as COMM_MGR_PROTO_DATATRANSFER_READY,
    // we can simply honour the request from the client. We can forward to the dest_uid if the
    // dest uid is present in the UID map with state as COMM_MGR_PROTO_DATATRANSFER_READY. Else
    // we will back the current packet in a seperate queue and also notify the src_uid with the
    // message that learning has started for the dest uid. The client should not send any data 
    // packets for the dest uid till it gets the learning done message from the comm mgr.
    // Once the learning is complete, the data will be sent to the dest UID and again the src uid 
    // will be notified. And any packets from src uid till this point will be dropped.

    /* <TODO> We need to maintain a data queue per dest UID
       <TODO> Also we need a seperate data queue per src UID. This is used only when dest UID is not
            learnt. We will register for a new event, when we are waiting on some dest UID to 
            be discovered and learnt. Once the dest UID is learnt , we will dequeue from this queue 
           and insert to the dest UID queue.
       <TODO> We will have two threads for sending data. One dedicated for Dest as Static UID and 
            another for Dynamic Dest UID. These threads will be per Master Instances
    */
    COMM_MGR_SRV_ERR ret = COMM_MGR_SRV_SUCCESS;
    COMM_MGR_SRV_PROTO_TBL *proto_tbl = __comm_mgr_srv_protocol_uid_map_get(msg->hdr.src_uid);
    if (proto_tbl == NULL) { //  case 1 : New UID discovered
        COMM_MGR_SRV_DEBUG("Client UID [%d] connecting to the Communication Manager for the first time",
                                                msg->hdr.src_uid);
        proto_tbl = __comm_mgr_srv_protocol_uid_map_insert(msg->hdr.src_uid); 
        
        // Start the Protocol State Machine (current state = COMM_MGR_PROTO_DISCOVERY_START)        
        ret = comm_mgr_srv_protocol_statemachine(proto_tbl->proto_state, msg->hdr.src_uid);
        return ret;
    }
    
    // case 2 : If src UID and dest UID is already present


    // case 3 : Only if src UID is present

}

static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_discovery_start(uint16_t uid) {
    // Send a discovery start msg to the UID by adding to protocol queue
    // and sending a high priority event to response handlers
    COMM_MGR_MSG *msg = //malloc();

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
        if (comm_mgr_srv_protocol_static_uid_tbl[uid].UID == COMM_MGR_SRV_INVALID_UID) {
            return NULL;
        }
        return comm_mgr_srv_protocol_static_uid_tbl[uid].uid_ptr;
    }
    if (comm_mgr_srv_protocol_dynamic_uid_tbl[uid].UID == COMM_MGR_SRV_INVALID_UID) {
        return NULL;
    }
    return comm_mgr_srv_protocol_dynamic_uid_tbl[uid].uid_ptr;
}

static COMM_MGR_SRV_PROTO_TBL* __comm_mgr_srv_protocol_uid_map_insert(uint16_t uid) {
    COMM_MGR_SRV_PROTO_TBL *proto_entry = NULL;

    proto_entry = (COMM_MGR_SRV_PROTO_TBL *)malloc(sizeof(COMM_MGR_SRV_PROTO_TBL));
    memset(proto_entry, 0, sizeof(COMM_MGR_SRV_PROTO_TBL));

    proto_entry->UID = uid;
    proto_entry->server_fd = -1;
    proto_entry->proto_state = COMM_MGR_PROTO_DISCOVERY_START;

    // Add the entry to the UID map
    if(__comm_mgr_srv_is_uid_static(uid)) {
        comm_mgr_srv_protocol_static_uid_tbl[uid].UID = uid;
        comm_mgr_srv_protocol_static_uid_tbl[uid].uid_ptr = proto_entry;
    } else {
        comm_mgr_srv_protocol_dynamic_uid_tbl[uid].UID = uid;
        comm_mgr_srv_protocol_dynamic_uid_tbl[uid].uid_ptr = proto_entry;
    }

    return proto_entry;
}

