/*******************************************************************************
    Description : Data structures heade file
                  Futute Request : TODO See if this file can be made as a 
                  wrapper for C++ STL. SO no need to change any other module,
                  if the interfaces are well defined

    TODO: USe BSD libraries and WRAP Utils library around it

    http://bxr.su/OpenBSD/sys/dev/pci/drm/include/linux/
                  
*******************************************************************************/

#ifndef INCLUDE_UTILS_DATASTRUCTURES_HASH_H__
#define INCLUDE_UTILS_DATASTRUCTURES_HASH_H__

#include "data_structures_cmn.h"

typedef enum {
    UTILS_DS_HASH_KEY_STRING,
    UTILS_DS_HASH_KEY_INTEGER,
} UTILS_DS_HASH_KEY_TYPE;

typedef struct {
    UTILS_DS_HASH_KEY_TYPE type;
    boolean isProtected; // Library will take care of synchronization
} UTILS_HASH;

/*******************************************************************************/
/*                  Internal Data structures                                   */
/*******************************************************************************/

typedef struct {
    UTILS_DS_HASH_KEY_TYPE type;
    uint32_t currsize;
    void **data;
    __UTILS_DS_LOCK lock;
    void *__container; // This can be any third party library or even C++ STL
} __UTILS_HASH_META;


#endif /* INCLUDE_UTILS_DATASTRUCTURES_HASH_H__ */
