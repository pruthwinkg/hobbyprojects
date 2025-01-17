#include "smarthome_essentials.h"

BEGIN_ENUM(SHELL_APP_ERR) {
    ADD_ENUM(SHELL_APP_SUCCESS)
    ADD_ENUM(SHELL_APP_FAILURE)
    ADD_ENUM(SHELL_APP_INVALID_ARG)
    ADD_ENUM(SHELL_APP_INIT_FAILURE)
    ADD_ENUM(SHELL_APP_SEND_ERR)
    ADD_ENUM(SHELL_APP_RECV_ERR)
    ADD_ENUM(SHELL_APP_UNKNOWN_EVENT)
    ADD_ENUM(SHELL_APP_UNKNOWN_USER_CMD)
    ADD_ENUM(SHELL_APP_UNKNOWN_SYSTEM_TASK)
    ADD_ENUM(SHELL_APP_UNKNOWN_APP)
    ADD_ENUM(SHELL_APP_DYNAMIC_APP)
} END_ENUM(SHELL_APP_ERR);

BEGIN_ENUM(SHELL_APP_USER_CMD_TYPE) {
    ADD_ENUM_STR(SHELL_APP_USER_CMD_SHOW, "show commands")
    ADD_ENUM_STR(SHELL_APP_USER_CMD_CONFIG, "config commands")
    ADD_ENUM_STR(SHELL_APP_USER_CMD_DEBUG, "debug commands")
    ADD_ENUM_STR(SHELL_APP_USER_CMD_HIDDEN, "hidden/secret commands")
    ADD_ENUM_STR(SHELL_APP_USER_CMD_HELP, "help commands")
} END_ENUM(SHELL_APP_USER_CMD_TYPE);

BEGIN_ENUM(SHELL_APP_SYSTEM_TASK) {
    ADD_ENUM_STR(SHELL_APP_SYSTEM_TASK_DISCOVER, "Discover the app pre-emptively")
    ADD_ENUM(SHELL_APP_SYSTEM_TASK_MAX)
} END_ENUM(SHELL_APP_SYSTEM_TASK);

BEGIN_ENUM(SHELL_APP_TASK_ID) {
    ADD_ENUM_STR(SHELL_APP_TASK_ID_COMM, "Shell Communication Handler")
    ADD_ENUM_STR(SHELL_APP_TASK_ID_ANC_COMM, "Shell Ancillary Communication Handler")
    ADD_ENUM_STR(SHELL_APP_TASK_ID_REQ, "Shell Request Handler")
    ADD_ENUM_STR(SHELL_APP_TASK_ID_PROCESS, "Shell Process Handler")
    ADD_ENUM(SHELL_APP_TASK_ID_MAX)
} END_ENUM(SHELL_APP_TASK_ID);

BEGIN_ENUM(SHELL_APP_DSID) {
	ADD_ENUM_STR(SHELL_APP_DSID_USER_CMD, "DSID for storing the User issued commands")
	ADD_ENUM(SHELL_APP_DSID_MAX)
} END_ENUM(SHELL_APP_DSID);

BEGIN_ENUM(SHELL_APP_LOCAL_EVENT) {
    ADD_ENUM_STR(SHELL_APP_LOCAL_EVENT_USER_CMD, "User has issued a Command")
    ADD_ENUM_STR(SHELL_APP_LOCAL_EVENT_APP_RES, "Application has sent a response")
    ADD_ENUM_STR(SHELL_APP_LOCAL_EVENT_SYSTEM, "A generic event to handle system related task")
    ADD_ENUM(SHELL_APP_LOCAL_EVENT_MAX)
} END_ENUM(SHELL_APP_LOCAL_EVENT);

BEGIN_ENUM(SHELL_APP_GLOBAL_EVENT) {
    ADD_ENUM(SHELL_APP_GLOBAL_EVENT_MAX)
} END_ENUM(SHELL_APP_GLOBAL_EVENT);
