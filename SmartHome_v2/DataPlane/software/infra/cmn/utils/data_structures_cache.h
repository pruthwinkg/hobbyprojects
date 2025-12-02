/*******************************************************************************
    Description : Data structures heade file
                  Futute Request : TODO See if this file can be made as a 
                  wrapper for C++ STL. SO no need to change any other module,
                  if the interfaces are well defined

    TODO: USe BSD libraries and WRAP Utils library around it

    http://bxr.su/OpenBSD/sys/dev/pci/drm/include/linux/
                  
*******************************************************************************/

#ifndef INCLUDE_UTILS_DATASTRUCTURES_CACHE_H__
#define INCLUDE_UTILS_DATASTRUCTURES_CACHE_H__

#include "data_structures_cmn.h"

// Various cache status flags
#define UTILS_DS_CACHE_FLAG_STALE       (1 >> 0) 

typedef enum {
    UTILS_DS_CACHE_LRU_ARRAY_DATA, // Pure data based
    UTILS_DS_CACHE_LRU_ARRAY_KEY, // Key based, but using simple array
    UTILS_DS_CACHE_LRU_HASH, // Hash table based
} UTILS_DS_CACHE_TYPE;

typedef struct {
    UTILS_DS_CACHE_TYPE type;
    uint8_t cacheSetNum; // Number of set-associativity.
    uint16_t cacheSize;
    boolean isProtected; // Library will take care of synchronization
} UTILS_CACHE;

/*******************************************************************************/
/*                  Internal Data structures                                   */
/*******************************************************************************/

#define UTILS_CACHE_SET_TASK_DONE       (1 >> 0) // Indicate any operation completion
#define UTILS_CACHE_SET_TASK_FAILED     (1 >> 1)
#define UTILS_CACHE_SET_SEARCH_DONE     (1 >> 2)

typedef enum {
    UTILS_CACHE_SET_TASK_SIMPLE_SEARCH,
    UTILS_CACHE_SET_TASK_INVALID
} UTILS_CACHE_SET_TASK;

typedef struct {
    uint16_t start;
    uint16_t end;
} UTILS_CACHE_SET_TASKLET;

typedef struct {
    uint8_t __cacheSetNum;
    pthread_t *__cacheThread;
    pthread_cond_t  __cacheCV;
    pthread_mutex_t __cacheMutex;
    boolean __cacheSetStop;
    boolean __cacheSetTaskStart;
    UTILS_CACHE_SET_TASK __cacheSetTask;
    void *__cacheSetTaskInput; // Input needed to perform the task
    UTILS_CACHE_SET_TASKLET *__cacheSetTasklet; // Array of tasklet
    pthread_mutex_t __cacheSetTaskMutex;
    uint8_t __cacheSetFlags;
} __UTILS_CACHE_SET_DATA;

typedef struct {
    UTILS_DS_CACHE_TYPE type;
    uint16_t cacheSize;
    uint16_t flags;
    void **data;
    int *references;
    __UTILS_CACHE_SET_DATA *cacheSet;
    __UTILS_DS_LOCK lock;
    void *__container; // This can be any third party library or even C++ STL
} __UTILS_CACHE_META;


#endif /* INCLUDE_UTILS_DATASTRUCTURES_CACHE_H__ */
