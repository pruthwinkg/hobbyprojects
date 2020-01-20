/******************************************************************************
    Description : This is the UDS masters header file
******************************************************************************/
#ifndef INCLUDE_COMM_MGR_UDS_H__
#define INCLUDE_COMM_MGR_UDS_H__

#include "utils.h"
#include "comm_mgr_srv.h"
#include "comm_mgr_srv_protocol.h"

#define UDS_MASTER_RECV_QUEUE_SIZE      (5)
#define UDS_MASTER_MSG_MAGIC_NUM        (0x2468)

// Actions on UDS messages
#define UDS_MASTER_MSG_ACTION_DROP          (1 << 0)
#define UDS_MASTER_MSG_ACTION_COPY          (1 << 1)
#define UDS_MASTER_MSG_ACTION_FORWARD       (1 << 2)
#define UDS_MASTER_MSG_ACTION_HOLD          (1 << 3)
#define UDS_MASTER_MSG_ACTION_PROCESS       (1 << 4)

// This is a local data structure specific for UDS alone
// Complex data structures can be stored in arg variable.
typedef struct {
    uint16_t magic;
    uint16_t action; // Can specify the actions needs to be taken on the packet
    boolean alloc; // Is data/arg needs to be malloced
    uint32_t uds_datalen;
    char *uds_data;
    void *arg;
    uint32_t arg_size;
} COMM_MGR_SRV_UDS_MSG;

/*****************************************************************************
                               Public Functions
*****************************************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_create_uds_master(uint16_t *masterID, COMM_MGR_SRV_MASTER_INSTANCE instance);
void* comm_mgr_srv_uds_process_handler(void *arg);
void* comm_mgr_srv_uds_request_handler(void *arg);
void* comm_mgr_srv_uds_response_static_handler(void *arg);
void* comm_mgr_srv_uds_response_dynamic_handler(void *arg);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_recv_data(UTILS_DS_ID id, char *data, uint32_t len, void *arg);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_proto_data(UTILS_DS_ID id, char *data, uint32_t len, void *arg);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_process_events(uint16_t masterID, boolean isLocalMode, uint32_t event);

void comm_mgr_srv_uds_process_register_events(uint32_t taskID);
void comm_mgr_srv_uds_response_static_register_events(uint32_t taskID);
void comm_mgr_srv_uds_response_dynamic_register_events(uint32_t taskID);


/*****************************************************************************
                                Internal Functions
*****************************************************************************/
static COMM_MGR_SRV_ERR __comm_mgr_srv_uds_msg_action(COMM_MGR_SRV_UDS_MSG *uds_msg);
static COMM_MGR_SRV_UDS_MSG* __comm_mgr_srv_uds_msg_encode(char *data, uint32_t datalen, void *arg, 
                                                           uint32_t arg_size);
static COMM_MGR_SRV_ERR __comm_mgr_srv_uds_msg_decode(COMM_MGR_SRV_UDS_MSG *uds_msg, char **data, uint32_t *datalen, 
                                          void **arg);
static void __comm_mgr_srv_uds_msg_free(COMM_MGR_SRV_UDS_MSG *uds_msg);



#endif /* INCLUDE_COMM_MGR_UDS_H__ */
