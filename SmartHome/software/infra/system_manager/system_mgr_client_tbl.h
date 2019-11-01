/*******************************************************************************
    Description : System manager is responsible for brining up the system.

*******************************************************************************/

// List of clients which is managed by the system manager
typedef enum {
    SYS_MGR_CLIENT_APP_MANAGER = 0,
    SYS_MGR_CLIENT_DATABASE_MANAGER,
    SYS_MGR_CLIENT_MAX_CLIENTS
} SYS_MGR_CLIENTS;


