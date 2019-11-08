/*******************************************************************************
    Description: Contains all the protypes for the system manager
    

*******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h> /* for pid_t */


#include "system_mgr_client_tbl.h"
#include "../cmn/smarthome_error.h"

#define SYS_MGR_ERROR   printf
#define SYS_MGR_TRACE   printf
#define SYS_MGR_DEBUG   printf    


#define SYS_MGR_ERR_BASE        (SMARTHOME_ERROR_CODE_SYS_MGR)

typedef enum {
    SYS_MGR_SUCCESS = 0,
    SYS_MGR_INIT_FAILURE = SYS_MGR_ERR_BASE,
    SYS_MGR_CLIENT_INIT_FAILURE,
} SYS_MGR_ERR;


typedef enum {
    SYS_MGR_CLIENT_BOOT_ONCE, // Boot only once
    SYS_MGR_CLIENT_BOOT_ALWAYS, // Boot always upon process crash
    SYS_MGR_CLIENT_BOOT_TRY // Boot X number of times upon process crash
} SYS_MGR_CLIENT_BOOT_MODE;

typedef enum {
    SYS_MGR_CLIENT_PRIO_LOW,
    SYS_MGR_CLIENT_PRIO_NORMAL, // Most of the process starts with this priority
    SYS_MGR_CLIENT_PRIO_HIGH,
    SYS_MGR_CLIENT_PRIO_CRITICAL // For critical apps, without which system can malform.
} SYS_MGR_CLIENT_PRIORITY;

typedef enum {
    SYS_MGR_CLIENT_HEAP_500M,
    SYS_MGR_CLIENT_HEAP_700M, // 700 MB
    SYS_MGR_CLIENT_HEAP_1GB,
    SYS_MGR_CLIENT_HEAP_2GB,
    SYS_MGR_CLIENT_HEAP_2p5GB, // 2.5 GB
    SYS_MGR_CLIENT_HEAP_USER_DEFINED
} SYS_MGR_CLIENT_HEAP_LIMIT;

typedef struct {
    SYS_MGR_CLIENT_BOOT_MODE bootMode;    
    uint8_t bootTryValue; // Applicable for SYS_MGR_CLIENT_BOOT_TRY
    SYS_MGR_CLIENT_PRIORITY priority;
    SYS_MGR_CLIENT_HEAP_LIMIT heapLimit;
    uint32_t userHeapLimit; // For SYS_MGR_CLIENT_HEAP_USER_DEFINED
} SYS_MGR_CLIENT_PROPERTIES;

typedef struct {
    uint32_t clientID; // Must field. Defined in system_mgr_client_tbl.h
    char clientName[128]; // Must field. Name of executable
    SYS_MGR_CLIENT_PROPERTIES clientProperty; // Optional field. Else set to sys manager decided values
} SYS_MGR_CLIENT_TBL;


typedef enum {
    SYS_MGR_CLIENT_STATE_STOPPED,
    SYS_MGR_CLIENT_STATE_RUNNING,
    SYS_MGR_CLIENT_STATE_PAUSED,
} SYS_MGR_CLIENT_STATE;

// This is an internal datastructure used by sys manager to maintain the info about the client in Running state
typedef struct {
    uint32_t clientID;
    pid_t pid;
    SYS_MGR_CLIENT_STATE state;
    int stateCause; // Change it to an enum later TODO
} SYS_MGR_CLIENT_STATUS;

extern SYS_MGR_CLIENT_TBL system_mgr_client_tbl[SYS_MGR_CLIENT_MAX_CLIENTS];
extern SYS_MGR_CLIENT_STATUS system_mgr_client_status[SYS_MGR_CLIENT_MAX_CLIENTS];


SYS_MGR_ERR sysmgr_init_clients(void);
SYS_MGR_ERR sysmgr_start_client(SYS_MGR_CLIENTS client);
SYS_MGR_ERR sysmgr_stop_client(SYS_MGR_CLIENTS client);
SYS_MGR_ERR sysmgr_restart_client(SYS_MGR_CLIENTS client);
void sysmgr_display_client_status(void);

