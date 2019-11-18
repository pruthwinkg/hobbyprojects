/*******************************************************************************
    Description : Communication manager prototypes and structures

 *******************************************************************************/
#ifndef INCLUDE_COMM_MGR_H__
#define INCLUDE_COMM_MGR_H__

#include "../../cmn/smarthome/smarthome_essentials.h"


#define COMM_MGR_SRV_APP_NAME        "Communication Manager Server"

#define COMM_MGR_SRV_ERR_BASE        (SMARTHOME_ERROR_CODE_COMM_MGR_SRV)

#define COMM_MGR_SRV_ERROR  printf
#define COMM_MGR_SRV_TRACE  printf
#define COMM_MGR_SRV_DEBUG  printf

#define COMM_MGR_SRV_BACKLOG        (32)
#define COMM_MGR_SRV_MAX_MASTERS    (5)


#define COMM_MGR_SRV_GET_MASTER_AF(x)       ((x & 0xF000) >> 12)
#define COMM_MGR_SRV_GET_MASTER_INDEX(x)    (x & 0x0FFF)

extern boolean comm_mgr_srv_initialized;

//extern char buffer[4096]; // // TODO :Make a sophesticated data structure


typedef enum {
    COMM_MGR_SRV_SUCCESS = 0,
    COMM_MGR_SRV_INIT_FAILURE = COMM_MGR_SRV_ERR_BASE,
    COMM_MGR_SRV_ALREADY_INITIALIZED,
    COMM_MGR_SRV_NOT_INITIALIZED,
    COMM_MGR_SRV_DESTROY_FAILURE,
    COMM_MGR_SRV_INVALID_ARG,
    COMM_MGR_SRV_UNKNOWN_AF_TYPE,
    COMM_MGR_SRV_SOCKET_CREATE_ERR,
    COMM_MGR_SRV_SOCKET_OPT_ERR,
    COMM_MGR_SRV_SOCKET_BIND_ERR,
    COMM_MGR_SRV_SOCKET_LISTEN_ERR,
    COMM_MGR_SRV_SOCKET_ACCEPT_ERR,
    COMM_MGR_SRV_CONNECT_ERR,
    COMM_MGR_SRV_FCNTL_NON_BLOCK_ERR,
    COMM_MGR_SRV_MASTER_NOT_READY, 
    COMM_MGR_SRV_BAD_SERVER,
    COMM_MGR_SRV_SERVER_TIMEOUT,
    COMM_MGR_SRV_SEND_ERR,
    COMM_MGR_SRV_RECV_ERR,
    COMM_MGR_SRV_CLIENT_NOT_CREATED,
    COMM_MGR_SRV_SELECT_ERR,
} COMM_MGR_SRV_ERR;


typedef enum {
    COMM_MGR_SRV_IPC_AF_UNIX_SOCK_STREAM = 0,
    COMM_MGR_SRV_IPC_AF_UNIX_SOCK_DGRAM,
    COMM_MGR_SRV_IPC_AF_INET_SOCK_STREAM,
    COMM_MGR_SRV_IPC_AF_INET_SOCK_DGRAM
} COMM_MGR_SRV_IPC_AF;

// This structure defines the Master (Server)
typedef struct {
    COMM_MGR_SRV_IPC_AF masterAf;   /* In */
    int portNum;                    /* In */
    boolean reuseaddr;              /* In */
    boolean nonblockingIO;          /* In */
    int srvInactivityTimeOut;       /* In */ // -1 to wait infinite, valid range (1 - INT_MAX) mins
    int __masterFd;                 /* Out */
    boolean __masterReady;          /* Out */ //Useful in multi-threaded environment.Protect by mutex if required 
    uint16_t __masterID;            /* Out */  // To idetify the Master 
} COMM_MGR_SRV_MASTER;


/************************************************************************/
/*                   Internal helper functions                          */
/************************************************************************/
static void __comm_mgr_srv_init_master_id();
static uint16_t __comm_mgr_srv_get_next_free_master_id(COMM_MGR_SRV_IPC_AF af);
static void __comm_mgr_srv_free_master_id(uint16_t masterID);



/************************************************************************/
/*                   Public  functions                                  */
/************************************************************************/
COMM_MGR_SRV_ERR comm_mgr_srv_init();
COMM_MGR_SRV_ERR comm_mgr_srv_destroy();
COMM_MGR_SRV_ERR comm_mgr_srv_init_master(COMM_MGR_SRV_MASTER *master);


#endif /* INCLUDE_COMM_MGR_H__ */
