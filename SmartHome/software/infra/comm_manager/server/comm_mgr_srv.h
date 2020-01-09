/*******************************************************************************
    Description : Communication manager prototypes and structures

 *******************************************************************************/
#ifndef INCLUDE_COMM_MGR_H__
#define INCLUDE_COMM_MGR_H__

#include "smarthome_essentials.h"
#include "logging.h"
#include "utils.h"
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
extern UTILS_TASK_HANDLER comm_mgr_srv_workers[COMM_MGR_SRV_TASK_ID_MAX];

typedef COMM_MGR_SRV_ERR (*comm_mgr_srv_recv_cb)(UTILS_DS_ID, char *, uint32_t);

//extern char buffer[4096]; // // TODO :Make a sophesticated data structure

// This structure defines the Master (Server)
typedef struct {
    COMM_MGR_SRV_IPC_AF masterAf;   /* In */
    int portNum;                    /* In */
    boolean reuseaddr;              /* In */
    boolean nonblockingIO;          /* In */
    int srvInactivityTimeOut;       /* In */ // -1 to wait infinite, valid range (1 - INT_MAX) mins
    UTILS_DS_ID recvDSID;           /* In */  // DS ID for storing the recived data
    comm_mgr_srv_recv_cb recv_cb;   /* In */ // Call back function for Recieve data
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
COMM_MGR_SRV_ERR comm_mgr_srv_init(void);
COMM_MGR_SRV_ERR comm_mgr_create_registered_apps_list(void);
COMM_MGR_SRV_ERR comm_mgr_srv_destroy(void);
COMM_MGR_SRV_ERR comm_mgr_srv_init_master(COMM_MGR_SRV_MASTER *master);
COMM_MGR_SRV_ERR comm_mgr_srv_accept_clients(uint16_t masterID);
COMM_MGR_SRV_ERR comm_mgr_srv_create_uds_master(uint16_t *masterID);
void* comm_mgr_srv_uds_request_handler(void *arg);
void* comm_mgr_srv_uds_response_handler(void *arg);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_master_recv_data(UTILS_DS_ID id, char *data, uint32_t len);
COMM_MGR_SRV_ERR comm_mgr_srv_uds_res_process_events(boolean isLocalMode, uint32_t event);
void comm_mgr_srv_uds_res_register_events(uint8_t taskID);

#endif /* INCLUDE_COMM_MGR_H__ */
