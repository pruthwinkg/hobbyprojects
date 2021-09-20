/*******************************************************************************
    Description : SmartHome sub systems header. It has all the static and
                dynamic modules required for the system

*******************************************************************************/

#ifndef INCLUDE_SMARTHOME_SUBSYSTEMS_H__
#define INCLUDE_SMARTHOME_SUBSYSTEMS_H__

#include "smarthome_enums_to_str.h"
#include <sys/stat.h>

// This location defines the file structure where all project specific runtime temporary files are created
#define SMARTHOME_SYSTEM_DEFAULT_FOLDER     "/tmp/smarthome"
#define SMARTHOME_GET_MODULE_DEFAULT_LOC(name) SMARTHOME_SYSTEM_DEFAULT_FOLDER "/" #name "/"

#define SMARTHOME_CREATE_PROJECT_DEFAULT_FOLDER()	  do { \
															struct stat st = {0}; \
															if(stat(SMARTHOME_SYSTEM_DEFAULT_FOLDER, &st) == -1) { \
												   	    		if(mkdir(SMARTHOME_SYSTEM_DEFAULT_FOLDER, 0700) == -1) { \
												            		printf("Error: Failed to create directory: %s\n", SMARTHOME_SYSTEM_DEFAULT_FOLDER); \
												                	perror("Error: "); \
												            	} \
											          		} \
														} while(0) \


#define SMARTHOME_CREATE_MODULE_DEFAULT_FOLDER(name)	do { \
															struct stat st = {0}; \
															if(stat(SMARTHOME_GET_MODULE_DEFAULT_LOC(name), &st) == -1) { \
												   	    		if(mkdir(SMARTHOME_GET_MODULE_DEFAULT_LOC(name), 0700) == -1) { \
												            		printf("Error: Failed to create directory: %s\n", SMARTHOME_GET_MODULE_DEFAULT_LOC(name)); \
												                	perror("Error: "); \
												            	} \
											          		} \
														} while(0) \

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
    ADD_ENUM_STR(SMARTHOME_SUBSYSTEM_INTERFACE_MANAGER, "Interface Manager")
    ADD_ENUM(SMARTHOME_SUBSYSTEM_MAX)
} END_ENUM(SMARTHOME_SUBSYSTEM);


/******************************************************************************************************************************/
/*                                           Defines for all infra subsystems                                                 */
/******************************************************************************************************************************/
#define COMMUNICATION_MANAGER_GET_DEFAULT_LOC           SMARTHOME_GET_MODULE_DEFAULT_LOC(communication_manager)
#define COMMUNICATION_MANAGER_FILEPATH(filename)        SMARTHOME_GET_MODULE_DEFAULT_LOC(communication_manager) #filename
#define COMMUNICATION_MANAGER_CREATE_LOGS_FOLDER 	    SMARTHOME_CREATE_MODULE_DEFAULT_FOLDER(communication_manager/logs)
#define COMMUNICATION_MANAGER_LOGS_FILEPATH(filename)   SMARTHOME_GET_MODULE_DEFAULT_LOC(communication_manager/logs) #filename

#define INTERFACE_MANAGER_GET_DEFAULT_LOC           SMARTHOME_GET_MODULE_DEFAULT_LOC(interface_manager)
#define INTERFACE_MANAGER_CREATE_LOGS_FOLDER		SMARTHOME_CREATE_MODULE_DEFAULT_FOLDER(interface_manager/logs)  
#define INTERFACE_MANAGER_LOGS_FILEPATH(filename)   SMARTHOME_GET_MODULE_DEFAULT_LOC(interface_manager/logs) #filename


/******************************************************************************************************************************/
/*                                           Defines for all user apps subsystems                                             */
/******************************************************************************************************************************/
#define SHELL_APP_GET_DEFAULT_LOC           SMARTHOME_GET_MODULE_DEFAULT_LOC(apps/shell)
#define SHELL_APP_CREATE_DEFAULT_LOC        SMARTHOME_CREATE_MODULE_DEFAULT_FOLDER(apps/shell)
#define SHELL_APP_FILEPATH(filename)        SMARTHOME_GET_MODULE_DEFAULT_LOC(apps/shell) #filename

#endif /* INCLUDE_SMARTHOME_SUBSYSTEMS_H__ */
