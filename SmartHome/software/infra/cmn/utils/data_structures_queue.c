/*****************************************************************************
    Description : The purpose of this file is to define various common
                datastructures qhich might be required by various modules.

                All these data strcutures will be very genereic. i.e they will
                agnostic of what kind of data they hold
*****************************************************************************/

#include "./utils_cpp/utils_cpp.h"
#include "data_structures_queue.h"

/****************************************************************************/
/*                      Internal functions declaration                      */
/****************************************************************************/
static int __utils_ds_queue_create_static(UTILS_DS_ID id, UTILS_QUEUE *queue);
static int __utils_ds_queue_enqueue_static(UTILS_DS_ID id, void *data);
static void* __utils_ds_queue_dequeue_static(UTILS_DS_ID id);
static void* __utils_ds_queue_lookup_at_pos_static(UTILS_DS_ID id, uint32_t pos);
static void __utils_ds_queue_destroy_static(UTILS_DS_ID id, boolean delete_data);
static int __utils_ds_queue_create_dynamic(UTILS_DS_ID id, UTILS_QUEUE *queue);
static int __utils_ds_queue_enqueue_dynamic(UTILS_DS_ID id, void *data);
static void* __utils_ds_queue_dequeue_dynamic(UTILS_DS_ID id);
static void* __utils_ds_queue_lookup_at_pos_dynamic(UTILS_DS_ID id, uint32_t pos);
static void __utils_ds_queue_destroy_dynamic(UTILS_DS_ID id, boolean delete_data);
static int __utils_ds_queue_create_circular(UTILS_DS_ID id, UTILS_QUEUE *queue);
static int __utils_ds_queue_enqueue_circular(UTILS_DS_ID id, void *data);
static void* __utils_ds_queue_dequeue_circular(UTILS_DS_ID id);
static void __utils_ds_queue_destroy_circular(UTILS_DS_ID id, boolean delete_data);
static boolean __utils_ds_queue_isfull(UTILS_DS_ID id);
static boolean __utils_ds_queue_isempty(UTILS_DS_ID id);
static uint32_t __utils_ds_queue_get_currsize(UTILS_DS_ID id);

/****************************************************************************/
/*                      Queue Public functions                              */
/****************************************************************************/
UTILS_DS_ID utils_ds_queue_create(UTILS_QUEUE *queue) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    UTILS_DS_ID id = utils_ds_get_id(UTILS_DS_QUEUE, queue->type);
    switch(queue->type) {
        case UTILS_QUEUE_STATIC:
            if(__utils_ds_queue_create_static(id, queue) < 0) {
                goto err;
            }
            break;
        case UTILS_QUEUE_DYNAMIC:
            if(__utils_ds_queue_create_dynamic(id, queue) < 0) {
                goto err;
            }
            break;
        case UTILS_QUEUE_CIRCULAR:
            if(__utils_ds_queue_create_circular(id, queue) < 0) {
                goto err;
            }           
            break;
        default:
            UTILS_LOG_ERROR("Invalid queue type\n");
            goto err;
    }
    return id;

err: 
   utils_ds_delete_id(id);
   return 0;
}

int utils_ds_queue_enqueue(UTILS_DS_ID id, void *data) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_QUEUE_STATIC:
            if(__utils_ds_queue_enqueue_static(id, data) < 0) {
                return -1;
            }           
            break;
         case UTILS_QUEUE_DYNAMIC:
            if(__utils_ds_queue_enqueue_dynamic(id, data) < 0) {
                return -1;
            }       
            break;          
        case UTILS_QUEUE_CIRCULAR:
            if(__utils_ds_queue_enqueue_circular(id, data) < 0) {
                return -1;
            }           
            break;
        default:
            UTILS_LOG_ERROR("Invalid queue type\n");
            return -1;           
    }
    return 0;
}

void* utils_ds_queue_dequeue(UTILS_DS_ID id) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return NULL;

    void *data = NULL;
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_QUEUE_STATIC:
            return __utils_ds_queue_dequeue_static(id);
        case UTILS_QUEUE_DYNAMIC:
            return __utils_ds_queue_dequeue_dynamic(id);
        case UTILS_QUEUE_CIRCULAR:
            return __utils_ds_queue_dequeue_circular(id);
        default:
            UTILS_LOG_ERROR("Invalid queue type\n");                      
    }
    return NULL;
}

void* utils_ds_queue_lookup_at_pos(UTILS_DS_ID id, uint32_t pos) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return NULL;

    void *data = NULL;
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_QUEUE_STATIC:
            return __utils_ds_queue_lookup_at_pos_static(id, pos);
        case UTILS_QUEUE_DYNAMIC:
            return __utils_ds_queue_lookup_at_pos_dynamic(id, pos);
        case UTILS_QUEUE_CIRCULAR: // Doesnt support this currently
            return NULL;
        default:
            UTILS_LOG_ERROR("Invalid queue type\n");                      
    }
    return NULL;
}

/*
    Note : This function does a FULL cleanup if delete_data is set. It 
        will try to delete even the data associated with the queue

    Success : Return the same id which was deleted
    Failure : 0 or -ve            
*/
int utils_ds_queue_destroy(UTILS_DS_ID id, boolean delete_data) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    
    int temp = id;

    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_QUEUE_STATIC:
            __utils_ds_queue_destroy_static(id, delete_data);
            goto del_id;            
            break;
        case UTILS_QUEUE_DYNAMIC:
            __utils_ds_queue_destroy_dynamic(id, delete_data);
            goto del_id;            
            break;
        case UTILS_QUEUE_CIRCULAR:
            __utils_ds_queue_destroy_circular(id, delete_data);
            goto del_id;                
            break;
        default:
            UTILS_LOG_ERROR("Invalid queue type\n");
            return -1;
    }

del_id:
    utils_ds_delete_id(id);
   return temp;
}

boolean utils_ds_queue_is_full(UTILS_DS_ID id) {
    return __utils_ds_queue_isfull(id);
}

boolean utils_ds_queue_is_empty(UTILS_DS_ID id) {
    return __utils_ds_queue_isempty(id);
}

uint32_t utils_ds_queue_get_count(UTILS_DS_ID id) {
    return __utils_ds_queue_get_currsize(id);
}

/*****************************************************************************
                    Internal Functions
*****************************************************************************/
static int __utils_ds_queue_create_static(UTILS_DS_ID id, UTILS_QUEUE *queue) {
    if (queue->isPriority) {
        UTILS_NOT_YET_IMPLEMENTED;
        return -1;
    }
    
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META *)malloc(sizeof(__UTILS_QUEUE_META));
    qmeta->front = 0;
    qmeta->currsize = 0;
    qmeta->rear = 0;
    qmeta->capacity = queue->size;
    qmeta->lock.isProtected = FALSE;

    if(queue->isProtected == TRUE) {
        UTILS_DS_LOCK_CREATE(qmeta);
    }

    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        qmeta->__container =  utils_ds_cpp_queue_create_container(0);
        qmeta->data = NULL;
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        // Create an array of void poiners for data storage
        qmeta->data = malloc(sizeof(void *) * queue->size);
        qmeta->__container = NULL;
    }

    // Save the meta pointer to global array
    utils_ds_set_meta(id, (void *)qmeta);

    return 0;
}

static int __utils_ds_queue_enqueue_static(UTILS_DS_ID id, void *data) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    if(__utils_ds_queue_isfull(id)) return -1;

    // Data will enqueued at 'rear' pointer
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        utils_ds_cpp_queue_enqueue_container(qmeta->__container, data, FALSE);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        qmeta->data[qmeta->rear] = data;
    }

    qmeta->rear += 1;
    qmeta->currsize += 1;

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return 0;
}

static void* __utils_ds_queue_dequeue_static(UTILS_DS_ID id) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    // Once the queue is empty, reset the queue for re-use
    if(qmeta->front == qmeta->capacity) {
        qmeta->currsize = 0;
        qmeta->front = 0;
        qmeta->rear = 0;
        return NULL;
    }

    // Note : cursize is NOT decremented intentionally in this type of queue.
    if (qmeta->front >= qmeta->rear) return NULL;

    void *data = NULL;
    // Dequeue always from front
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        data = utils_ds_cpp_queue_dequeue_container(qmeta->__container, TRUE);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        data = qmeta->data[qmeta->front];
    }

    qmeta->front += 1;

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return data;
}

static void* __utils_ds_queue_lookup_at_pos_static(UTILS_DS_ID id, uint32_t pos) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    if(__utils_ds_queue_isempty(id)) return NULL;
    if(pos >= qmeta->capacity) return NULL;

    void *data = NULL;

    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        data = utils_ds_cpp_queue_lookup_at_pos_container(qmeta->__container, pos);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        data = qmeta->data[pos];
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return data;
}

static void __utils_ds_queue_destroy_static(UTILS_DS_ID id, boolean delete_data) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_LOCK_DESTROY(qmeta);

    // First try to delete the data in this queue
    if (delete_data == TRUE) {
        if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
            for (uint32_t i = qmeta->front; i < qmeta->rear; i++) { // Need to pass a valid pos for container
                void *data = utils_ds_cpp_queue_lookup_at_pos_container(qmeta->__container, i);
                if(data != NULL) {
                    free(data);
                }
            }
        } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
            for (uint32_t i = 0; i < qmeta->capacity; i++) {
                if(qmeta->data[i] != NULL) {
                    free(qmeta->data[i]);
                }
            }
        }
    }

    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        utils_ds_cpp_queue_destroy_container(qmeta->__container);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        free(qmeta->data);       
    }

    // Start deleting meta for this id
    utils_ds_set_meta(id, NULL);
    memset(qmeta, 0, sizeof(__UTILS_QUEUE_META));
    free(qmeta);
}
/*****************************************************************************/
static int __utils_ds_queue_create_dynamic(UTILS_DS_ID id, UTILS_QUEUE *queue) {
    if (queue->isPriority) {
        UTILS_NOT_YET_IMPLEMENTED;
        return -1;
    }
    
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META *)malloc(sizeof(__UTILS_QUEUE_META));
    qmeta->front = 0;
    qmeta->currsize = 0;
    qmeta->rear = 0;
    qmeta->capacity = UTILS_QUEUE_DYNAMIC_MAX_SIZE;
    qmeta->lock.isProtected = FALSE;

    if(queue->isProtected == TRUE) {
        UTILS_DS_LOCK_CREATE(qmeta);
    }

    if((utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
        qmeta->__container =  utils_ds_cpp_queue_create_container(0);
        qmeta->data = NULL;
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) { // Not supported in this mode
        UTILS_NOT_SUPPORTED;
        return -1;
    }

    // Save the meta pointer to global array
    utils_ds_set_meta(id, (void *)qmeta);

    return 0;
}

static int __utils_ds_queue_enqueue_dynamic(UTILS_DS_ID id, void *data) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    if(__utils_ds_queue_isfull(id)) return -1;

    // Data will enqueued at 'rear' pointer
    if((utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
        utils_ds_cpp_queue_enqueue_container(qmeta->__container, data, FALSE);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;
        return -1;
    }

    qmeta->currsize += 1;

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return 0;
}

static void* __utils_ds_queue_dequeue_dynamic(UTILS_DS_ID id) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    if(__utils_ds_queue_isempty(id)) return NULL;

    void *data = NULL;
    // Dequeue always from front
    if((utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
        data = utils_ds_cpp_queue_dequeue_container(qmeta->__container, TRUE);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;
        return NULL;
    }

    qmeta->currsize -= 1;

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return data;
}

static void* __utils_ds_queue_lookup_at_pos_dynamic(UTILS_DS_ID id, uint32_t pos) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    if(__utils_ds_queue_isempty(id)) return NULL;
    if(pos >= qmeta->capacity) return NULL;

    void *data = NULL;

    if((utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
        data = utils_ds_cpp_queue_lookup_at_pos_container(qmeta->__container, pos);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;
        return NULL;
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return data;
}

static void __utils_ds_queue_destroy_dynamic(UTILS_DS_ID id, boolean delete_data) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_LOCK_DESTROY(qmeta);

    // First try to delete the data in this queue
    if (delete_data == TRUE) {
        if((utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
            for (uint32_t i = qmeta->front; i < qmeta->rear; i++) { // Need to pass a valid pos for container
                void *data = utils_ds_cpp_queue_lookup_at_pos_container(qmeta->__container, i);
                if(data != NULL) {
                    free(data);
                }
            }
        } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
            UTILS_NOT_SUPPORTED;
            return;
        }
    }

    if((utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
        utils_ds_cpp_queue_destroy_container(qmeta->__container);
    }

    // Start deleting meta for this id
    utils_ds_set_meta(id, NULL);
    memset(qmeta, 0, sizeof(__UTILS_QUEUE_META));
    free(qmeta);
}
/*****************************************************************************/

static int __utils_ds_queue_create_circular(UTILS_DS_ID id, UTILS_QUEUE *queue) {
    if (queue->isPriority) {
        UTILS_NOT_YET_IMPLEMENTED;
        return -1;
    }
    
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META *)malloc(sizeof(__UTILS_QUEUE_META));
    qmeta->front = 0;
    qmeta->currsize = 0;
    qmeta->rear = queue->size - 1;
    qmeta->capacity = queue->size;
    qmeta->lock.isProtected = FALSE;

    if(queue->isProtected == TRUE) {
        UTILS_DS_LOCK_CREATE(qmeta);
    }

    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        qmeta->__container = utils_ds_cpp_queue_create_container(queue->size);
        qmeta->data = NULL;
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        // Create an array of void poiners for data storage
        qmeta->data = malloc(sizeof(void *) * queue->size);
        qmeta->__container = NULL;
    }

    // Save the meta pointer to global array
    utils_ds_set_meta(id, (void *)qmeta);

    return 0;
}

static int __utils_ds_queue_enqueue_circular(UTILS_DS_ID id, void *data) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    if(__utils_ds_queue_isfull(id)) return -1;

    // Data will enqueued at 'rear' pointer
    qmeta->rear = (qmeta->rear + 1)%qmeta->capacity;

    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        utils_ds_cpp_queue_insert_at_pos_container(qmeta->__container, qmeta->rear, data);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        qmeta->data[qmeta->rear] = data;    
    }

    qmeta->currsize += 1;

    UTILS_DS_CHECK_UNLOCK(qmeta);    

    return 0;
}

static void* __utils_ds_queue_dequeue_circular(UTILS_DS_ID id) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);    

    if(__utils_ds_queue_isempty(id)) return NULL;

    void *data = NULL;
    // Data will dequeued at 'front' pointer
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        data = utils_ds_cpp_queue_lookup_at_pos_container(qmeta->__container, qmeta->front);     
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        data = qmeta->data[qmeta->front];
    }

    qmeta->front = (qmeta->front + 1)%qmeta->capacity;
    qmeta->currsize -= 1;

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return data;
}

static void __utils_ds_queue_destroy_circular(UTILS_DS_ID id, boolean delete_data) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    UTILS_DS_LOCK_DESTROY(qmeta);

    // First try to delete the data in this queue
    if (delete_data == TRUE) {
        if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
            for (uint32_t i = 0; i < qmeta->capacity; i++) {
                void *data = utils_ds_cpp_queue_lookup_at_pos_container(qmeta->__container, i);
                if(data != NULL) {
                    free(data);
                }
            }
        } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
            for (uint32_t i = 0; i < qmeta->capacity; i++) {
                if(qmeta->data[i] != NULL) {
                    free(qmeta->data[i]);
                }
            }
        }
    }

    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        utils_ds_cpp_queue_destroy_container(qmeta->__container);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        free(qmeta->data);       
    }

    // Start deleting meta for this id
    utils_ds_set_meta(id, NULL);
    free(qmeta);
}

/*****************************************************************************/

static boolean __utils_ds_queue_isfull(UTILS_DS_ID id) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    if(qmeta->currsize >= qmeta->capacity) { return TRUE; }
    return FALSE;
}

static boolean __utils_ds_queue_isempty(UTILS_DS_ID id) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    if(qmeta->currsize == 0) { return TRUE; }
    return FALSE;
}

static uint32_t __utils_ds_queue_get_currsize(UTILS_DS_ID id) {
    __UTILS_QUEUE_META *qmeta = (__UTILS_QUEUE_META*)utils_ds_get_meta(id);

    return qmeta->currsize;
}

