/*******************************************************************************
    Description : Shell program prototypes and structures

*******************************************************************************/
#ifndef INCLUDE_SHELL_APP_H__
#define INCLUDE_SHELL_APP_H__

#include "logging.h"
#include "utils.h"
#include "shell_enums.h"
#include "comm_mgr_lib.h"
#include "comm_mgr_cmn.h"

#define SHELL_APP_NAME      "shell"

#define SHELL_APP_ERROR  LOG_ERROR
#define SHELL_APP_TRACE  LOG_TRACE
#define SHELL_APP_DEBUG  LOG_DEBUG
#define SHELL_APP_PRINT  printf

#define SHELL_APP_SRC_UID       (100) // <TODO : Derive it from SamrtHome folder later>

#define SHELL_APP_COMM_MGR_LIB_RECV_QUEUE_SIZE  (10)
#define SHELL_APP_COMM_MGR_LIB_SEND_QUEUE_SIZE  (10)

extern UTILS_TASK_HANDLER shell_app_workers[SHELL_APP_TASK_ID_MAX];

/******************************************************************************
                            Public Functions
******************************************************************************/
void *shell_app_req_handler(void *arg);
void *shell_app_process_handler(void *arg);
void shell_app_register_process_events(uint32_t taskID);
SHELL_APP_ERR shell_app_process_events(uint16_t cid, boolean isLocalMode, uint32_t event);
void shell_app_comm_lib_cb(COMM_MGR_LIB_EVENT event);

/******************************************************************************
                            Internal Functions
******************************************************************************/


#endif /* INCLUDE_SHELL_APP_H__ */
