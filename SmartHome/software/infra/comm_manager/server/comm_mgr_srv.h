/*******************************************************************************
    Description : Communication manager prototypes and structures

 *******************************************************************************/
#ifndef INCLUDE_COMM_MGR_H__
#define INCLUDE_COMM_MGR_H__

#include "smarthome_essentials.h"
#include "logging.h"
#include "comm_mgr_srv_enums.h"

#define COMM_MGR_SRV_APP_NAME        "Communication Manager Server"

#define COMM_MGR_SRV_ERROR  LOG_ERROR
#define COMM_MGR_SRV_TRACE  LOG_TRACE
#define COMM_MGR_SRV_DEBUG  LOG_DEBUG

#define COMM_MGR_SRV_BACKLOG        (32)
#define COMM_MGR_SRV_MAX_MASTERS    (5)


#define COMM_MGR_SRV_GET_MASTER_AF(x)       ((x & 0xF000) >> 12)
#define COMM_MGR_SRV_GET_MASTER_INDEX(x)    (x & 0x0FFF)

extern boolean comm_mgr_srv_initialized;

//extern char buffer[4096]; // // TODO :Make a sophesticated data structure

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
