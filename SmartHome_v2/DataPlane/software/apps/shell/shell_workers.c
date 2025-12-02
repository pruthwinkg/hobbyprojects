#include "shell.h"

UTILS_TASK_HANDLER shell_app_workers[] = 
{
  	{   
    	/*  
        	Description : This task is dedicated to handle communication       
    	*/
        .taskID = SHELL_APP_TASK_ID_COMM,
        .handler = shell_app_communication_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
    	//.reg_event_cb = ,
    },
   	{   
    	/*  
        	Description : This task is dedicated to handle communication       
    	*/
        .taskID = SHELL_APP_TASK_ID_ANC_COMM,
        .handler = shell_app_communication_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
    	//.reg_event_cb = ,
    },
   
    {
       /*
            Description: This task is dedicated to handle request from User
       */ 
        .taskID = SHELL_APP_TASK_ID_REQ,
        .handler = shell_app_req_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
        //.reg_event_cb = 
    },
    {
        /*
            Description: This task is dedicated to process the request received
            by the user and sent the request to appropriate modules. It also
            handles any error responses from the various components
        */
        .taskID = SHELL_APP_TASK_ID_PROCESS,
        .handler = shell_app_process_handler,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = TRUE,
        .reg_event_cb = shell_app_register_process_events,
    },
};
