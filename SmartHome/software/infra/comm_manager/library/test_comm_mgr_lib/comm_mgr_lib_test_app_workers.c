#include "utils.h"
#include "comm_mgr_lib_test_app_enums.h"

void *comm_mgr_test_app_communication_handler(void *arg);
void *comm_mgr_test_app_housekeeper(void *arg);

UTILS_TASK_HANDLER comm_mgr_test_app_workers[] = {
  {  
    /* 
        Description : This task is dedicated to handle communication
		for this test app
	
	*/
        .taskID = COMM_MGR_TEST_APP_TASK_ID_COMM,
        .handler = comm_mgr_test_app_communication_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
        //.eventEnable = TRUE,
		//.reg_event_cb = comm_mgr_test_app_process_comm_events,
    },
    {  
    /* 
        Description : This task is dedicated to handle housekeeping
		for this test app
	
	*/
        .taskID = COMM_MGR_TEST_APP_TASK_ID_COMM,
        .handler = comm_mgr_test_app_housekeeper,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
        //.eventEnable = TRUE,
		//.reg_event_cb = comm_mgr_test_app_process_comm_events,
    },
   
};