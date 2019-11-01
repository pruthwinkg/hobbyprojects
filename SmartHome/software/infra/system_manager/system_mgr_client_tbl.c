/*******************************************************************************
    Description : System manager is responsible for brining up the system.

*******************************************************************************/

#include "system_mgr.h"


SYS_MGR_CLIENT_TBL system_mgr_client_tbl[] = { 
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
    },
};
