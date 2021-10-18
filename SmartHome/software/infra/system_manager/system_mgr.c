/*******************************************************************************
    Description : System manager is responsible for brining up the system.


*******************************************************************************/
#include "system_mgr.h"
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/wait.h> /* for wait */
#include "utils.h"

SYS_MGR_CLIENT_STATUS system_mgr_client_status[SYS_MGR_CLIENT_MAX_CLIENTS+1];
UTILS_SHM_OBJ *sysmgr_shm_obj;
uint32_t sysmgr_num_of_registered_apps = 0; // whenever there is a change in this value,
                                            // comm_manager needs to be notified, so that
                                            // it reads the shm client table again to get the
                                            // lastest updated list

/*****************************************************************************/
/*                  Static Function delcaration                              */
/*****************************************************************************/
static SYS_MGR_ERR sysmgr_create_shm_obj_client_tbl(void);
static SYS_MGR_ERR sysmgr_add_shm_obj_client_tbl_entry(SYS_MGR_CLIENTS client); 
static SYS_MGR_ERR sysmgr_del_shm_obj_client_tbl_entry(SYS_MGR_CLIENTS client); 
static SYS_MGR_ERR sysmgr_update_shm_obj_hdr(int bitfield);
static SYS_MGR_ERR sysmgr_update_shm_obj_hdr_validclients(int validclients);

SYS_MGR_ERR sysmgr_init_clients() {
    SYS_MGR_ERR ret = SYS_MGR_SUCCESS;
    struct stat st = {0};

    SYS_MGR_TRACE("Initializing the %s", SYS_MGR_APP_NAME);

    ret = sysmgr_create_shm_obj_client_tbl();
    if(ret != SYS_MGR_SUCCESS) {
        SYS_MGR_ERROR("Failed to create shm obj client table");
        return ret;
    }

    sleep(1);

    SMARTHOME_CREATE_PROJECT_DEFAULT_FOLDER();
    SMARTHOME_CREATE_MODULE_DEFAULT_FOLDER(apps);
    SMARTHOME_CREATE_MODULE_DEFAULT_FOLDER(mapi);
    SMARTHOME_CREATE_MODULE_DEFAULT_FOLDER(communication_manager);
    SMARTHOME_CREATE_MODULE_DEFAULT_FOLDER(interface_manager);

    uint16_t i = 0;
    while(system_mgr_client_tbl[i].clientID != SYS_MGR_CLIENT_MAX_CLIENTS) {
        // Initialize the client       
        system_mgr_client_status[i].clientID = i;
        system_mgr_client_status[i].pid = -1;
        system_mgr_client_status[i].state = SYS_MGR_CLIENT_STATE_STOPPED;
        system_mgr_client_status[i].stateCause = -1;


        if (system_mgr_client_tbl[i].clientProperty.bootMode == SYS_MGR_CLIENT_BOOT_NEVER) {
            SYS_MGR_DEBUG("Skipping the boot of process %s, UID %d",
                    system_mgr_client_tbl[i].clientName, system_mgr_client_tbl[i].UID);
            i++;
            continue;
        }

        // Now start the client 
        SYS_MGR_TRACE("Initializing %s, UID %d", 
               system_mgr_client_tbl[i].clientName, system_mgr_client_tbl[i].UID);
        sysmgr_start_client(system_mgr_client_tbl[i].clientID);
        SYS_MGR_TRACE("Initializing %s done", system_mgr_client_tbl[i].clientName);
        i++;
    } 

    // Mark the shm obj hdr as ready for use by other sub systems
    if(sysmgr_update_shm_obj_hdr(SYS_MGR_SHM_OBJ_USERDEFINED_READY) != SYS_MGR_SUCCESS) {
        return SYS_MGR_INIT_FAILURE;
    }

    // Update the num of registered apps in the shm obj
    if(sysmgr_update_shm_obj_hdr_validclients(sysmgr_num_of_registered_apps) != SYS_MGR_SUCCESS) {
        return SYS_MGR_INIT_FAILURE;
    }

    return ret;
}

SYS_MGR_ERR sysmgr_start_client(SYS_MGR_CLIENTS client) {    
    char *args[] = {system_mgr_client_tbl[client].clientName, NULL};
    pid_t pid = fork();

    if (pid == 0) {
        execv(args[0], args);
        SYS_MGR_ERROR("Client %s cannot be found or failed to start",
                                                system_mgr_client_tbl[client].clientName);
        exit(127);
    } else {
        // Sys manager process
        system_mgr_client_status[client].pid = pid;
        system_mgr_client_status[client].UID = system_mgr_client_tbl[client].UID;
        system_mgr_client_status[client].state = SYS_MGR_CLIENT_STATE_RUNNING;
        system_mgr_client_status[client].stateCause = 2;     

        // Add the entry to shm_obj
        sysmgr_add_shm_obj_client_tbl_entry(client);
        sysmgr_num_of_registered_apps++;

    }
    return SYS_MGR_SUCCESS;
}

// TODO : This function needs to be enhanced. For now continuing
// with this logic of simple delete
SYS_MGR_ERR sysmgr_destroy_clients() {
    SYS_MGR_ERR ret = SYS_MGR_SUCCESS;

    for (uint16_t i = 0; i < SYS_MGR_CLIENT_MAX_CLIENTS; i++) {
        // No need to try deleting the clients which is not even started by sys manager
        if (system_mgr_client_tbl[i].clientProperty.bootMode == SYS_MGR_CLIENT_BOOT_NEVER) {
            SYS_MGR_DEBUG("Skipping the delete of clientID %d", system_mgr_client_tbl[i].clientID); 
            continue;
        }

        ret = sysmgr_stop_client(system_mgr_client_tbl[i].clientID);
        if (ret != SYS_MGR_SUCCESS) {
            SYS_MGR_ERROR("Failed to stop client %d, process name %s", 
                                            system_mgr_client_tbl[i].clientID,
                                            system_mgr_client_tbl[i].clientName);
            continue;                    
        }
        SYS_MGR_TRACE("Successfully deleted the client %d, process name %s", 
                                            system_mgr_client_tbl[i].clientID,
                                            system_mgr_client_tbl[i].clientName); 

    }

    // Finally destroy the shm obj. Since sysmgr is the owner no need to force delete it
    int shm_ret = utils_destroy_shared_obj(sysmgr_shm_obj, FALSE);
    if(shm_ret < 0) {
        SYS_MGR_ERROR("Failed to delete the sysmgr shm obj, return code %d", shm_ret);
        return SYS_MGR_CLIENT_SHM_OBJ_DEL_ERR;
    }

    return SYS_MGR_SUCCESS;
}

/*
    @brief This function is used to stop(kill) a running client. This function can be
           called from sysmgr_destroy_clients() when sys manager wants to destroy all the
           clients (during system reboot/shutdown) OR when the sys manager feels that it
           needs to stop a particular client on the decision made by sys manager
*/
SYS_MGR_ERR sysmgr_stop_client(SYS_MGR_CLIENTS client) {
    SYS_MGR_TRACE("NOT YET IMPLEMENTED...%d", client);
    SYS_MGR_ERR ret = SYS_MGR_SUCCESS;    

    ret = sysmgr_del_shm_obj_client_tbl_entry(client);
    if(ret != SYS_MGR_SUCCESS) {
        SYS_MGR_ERROR("Failed to delete the shm obj entry for clientID %d",
                        client);
        return ret; 
    }

    sysmgr_num_of_registered_apps--;

    return SYS_MGR_SUCCESS;
}

SYS_MGR_ERR sysmgr_restart_client(SYS_MGR_CLIENTS client) {
    SYS_MGR_TRACE("NOT YET IMPLEMENTED...%d", client);
    SYS_MGR_ERR ret = SYS_MGR_SUCCESS;    

    ret = sysmgr_del_shm_obj_client_tbl_entry(client);
    if(ret != SYS_MGR_SUCCESS) {
        SYS_MGR_ERROR("Failed to delete the shm obj entry for clientID %d",
                        client);
        return ret; 
    }
   
    sysmgr_num_of_registered_apps--;
  
    // Start the app again

    return SYS_MGR_SUCCESS;
}

void sysmgr_display_client_status() {
    SYS_MGR_CLIENTS client;

    SYS_MGR_TRACE("Client Name                 | PID       | UID    | State   | Cause");
    SYS_MGR_TRACE("---------------------------------------------------------");
    for (uint16_t i = 0; i < SYS_MGR_CLIENT_MAX_CLIENTS; i++) {
        client = system_mgr_client_status[i].clientID;
        SYS_MGR_TRACE("%-22s      | %-4d      |  %-4d      | %-6d  | %d  ", 
                            system_mgr_client_tbl[client].clientName, 
                            system_mgr_client_status[client].pid,
                            system_mgr_client_status[client].UID,
                            system_mgr_client_status[client].state,
                            system_mgr_client_status[client].stateCause);

    }

}

static SYS_MGR_ERR sysmgr_create_shm_obj_client_tbl() {
    // Create a shm obj for maintainig the clients.
    // SYs manager will be the sole owner with write permission and all infra
    // modules should have read permission for this shm obj
    int shm_obj_size = SYS_MGR_CLIENT_MAX_CLIENTS * sizeof(SYS_MGR_CLIENT_SHM_TBL_ENTRY);

    sysmgr_shm_obj = utils_create_shared_obj(SYS_MGR_SHM_ID_SYS_MANAGER_CLIENT_TBL, 
                                     shm_obj_size,
            UTILS_SHM_FLAGS_CREATE | UTILS_SHM_FLAGS_RDWR | UTILS_SHM_FLAGS_SHARED);

    if (sysmgr_shm_obj == NULL) {
        SYS_MGR_ERROR("Unable to create shm obj");
        return SYS_MGR_CLIENT_SHM_OBJ_CREATE_ERR;
    }

    memset(sysmgr_shm_obj->addr, 0, shm_obj_size);

    // To indicate to other system which is using this shm obj ID that,
    // sys mgr has created this. Other proccess must wait till flag is set.
    if(sysmgr_update_shm_obj_hdr(SYS_MGR_SHM_OBJ_USERDEFINED_CREATED) != SYS_MGR_SUCCESS) {
        return SYS_MGR_CLIENT_SHM_OBJ_CREATE_ERR;
    }

    return SYS_MGR_SUCCESS;
}

// We will overide the "userdefined.field1" field in the header for our own purpose.
// Its a uint32_t field. Will use it in a bitmap fashion.
// Used to update the user field in the shm obj (Override)
static SYS_MGR_ERR sysmgr_update_shm_obj_hdr(int bitfield) {
    UTILS_SHM_OBJ_HDR *shm_obj_hdr = utils_get_shared_obj_hdr(sysmgr_shm_obj->addr);
    SYS_MGR_TRACE("shm obj header : magic = 0x%x, refcount = %d, obj_id = %d",
                    shm_obj_hdr->magic, shm_obj_hdr->refcount, shm_obj_hdr->obj_id);

    if (shm_obj_hdr == NULL) {
        SYS_MGR_ERROR("Unable to get the shm obj hdr. Bad shm obj");
        return SYS_MGR_CLIENT_SHM_OBJ_BAD_OBJ;
    }

    shm_obj_hdr->userdefined.field1 |= bitfield;

    return SYS_MGR_SUCCESS;
}

// Overriding the "userdefined.field2" for storing the number of valid regsitered clients
static SYS_MGR_ERR sysmgr_update_shm_obj_hdr_validclients(int validclients) {
    UTILS_SHM_OBJ_HDR *shm_obj_hdr = utils_get_shared_obj_hdr(sysmgr_shm_obj->addr);
    SYS_MGR_TRACE("shm obj header : magic = 0x%x, refcount = %d, obj_id = %d",
                    shm_obj_hdr->magic, shm_obj_hdr->refcount, shm_obj_hdr->obj_id);

    if (shm_obj_hdr == NULL) {
        SYS_MGR_ERROR("Unable to get the shm obj hdr. Bad shm obj");
        return SYS_MGR_CLIENT_SHM_OBJ_BAD_OBJ;
    }
    shm_obj_hdr->userdefined.field2 = validclients;

    return SYS_MGR_SUCCESS;  
}

static SYS_MGR_ERR sysmgr_add_shm_obj_client_tbl_entry(SYS_MGR_CLIENTS client) {   
    SYS_MGR_CLIENT_SHM_TBL_ENTRY shm_obj_entry;
    UTILS_SHM_OBJ_HDR *shm_obj_hdr;
    SYS_MGR_ERR ret = SYS_MGR_SUCCESS;
    SYS_MGR_CLIENT_SHM_TBL_ENTRY *shm_obj_addr_ptr;

    memset(&shm_obj_entry, 0, sizeof(SYS_MGR_CLIENT_SHM_TBL_ENTRY));

    shm_obj_entry.valid = TRUE;
    shm_obj_entry.UID = system_mgr_client_status[client].UID;
    shm_obj_entry.clientID = system_mgr_client_status[client].clientID;

    shm_obj_hdr = utils_get_shared_obj_hdr(sysmgr_shm_obj->addr);

    if(shm_obj_hdr->magic != UTILS_SHM_OBJ_MAGIC_NUM) {
        SYS_MGR_ERROR("System Manager client shm obj table is inconsistent");
        return SYS_MGR_CLIENT_SHM_OBJ_ENTRY_ADD_ERR;
    }
    
    // client ID will be the index into this table
    shm_obj_addr_ptr = (SYS_MGR_CLIENT_SHM_TBL_ENTRY *)sysmgr_shm_obj->addr + client;
    memcpy((void *)shm_obj_addr_ptr, &shm_obj_entry, sizeof(shm_obj_entry));

    return ret;
}

static SYS_MGR_ERR sysmgr_del_shm_obj_client_tbl_entry(SYS_MGR_CLIENTS client) {
    SYS_MGR_CLIENT_SHM_TBL_ENTRY shm_obj_entry;
    UTILS_SHM_OBJ_HDR *shm_obj_hdr;
    SYS_MGR_ERR ret = SYS_MGR_SUCCESS;
    SYS_MGR_CLIENT_SHM_TBL_ENTRY *shm_obj_addr_ptr;

    shm_obj_hdr = utils_get_shared_obj_hdr(sysmgr_shm_obj->addr);

    if(shm_obj_hdr->magic != UTILS_SHM_OBJ_MAGIC_NUM) {
        SYS_MGR_ERROR("System Manager client shm obj table is inconsistent");
        return SYS_MGR_CLIENT_SHM_OBJ_ENTRY_DEL_ERR;
    }

    shm_obj_addr_ptr = (SYS_MGR_CLIENT_SHM_TBL_ENTRY *)sysmgr_shm_obj->addr + client;

    // Setting the valid bit to False is good enough to delete the entry
    shm_obj_addr_ptr->valid = FALSE;

    return ret;
}

// TODO:
// Spwan a thread and periodically keep checking the status of processes.
// Check for the processes CPU utilization etc.
// Take action on these processes based on policies or rules set for those processes



