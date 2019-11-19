/*******************************************************************************
    Description : Communication Manager client library header file

*******************************************************************************/
#ifndef INCLUDE_COMM_MGR_LIB_H__
#define INCLUDE_COMM_MGR_LIB_H__

#include <netdb.h>
#include "../../cmn/smarthome/smarthome_essentials.h"
#include "../../cmn/logging/logging.h"

#define COMM_MGR_LIB_NAME        "Communication Manager Library"

#define COMM_MGR_LIB_ERR_BASE        (SMARTHOME_ERROR_CODE_COMM_MGR_LIB)

#define COMM_MGR_LIB_ERROR  LOG_ERROR
#define COMM_MGR_LIB_TRACE  LOG_TRACE
#define COMM_MGR_LIB_DEBUG  LOG_DEBUG


typedef enum {
    COMM_MGR_LIB_SUCCESS = 0,
    COMM_MGR_LIB_INIT_FAILURE = COMM_MGR_LIB_ERR_BASE,
    COMM_MGR_LIB_INVALID_ARG,
    COMM_MGR_LIB_UNKNOWN_AF_TYPE,
    COMM_MGR_LIB_SOCKET_CREATE_ERR,
    COMM_MGR_LIB_CONNECT_ERR,
    COMM_MGR_LIB_BAD_SERVER,
    COMM_MGR_LIB_SEND_ERR,
    COMM_MGR_LIB_RECV_ERR,
    COMM_MGR_LIB_CLIENT_NOT_CREATED,
}COMM_MGR_LIB_ERR;

typedef enum {
    COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM = 0,
    COMM_MGR_LIB_IPC_AF_UNIX_SOCK_DGRAM,
    COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM,
    COMM_MGR_LIB_IPC_AF_INET_SOCK_DGRAM
} COMM_MGR_LIB_IPC_AF;

// Data structure to hold client properties
typedef struct {
    COMM_MGR_LIB_IPC_AF clientAf;   /* In */
    struct hostent server;          /* In */
    int portNum;                    /* In */
    int __fd;                       /* Out */
    uint8_t __clientReady;          /* Out */
} COMM_MGR_LIB_CLIENT;


/******************************************************************************/
/*          Public Functions                                                  */
/******************************************************************************/
COMM_MGR_LIB_ERR comm_mgr_lib_create_client(COMM_MGR_LIB_CLIENT *client);
COMM_MGR_LIB_ERR comm_mgr_lib_send_data(COMM_MGR_LIB_CLIENT *client, char *msg, int len);

#endif /* INCLUDE_COMM_MGR_LIB_H__ */
