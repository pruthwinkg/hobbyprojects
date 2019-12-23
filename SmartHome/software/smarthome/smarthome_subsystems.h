/*******************************************************************************
    Description : SmartHome sub systems header. It has all the static and
                dynamic modules required for the system

*******************************************************************************/

#ifndef INCLUDE_SMARTHOME_SUBSYSTEMS_H__
#define INCLUDE_SMARTHOME_SUBSYSTEMS_H__

#include "smarthome_enums_to_str.h"

// There only 1024 well UIDs which are statically defined
#define SMARTHOME_SUBSYSTEM_STATIC_UID_BASE   (0)    // 0 UID is always System Manager
#define SMARTHOME_SUBSYSTEM_STATIC_UID_MAX    (1024)

// Most of the user apps are allocated UIDs dynamically
#define SMARTHOME_SUBSYSTEM_DYNAMIC_UID_BASE  (2000)
#define SMARTHOME_SUBSYSTEM_DYNAMIC_UID_MAX   (5000)

BEGIN_ENUM(SMARTHOME_SUBSYSTEM) {
    ADD_ENUM_VAL_STR(SMARTHOME_SUBSYSTEM_SYS_MANAGER, SMARTHOME_SUBSYSTEM_STATIC_UID_BASE, "System Manager")
    ADD_ENUM_STR(SMARTHOME_SUBSYSTEM_COMM_MANAGER, "Communication Manager")
    ADD_ENUM_STR(SMARTHOME_SUBSYSTEM_APP_MANAGER, "Application Manager")
    ADD_ENUM_STR(SMARTHOME_SUBSYSTEM_DATABASE_MANAGER, "Database Manager")
    ADD_ENUM_STR(SMARTHOME_SUBSYSTEM_USERS_MANAGER, "Users Manager")
    ADD_ENUM(SMARTHOME_SUBSYSTEM_MAX)
} END_ENUM(SMARTHOME_SUBSYSTEM);

    
#endif /* INCLUDE_SMARTHOME_SUBSYSTEMS_H__ */
