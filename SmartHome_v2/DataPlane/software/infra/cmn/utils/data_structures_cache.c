/*****************************************************************************
    Description : The purpose of this file is to define various common
                datastructures qhich might be required by various modules.

                All these data strcutures will be very genereic. i.e they will
                agnostic of what kind of data they hold
*****************************************************************************/

#if 0

#include "./utils_cpp/utils_cpp.h"
#include "data_structures_cache.h"

/****************************************************************************/
/*                      Internal functions declaration                      */
/****************************************************************************/
static int __utils_ds_cache_create(UTILS_DS_ID id, UTILS_CACHE *cache);
static int __utils_ds_cache_lru_insert(UTILS_DS_ID id, void *data, void *key);
static int __utils_ds_cache_lru_remove(UTILS_DS_ID id, void *data, void *key);
static void* __utils_ds_cache_lru_get(UTILS_DS_ID id, void *key);
static int __utils_ds_cache_clear(UTILS_DS_ID id);
static void __utils_ds_cache_destroy(UTILS_DS_ID id);

/****************************************************************************/
/*                      Cache Public functions                              */
/****************************************************************************/
UTILS_DS_ID utils_ds_cache_create(UTILS_CACHE *cache) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    UTILS_DS_ID id = utils_ds_get_id(UTILS_DS_CACHE, cache->type);
    switch(cache->type) {
        case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            if(__utils_ds_cache_create(id, cache) < 0) {
                goto err;
            }
            break;
        default:
            UTILS_LOG_ERROR("Invalid cache type\n");
            goto err;
    }
    return id;

err: 
   utils_ds_delete_id(id);
   return 0;
}

/*
    Depending on the 'cacheSetNum' parameter, below cache types can do parallel search

    UTILS_DS_CACHE_LRU_ARRAY_DATA :
        LRU cache based on only Data. There is no key associated with it. The get method will only
        return true/false for this type of cache. i.e, if the data is present in the cache or not.
        
    UTILS_DS_CACHE_LRU_ARRAY_KEY:
        LRU cache based on integer type key-value. The get method will return the data associated with the key if present.
        Bit faster than UTILS_DS_CACHE_LRU_ARRAY_DATA, but only for simpler keys
        
    UTILS_DS_CACHE_LRU_HASH:
        LRU cache based on complex key-value. Similar to UTILS_DS_CACHE_LRU_ARRAY_KEY
        Uses medium resource, but faster (though as fast as THREADED caches), but works for complex key-values        
*/
int utils_ds_cache_insert(UTILS_DS_ID id, void *data, void *key) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            if(__utils_ds_cache_lru_insert(id, data, key) < 0) {
                return -1;
            }           
            break;
        default:
            UTILS_LOG_ERROR("Invalid cache type\n");
            return -1;           
    }
    return 0;
}

int utils_ds_cache_remove(UTILS_DS_ID id, void *data, void *key) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            if(__utils_ds_cache_lru_remove(id, data, key) < 0) {
                return -1;
            }           
            break;
        default:
            UTILS_LOG_ERROR("Invalid cache type\n");
            return -1;           
    }
    return 0;
}

void* utils_ds_cache_get(UTILS_DS_ID id, void *key) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    
    int *data = NULL;
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            data = __utils_ds_cache_lru_get(id, data, key);
            break;
        default:
            UTILS_LOG_ERROR("Invalid cache type\n");
            return NULL;           
    }
    return data;
}

int utils_ds_cache_clear(UTILS_DS_ID id) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            if(__utils_ds_cache_clear(id) < 0) {
                return -1;
            }           
            break;
        default:
            UTILS_LOG_ERROR("Invalid cache type\n");
            return -1;           
    }
    return 0;
}

/*
    Success : Return the same id which was deleted
    Failure : 0 or -ve
*/
int utils_ds_cache_destroy(UTILS_DS_ID id) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;

    int temp = id;

    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            __utils_ds_cache_destroy(id);
            goto del_id;
            break;
        default:
            UTILS_LOG_ERROR("Invalid cache type\n");
            return -1;           
    }

del_id:    
    utils_ds_delete_id(id);
    return temp;
}

/*****************************************************************************
                    Internal Functions
*****************************************************************************/
static int __utils_ds_cache_create(UTILS_DS_ID id, UTILS_CACHE *cache) {
    __UTILS_CACHE_META *qmeta = (__UTILS_CACHE_META *)malloc(sizeof(__UTILS_CACHE_META));

    qmeta->type = cache->type;
    qmeta->cacheSize = cache->cacheSize;
    qmeta->data = NULL;
    qmeta->__container = NULL;
    qmeta->lock.isProtected = FALSE;

    if(cache->isProtected == TRUE) {
        UTILS_DS_LOCK_CREATE(qmeta);
    }

    qmeta->cacheSet = NULL;
    if(cache->cacheSetNum > 1) {
        qmeta->cacheSet = (__UTILS_CACHE_SET_DATA *)malloc(sizeof(__UTILS_CACHE_SET_DATA));
        qmeta->cacheSet->__cacheThread = (pthread_t *)malloc(sizeof(pthread_t) * cache->cacheSetNum);
        if(cache->cacheSetNum > qmeta->cacheSize) { // Set cannot be greater than the size
            cache->cacheSetNum = qmeta->cacheSize; // In this case every element is serviced by a seperate thread
        }
        qmeta->cacheSet->__cacheSetNum = cache->cacheSetNum;
        qmeta->cacheSet->__cacheSetStop = FALSE;
        qmeta->cacheSet->__cacheSetTask = UTILS_CACHE_SET_TASK_INVALID;
        qmeta->cacheSet->__cacheSetTaskInput = NULL;
        qmeta->cacheSet->__cacheSetFlags = 0;
        qmeta->cacheSet->__cacheSetTasklet = (UTILS_CACHE_SET_TASKLET *)malloc(sizeof(UTILS_CACHE_SET_TASKLET) *
                                             cache->cacheSetNum);
        __utils_ds_cache_set_get_tasklet();
        for (int i = 0; i < cache->cacheSetNum; i++) {
            pthread_create(&qmeta->cacheSet->__cacheThread[i], NULL, __utils_ds_cache_set_handler, (void *)qmeta);
        }
    }

    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
                break;
            default:
                free(qmeta);
                return -1;
        }                
    } else if ((utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
                qmeta->data = (void **)malloc(sizeof(void *) * qmeta->cacheSize);
                qmeta->references = (int *)malloc(sizeof(int) * qmeta->cacheSize);
                break;
            default:
                free(qmeta);
                return -1;
        }
    }

    // Save the meta pointer to global array
    utils_ds_set_meta(id, (void *)qmeta);

    return 0;
}

static int __utils_ds_cache_lru_insert(UTILS_DS_ID id, void *data, void *key) {
    __UTILS_CACHE_META *qmeta = (__UTILS_CACHE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    int ret_val = 0;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
                break;
            default:
                ret_val = -1;
        }                
    } else if ((utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            {
                uint16_t lru_entry = 0, lru_entry_ref = 0;
                boolean isCacheFull = TRUE;
                for(int i = 0; i < qmeta->cacheSize; i++) {
                    if(qmeta->data[i] == NULL) {
                        qmeta->data[i] = data;
                        qmeta->references[i] = 1;
                        isCacheFull = FALSE;
                        break;
                    } else {
                        if(lru_entry_ref > qmeta->references[i]) {
                            lru_entry_ref = qmeta->references[i];
                            lru_entry = i;
                        }
                    }
                }

                if(isCacheFull == TRUE) {
                    qmeta->data[lru_entry] = data;
                    qmeta->references[lru_entry] = 1;
                }
                break;
            }                
            default:
                ret_val = -1;
        }
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return ret_val;
}

static int __utils_ds_cache_lru_remove(UTILS_DS_ID id, void *data, void *key) {
    __UTILS_CACHE_META *qmeta = (__UTILS_CACHE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    int ret_val = 0;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
                break;
            default:
                ret_val = -1;
        }                
    } else if ((utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            {
                for(int i = 0; i < qmeta->cacheSize; i++) {
                    if(qmeta->data[i] == data) {
                        qmeta->data[i] = NULL;
                        qmeta->references[i] = 0;
                        break;
                    } 
                }

                break;
            }                
            default:
                ret_val = -1;
        }
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return ret_val;
}

static void* __utils_ds_cache_lru_get(UTILS_DS_ID id, void *key) {
    __UTILS_CACHE_META *qmeta = (__UTILS_CACHE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    int data = NULL;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
                break;
            default:
                data = NULL;
        }                
    } else if ((utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            {
                if(qmeta->cacheSet == NULL) { // If there is no cache set, then do it in main thread
                    for(int i = 0; i < qmeta->cacheSize; i++) {
                        if(qmeta->data[i] == key) { // Need to pass Data as key
                            data = key; // Mark as found
                            break;
                        } 
                    }
                } else { // Ask the cache set to do parallel search
                    data = __utils_ds_cache_set_task_start(qmeta, UTILS_CACHE_SET_TASK_SIMPLE_SEARCH, key, TRUE);
                }
                break;
            }                
            default:
                data = NULL;
        }
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return data;
}

static int __utils_ds_cache_clear(UTILS_DS_ID id) {
    __UTILS_CACHE_META *qmeta = (__UTILS_CACHE_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    int ret_val = 0;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
                break;
            default:
                ret_val = -1;
        }                
    } else if ((utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED))  {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            {
                for(int i = 0; i < qmeta->cacheSize; i++) {
                    qmeta->data[i] = NULL;
                    qmeta->references[i] = 0;
                }
            }
            default:
                ret_val = -1;
        }
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return ret_val;
}

static void __utils_ds_cache_destroy(UTILS_DS_ID id) {
    __UTILS_CACHE_META *qmeta = (__UTILS_CACHE_META*)utils_ds_get_meta(id);

    UTILS_DS_LOCK_DESTROY(qmeta);

    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
                break;
            default:
                break;
        }                
    } else if ((utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) || (utils_ds_lib_mode == UTILS_DS_LIB_MODE_MIXED)) {
        switch(qmeta->type) {
            case UTILS_DS_CACHE_LRU_ARRAY_DATA:
            {
                for(int i = 0; i < qmeta->cacheSize; i++) {
                    qmeta->data[i] = NULL;
                    qmeta->references[i] = 0;
                }
            }
            default:
                break;
        }
    }

    // Start deleting meta for this id
    utils_ds_set_meta(id, NULL);
    memset(qmeta, 0, sizeof(__UTILS_CACHE_META));
    free(qmeta);
}

void *__utils_ds_cache_set_handler(void *arg) {
    __UTILS_CACHE_META *qmeta = (__UTILS_CACHE_META *)arg;
    __UTILS_CACHE_SET_DATA *cacheSetData = qmeta->cacheSet;
    
    pthread_cond_init(&cacheSetData->__cacheCV, NULL);
    pthread_mutex_init(&cacheSetData->__cacheMutex, NULL);

    while(cacheSetData->__cacheSetStop == FALSE) {
        pthread_mutex_lock(&cacheSetData->__cacheMutex);
        while(cacheSetData->__cacheSetTaskStart == FALSE) {
            pthread_cond_wait(&cacheSetData->__cacheCV, &cacheSetData->__cacheMutex);
        }
        pthread_mutex_unlock(&cacheSetData->__cacheMutex);

        // Process the task requested in the qmeta
        __utils_ds_cache_set_process_task(qmeta);
    }
    return NULL;
}

// This is a blocking call. It sets the task and gets the result for the on-going cache set task
void* __utils_ds_cache_set_task_start(__UTILS_CACHE_META *qmeta, UTILS_CACHE_SET_TASK task, void *taskInput, boolean start) {
    __UTILS_CACHE_SET_DATA *cacheSetData = qmeta->cacheSet;
    pthread_mutex_lock(&cacheSetData->__cacheMutex);
    cacheSetData->__cacheSetTask = task;
    cacheSetData->__cacheSetTaskInput = taskInput;
    cacheSetData->__cacheSetTaskStart = start;
    cacheSetData->__cacheSetFlags = 0; // Clear the flags
    pthread_cond_broadcast(&cacheSetData->__cacheCV);
    pthread_mutex_unlock(&cacheSetData->__cacheMutex);

    while(!(cacheSetData->__cacheSetFlags & UTILS_CACHE_SET_TASK_DONE)) {
        usleep(10); // sleep for 10 usec
    }
}

void __utils_ds_cache_set_process_task(__UTILS_CACHE_META *qmeta) {
    __UTILS_CACHE_SET_DATA *cacheSetData = qmeta->cacheSet;

    // If the task is not started/already stopped, bail out
    if(cacheSetData->__cacheSetTaskStart == FALSE) {
        return;
    }

    // If the task is already done by any of the threads, even before coming to this point just return
    if(cacheSetData->__cacheSetFlags & UTILS_CACHE_SET_TASK_DONE) {
        return;
    }

    switch(cacheSetData->__cacheSetTask) {
        case UTILS_CACHE_SET_TASK_SIMPLE_SEARCH:
            UTILS_CACHE_SET_SIMPLE_SEARCH_TASKLET tasklet;
            __utils_ds_cache_set_get_task(qmeta, &tasklet);
            void *key = cacheSetData->__cacheSetTaskInput;
            for(int i = tasklet.start; i < tasklet.end; i++) {
                if(qmeta->data[i] == key) { // Need to pass Data as key
                    data = key; // Mark as found
                    cacheSetData->__cacheSetFlags |= UTILS_CACHE_SET_TASK_DONE;
                    break;
                }
            }
            cacheSetData->__cacheSetFlags |= UTILS_CACHE_SET_SEARCH_DONE;
            break;
        default:
            
    }

    if(cacheSetData->__cacheSetFlags & UTILS_CACHE_SET_TASK_DONE) {

    }
}

// This function gives each thread a tasklet to perform
// depending on various factors
void __utils_ds_cache_set_get_tasklet(__UTILS_CACHE_META *qmeta) {
    __UTILS_CACHE_SET_DATA *cacheSetData = qmeta->cacheSet;

    switch(cacheSetData->__cacheSetTask) {
        case UTILS_CACHE_SET_TASK_SIMPLE_SEARCH:
            
            UTILS_CACHE_SET_SIMPLE_SEARCH_TASKLET *search_tasklet = (UTILS_CACHE_SET_SIMPLE_SEARCH_TASKLET *)malloc();
            uint16_t chunk_size = qmeta->cacheSize / cacheSetData->__cacheSetNum;
            static uint8_t chunk_num = 0;
            static uint16_t chunk = 0;
            search_tasklet->start = chunk;
            chunk = chunk + chunk_size;
            if(chunk_num == (cacheSetData->__cacheSetNum-1)) { // Last chunk
                search_tasklet->end = qmeta->cacheSize;
                chunk = 0;
                chunk_num = 0;
            } else {
                search_tasklet->end = chunk;
            }
            chunk_num++;
            break;
        default:
    }
}

#endif