/******************************************************************************
    Description : This is the UDS masters header file
******************************************************************************/
#ifndef INCLUDE_COMM_MGR_UDS_H__
#define INCLUDE_COMM_MGR_UDS_H__

#include "utils.h"
#include "comm_mgr_srv.h"
#include "comm_mgr_srv_protocol.h"

#define UDS_MASTER_RECV_QUEUE_SIZE          (2048)
#define UDS_MASTER_SEND_QUEUE_SIZE          (2048)
#define UDS_MASTER_HOUSEKEEP_QUEUE_SIZE     (128)
#define UDS_MASTER_TRANSIT_QUEUE_SIZE       (256)
#define UDS_MASTER_MSG_MAGIC_NUM            (0x2468)

// Actions on UDS messages
#define UDS_MASTER_MSG_ACTION_DROP          (1 << 0)
#define UDS_MASTER_MSG_ACTION_COPY          (1 << 1)
#define UDS_MASTER_MSG_ACTION_FORWARD       (1 << 2)
#define UDS_MASTER_MSG_ACTION_HOLD          (1 << 3)
#define UDS_MASTER_MSG_ACTION_PROCESS       (1 << 4)

#define UDS_MASTER_NUM_OF_INSTANCES    (2)

// A generic message encoding for UDS
typedef struct {
    uint16_t action; // Can specify the actions needs to be taken on the packet
    void *msg; // It can be any format
    uint32_t server_fd;
} COMM_MGR_SRV_UDS_MSG;

/*****************************************************************************
                               Public Functions
*****************************************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_create_uds_master(uint16_t *masterID, COMM_MGR_SRV_MASTER_INSTANCE *instances,
                                                uint8_t num_instances, boolean loadsharing);
void* comm_mgr_srv_uds_process_handler(void *arg);
void* comm_mgr_srv_uds_request_handler(void *arg);
void* comm_mgr_srv_sec_uds_request_handler(void *arg);
void* comm_mgr_srv_uds_response_static_handler(void *arg);
void* comm_mgr_srv_uds_response_dynamic_handler(void *arg);
void* comm_mgr_srv_uds_housekeeping_handler(void *arg);

COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_recv_data(UTILS_DS_ID id, void *arg1, void *arg2, void **arg);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_proto_data(UTILS_DS_ID id, void *arg1, void *arg2, void **arg);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_send_data(UTILS_DS_ID id, void *arg1, void *arg2, void **arg);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_housekeeper(UTILS_DS_ID id, void *arg1, void *arg2, void **arg);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_transit_data(UTILS_DS_ID id, void *arg1, void *arg2, void **arg);

COMM_MGR_SRV_ERR comm_mgr_srv_uds_process_events(uint16_t masterID, boolean isLocalMode, uint32_t event);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_handle_housekeeping_events(COMM_MGR_SRV_MASTER *master);

void comm_mgr_srv_uds_process_register_events(uint32_t taskID);
void comm_mgr_srv_uds_response_static_register_events(uint32_t taskID);
void comm_mgr_srv_uds_response_dynamic_register_events(uint32_t taskID);
void comm_mgr_srv_uds_housekeeping_register_events(uint32_t taskID);

uint16_t comm_mgr_srv_uds_master_conflict_resolver(COMM_MGR_SRV_MASTER_CONFLICT_TYPE type, void *arg,
                                                   void *workerArg);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_transit_event(uint8_t ev, void *arg);                                                   
/*****************************************************************************
                                Internal Functions
*****************************************************************************/
static COMM_MGR_SRV_ERR __comm_mgr_srv_uds_msg_action(COMM_MGR_SRV_UDS_MSG *uds_msg);
static COMM_MGR_SRV_UDS_MSG* __comm_mgr_srv_uds_msg_create(void *msg, uint32_t server_fd);
static void __comm_mgr_srv_uds_msg_free(COMM_MGR_SRV_UDS_MSG *uds_msg);



#endif /* INCLUDE_COMM_MGR_UDS_H__ */
