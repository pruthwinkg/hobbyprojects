/*******************************************************************************
    Description : MAPI library (Fine tuning configurations)

    This file allows advanced users who understand the library's internals to adjust 
    its behavior to fit their specific needs or optimize for specific performance 
    characteristics. Via this file, users get extremely fine-grained control over
    the library's behavior, such as the port selection algorithm, failure thresholds,
    recovery intervals, and more.

    NOTE : The default values are chosen to be safe and work well in most scenarios.
    Changing these values can have unintended consequences, so use with caution.

    Also these tuning params are global across all MAPI IDs for an application.

*******************************************************************************/
#include "mapi_config.h"
#include "mapi_internal.h"
#include <string.h>

boolean mapi_tuning_params_applied = FALSE;

// Default tuning params. Do not modify this table directly.
// For majority of the cases, the default values should be sufficient. It is carefully chosen to work well in most scenarios.
// If you want to change any of the values for your app, use the mapi_apply_tuning_params function.
MAPI_DEFAULT_TUNING_GROUP mapi_tuning_group[] = {
    {
        .group_name = MAPI_TUNING_GROUP_GROUP1,
        .params = (MAPI_TUNING_PARAM_INFO[]) {            
            {                
                .param_idx = 0,
                .name = "port_selection_params",
                .size = sizeof(MAPI_PORT_SELECTION_ALGORITHM),
                .value = (MAPI_PORT_SELECTION_ALGORITHM*){MAPI_PORT_SELECTION_ALGORITHM_FIRST_AVAILABLE},
                .description = "Port selection algorithm"
            },
            {
                .param_idx = 1,
                .name = "port_failure_threshold",
                .size = sizeof(uint8_t),
                .value = (uint8_t*){3},
                .description = "Port failure threshold"
            },
            {
                .param_idx = 2,
                .name = "jitter_enabled",
                .size = sizeof(boolean),
                .value = (boolean*){FALSE},
                .description = "Jitter enabled"
            }
        },
        .num_params = 3
    },
    {
        .group_name = MAPI_TUNING_GROUP_GROUP2,
        .params = (MAPI_TUNING_PARAM_INFO[]) {
            {
                .param_idx = 0,
                .name = "group2_param1",
                .size = sizeof(uint8_t),
                .value = (uint8_t*){5},
                .description = "Group 2 Param 1"
            },
            {
                .param_idx = 1,
                .name = "group2_param2", 
                .size = sizeof(uint8_t),
                .value = (uint8_t*){10},
                .description = "Group 2 Param 2"
            }
        },
        .num_params = 2
    }
};

/*************************************************************************************
 *                Public functions
 *************************************************************************************/
/*
* @brief Applies the fine tuning parameters to the MAPI library.
*
* This function allows advanced users to adjust the library's behavior to fit their
* specific needs or optimize for specific performance characteristics. The function
* takes a pointer to a struct containing the fine tuning parameters and applies them
* to the library.
*
*  NOTE: This function should be called only after the MAPI library has been initialized.
*     It can be applied only once immediately after initialization. Any subsequent calls
*    will be ignored.
*
*   Also these tuning params are global across all MAPI IDs for an application.
* 
* @param tuning_params A pointer to a struct containing the fine tuning parameters.

 Example usage:

        mapi_init(LOG_LVL_DEBUG, TEST_COMM_MGR_LIB_SRC_UID, 0);

        MAPI_UPDATED_TUNING_PARAM mapi_updated_tuning[] = {
            SET_TUNING_PARAM(MAPI_TUNING_GROUP_GROUP1, 0, MAPI_PORT_SELECTION_ALGORITHM_ROUND_ROBIN, MAPI_PORT_SELECTION_ALGORITHM),
            SET_TUNING_PARAM(MAPI_TUNING_GROUP_GROUP1, 2, TRUE, boolean),
            SET_TUNING_PARAM(MAPI_TUNING_GROUP_GROUP2, 1, 20, uint8_t)
        };

        mapi_apply_tuning_params(mapi_updated_tuning, sizeof(mapi_updated_tuning)/sizeof(MAPI_UPDATED_TUNING_PARAM));

        // Rest of MAPI code



*/
void mapi_apply_tuning_params(MAPI_UPDATED_TUNING_PARAM *tuning_params, int num_params) {
    if (mapi_initialized == FALSE) {
        MAPI_LOG_ERROR("MAPI not initialized");
        return;
    }
    if (mapi_tuning_params_applied == TRUE) {
        MAPI_LOG_ERROR("Tuning parameters already applied");
        return;
    }
    if(__mapi_usage_started == TRUE) { // Make sure that the tuning params are applied before the usage starts
        MAPI_LOG_ERROR("MAPI already in use. Cannot apply tuning params now");
        return;
    }

    if (tuning_params == NULL || num_params <= 0) {
        MAPI_LOG_ERROR("Invalid tuning params");
        return;
    }

    for (int i = 0; i < num_params; i++) {
        MAPI_UPDATED_TUNING_PARAM *current_param = &tuning_params[i];

        MAPI_DEFAULT_TUNING_GROUP *default_group = &mapi_tuning_group[current_param->group_name];
        MAPI_TUNING_PARAM_INFO *default_param = &default_group->params[current_param->param_idx];

        // Check for the valid value of the param
        if((current_param->group_name >= MAPI_TUNING_GROUP_MAX) || (current_param->param_idx >= default_group->num_params)) {
            MAPI_LOG_ERROR("Invalid group name or param idx");
            continue;
        }

        // Check the size of the provided value
        if (default_param->size != sizeof(*(current_param->value))) {
            MAPI_LOG_ERROR("Size mismatch for parameter %s. Expected size: %zu, Provided size: %zu", 
                            default_param->name, default_param->size, sizeof(*(current_param->value)));
            continue; // Skip this parameter
        }

        memcpy(default_param->value, current_param->value, default_param->size);
        MAPI_LOG_TRACE("Updated the tuning param : %s in group : %s with the new value", default_param->name, default_group->group_name);
    }

    mapi_tuning_params_applied = TRUE;
}

void *mapi_get_tuning_param_value(MAPI_TUNING_GROUPS group_name, uint8_t param_idx) {
    if (group_name >= MAPI_TUNING_GROUP_MAX) {
        MAPI_LOG_ERROR("Invalid group name");
        return NULL;
    }

    MAPI_DEFAULT_TUNING_GROUP *default_group = &mapi_tuning_group[group_name];
    if (param_idx >= default_group->num_params) {
        MAPI_LOG_ERROR("Invalid param index");
        return NULL;
    }

    MAPI_TUNING_PARAM_INFO *default_param = &default_group->params[param_idx];
    return default_param->value;
}
