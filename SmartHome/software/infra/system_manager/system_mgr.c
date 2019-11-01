/*******************************************************************************
    Description : System manager is responsible for brining up the system.


*******************************************************************************/
#include "system_mgr.h"
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/wait.h> /* for wait */

SYS_MGR_CLIENT_STATUS system_mgr_client_status[SYS_MGR_CLIENT_MAX_CLIENTS];

SYS_MGR_ERR sysmgr_init_clients() {
   
    for (uint16_t i = 0; i < SYS_MGR_CLIENT_MAX_CLIENTS; i++) {
        // Initialize the client       


        // Now start the client 
        sysmgr_start_client(system_mgr_client_tbl[i].clientID);
        SYS_MGR_TRACE("Initializing %s done\n", system_mgr_client_tbl[i].clientName);
    } 

    return SYS_MGR_SUCCESS;
}

SYS_MGR_ERR sysmgr_start_client(SYS_MGR_CLIENTS client) {
    char *args[] = {system_mgr_client_tbl[client].clientName, NULL};
    pid_t pid = fork();
    if (pid == 0) {
        execv(args[0], args);
        SYS_MGR_ERROR("Client %s cannot be found or failed to start\n",
                                                system_mgr_client_tbl[client].clientName);
        exit(127);
    } else {
        // Sys manager process
        system_mgr_client_status[client].clientID = client;
        system_mgr_client_status[client].pid = pid;
        system_mgr_client_status[client].state = SYS_MGR_CLIENT_STATE_RUNNING;
    }
    return SYS_MGR_SUCCESS;
}

SYS_MGR_ERR sysmgr_stop_client(SYS_MGR_CLIENTS client) {
    SYS_MGR_TRACE("%d\n", client);
    return SYS_MGR_SUCCESS;
}

SYS_MGR_ERR sysmgr_restart_client(SYS_MGR_CLIENTS client) {
    SYS_MGR_TRACE("%d\n", client);
    return SYS_MGR_SUCCESS;
}
