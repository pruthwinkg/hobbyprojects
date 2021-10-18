/*******************************************************************************
    Description : Data structures heade file
                  Futute Request : TODO See if this file can be made as a 
                  wrapper for C++ STL. SO no need to change any other module,
                  if the interfaces are well defined

    TODO: USe BSD libraries and WRAP Utils library around it

    http://bxr.su/OpenBSD/sys/dev/pci/drm/include/linux/
                  
*******************************************************************************/

#ifndef INCLUDE_UTILS_DATASTRUCTURES_LIST_H__
#define INCLUDE_UTILS_DATASTRUCTURES_LIST_H__

#include "data_structures_cmn.h"

typedef enum {
    UTILS_LIST_SINGLE, // Singly linked list
    UTILS_LIST_DOUBLE, // Doubly linked list
    UTILS_LIST_SINGLE_CIRCULAR,
    UTILS_LIST_DOUBLE_CIRCULAR
} UTILS_LIST_TYPE;

typedef struct {
    UTILS_LIST_TYPE type;
    uint32_t max_size; // Applicable only for circular lists
    boolean withCache; // For faster lookup
    uint8_t cacheSize; // Max allowed by default is 10. Could be changed by api to a max of 64
    boolean isProtected; // Library will take care of synchronization
} UTILS_LIST;

/*******************************************************************************/
/*                  Internal Data structures                                   */
/*******************************************************************************/
typedef struct __utils_list_single {
    struct __utils_list_single *next;
    void *data;
} __UTILS_LIST_SINGLE;

typedef struct __utils_list_double {
    struct __utils_list_double *next;
    struct __utils_list_double *prev;
    void *data;
} __UTILS_LIST_DOUBLE;

typedef struct __utils_list_node {    
    union {
        __UTILS_LIST_SINGLE singly;
        __UTILS_LIST_DOUBLE doubly;
    } list_type;
} __UTILS_LIST_NODE;

typedef struct {
    __UTILS_LIST_NODE *entry; // Array
    uint16_t references; // LRU algorithm is used to kick out from cache when full
} __UTILS_LIST_CACHE;

typedef struct {
    __UTILS_LIST_NODE anchor; // Similar to a dummy head, for easy reference, where next points to head and prev to tail
    uint32_t max_size;
    uint32_t curr_size;
    boolean withCache;
    uint8_t cacheSize;
    __UTILS_LIST_CACHE **__cache; // Array
    __UTILS_DS_LOCK lock;
} __UTILS_LIST_META;

#endif /* INCLUDE_UTILS_DATASTRUCTURES_LIST_H__ */
