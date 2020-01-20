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
    int server_fd;
    COMM_MGR_PROTO_STATES proto_state; // Current state
    uint16_t masterID; // Can map a UID for a Master instance
    COMM_MGR_SRV_PROTO_TBL_PROPERTY *property; // If null, use default
} COMM_MGR_SRV_PROTO_TBL;

// Map of <UID, Server FD>
// DONOT INCREASE THE SIZE OF THIS STRUCTURE!!!! Memory impact
// A array of Max UIDs will be created for direct access.
// To save memory two maps will be created. (Static and Dynamic)
typedef struct {
    uint16_t UID;
    COMM_MGR_SRV_PROTO_TBL *uid_ptr;
} COMM_MGR_SRV_UID_MAP; // 8 bytes total size

extern COMM_MGR_SRV_REG_APPS *comm_mgr_reg_apps_list;

/************************************************************************/
/*                   Internal helper functions                          */
/************************************************************************/
static COMM_MGR_SRV_UID_MAP* __comm_mgr_srv_protocol_create_uid_tbl(uint32_t base, uint32_t max);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_proto_packet(COMM_MGR_MSG *msg);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_ack_packet(COMM_MGR_MSG *msg);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_process_data_packet(COMM_MGR_MSG *msg);
static COMM_MGR_SRV_ERR __comm_mgr_srv_protocol_discovery_start(uint16_t uid);
static boolean __comm_mgr_srv_is_uid_valid(uint16_t uid);
static boolean __comm_mgr_srv_is_uid_static(uint16_t uid);
static COMM_MGR_SRV_PROTO_TBL* __comm_mgr_srv_protocol_uid_map_get(uint16_t uid);
static COMM_MGR_SRV_PROTO_TBL* __comm_mgr_srv_protocol_uid_map_insert(uint16_t uid);

static COMM_MGR_SRV_MASTER* __comm_mgr_srv_protocol_get_master(void);


/************************************************************************/
/*                   Public  functions                                  */
/************************************************************************/COMM_MGR_SRV_ERR comm_mgr_srv_protocol_init(void);
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_master_init(COMM_MGR_SRV_MASTER *master);
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_statemachine(COMM_MGR_PROTO_STATES state, uint16_t uid);
COMM_MGR_SRV_ERR comm_mgr_srv_protocol_process_packet(COMM_MGR_MSG *msg);








#endif /* INCLUDE_COMM_MGR_PROTOCOL_H__ */
