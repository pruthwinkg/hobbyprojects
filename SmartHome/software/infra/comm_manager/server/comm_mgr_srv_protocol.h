/*******************************************************************************
    Description : Communication manager prototypes and structures

 *******************************************************************************/
#ifndef INCLUDE_COMM_MGR_PROTOCOL_H__
#define INCLUDE_COMM_MGR_PROTOCOL_H__

#include "comm_mgr_srv.h"
#include "comm_mgr_cmn.h"

#define COMM_MGR_SRV_INVALID_UID        (0xFFFF)

// Need to increase if at any single point of time, more than 1024 UIDs
//  is discovered at the same time (Unlikely in a small-mid sized system)
#define COMM_MGR_SRV_PROTOCOL_QUEUE_SIZE    (1024)

// Actions on COMM_MGR_SRV messages
#define COMM_MGR_SRV_MSG_ACTION_DROP          (1 << 0)
#define COMM_MGR_SRV_MSG_ACTION_COPY          (1 << 1)
#define COMM_MGR_SRV_MSG_ACTION_FORWARD       (1 << 2)
#define COMM_MGR_SRV_MSG_ACTION_HOLD          (1 << 3)
#define COMM_MGR_SRV_MSG_ACTION_PROCESS       (1 << 4)


// There is no valid bit. So the list must always contain
// valid registered apps
typedef struct {
    uint32_t UID;
    uint32_t clientID;
    uint32_t priority; // TODO : Change it to enum later    
} COMM_MGR_SRV_REG_APPS;

typedef struct {
    uint32_t reserved; // TODO : Update this later 
} COMM_MGR_SRV_PROTO_TBL_PROPERTY;

typedef struct {        
    uint32_t UID;
    int server_fd; // Used for Normal channel
    int server_anc_fd; // Used for Ancillary Channel
    COMM_MGR_PROTO_STATES proto_state; // Current state
    uint8_t proto_sub_state; // Used for intermediate state transitions
    uint16_t masterID; // Can map a UID for a Master instance
    COMM_MGR_SRV_PROTO_TBL_PROPERTY *property; // If null, use default
} COMM_MGR_SRV_PROTO_TBL;

// This is a very compact structure. Two seperate pointers are
// used to save space, since static and dynamic uids are not contagious.
// Also, both the static_uid_tbl and dynamic_uid_tbl pointer here are
// bitmaps. Their position will tell the UID and 0/1, will tell whether an UID
// is interested in this UID
typedef struct {
    uint32_t *static_uid_tbl;
    uint32_t *dynamic_uid_tbl;
} COMM_MGR_SRV_INTEREST_TBL;

// Map of <UID, Server FD>
// DONOT INCREASE THE SIZE OF THIS STRUCTURE!!!! Memory impact
// A array of Max UIDs will be created for direct access.
// To save memory two maps will be created. (Static and Dynamic)
typedef struct {
    uint16_t UID; // 2 byte
    COMM_MGR_SRV_PROTO_TBL *uid_ptr; // 4 bytes
    COMM_MGR_SRV_INTEREST_TBL *interest_tbl; // 4 bytes
} COMM_MGR_SRV_UID_MAP;

extern COMM_MGR_SRV_REG_APPS *comm_mgr_reg_apps_list;

/************************************************************************/
/*                   Internal helper functions                          */
/************************************************************************/
static COMM_MGR_SRV_UID_MAP** __comm_mgr_srv_protocol_create_uid_tbl(uint32_t base, uint32_t max);
static COMM_MGR_SRV_INTEREST_TBL* __comm_mgr_srv_protocol_create_interest_tbl(void);
static void __comm_mgr_srv_protocol_interest_tbl_update_uid(COMM_MGR_SRV_INTEREST_TBL *interest_tbl, 
                                                            uint16_t uid, boolean add);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_interest_tbl_notify(uint16_t uid);
static COMM_MGR_SRV_INTEREST_TBL* __comm_mgr_srv_protocol_get_interest_tbl(uint16_t uid);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_proto_packet(COMM_MGR_SRV_MSG *srv_msg);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_ack_packet(COMM_MGR_SRV_MSG *srv_msg);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_data_packet(COMM_MGR_SRV_MSG *srv_msg);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_discovery_start(uint16_t uid, COMM_MGR_SRV_MSG *srv_msg);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_discovery_done(uint16_t uid, COMM_MGR_SRV_MSG *srv_msg);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_learning(uint16_t uid, 
                                            COMM_MGR_SUBMSG_LEARNING_ACTION_TYPE action, uint16_t dst_uid);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_anc_learning(uint16_t dst_uid);                                            
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_datattransfer_ready(uint16_t uid, COMM_MGR_SRV_MSG *srv_msg);
static boolean __comm_mgr_srv_is_uid_valid(uint16_t uid);
static boolean __comm_mgr_srv_is_uid_static(uint16_t uid);
static COMM_MGR_SRV_PROTO_TBL* __comm_mgr_srv_protocol_uid_map_get(uint16_t uid);
static COMM_MGR_SRV_PROTO_TBL* __comm_mgr_srv_protocol_uid_map_insert(uint16_t uid, uint32_t fd);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_uid_map_remove(uint16_t uid);

static COMM_MGR_SRV_MASTER* __comm_mgr_srv_protocol_get_master(COMM_MGR_SRV_MASTER_CONFLICT_TYPE type, void *arg);
static COMM_MGR_SRV_ERR __comm_mgr_srv_forward_data(COMM_MGR_SRV_MSG *srv_msg);
static COMM_MGR_SRV_ERR __comm_mgr_srv_send_msg(COMM_MGR_MSG_HDR *hdr, char *payload);
/************************************************************************/
/*                   Public  functions                                  */
/************************************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_init(void);
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_master_init(COMM_MGR_SRV_MASTER *master);
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_statemachine(COMM_MGR_PROTO_STATES state, uint16_t uid, COMM_MGR_SRV_MSG *srv_msg);
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_process_packet(COMM_MGR_SRV_MSG *msg);
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_client_event(uint8_t ev, void *arg);
void comm_mgr_srv_msg_action(COMM_MGR_SRV_MSG *srv_msg);







#endif /* INCLUDE_COMM_MGR_PROTOCOL_H__ */
