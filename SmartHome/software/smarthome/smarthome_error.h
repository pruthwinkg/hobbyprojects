/*******************************************************************************
    Description : SmartHome Error codes.

*******************************************************************************/
#ifndef INCLUDE_SMARTHOME_ERROR_H__
#define INCLUDE_SMARTHOME_ERROR_H__

#include "smarthome_enums_to_str.h"

// Each module is allocated a max of 256 error codes
// It is upto each module to define its own set of 256 specific error codes

BEGIN_ENUM(SMARTHOME_ERROR_CODES) {
    ADD_ENUM_VAL(SMARTHOME_ERROR_CODE_SYS_MGR, 0xFFFF0000)
    ADD_ENUM_VAL(SMARTHOME_ERROR_CODE_APP_MANAGER, 0xFFFF0100)
    ADD_ENUM_VAL(SMARTHOME_ERROR_CODE_DATABASE_MGR, 0xFFFF0200)
    ADD_ENUM_VAL(SMARTHOME_ERROR_CODE_COMM_MGR_SRV, 0xFFFF0300)
    ADD_ENUM_VAL(SMARTHOME_ERROR_CODE_COMM_MGR_LIB, 0xFFFF0400)
    ADD_ENUM_VAL(SMARTHOME_ERROR_CODE_MAX_ERROR, 0xFFFFFFFF)
} END_ENUM (SMARTHOME_ERROR_CODES);



#endif /* INCLUDE_SMARTHOME_ERROR_H__  */
