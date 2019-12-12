/*******************************************************************************
    Description : System manager is responsible for brining up the system.

*******************************************************************************/

#include "system_mgr.h"

// Order of the sub-systems is important for correct behaviour
SYS_MGR_CLIENT_TBL system_mgr_client_tbl[] = { 
    {
        .clientID = SYS_MGR_CLIENT_IPC_MANAGER,
        .clientName = "comm_manager",
        .clientProperty = 
            {
                .bootMode = SYS_MGR_CLIENT_BOOT_ALWAYS,
                .bootTryValue = -1,
                .priority = SYS_MGR_CLIENT_PRIO_CRITICAL,
                .heapLimit = SYS_MGR_CLIENT_HEAP_2GB,
                .userHeapLimit = -1,
            }
    },

    {
        .clientID = SYS_MGR_CLIENT_APP_MANAGER,
        .clientName = "app_manager",
        .clientProperty = 
            {
                .bootMode = SYS_MGR_CLIENT_BOOT_ALWAYS,
                .bootTryValue = -1,
                .priority = SYS_MGR_CLIENT_PRIO_HIGH,
                .heapLimit = SYS_MGR_CLIENT_HEAP_1GB,
                .userHeapLimit = -1,
            }
    },
    {
        .clientID = SYS_MGR_CLIENT_DATABASE_MANAGER,
        .clientName = "database_manager",
        .clientProperty = 
            {
                .bootMode = SYS_MGR_CLIENT_BOOT_ALWAYS,
                .bootTryValue = -1,
                .priority = SYS_MGR_CLIENT_PRIO_HIGH,
                .heapLimit = SYS_MGR_CLIENT_HEAP_1GB,
                .userHeapLimit = -1,
            }

    },

    {
        .clientID = SYS_MGR_CLIENT_USERS_MANAGER,
        .clientName = "users_manager",
        .clientProperty = 
            {
                .bootMode = SYS_MGR_CLIENT_BOOT_ALWAYS,
                .bootTryValue = -1,
                .priority = SYS_MGR_CLIENT_PRIO_NORMAL,
                .heapLimit = SYS_MGR_CLIENT_HEAP_1GB,
                .userHeapLimit = -1,
            }
    },

};
