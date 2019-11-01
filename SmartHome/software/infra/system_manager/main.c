/*******************************************************************************
    Description : This is the entry point for system manager. System manager
                is responsible for brining up the system.

                This is the first process which comes up in this system. It is
                the parent for all other processes
*******************************************************************************/

#include "system_mgr.h"

int main() {

    SYS_MGR_TRACE("Starting system manager....\n");

    sysmgr_init_clients();

    return 0;
}
