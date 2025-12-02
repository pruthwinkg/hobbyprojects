/*******************************************************************************
    Description : Communication manager prototypes and structures

 *******************************************************************************/
#ifndef INCLUDE_COMM_MGR_H__
#define INCLUDE_COMM_MGR_H__

#include "smarthome_essentials.h"
#include "logging.h"
#include "utils.h"
#include "comm_mgr_srv_enums.h"
#include "comm_mgr_cmn.h"

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

// The last argument (void **) can be used to send array of complex datastrcuture
// The corresponding dsid_cb should typecast to apprioate type for that DSID and use it.
typedef COMM_MGR_SRV_ERR (*comm_mgr_srv_dsid_cb)(UTILS_DS_ID, void *arg1, void *arg2, void **arg);

//extern char buffer[4096]; // // TODO :Make a sophesticated data structure

// This structure defines the Master (Server)
typedef struct {
    COMM_MGR_SRV_IPC_AF masterAf;   /* In */
    const char *uds_file;           /* In (Only for UDS) */
    boolean ancillary;              /* In */
    int portNum;                    /* In */
    boolean reuseaddr;              /* In */
    boolean nonblockingIO;          /* In */
    int srvInactivityTimeOut;       /* In */ // -1 to wait infinite, valid range (1 - INT_MAX) mins
    UTILS_DS_ID *__DSID;            /* In */ // Array of DS ID needed by Master instances
    comm_mgr_srv_dsid_cb *__dsid_cb;/* In */ // Array of Call back function needed by callback functions
    int __masterFd;                 /* Out */
    boolean __masterReady;          /* Out */ //Useful in multi-threaded environment.Protect by mutex if required 
    uint16_t __masterID;            /* Out */  // To idetify the Master    
} COMM_MGR_SRV_MASTER;

// This message formt is very internal to Communicaton Manager.
// It carries some internal header information along with the
// actual message when it is passed from one block to another block
// in the Communication Manager
typedef struct {
    uint32_t server_fd;
    uint32_t action; // Action the Master instance need to take
    COMM_MGR_MSG *msg;
} COMM_MGR_SRV_MSG;


typedef struct {
    COMM_MGR_MSG **msg;
    uint8_t num_msgs;
    uint32_t server_fd;
} COMM_MGR_SRV_RECV_MSG;

// The various Master instances needs use this strcuture to pass the
// arguments to their workers. This is used to resolve conflicts to
// determine the appropriate master instance in a load sharing scenerio.
// In load sharing a single task can be owned by multiple masters. In such cases,
// in any point when a task needs to determine which master instance to use,
// decision will be made on the nature of data or action being performed and an
// appropriate master will be used.
typedef uint16_t (*comm_mgr_srv_master_conflict_resolver)(COMM_MGR_SRV_MASTER_CONFLICT_TYPE type, \
                                                void *arg, void *workerArg);
typedef struct {
    boolean isLoadSharingEn;    
    uint16_t *masterFDs;
    uint8_t num_masterFDs;
    comm_mgr_srv_master_conflict_resolver resolver;
} COMM_MGR_SRV_WORKER_ARG;

/*
    This data structure is used internally by the Master server instance for managing
    the jobs given to the Housekeeping task handler 

    The Housekeeping jobs are identified by event. Depeding on the event, the Housekeeping 
    task handler will perform actions using the other metadata available in the job 
*/
typedef struct { 
    COMM_MGR_SRV_HOUSEKEEP_EVENT event;
    uint8_t priority; // Lower the value, higher priority  
    void *eventData; // event specific data 
} COMM_MGR_SRV_HK_JOB;

/*
    Used hold data related to a Transit event job 

    which_<> : which field is a wildcard entry to select all/none/specific uid 
            Refer COMM_MGR_SRV_TRANSIT_SELECT enum type for various values 
*/
typedef struct {
    uint16_t masterID;  // Transit DSID is per master
    COMM_MGR_SRV_TRANSIT_SELECT which_dst;
    uint16_t dst_uid;   // To which dest UIDs needs to be processed 
    COMM_MGR_SRV_TRANSIT_SELECT which_src;
    uint16_t src_uid;   // From which src UIDs needs to be processed
} COMM_MGR_SRV_TRANSIT_ENTRY;

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
COMM_MGR_SRV_ERR comm_mgr_srv_send_data(COMM_MGR_SRV_MASTER *master, COMM_MGR_SRV_MSG *srv_msg);
COMM_MGR_SRV_ERR comm_mgr_create_registered_apps_list(void);
COMM_MGR_SRV_MASTER* comm_mgr_srv_get_master(uint16_t masterID);

#endif /* INCLUDE_COMM_MGR_H__ */
