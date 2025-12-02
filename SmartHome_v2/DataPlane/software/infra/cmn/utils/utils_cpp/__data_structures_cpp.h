/*******************************************************************************
    Description: This file is used as a wrapper around the C++ functions.


*******************************************************************************/
#ifndef INCLUDE_DATASTRUCTURES_CPP_H__
#define INCLUDE_DATASTRUCTURES_CPP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// Hash
typedef enum {
    UTILS_DS_CPP_HASH_KEY_STRING = 0,
    UTILS_DS_CPP_HASH_KEY_INTEGER = 1
} UTILS_DS_CPP_HASH_KEY_TYPE;

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DATASTRUCTURES_CPP_H__ */
