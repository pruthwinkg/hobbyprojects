/*******************************************************************************
    Description : This is the entry point for system manager. System manager
                is responsible for brining up the system.

                This is the first process which comes up in this system. It is
                the parent for all other processes
*******************************************************************************/

#include "system_mgr.h"
#include <unistd.h> /* for fork */
#include <sys/wait.h> /* for wait */


int main() {
    int status;
    int c_pid;

    SYS_MGR_TRACE("Starting system manager....\n");

    sysmgr_init_clients();

    // Wait for ALL child processes to exit
    while((c_pid = wait(&status)) > 0) {
        SYS_MGR_DEBUG("pid = %d exited with status %d\n", c_pid, status);
    }

    sysmgr_display_client_status();    

    return 0;
}
