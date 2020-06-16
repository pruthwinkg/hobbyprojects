/*****************************************************************************
    Description : This is a simple shell program for interfacing with various
        componens of this system
******************************************************************************/
#include "shell.h"
#include "shell_intf.h"


void shell_app_display_help() {
    SHELL_APP_PRINT("\nShell Commands :\n\n");
    SHELL_APP_PRINT("\thelp             Displays shell commands\n");
    SHELL_APP_PRINT("\thelp <app>       Displays help for the app\n");
    SHELL_APP_PRINT("\tquit             Exits the shell\n"); 
    SHELL_APP_PRINT("\tlist             Displays shell supported apps\n");

}

void shell_app_display_list() {
    uint16_t i = 0;
   
    SHELL_APP_PRINT("\nShell supported apps list\n");
    SHELL_APP_PRINT("Flags : D - Dynamic UID, S - Static UID\n");
    SHELL_APP_PRINT("\t     AppName                             UID \n");
    SHELL_APP_PRINT("\t-----------------------------------------------\n");
    while(shell_supported_apps[i].appName != NULL) {
        SHELL_APP_PRINT("\t%s\t\t\t%d%s\n", 
                shell_supported_apps[i].appName,
                shell_supported_apps[i].uid,
                shell_supported_apps[i].uid_type ? "(D)":"(S)");
        i++;
    }
    SHELL_APP_PRINT("\n");
}

void shell_app_display_apps_help(const char *app) {
    uint16_t i = 0, j = 0;

    while(shell_supported_apps[i].appName != NULL) {
        if(!strcmp(shell_supported_apps[i].appName, app)) {
            SHELL_APP_PRINT("\nHelp for app : %s , %d%s\n", 
                            shell_supported_apps[i].appName,
                            shell_supported_apps[i].uid,
                            shell_supported_apps[i].uid_type ? "(D)":"(S)");
            while(shell_supported_apps[i].appArray[j].token != 0xFFFF) {  
                SHELL_APP_PRINT("\t%s\n", shell_supported_apps[i].appArray[j].full_query);
                j++;
            }
            break;
        }
        i++;
    }

}

SHELL_APP_ERR shell_app_get_uid_from_appName(const char *app, uint16_t *uid) {
    uint16_t i = 0;

    while(shell_supported_apps[i].appName != NULL) {
        if(!strcmp(shell_supported_apps[i].appName, app)) {
            if(shell_supported_apps[i].uid_type == SHELL_APP_UID_STATIC) {
                *uid = shell_supported_apps[i].uid;
                return SHELL_APP_SUCCESS; 
            } else { // Dynamic
                return SHELL_APP_DYNAMIC_APP;
            }
        }
        i++;
    }
    return SHELL_APP_UNKNOWN_APP;
}


SHELL_APP_ERR shell_app_get_token_from_query(const char *app, const char *query, uint16_t *token) {
    uint16_t i = 0, j = 0;

    while(shell_supported_apps[i].appName != NULL) { 
        if(!strcmp(shell_supported_apps[i].appName, app)) {
            while(shell_supported_apps[i].appArray[j].token != 0xFFFF) {
                if(!strcmp(shell_supported_apps[i].appArray[j].full_query, query)) {
                    *token = shell_supported_apps[i].appArray[j].token;
                    return SHELL_APP_SUCCESS;
                }
                j++;
            }
            break;
        }
        i++;
    }
    return SHELL_APP_FAILURE;
}

