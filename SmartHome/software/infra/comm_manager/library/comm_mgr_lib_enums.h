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
    ADD_ENUM(COMM_MGR_LIB_SEND_ERR)
    ADD_ENUM(COMM_MGR_LIB_RECV_ERR)
    ADD_ENUM(COMM_MGR_LIB_CLIENT_NOT_CREATED)
    ADD_ENUM(COMM_MGR_LIB_NOT_INITIALIZED)
}END_ENUM(COMM_MGR_LIB_ERR);

BEGIN_ENUM(COMM_MGR_LIB_IPC_AF) {
    ADD_ENUM_VAL(COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM, 0)
    ADD_ENUM(COMM_MGR_LIB_IPC_AF_UNIX_SOCK_DGRAM)
    ADD_ENUM(COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM)
    ADD_ENUM(COMM_MGR_LIB_IPC_AF_INET_SOCK_DGRAM)
} END_ENUM(COMM_MGR_LIB_IPC_AF);

