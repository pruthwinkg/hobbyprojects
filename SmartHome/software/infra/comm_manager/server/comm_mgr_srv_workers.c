/*****************************************************************************
    Description : This file declares various workers required by the
                 Communication Manager.
******************************************************************************/

#include "comm_mgr_srv.h"
#include "utils.h"

UTILS_TASK_HANDLER comm_mgr_srv_workers[] = 
{
    {   
        .taskID = COMM_MGR_SRV_TASK_ID_UDS_REQ,
        .handler = comm_mgr_srv_uds_request_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
    },
    {
        .taskID = COMM_MGR_SRV_TASK_ID_UDS_RES,
        .handler = comm_mgr_srv_uds_response_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = TRUE,
        .reg_event_cb = comm_mgr_srv_uds_res_register_events,
    }

};


