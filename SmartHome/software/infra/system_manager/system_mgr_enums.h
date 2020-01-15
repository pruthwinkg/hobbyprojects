/*******************************************************************************
    Description: Contains all the protypes for the system manager
    

*******************************************************************************/

#include "smarthome_essentials.h"

#define SYS_MGR_ERR_BASE        (SMARTHOME_ERROR_CODE_SYS_MGR)

BEGIN_ENUM(SYS_MGR_ERR) {
    ADD_ENUM_VAL(SYS_MGR_SUCCESS, 0)
    ADD_ENUM_VAL(SYS_MGR_INIT_FAILURE, SYS_MGR_ERR_BASE)
    ADD_ENUM(SYS_MGR_CLIENT_INIT_FAILURE)
    ADD_ENUM_STR(SYS_MGR_CLIENT_SHM_OBJ_CREATE_ERR, "Failed to create shm obj")
    ADD_ENUM_STR(SYS_MGR_CLIENT_SHM_OBJ_DEL_ERR, "Failed to delete shm obj")
    ADD_ENUM_STR(SYS_MGR_CLIENT_SHM_OBJ_ENTRY_ADD_ERR, "Failed to add shm obj entry to tbl")
    ADD_ENUM_STR(SYS_MGR_CLIENT_SHM_OBJ_ENTRY_DEL_ERR, "Failed to delete shm obj entry from tbl")
    ADD_ENUM_STR(SYS_MGR_CLIENT_SHM_OBJ_BAD_OBJ, "Bad shm obj")
} END_ENUM (SYS_MGR_ERR);


BEGIN_ENUM(SYS_MGR_CLIENT_BOOT_MODE) {
    ADD_ENUM_STR(SYS_MGR_CLIENT_BOOT_NEVER, "Disable booting of process") // Depending on end-application/power/memory constraint
    ADD_ENUM_STR(SYS_MGR_CLIENT_BOOT_ONCE, "Boot only once")
    ADD_ENUM_STR(SYS_MGR_CLIENT_BOOT_ALWAYS, "Boot always upon process crash")
    ADD_ENUM_STR(SYS_MGR_CLIENT_BOOT_TRY, "Boot X number of times upon process crash")
} END_ENUM(SYS_MGR_CLIENT_BOOT_MODE);


BEGIN_ENUM(SYS_MGR_CLIENT_PRIORITY) {
    ADD_ENUM_VAL(SYS_MGR_CLIENT_PRIO_LOW, 0)
    ADD_ENUM(SYS_MGR_CLIENT_PRIO_NORMAL) // Most of the process starts with this priority
    ADD_ENUM(SYS_MGR_CLIENT_PRIO_HIGH)
    ADD_ENUM(SYS_MGR_CLIENT_PRIO_CRITICAL) // For critical apps, without which system can malform.
} END_ENUM(SYS_MGR_CLIENT_PRIORITY);

BEGIN_ENUM(SYS_MGR_CLIENT_HEAP_LIMIT) {
    ADD_ENUM(SYS_MGR_CLIENT_HEAP_500M)
    ADD_ENUM(SYS_MGR_CLIENT_HEAP_700M) // 700 MB
    ADD_ENUM(SYS_MGR_CLIENT_HEAP_1GB)
    ADD_ENUM(SYS_MGR_CLIENT_HEAP_2GB)
    ADD_ENUM(SYS_MGR_CLIENT_HEAP_2p5GB) // 2.5 GB
    ADD_ENUM(SYS_MGR_CLIENT_HEAP_USER_DEFINED)
} END_ENUM(SYS_MGR_CLIENT_HEAP_LIMIT);

BEGIN_ENUM(SYS_MGR_CLIENT_STATE) {
    ADD_ENUM(SYS_MGR_CLIENT_STATE_STOPPED)
    ADD_ENUM(SYS_MGR_CLIENT_STATE_RUNNING)
    ADD_ENUM(SYS_MGR_CLIENT_STATE_PAUSED)
} END_ENUM(SYS_MGR_CLIENT_STATE);



// Add the clients which needs to be managed by sys manager. These are clientID. 
// NOTE : UIDs are very different from clientID
BEGIN_ENUM(SYS_MGR_CLIENTS) {
    ADD_ENUM_STR(SYS_MGR_CLIENT_COMM_MANAGER, "Communication Manager")
    ADD_ENUM_STR(SYS_MGR_CLIENT_APP_MANAGER,  "Application Manager")
    ADD_ENUM_STR(SYS_MGR_CLIENT_DATABASE_MANAGER, "Database Manager")
    ADD_ENUM_STR(SYS_MGR_CLIENT_USERS_MANAGER, "Users Manager")
    ADD_ENUM(SYS_MGR_CLIENT_MAX_CLIENTS)
} END_ENUM(SYS_MGR_CLIENTS);


// The sys manager enums should be used by full infra for portability purpose
// This ensures that infra is agnostic of end application and can be easily reused
// for any end application

#define SYS_MGR_SYSTEM_STATIC_UID_BASE          (SMARTHOME_SUBSYSTEM_STATIC_UID_BASE)
#define SYS_MGR_SYSTEM_STATIC_UID_MAX           (SMARTHOME_SUBSYSTEM_STATIC_UID_MAX)
#define SYS_MGR_SYSTEM_DYNAMIC_UID_BASE         (SMARTHOME_SUBSYSTEM_DYNAMIC_UID_BASE)
#define SYS_MGR_SYSTEM_DYNAMIC_UID_MAX          (SMARTHOME_SUBSYSTEM_DYNAMIC_UID_MAX)

BEGIN_ENUM(SYS_MGR_SYSTEM_UID) {
    ADD_ENUM_VAL(SYS_MGR_SYSTEM_UID_SYS_MANAGER, SMARTHOME_SUBSYSTEM_SYS_MANAGER)
    ADD_ENUM_VAL(SYS_MGR_SYSTEM_UID_COMM_MANAGER, SMARTHOME_SUBSYSTEM_COMM_MANAGER)
    ADD_ENUM_VAL(SYS_MGR_SYSTEM_UID_APP_MANAGER, SMARTHOME_SUBSYSTEM_APP_MANAGER)
    ADD_ENUM_VAL(SYS_MGR_SYSTEM_UID_DATABASE_MANAGER, SMARTHOME_SUBSYSTEM_DATABASE_MANAGER)
    ADD_ENUM_VAL(SYS_MGR_SYSTEM_UID_USERS_MANAGER, SMARTHOME_SUBSYSTEM_USERS_MANAGER)
} END_ENUM(SYS_MGR_SYSTEM_UID);


// This enum is for identifying the shm obj uniquiely across the system.
// They are defined for a particular table.
// NOTE : Please make sure these are IDs are UNIQUE for the entire system. Else
// they will end up accessing wrong shm objs
#define SYS_MGR_SHM_ID_BASE             (0x01)
BEGIN_ENUM(SYS_MGR_SHM_ID) {
    ADD_ENUM_VAL_STR(SYS_MGR_SHM_ID_SYS_MANAGER_CLIENT_TBL, SYS_MGR_SHM_ID_BASE, "System Manager SHM ID for Client table")
} END_ENUM(SYS_MGR_SHM_ID);



