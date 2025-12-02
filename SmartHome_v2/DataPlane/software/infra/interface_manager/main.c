/*******************************************************************************
    Description : This is the entry point for Interface manager. Interface Manager
        is responsible for allowing internal and extern sub systems to interact with
        the system.
*******************************************************************************/

#include "intf_mgr.h"

int main() {

    INTERFACE_MANAGER_CREATE_LOGS_FOLDER;
    // Initialize logger
    log_lib_init(INTERFACE_MANAGER_LOGS_FILEPATH(interface_manager.log), LOG_LVL_DEBUG);

    INTF_MGR_TRACE("Starting interface manager...");

    return 0;
}
