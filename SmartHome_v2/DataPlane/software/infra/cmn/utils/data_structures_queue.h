/*******************************************************************************
    Description : Data structures heade file
                  Futute Request : TODO See if this file can be made as a 
                  wrapper for C++ STL. SO no need to change any other module,
                  if the interfaces are well defined

    TODO: USe BSD libraries and WRAP Utils library around it

    http://bxr.su/OpenBSD/sys/dev/pci/drm/include/linux/
                  
*******************************************************************************/

#ifndef INCLUDE_UTILS_DATASTRUCTURES_QUEUE_H__
#define INCLUDE_UTILS_DATASTRUCTURES_QUEUE_H__

#include "data_structures_cmn.h"

#define UTILS_QUEUE_DYNAMIC_MAX_SIZE        0xFFFFFFFF // (4 billion)

/*
    STATIC : These are very special purpose queues. Once they are
        filled, it can be reused only even if it is fully dequeued.

    DYNAMIC : These queues are dynamically growing normal behaviour queues

    CIRCULAR : Most widely used queues. Fixed sized queues. 
        But the usage is controlled by enqueues and dequeues
*/
typedef enum {
    UTILS_QUEUE_STATIC, // Queue of Static Length (using array)
    UTILS_QUEUE_DYNAMIC, // Queue of Dynamic Length (using list)
    UTILS_QUEUE_CIRCULAR, // Circular queue (fixed length)
} UTILS_QUEUE_TYPE;

typedef struct {
    UTILS_QUEUE_TYPE type;
    uint32_t size;
    boolean isPriority; // Priority queues (All the above types are supported)
    uint8_t numPriorities; // Number of priorities. Applicable only if isPriority == 1
    boolean isProtected; // Library will take care of synchronization
} UTILS_QUEUE;

/*******************************************************************************/
/*                  Internal Data structures                                   */
/*******************************************************************************/

typedef struct {
    uint32_t front;
    uint32_t rear;
    uint32_t currsize;
    uint32_t capacity;
    void **data;
    __UTILS_DS_LOCK lock;
    void *__container; // This can be any third party library or even C++ STL
} __UTILS_QUEUE_META;


#endif /* INCLUDE_UTILS_DATASTRUCTURES_QUEUE_H__ */
