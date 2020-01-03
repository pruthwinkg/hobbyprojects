/*****************************************************************************
    Description : The purpose of this file is to define various common
                datastructures qhich might be required by various modules.

                All these data strcutures will be very genereic. i.e they will
                agnostic of what kind of data they hold
*****************************************************************************/

#include "data_structures.h"

UTILS_DS_ID utils_ds_bitmap[UTILS_DS_MAX_ID];
void *utils_ds_metadata[UTILS_DS_MAX_ID];

boolean utils_ds_initialized = FALSE;

/****************************************************************************/
/*                      Internal functions declaration                      */
/****************************************************************************/
static UTILS_DS_ID __utils_get_free_id(UTILS_DS_TYPE type, int subtype);
static void __utils_delete_id(UTILS_DS_ID id);
static int __utils_ds_queue_create_static(UTILS_DS_ID id, UTILS_QUEUE *queue);
static int __utils_ds_queue_enqueue_static(UTILS_DS_ID id, void *data);
static void* __utils_ds_queue_dequeue_static(UTILS_DS_ID id);
static void __utils_ds_queue_destroy_static(UTILS_DS_ID id, boolean delete_data);
static int __utils_ds_queue_create_circular(UTILS_DS_ID id, UTILS_QUEUE *queue);
static int __utils_ds_queue_enqueue_circular(UTILS_DS_ID id, void *data);
static void* __utils_ds_queue_dequeue_circular(UTILS_DS_ID id);
static void __utils_ds_queue_destroy_circular(UTILS_DS_ID id, boolean delete_data);
static boolean __utils_ds_queue_isfull(UTILS_DS_ID id);
static boolean __utils_ds_queue_isempty(UTILS_DS_ID id);





void utils_ds_init() {
    // 0 will be treated as a unused ID
    memset(utils_ds_bitmap, 0, sizeof(utils_ds_bitmap));

    // Create an array of pointers to hold the metadata of the ds.
    // Even this array will be generic (void *). Its upto the DS
    // to typecast and malloc properly
    memset(utils_ds_metadata, 0, sizeof(utils_ds_metadata));

    utils_ds_initialized = TRUE;    
}


UTILS_DS_ID utils_ds_queue_create(UTILS_QUEUE *queue) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    UTILS_DS_ID id = __utils_get_free_id(UTILS_DS_QUEUE, queue->type);
    switch(queue->type) {
        case UTILS_QUEUE_STATIC:
            if(__utils_ds_queue_create_static(id, queue) < 0) {
                goto err;
            }
            break;
        case UTILS_QUEUE_DYNAMIC:
            UTILS_NOT_YET_IMPLEMENTED;
            return 0;
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
    __utils_delete_id(id);
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
            UTILS_NOT_YET_IMPLEMENTED;
            return -1;
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
            UTILS_NOT_YET_IMPLEMENTED;
            return NULL;       
        case UTILS_QUEUE_CIRCULAR:
            return __utils_ds_queue_dequeue_circular(id);
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
            UTILS_NOT_YET_IMPLEMENTED;
            return 0;
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
    __utils_delete_id(id);
   return temp;
}

/*****************************************************************************
                    Internal Functions
*****************************************************************************/
static UTILS_DS_ID __utils_get_free_id(UTILS_DS_TYPE type, int subtype) {
    for (UTILS_DS_ID i = 0; i < UTILS_DS_MAX_ID; i++) {
        if (utils_ds_bitmap[i] == 0) {
            utils_ds_bitmap[i] = (((type << UTILS_DS_TYPE_SHIFT) & UTILS_DS_TYPE_MASK) |
                   ((subtype << UTILS_DS_SUB_TYPE_SHIFT) & UTILS_DS_SUB_TYPE_MASK) |
                   (i & UTILS_DS_ID_MASK));
            return utils_ds_bitmap[i];                   
        }
    }
    return 0;
}

static void __utils_delete_id(UTILS_DS_ID id) {
    if (id == 0) {
        return;        
    }
    utils_ds_bitmap[UTILS_DS_GET_ID(id)] = 0;
}


/*****************************************************************************/
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

    // Create an array of void poiners for data storage
    qmeta->data = malloc(sizeof(void *) * queue->size);

    // Save the meta pointer to global array
    utils_ds_metadata[UTILS_DS_GET_ID(id)] = (void *)qmeta;

    return 0;
}

static int __utils_ds_queue_enqueue_static(UTILS_DS_ID id, void *data) {
    __UTILS_QUEUE_META *qmeta = utils_ds_metadata[UTILS_DS_GET_ID(id)];

    if(__utils_ds_queue_isfull(id)) return -1;

    // Data will enqueued at 'rear' pointer
    qmeta->data[qmeta->rear] = data;
    qmeta->rear += 1;
    qmeta->currsize += 1;
}

static void* __utils_ds_queue_dequeue_static(UTILS_DS_ID id) {
    __UTILS_QUEUE_META *qmeta = utils_ds_metadata[UTILS_DS_GET_ID(id)];

    if(__utils_ds_queue_isempty(id)) return NULL;

    // Note : cursize is NOT incremented intentionally in this type of queue.
    if (qmeta->front >= qmeta->rear) return NULL;

    // Data will dequeued at 'front' pointer
    void *data = qmeta->data[qmeta->front];
    qmeta->front += 1;

    return data;
}

static void __utils_ds_queue_destroy_static(UTILS_DS_ID id, boolean delete_data) {
    __UTILS_QUEUE_META *qmeta = utils_ds_metadata[UTILS_DS_GET_ID(id)];

    // First try to delete the data in this queue
    if (delete_data == TRUE) {
        for (uint32_t i = 0; i < qmeta->capacity; i++) {
            if(qmeta->data[i] != NULL) {
                free(qmeta->data[i]);
            }
        }
    }

    // Start deleting meta for this id
    utils_ds_metadata[UTILS_DS_GET_ID(id)] = NULL;
    free(qmeta->data);
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

    // Create an array of void poiners for data storage
    qmeta->data = malloc(sizeof(void *) * queue->size);

    // Save the meta pointer to global array
    utils_ds_metadata[UTILS_DS_GET_ID(id)] = (void *)qmeta;

    return 0;
}

static int __utils_ds_queue_enqueue_circular(UTILS_DS_ID id, void *data) {
    __UTILS_QUEUE_META *qmeta = utils_ds_metadata[UTILS_DS_GET_ID(id)];

    if(__utils_ds_queue_isfull(id)) return -1;

    // Data will enqueued at 'rear' pointer
    qmeta->rear = (qmeta->rear + 1)%qmeta->capacity;
    qmeta->data[qmeta->rear] = data;
    qmeta->currsize += 1;
}

static void* __utils_ds_queue_dequeue_circular(UTILS_DS_ID id) {
    __UTILS_QUEUE_META *qmeta = utils_ds_metadata[UTILS_DS_GET_ID(id)];

    if(__utils_ds_queue_isempty(id)) return NULL;

    // Data will dequeued at 'front' pointer
    void *data = qmeta->data[qmeta->front];    
    qmeta->front = (qmeta->front + 1)%qmeta->capacity;
    qmeta->currsize -= 1;

    return data;
}

static void __utils_ds_queue_destroy_circular(UTILS_DS_ID id, boolean delete_data) {
    __UTILS_QUEUE_META *qmeta = utils_ds_metadata[UTILS_DS_GET_ID(id)];

    // First try to delete the data in this queue
    if (delete_data == TRUE) {
        for (uint32_t i = 0; i < qmeta->capacity; i++) {
            if(qmeta->data[i] != NULL) {
                free(qmeta->data[i]);
            }
        }
    }

    // Start deleting meta for this id
    utils_ds_metadata[UTILS_DS_GET_ID(id)] = NULL;
    free(qmeta->data);
    free(qmeta);
}

/*****************************************************************************/

static boolean __utils_ds_queue_isfull(UTILS_DS_ID id) {
    __UTILS_QUEUE_META *qmeta = utils_ds_metadata[UTILS_DS_GET_ID(id)];

    if(qmeta->currsize == qmeta->capacity) { return TRUE; }
    return FALSE;
}

static boolean __utils_ds_queue_isempty(UTILS_DS_ID id) {
    __UTILS_QUEUE_META *qmeta = utils_ds_metadata[UTILS_DS_GET_ID(id)];

    if(qmeta->currsize == 0) { return TRUE; }
    return FALSE;
}
