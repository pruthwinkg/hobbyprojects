/*****************************************************************************
    Description: MAPI library

******************************************************************************/
#include "mapi_adv.h"

MAPI_LIB_ERR mapi_update_comms_policy(mapiID mid, MAPI_USER_ADVANCED_CONFIG *new_policy) {
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];
    MAPI_USER_ADVANCED_CONFIG *adv_config = (MAPI_USER_ADVANCED_CONFIG *)mapi_internal_info->adv_config;

    if (!mapi_internal_info || !new_policy) {
        return MAPI_LIB_INVALID_ARG;
    }

    if(new_policy->filtering_policy) {
            MAPI_LOG_DEBUG("Updating the filtering policy");
            // Replace the existing filtering policy with the new one
            memcpy(&(adv_config->filtering_policy), new_policy->filtering_policy, sizeof(MAPI_USER_FILTERING_POLICY));
    }

    if(new_policy->traffic_shaping_policy) {
            MAPI_LOG_DEBUG("Updating the traffic shaping policy");
        // Replace the existing traffic shaping policy with the new one
        memcpy(&(adv_config->traffic_shaping_policy), new_policy->traffic_shaping_policy, sizeof(MAPI_USER_TRAFFIC_SHAPING_POLICY));
    }

    if(new_policy->security_policy) {
            MAPI_LOG_DEBUG("Updating the security policy");
        // Replace the existing security policy with the new one
        memcpy(&(adv_config->security_policy), new_policy->security_policy, sizeof(MAPI_USER_SECURITY_POLICY));
    }
    if(new_policy->monitoring_policy) {
            MAPI_LOG_DEBUG("Updating the monitoring policy");
        // Replace the existing monitoring policy with the new one
        memcpy(&(adv_config->monitoring_policy), new_policy->monitoring_policy, sizeof(MAPI_USER_MONITORING_POLICY));
    }

    return MAPI_LIB_SUCCESS;
}

/*******************************************************************************/
/*                      Private functions                                       */
/*******************************************************************************/
MAPI_USER_ADVANCED_CONFIG *__mapi_create_adv_config(mapiID mid, MAPI_USER_ADVANCED_CONFIG *user_config) {
    if(user_config == NULL) { // Advanced config is disabled
        return NULL;
    }

    MAPI_USER_ADVANCED_CONFIG *mapi_adv_config = (MAPI_USER_ADVANCED_CONFIG *)malloc(sizeof(MAPI_USER_ADVANCED_CONFIG));
    if(mapi_adv_config == NULL) {
        MAPI_LOG_ERROR("Failed to create advanced config for MAPI ID = %d", mid);
        return MAPI_INVALID_ID;
    }
    memset(mapi_adv_config, 0, sizeof(MAPI_USER_ADVANCED_CONFIG));

    __mapi_sanitize_adv_config(mapi_adv_config, user_config);    
    return mapi_adv_config;
}

// Get the advanced config for a given MAPI ID
// This will be the final config decided by the MAPI library
MAPI_USER_ADVANCED_CONFIG *__mapi_get_adv_config(mapiID mid) {
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];
    if(mapi_internal_info == NULL) {
        MAPI_LOG_ERROR("Invalid MAPI ID passed");
        return NULL;
    }
    return (MAPI_USER_ADVANCED_CONFIG *)mapi_internal_info->adv_config;
}

void __mapi_delete_adv_config(mapiID mid) {
    MAPI_INTERNAL_INFO *mapi_internal_info = mapi_internal_info_map[MAPI_GET_MID(mid)];
    MAPI_USER_ADVANCED_CONFIG *adv_config = (MAPI_USER_ADVANCED_CONFIG *)mapi_internal_info->adv_config;
    if(mapi_internal_info == NULL) {
        MAPI_LOG_ERROR("Invalid MAPI ID passed");
        return;
    }
    if(adv_config != NULL) {
        free(adv_config);
        mapi_internal_info->adv_config = NULL;
    }
    return;
}

void __mapi_sanitize_adv_config(MAPI_USER_ADVANCED_CONFIG *mapi_adv_config, MAPI_USER_ADVANCED_CONFIG *user_config) {
    // TODO : Do some sanity checks on the user_config and decide what will be the final config
    // For now, just copy the user_config to mapi_adv_config
    // It means that the user config might be different from the final config decided by the MAPI library
#if 0
    __mapi_validate_filtering_policy()
    __mapi_validate_traffic_shaping_policy()
    __mapi_validate_security_policy()
    __mapi_validate_monitoring_policy()
#endif

    memcpy(mapi_adv_config, user_config, sizeof(MAPI_USER_ADVANCED_CONFIG));
}