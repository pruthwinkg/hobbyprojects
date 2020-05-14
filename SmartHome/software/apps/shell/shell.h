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
#define SHELL_APP_USER_CMD_QUEUE_SIZE           (5)

#define SHELL_APP_MAX_CMDS          (5)     // Tells how many parallel user cmds can issued
#define SHELL_APP_MAX_CMD_TOK       (5)    // Tells how many words/tokens each user comd can have
#define SHELL_APP_MAX_CMD_TOK_SIZE  (10)    // Size of each token in a user cmd
#define SHELL_APP_MAX_CMD_SIZE      (SHELL_APP_MAX_CMD_TOK * SHELL_APP_MAX_CMD_TOK_SIZE) // Tells what is maximum length of each user cmd
#define SHELL_APP_TOK_DELIM         " \t\r\n\a" // Various valid delimiters in a user cmd

extern UTILS_TASK_HANDLER shell_app_workers[SHELL_APP_TASK_ID_MAX];

typedef SHELL_APP_ERR (*shell_app_dsid_cb)(UTILS_DS_ID, char *, uint32_t, void *);

typedef enum {
    SHELL_APP_ARGS_USAGE_FREE = 0xAA,
    SHELL_APP_ARGS_USAGE_IN_USE = 0xBB,
    SHELL_APP_ARGS_USAGE_RESERVED = 0xCC,
} SHELL_APP_ARGS_USAGE;

typedef struct {
    char shell_name[10];            // Usser defined name for the shell
    UTILS_DS_ID *__DSID;            // Array of DSIDs
    shell_app_dsid_cb *__dsid_cb;   // Array of Call back functions
    COMM_MGR_LIB_CLIENT_ID *cid;    // Comm Lib CID associated with shell
    char *line;                     // Buffer to hold user command
    char **args[SHELL_APP_MAX_CMDS];// Buffer to hold the user commands arguments
    SHELL_APP_ARGS_USAGE args_usage[SHELL_APP_MAX_CMDS]; // A bitmap to indicate about the usage of args[]
} SHELL_APP;


/******************************************************************************
                            Public Functions
******************************************************************************/
void *shell_app_req_handler(void *arg);
void *shell_app_process_handler(void *arg);
void shell_app_register_process_events(uint32_t taskID);
SHELL_APP_ERR shell_app_process_events(uint16_t cid, boolean isLocalMode, uint32_t event);
void shell_app_comm_lib_cb(COMM_MGR_LIB_EVENT event);
SHELL_APP_ERR shell_app_process_user_cmd(uint8_t slot);

/******************************************************************************
                            Internal Functions
******************************************************************************/
static void shell_app_read_line(void);
static void shell_app_split_line(char *line, uint8_t slot);

#endif /* INCLUDE_SHELL_APP_H__ */
