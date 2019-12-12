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

    // This cannot be set inside the child process, because the context will be different
    system_mgr_client_status[client].clientID = client;
    //system_mgr_client_status[client].pid = -1;
    //system_mgr_client_status[client].state = SYS_MGR_CLIENT_STATE_STOPPED;
    //system_mgr_client_status[client].stateCause = -1;

    if (pid == 0) {
        execv(args[0], args);
        SYS_MGR_ERROR("Client %s cannot be found or failed to start\n",
                                                system_mgr_client_tbl[client].clientName);
        exit(127);
    } else {
        // Sys manager process
        system_mgr_client_status[client].pid = pid;
        system_mgr_client_status[client].state = SYS_MGR_CLIENT_STATE_RUNNING;
        system_mgr_client_status[client].stateCause = 2;
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

void sysmgr_display_client_status() {
    SYS_MGR_CLIENTS client;

    SYS_MGR_TRACE("Client Name                 | PID       | State   | Cause\n");
    SYS_MGR_TRACE("---------------------------------------------------------\n");
    for (uint16_t i = 0; i < SYS_MGR_CLIENT_MAX_CLIENTS; i++) {
        client = system_mgr_client_status[i].clientID;
        SYS_MGR_TRACE("%-22s      | %-4d      | %-6d  | %d  \n", 
                            system_mgr_client_tbl[client].clientName, 
                            system_mgr_client_status[client].pid,
                            system_mgr_client_status[client].state,
                            system_mgr_client_status[client].stateCause);

    }

}




// TODO:
// Spwan a thread and periodically keep checking the status of processes.
// Check for the processes CPU utilization etc.
// Take action on these processes based on policies or rules set for those processes



