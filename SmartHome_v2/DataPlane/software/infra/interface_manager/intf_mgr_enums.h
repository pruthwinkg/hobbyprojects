/*******************************************************************************
    Description : Interface manager enums

*******************************************************************************/

#include "smarthome_essentials.h"

#define INTF_MGR_ERR_BASE        (SMARTHOME_ERROR_CODE_INTF_MGR)

BEGIN_ENUM(INTF_MGR_ERR) {
    ADD_ENUM_VAL(INTF_MGR_SUCCESS, 0)
    ADD_ENUM(INTF_MGR_INVALID_ARG)
} END_ENUM(INTF_MGR_ERR);
