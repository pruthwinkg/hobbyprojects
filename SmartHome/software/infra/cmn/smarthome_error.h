/*******************************************************************************
    Description : SmartHome Error codes.

*******************************************************************************/

// Each module is allocated a max of 256 error codes
// It is upto each module to define its own set of 256 specific error codes
typedef enum {
    SMARTHOME_ERROR_CODE_SYS_MGR = 0xFFFF0000,
    SMARTHOME_ERROR_CODE_APP_MANAGER = 0xFFFF0100,
    SMARTHOME_ERROR_CODE_DATABASE_MGR = 0xFFFF0200,
    SMARTHOME_ERROR_CODE_MAX_ERROR = 0xFFFFFFFF
} SMARTHOME_ERROR_CODES;


