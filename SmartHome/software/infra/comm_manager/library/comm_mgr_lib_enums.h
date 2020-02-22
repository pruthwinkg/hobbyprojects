/*******************************************************************************
    Description : Communication Manager client library header file for enums

*******************************************************************************/

#include "smarthome_essentials.h"

#define COMM_MGR_LIB_ERR_BASE        (SMARTHOME_ERROR_CODE_COMM_MGR_LIB)

// Note : To generate the enum strings, create a file 
// comm_mgr_lib_enums_defs.c and add the below lines
// #include "comm_mgr_lib_enums.h"
// #define GENERATE_ENUM_STRINGS  // Start string generation
// #include "smarthome_enums_to_str.h"
// #include "comm_mgr_lib_enums.h"
// #undef GENERATE_ENUM_STRINGS   // Stop string generation

BEGIN_ENUM(COMM_MGR_LIB_ERR) {
    ADD_ENUM_VAL(COMM_MGR_LIB_SUCCESS, 0)
    ADD_ENUM_VAL(COMM_MGR_LIB_INIT_FAILURE, COMM_MGR_LIB_ERR_BASE)
    ADD_ENUM(COMM_MGR_LIB_INVALID_ARG)
    ADD_ENUM(COMM_MGR_LIB_UNKNOWN_AF_TYPE)
    ADD_ENUM(COMM_MGR_LIB_SOCKET_CREATE_ERR)
    ADD_ENUM(COMM_MGR_LIB_CONNECT_ERR)
    ADD_ENUM(COMM_MGR_LIB_BAD_SERVER)
    ADD_ENUM(COMM_MGR_LIB_FCNTL_NON_BLOCK_ERR)
    ADD_ENUM(COMM_MGR_LIB_SELECT_ERR)
    ADD_ENUM(COMM_MGR_LIB_CLIENT_TIMEOUT)
    ADD_ENUM(COMM_MGR_LIB_SEND_ERR)
    ADD_ENUM(COMM_MGR_LIB_SEND_ACK_ERR)
    ADD_ENUM(COMM_MGR_LIB_RECV_ERR)
    ADD_ENUM(COMM_MGR_LIB_PROTO_ERR)
    ADD_ENUM(COMM_MGR_LIB_PROTO_INVALID_STATE)
    ADD_ENUM(COMM_MGR_LIB_INVALID_CLIENT_ERR)
    ADD_ENUM(COMM_MGR_LIB_NOT_INITIALIZED)
    ADD_ENUM(COMM_MGR_LIB_BAD_PACKET)
    ADD_ENUM(COMM_MGR_LIB_PROTO_BAD_PACKET)
    ADD_ENUM(COMM_MGR_LIB_ACK_BAD_PACKET)
    ADD_ENUM(COMM_MGR_LIB_UTILS_DSID_ERR)
}END_ENUM(COMM_MGR_LIB_ERR);

BEGIN_ENUM(COMM_MGR_LIB_IPC_AF) {
    ADD_ENUM_VAL(COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM, 0)
    ADD_ENUM(COMM_MGR_LIB_IPC_AF_UNIX_SOCK_DGRAM)
    ADD_ENUM(COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM)
    ADD_ENUM(COMM_MGR_LIB_IPC_AF_INET_SOCK_DGRAM)
} END_ENUM(COMM_MGR_LIB_IPC_AF);

// These DSIDs are internal to the comm_mgr_lib
BEGIN_ENUM(COMM_MGR_LIB_DSID) {
    ADD_ENUM_STR(COMM_MGR_LIB_DSID_PROTO_RECV, "DSID for receiving protocols/ack")
    ADD_ENUM_STR(COMM_MGR_LIB_DSID_PROTO_SEND, "DSID for sending protocols/ack")
    ADD_ENUM_STR(COMM_MGR_LIB_DSID_DATA_RECV, "DSID for receiving the Data/ack")
    ADD_ENUM_STR(COMM_MGR_LIB_DSID_DATA_SEND, "DSID for sending the Data/ack")
    ADD_ENUM(COMM_MGR_LIB_DSID_MAX)
} END_ENUM(COMM_MGR_LIB_DSID);




