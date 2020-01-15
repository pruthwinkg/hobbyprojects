/*****************************************************************************
    Description : This file declares various workers required by the
                 Communication Manager.
******************************************************************************/

#include "comm_mgr_srv.h"
#include "utils.h"
#include "comm_mgr_srv_uds.h"

UTILS_TASK_HANDLER comm_mgr_srv_workers[] = 
{
    {  
    /* 
        Description : This task is dedicated to receive the requests from 
                ALL clients. The requests can be protocol packets/ack packets/
                data packets.
    */
        .taskID = COMM_MGR_SRV_TASK_ID_UDS_REQ,
        .handler = comm_mgr_srv_uds_request_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
    },
    {
    /* 
        Description : This task is dedicated to processing ALL types of packets
        from ALL the clients
    */
        .taskID = COMM_MGR_SRV_TASK_ID_UDS_PROCESS,
        .handler = comm_mgr_srv_uds_process_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = TRUE,
        .reg_event_cb = comm_mgr_srv_uds_res_register_events,
    }
    {
    /* 
        Description : This task is dedicated to send responses to static dest UIDs. 
    */   
        .taskID = COMM_MGR_SRV_TASK_ID_UDS_RES_STATIC_UID,
        .handler = comm_mgr_srv_uds_response_static_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = TRUE,
        .reg_event_cb = comm_mgr_srv_uds_response_static_register_events,
    }
    /* 
        Description : This task is dedicated to send responses to dynamic dest UIDs. 
    */   
        .taskID = COMM_MGR_SRV_TASK_ID_UDS_RES_DYNAMIC_UID,
        .handler = comm_mgr_srv_uds_response_dynamic_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = TRUE,
        .reg_event_cb = comm_mgr_srv_uds_response_dynamic_register_events,
    }


};


