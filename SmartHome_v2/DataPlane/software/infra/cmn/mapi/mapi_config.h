
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
// mapi_config.h (internal)
#ifndef MAPI_CONFIG_H
#define MAPI_CONFIG_H

#include "mapi_internal.h"

typedef struct {
    int param_idx;
    const char* name;
    size_t size;
    void* value;
    const char* description;
} MAPI_TUNING_PARAM_INFO;

typedef struct {
    MAPI_TUNING_GROUPS group_name;
    MAPI_TUNING_PARAM_INFO *params;
    int num_params;
} MAPI_DEFAULT_TUNING_GROUP;

// Add enums for better clarity and safety
typedef enum {
    MAPI_TUNING_GROUP_GROUP1,
    MAPI_TUNING_GROUP_GROUP2,
    MAPI_TUNING_GROUP_MAX // Always add a max
} MAPI_TUNING_GROUPS;

extern boolean mapi_tuning_params_applied;

// Structure to pass the updated tuning params to mapi_apply_tuning_params
// This will be used in the SET_TUNING_PARAM macro
typedef struct {
    MAPI_TUNING_GROUPS group_name;
    uint8_t param_idx;
    void *value;
} MAPI_UPDATED_TUNING_PARAM;

// Macro to update the tuning param
#define SET_TUNING_PARAM(g, p, v, t) \
    { .group_name = g, .param_idx = p, .value = (t*)(v) }


// Add the default tuning params here

typedef enum {
    MAPI_PORT_SELECTION_ALGORITHM_FIRST_AVAILABLE = 0,
    MAPI_PORT_SELECTION_ALGORITHM_ROUND_ROBIN,
    MAPI_PORT_SELECTION_ALGORITHM_RANDOM,
    MAPI_PORT_SELECTION_ALGORITHM_LRU
} MAPI_PORT_SELECTION_ALGORITHM;


/*******************************************************************************/
/*                      Public functions                                       */
/*******************************************************************************/
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
* @param tuning_params A pointer to a struct containing the fine tuning parameters.
*/
void mapi_apply_tuning_params(MAPI_UPDATED_TUNING_PARAM *tuning_params, int num_params);

/*
* @brief Get the value of a specific tuning parameter.
*
* This function allows users to query the current value of a specific tuning parameter.
*
* @param group_name The tuning group name.
* @param param_idx The index of the parameter within the group.
* @return The value of the tuning parameter.
*/  
void *mapi_get_tuning_param_value(MAPI_TUNING_GROUPS group_name, uint8_t param_idx)

#endif // MAPI_CONFIG_H
