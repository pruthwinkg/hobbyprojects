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

// This is a local data structure specific for UDS alone
typedef struct {
    uint16_t magic;
    uint32_t uds_datalen;
    char *uds_data;
} COMM_MGR_SRV_UDS_MSG;

/*****************************************************************************
                               Public Functions
*****************************************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_create_uds_master(uint16_t *masterID);
void* comm_mgr_srv_uds_request_handler(void *arg);
void* comm_mgr_srv_uds_response_handler(void *arg);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_recv_data(UTILS_DS_ID id, char *data, uint32_t len);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_process_events(boolean isLocalMode, uint32_t event);
void comm_mgr_srv_uds_res_register_events(uint32_t taskID);

/*****************************************************************************
                                Internal Functions
*****************************************************************************/
static COMM_MGR_SRV_UDS_MSG* __comm_mgr_srv_uds_msg_encode(char *data, uint32_t datalen);
static char* __comm_mgr_srv_uds_msg_decode(COMM_MGR_SRV_UDS_MSG *uds_msg, uint32_t *len);
static void __comm_mgr_srv_uds_msg_free(COMM_MGR_SRV_UDS_MSG *uds_msg);



#endif /* INCLUDE_COMM_MGR_UDS_H__ */
