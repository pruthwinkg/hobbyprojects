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

#define SHELL_APP_OUT_FILE_LOC      "/tmp"
#define SHELL_APP_MAX_SEND_BUF_SIZE     (INTERFACE_QUERY_HEADER_SIZE+INTERFACE_LIB_MAX_QUERY_SIZE)

extern UTILS_TASK_HANDLER shell_app_workers[SHELL_APP_TASK_ID_MAX];

typedef SHELL_APP_ERR (*shell_app_dsid_cb)(UTILS_DS_ID, char *, uint32_t, void *);

typedef enum {
    SHELL_APP_ARGS_USAGE_FREE = 0xAA,
    SHELL_APP_ARGS_USAGE_IN_USE = 0xBB,
    SHELL_APP_ARGS_USAGE_RESERVED = 0xCC,
} SHELL_APP_ARGS_USAGE;

#define SHELL_APP_NORMAL_MODE_CLIENT        0
#define SHELL_APP_ANCILLARY_MODE_CLIENT     1

typedef struct {
    char shell_name[10];            // Usser defined name for the shell
    UTILS_DS_ID *__DSID;            // Array of DSIDs
    shell_app_dsid_cb *__dsid_cb;   // Array of Call back functions
    COMM_MGR_LIB_CLIENT_ID *cid;    // Comm Lib CIDs associated with shell
    uint8_t num_cid;                // Number of CIDs used in this shell
    char *line;                     // Buffer to hold user command
    char **args[SHELL_APP_MAX_CMDS];// Buffer to hold the user commands arguments
    SHELL_APP_ARGS_USAGE args_usage[SHELL_APP_MAX_CMDS]; // A bitmap to indicate about the usage of args[]
    FILE *shellFile[SHELL_APP_MAX_CMDS];   // The output file where the apps will write their responses
    uint8_t query_req_type;         // By default it is set to send Tokens
} SHELL_APP;

typedef enum {
    SHELL_APP_UID_STATIC = 0,
    SHELL_APP_UID_DYNAMIC,
} SHELL_APP_UID_TYPE;

// Various query requests generated from CLI files
typedef struct {
    uint16_t token;
    const char *full_query;
} SHELL_APP_QUERY;


typedef struct {
    const char* appName;
    uint16_t uid;
    SHELL_APP_UID_TYPE uid_type;
    SHELL_APP_QUERY *appArray;
} SHELL_SUPPORTED_APP;

typedef struct {
    SHELL_APP_SYSTEM_TASK task;
} SHELL_APP_SYSTEM_TASKS;

// Currently one system task can be processed per event call. Batch processing support will be added later (TODO)
SHELL_APP_SYSTEM_TASKS shell_system_task;

/******************************************************************************
                            Public Functions
******************************************************************************/
SHELL_APP* shell_app_init(char *name);
void *shell_app_req_handler(void *arg);
void *shell_app_process_handler(void *arg);
void *shell_app_communication_handler(void *arg);
void shell_app_register_process_events(uint32_t taskID);
SHELL_APP_ERR shell_app_process_events(uint16_t cid, boolean isLocalMode, uint32_t event);
void shell_app_comm_lib_cb(COMM_MGR_LIB_EVENT event);
SHELL_APP_ERR shell_app_process_user_cmd(uint8_t slot);
SHELL_APP_ERR shell_app_send_user_cmd(uint8_t slot, uint16_t dst_uid, SHELL_APP_USER_CMD_TYPE type);
void shell_app_send_system_tasks(SHELL_APP_SYSTEM_TASK task, boolean priority);
SHELL_APP_ERR shell_app_process_system_tasks(void);
SHELL_APP_ERR shell_app_send_discovery(void);
void shell_app_close();


void shell_app_display_help();
void shell_app_display_list();
void shell_app_display_apps_help(const char *app);
SHELL_APP_ERR shell_app_get_uid_from_appName(const char *app, uint16_t *uid);
SHELL_APP_ERR shell_app_get_token_from_query(const char *app, const char *query, uint16_t *token);

/******************************************************************************
                            Internal Functions
******************************************************************************/
static void shell_app_read_line(void);
static void shell_app_split_line(char *line, uint8_t slot);

#endif /* INCLUDE_SHELL_APP_H__ */
