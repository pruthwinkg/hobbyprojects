/*******************************************************************************
    Description: Contains all the protypes for the system manager
    

*******************************************************************************/
#ifndef INCLUDE_SYSTEM_MGR_H__
#define INCLUDE_SYSTEM_MGR_H__

#include <stdint.h>
#include <stdio.h>
#include <sys/types.h> /* for pid_t */


#include "system_mgr_enums.h"
#include "smarthome_essentials.h"
#include "logging.h"

#define SYS_MGR_ERROR   LOG_ERROR
#define SYS_MGR_TRACE   LOG_TRACE
#define SYS_MGR_DEBUG   LOG_DEBUG 

#define SYS_MGR_APP_NAME        "System Manager"

typedef struct {
    SYS_MGR_CLIENT_BOOT_MODE bootMode;    
    uint8_t bootTryValue; // Applicable for SYS_MGR_CLIENT_BOOT_TRY
    SYS_MGR_CLIENT_PRIORITY priority;
    SYS_MGR_CLIENT_HEAP_LIMIT heapLimit;
    uint32_t userHeapLimit; // For SYS_MGR_CLIENT_HEAP_USER_DEFINED
} SYS_MGR_CLIENT_PROPERTIES;

typedef struct {
    uint32_t clientID; // Sys manager specific value (Internal use)
    char clientName[128]; // Must field. Name of executable
    boolean isStaticUID; // If false,then sys manager allocates dynamically
    int UID; // Unique ID for the module
    SYS_MGR_CLIENT_PROPERTIES clientProperty; // Optional field. Else set to sys manager decided values
} SYS_MGR_CLIENT_TBL;


// This is an internal datastructure used by sys manager to maintain the info about the client in Running state
typedef struct {
    uint32_t clientID;
    pid_t pid;
    int UID;
    SYS_MGR_CLIENT_STATE state;
    int stateCause; // Change it to an enum later TODO
} SYS_MGR_CLIENT_STATUS;

// Only this table will visibile to other infra modules. But they should be hidden from user apps
typedef struct {
    boolean valid; // Whether the entry is valid in shm obj
    uint32_t UID;  // UID of the client
    uint32_t clientID; // client ID of the client
} SYS_MGR_CLIENT_SHM_TBL_ENTRY;

// Sys Manager overidded field values in the shm obj
#define SYS_MGR_SHM_OBJ_USERDEFINED_CREATED         (1 << 0)
#define SYS_MGR_SHM_OBJ_USERDEFINED_READY           (1 << 1)



extern SYS_MGR_CLIENT_TBL system_mgr_client_tbl[SYS_MGR_CLIENT_MAX_CLIENTS+1];
extern SYS_MGR_CLIENT_STATUS system_mgr_client_status[SYS_MGR_CLIENT_MAX_CLIENTS+1];


SYS_MGR_ERR sysmgr_init_clients(void);
SYS_MGR_ERR sysmgr_start_client(SYS_MGR_CLIENTS client);
SYS_MGR_ERR sysmgr_destroy_clients(void);
SYS_MGR_ERR sysmgr_stop_client(SYS_MGR_CLIENTS client);
SYS_MGR_ERR sysmgr_restart_client(SYS_MGR_CLIENTS client);
void sysmgr_display_client_status(void);


#endif /* INCLUDE_SYSTEM_MGR_H__ */
