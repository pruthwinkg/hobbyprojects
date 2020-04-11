/*******************************************************************************
    Description : Communication manager enums

 *******************************************************************************/

#include "smarthome_essentials.h"

#define COMM_MGR_SRV_ERR_BASE        (SMARTHOME_ERROR_CODE_COMM_MGR_SRV)

BEGIN_ENUM(COMM_MGR_SRV_ERR) {
    ADD_ENUM_VAL(COMM_MGR_SRV_SUCCESS, 0)
    ADD_ENUM_VAL(COMM_MGR_SRV_INIT_FAILURE, COMM_MGR_SRV_ERR_BASE)
    ADD_ENUM(COMM_MGR_SRV_ALREADY_INITIALIZED)
    ADD_ENUM(COMM_MGR_SRV_NOT_INITIALIZED)
    ADD_ENUM(COMM_MGR_SRV_DESTROY_FAILURE)
    ADD_ENUM(COMM_MGR_SRV_INVALID_ARG)
    ADD_ENUM(COMM_MGR_SRV_UNKNOWN_AF_TYPE)
    ADD_ENUM(COMM_MGR_SRV_SOCKET_CREATE_ERR)
    ADD_ENUM(COMM_MGR_SRV_SOCKET_OPT_ERR)
    ADD_ENUM(COMM_MGR_SRV_SOCKET_BIND_ERR)
    ADD_ENUM(COMM_MGR_SRV_SOCKET_LISTEN_ERR)
    ADD_ENUM(COMM_MGR_SRV_SOCKET_ACCEPT_ERR)
    ADD_ENUM(COMM_MGR_SRV_CONNECT_ERR)
    ADD_ENUM(COMM_MGR_SRV_FCNTL_NON_BLOCK_ERR)
    ADD_ENUM(COMM_MGR_SRV_MASTER_NOT_READY)
    ADD_ENUM(COMM_MGR_SRV_BAD_SERVER)
    ADD_ENUM(COMM_MGR_SRV_SERVER_TIMEOUT)
    ADD_ENUM(COMM_MGR_SRV_SEND_ERR)
    ADD_ENUM(COMM_MGR_SRV_RECV_ERR)
    ADD_ENUM(COMM_MGR_SRV_CLIENT_NOT_CREATED)
    ADD_ENUM(COMM_MGR_SRV_SELECT_ERR)
    ADD_ENUM(COMM_MGR_SRV_BAD_SHM_OBJ)
    ADD_ENUM(COMM_MGR_SRV_PROTO_INIT_ERR)
    ADD_ENUM(COMM_MGR_SRV_PROTO_INVALID_STATE)
    ADD_ENUM(COMM_MGR_SRV_PROTO_ERR)
    ADD_ENUM(COMM_MGR_SRV_PROTO_BAD_PACKET)
    ADD_ENUM(COMM_MGR_SRV_OUT_OF_MEMORY)
    ADD_ENUM(COMM_MGR_SRV_UTILS_DSID_ERR)
    ADD_ENUM(COMM_MGR_SRV_UNKNOWN_EVENT)
    ADD_ENUM(COMM_MGR_SRV_UDS_MASTER_INIT_ERR)
    ADD_ENUM(COMM_MGR_SRV_UDS_BAD_PACKET)
    ADD_ENUM(COMM_MGR_SRV_UDS_PROCESS_EVENT_ERR)
} END_ENUM(COMM_MGR_SRV_ERR);


BEGIN_ENUM(COMM_MGR_SRV_IPC_AF) {
    ADD_ENUM_VAL(COMM_MGR_SRV_IPC_AF_UNIX_SOCK_STREAM, 1)
    ADD_ENUM(COMM_MGR_SRV_IPC_AF_UNIX_SOCK_DGRAM)
    ADD_ENUM(COMM_MGR_SRV_IPC_AF_INET_SOCK_STREAM)
    ADD_ENUM(COMM_MGR_SRV_IPC_AF_INET_SOCK_DGRAM)
} END_ENUM(COMM_MGR_SRV_IPC_AF);


BEGIN_ENUM(COMM_MGR_SRV_MASTER_INSTANCE) {
    ADD_ENUM_STR(COMM_MGR_SRV_MASTER_DEFAULT_UDS, "Default UDS Master Instance")
    ADD_ENUM_STR(COMM_MGR_SRV_MASTER_SECONDARY_UDS, "Secondary UDS Master Instance")
    ADD_ENUM_STR(COMM_MGR_SRV_MASTER_DEFAULT_IDS, "Default IDS Master Instance")
    ADD_ENUM(COMM_MGR_SRV_MASTER_INSTANCE_MAX)
} END_ENUM(COMM_MGR_SRV_MASTER_INSTANCE);

BEGIN_ENUM(COMM_MGR_SRV_TASK_ID) {
    ADD_ENUM_STR(COMM_MGR_SRV_TASK_ID_UDS_REQ, "UDS request handler")
    ADD_ENUM_STR(COMM_MGR_SRV_TASK_ID_UDS_PROCESS, "UDS process handler")
    ADD_ENUM_STR(COMM_MGR_SRV_TASK_ID_UDS_RES_STATIC_UID, "UDS Static UID response handler")
    ADD_ENUM_STR(COMM_MGR_SRV_TASK_ID_UDS_RES_DYNAMIC_UID, "UDS Dynamic UID response handler")
    ADD_ENUM_STR(COMM_MGR_SRV_TASK_ID_UDS_HOUSEKEEPER, "UDS house keeper handler")
    ADD_ENUM(COMM_MGR_SRV_TASK_ID_MAX)
} END_ENUM(COMM_MGR_SRV_TASK_ID);

//These are some of the predefined DSID needed by Communication Manager. The master
// instance can also add its own DSIDs outside this range
BEGIN_ENUM(COMM_MGR_SRV_DSID) {
    ADD_ENUM_STR(COMM_MGR_SRV_DSID_RECV, "DSID for receiving the Data")
    ADD_ENUM_STR(COMM_MGR_SRV_DSID_PROTO, "DSID for Protocols")
    ADD_ENUM_STR(COMM_MGR_SRV_DSID_SEND, "DSID for sending the Data")
    ADD_ENUM_STR(COMM_MGR_SRV_DSID_HOUSEKEEP, "DSID for Internal house keeping")
    ADD_ENUM(COMM_MGR_SRV_DSID_MAX) // Master instances can use private DSIDs outside this
} END_ENUM(COMM_MGR_SRV_DSID);

// These are default House keeping events. Any Custom events by the various server instances
// should be outside this range
BEGIN_ENUM(COMM_MGR_SRV_HOUSEKEEP_EVENT) {
    ADD_ENUM_STR(COMM_MGR_SRV_HOUSEKEEP_EVENT_CLIENT_DOWN, "Client is going down")
    ADD_ENUM_STR(COMM_MGR_SRV_HOUSEKEEP_EVENT_CLIENT_UP, "Client has come up")
    ADD_ENUM(COMM_MGR_SRV_HOUSEKEEP_EVENT_MAX)
} END_ENUM(COMM_MGR_SRV_HOUSEKEEP_EVENT);

/********************************************************************************/
/*                      Event functionality (using utils library)               */
/********************************************************************************/
// These events are used by various workers of comm mgr server

// Local events are targeted events. They need to be registered by the receiving tasks
BEGIN_ENUM(COMM_MGR_SRV_LOCAL_EVENT) {
    ADD_ENUM_STR(COMM_MGR_SRV_LOCAL_EVENT_RECV_READY, "Data Received from clients")
    ADD_ENUM_STR(COMM_MGR_SRV_LOCAL_EVENT_PROTO_SEND, "Send Protocol packets to clients")
    ADD_ENUM_STR(COMM_MGR_SRV_LOCAL_EVENT_DATA_SEND, "Send Data packets to clients")
    ADD_ENUM_STR(COMM_MGR_SRV_LOCAL_EVENT_HOUSEKEEP, "Internal house keeping event")
    ADD_ENUM(COMM_MGR_SRV_LOCAL_EVENT_MAX)
} END_ENUM(COMM_MGR_SRV_LOCAL_EVENT);

// These events are global. No registration is required. Delievred to all workers
// as long as event mechanism is enabled for those tasks
BEGIN_ENUM(COMM_MGR_SRV_GLOBAL_EVENT) {
    ADD_ENUM(COMM_MGR_SRV_GLOBAL_EVENT_MAX)
} END_ENUM(COMM_MGR_SRV_GLOBAL_EVENT);

/********************************************************************************/



