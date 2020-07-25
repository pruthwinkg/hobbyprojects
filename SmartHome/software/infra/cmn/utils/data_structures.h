/*******************************************************************************
    Description : Data structures heade file
                  Futute Request : TODO See if this file can be made as a 
                  wrapper for C++ STL. SO no need to change any other module,
                  if the interfaces are well defined
*******************************************************************************/

#ifndef INCLUDE_UTILS_DATASTRUCTURES_H__
#define INCLUDE_UTILS_DATASTRUCTURES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "smarthome_essentials.h"
#include "logging.h"

#define UTILS_LOG_ERROR  LOG_ERROR
#define UTILS_LOG_TRACE  LOG_TRACE
#define UTILS_LOG_DEBUG  LOG_DEBUG
#define UTILS_NOT_YET_IMPLEMENTED   printf("Not yet implemented\n")

#define UTILS_DS_MAX_ID             (100) // Max IDs support (soft limit)

// Type (8 bit), sub-type (4 bit), ID (20 bit)
typedef uint32_t UTILS_DS_ID;

#define UTILS_DS_TYPE_SHIFT          (24)
#define UTILS_DS_SUB_TYPE_SHIFT      (20)
#define UTILS_DS_ID_SHIFT            (0)

#define UTILS_DS_TYPE_MASK          (0x00FF << UTILS_DS_TYPE_SHIFT)
#define UTILS_DS_SUB_TYPE_MASK      (0x0F << UTILS_DS_SUB_TYPE_SHIFT)
#define UTILS_DS_ID_MASK            (0x0FFFFF << UTILS_DS_ID_SHIFT)

#define UTILS_DS_GET_TYPE(id)       ((id & UTILS_DS_TYPE_MASK) >> UTILS_DS_TYPE_SHIFT)
#define UTILS_DS_GET_SUBTYPE(id)    ((id & UTILS_DS_SUB_TYPE_MASK) >> UTILS_DS_SUB_TYPE_SHIFT)
#define UTILS_DS_GET_ID(id)         ((id & UTILS_DS_ID_MASK) >> UTILS_DS_ID_SHIFT)

#define UTILS_DS_LOCK_CREATE(qmeta)  do {\
                                        qmeta->lock.isProtected = TRUE;\
                                        pthread_mutex_init(&(qmeta->lock.__lock), NULL);\
                                     } while(0)

#define UTILS_DS_CHECK_LOCK(qmeta)  do {\
                                        if(qmeta->lock.isProtected) {\
                                            pthread_mutex_lock(&(qmeta->lock.__lock));\
                                        }\
                                    } while(0)                                        

#define UTILS_DS_CHECK_UNLOCK(qmeta)  do {\
                                            if(qmeta->lock.isProtected) {\
                                                pthread_mutex_unlock(&(qmeta->lock.__lock));\
                                            }\
                                        } while(0)                                        
#define UTILS_DS_LOCK_DESTROY(qmeta)  do {\
                                            if(qmeta->lock.isProtected) {\
                                                pthread_mutex_destroy(&qmeta->lock.__lock);\
                                            }\
                                        } while(0)
typedef enum {
    UTILS_DS_QUEUE = 0x1,
    UTILS_DS_LIST = 0x2,
    UTILS_DS_STACK = 0x3,
} UTILS_DS_TYPE;

/*
    STATIC : These are very special purpose queues. Once they are
        filled, it cannot be reused even if dequeued.

    DYNAMIC : These queues are similar in behaviour to STATIC. But
        they can keep growing

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
    boolean isProtected;
    pthread_mutex_t __lock;
} __UTILS_QUEUE_LOCK;

typedef struct {
    uint32_t front;
    uint32_t rear;
    uint32_t currsize;
    uint32_t capacity;
    void **data;
    __UTILS_QUEUE_LOCK lock;
} __UTILS_QUEUE_META;


/*******************************************************************************/
/*              Public Functions                                               */
/* Note : ALL the datastructures directly maintained by this library will be   */
/*        identified by a unique ID. Pass the same ID for all subsequent       */
/*        operation after its creation.                                        */
/*******************************************************************************/
// Common Functions
void utils_ds_init();

// Queue Functions
UTILS_DS_ID utils_ds_queue_create(UTILS_QUEUE *queue);
int utils_ds_queue_enqueue(UTILS_DS_ID id, void *data);
void* utils_ds_queue_dequeue(UTILS_DS_ID id);
int utils_ds_queue_destroy(UTILS_DS_ID id, boolean delete_data); // Deletes FULL queue
boolean utils_ds_queue_is_full(UTILS_DS_ID id);
boolean utils_ds_queue_is_empty(UTILS_DS_ID id);
uint32_t utils_ds_queue_get_count(UTILS_DS_ID id);
// Linked List functions


// Stack functions



#endif /* INCLUDE_UTILS_DATASTRUCTURES_H__ */
