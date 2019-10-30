/*******************************************************************************
    Description : System manager is responsible for brining up the system.

*******************************************************************************/

#include "system_mgr.h"

SYS_MGR_CLIENT_TBL system_mgr_client_tbl[] = { 
    {
        .clientName = "app_manager",
        .clientLocation = "build/bin/app_manager",
    },
    {
        .clientName = "database_manager",
        .clientLocation = "build/bin/app_manager",
    },
};
