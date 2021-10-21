/*****************************************************************************
    Description : The purpose of this file is to define various common
                datastructures qhich might be required by various modules.

                All these data strcutures will be very genereic. i.e they will
                agnostic of what kind of data they hold
*****************************************************************************/

#include "./utils_cpp/utils_cpp.h"
#include "data_structures_hash.h"

/****************************************************************************/
/*                      Internal functions declaration                      */
/****************************************************************************/
static int __utils_ds_hash_create(UTILS_DS_ID id, UTILS_HASH *hash);
static int __utils_ds_hash_string_insert(UTILS_DS_ID id, void *key, uint16_t key_len, void *data);
static int __utils_ds_hash_integer_insert(UTILS_DS_ID id, void *key, void *data);
static void* __utils_ds_hash_string_lookup(UTILS_DS_ID id, void *key, uint16_t key_len);
static void* __utils_ds_hash_integer_lookup(UTILS_DS_ID id, void *key);
static int __utils_ds_hash_string_erase(UTILS_DS_ID id, void *key, uint16_t key_len);
static int __utils_ds_hash_integer_erase(UTILS_DS_ID id, void *key);
static int __utils_ds_hash_reset(UTILS_DS_ID id);
static void __utils_ds_hash_destroy(UTILS_DS_ID id);
static int __utils_ds_hash_get_size(UTILS_DS_ID id);
static boolean __utils_ds_hash_isempty(UTILS_DS_ID id);

/****************************************************************************/
/*                      Queue Public functions                              */
/****************************************************************************/
UTILS_DS_ID utils_ds_hash_create(UTILS_HASH *hash) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    UTILS_DS_ID id = utils_ds_get_id(UTILS_DS_HASH, hash->type);
    switch(hash->type) {
        case UTILS_DS_HASH_KEY_STRING:
        case UTILS_DS_HASH_KEY_INTEGER:
            if(__utils_ds_hash_create(id, hash) < 0) {
                goto err;
            }
            break;
        default:
            UTILS_LOG_ERROR("Invalid hash type\n");
            goto err;
    }
    return id;

err: 
   utils_ds_delete_id(id);
   return 0;
}

int utils_ds_hash_insert(UTILS_DS_ID id, void *key, uint16_t key_len, void *data) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    if(key == NULL) return -1;
    
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_DS_HASH_KEY_STRING:
            if(__utils_ds_hash_string_insert(id, key, key_len, data) < 0) {
                return -1;
            }           
            break;
         case UTILS_DS_HASH_KEY_INTEGER:
            if(__utils_ds_hash_integer_insert(id, key, data) < 0) {
                return -1;
            }       
            break;          
        default:
            UTILS_LOG_ERROR("Invalid hash type\n");
            return -1;           
    }
    return 0;
}

void* utils_ds_hash_lookup(UTILS_DS_ID id, void *key, uint16_t key_len) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return NULL;
    if(key == NULL) return NULL;

    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_DS_HASH_KEY_STRING:
            return __utils_ds_hash_string_lookup(id, key, key_len);
        case UTILS_DS_HASH_KEY_INTEGER:
            return __utils_ds_hash_integer_lookup(id, key);
        default:
            UTILS_LOG_ERROR("Invalid hash type\n");
    }
    return NULL;
}

int utils_ds_hash_erase(UTILS_DS_ID id, void *key, uint16_t key_len) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    if(key == NULL) return -1;
    
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_DS_HASH_KEY_STRING:
            return __utils_ds_hash_string_erase(id, key, key_len);
        case UTILS_DS_HASH_KEY_INTEGER:
            return __utils_ds_hash_integer_erase(id, key);
        default:
            UTILS_LOG_ERROR("Invalid hash type\n");
            return -1;
    }
    return -1;
}

int utils_ds_hash_reset(UTILS_DS_ID id) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_DS_HASH_KEY_STRING:
        case UTILS_DS_HASH_KEY_INTEGER:
            return __utils_ds_hash_reset(id);
        default:
            UTILS_LOG_ERROR("Invalid hash type\n");
            return -1;
    }
    return -1;
}

/*
    Success : Return the same id which was deleted
    Failure : 0 or -ve
*/
int utils_ds_hash_destroy(UTILS_DS_ID id) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
   
    int temp = id;
    
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_DS_HASH_KEY_STRING:
        case UTILS_DS_HASH_KEY_INTEGER:
            __utils_ds_hash_destroy(id);
            goto del_id;
            break;
        default:
            UTILS_LOG_ERROR("Invalid hash type\n");
            return -1;
    }

del_id:    
    utils_ds_delete_id(id);
    return temp;
}

int utils_ds_hash_get_size(UTILS_DS_ID id) {
    return __utils_ds_hash_get_size(id);
}

boolean utils_ds_hash_is_empty(UTILS_DS_ID id) {
    return __utils_ds_hash_isempty(id);
}

/*****************************************************************************
                    Internal Functions
*****************************************************************************/
static int __utils_ds_hash_create(UTILS_DS_ID id, UTILS_HASH *hash) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META *)malloc(sizeof(__UTILS_HASH_META));

    qmeta->type = hash->type;
    qmeta->currsize = 0;
    qmeta->data = NULL;
    qmeta->__container = NULL;
    qmeta->lock.isProtected = FALSE;

    if(hash->isProtected == TRUE) {
        UTILS_DS_LOCK_CREATE(qmeta);
    }

    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        switch(qmeta->type) {
            case UTILS_DS_HASH_KEY_STRING:
                qmeta->__container = utils_ds_cpp_hash_create_container(UTILS_DS_CPP_HASH_KEY_STRING);
                break;
            case UTILS_DS_HASH_KEY_INTEGER:
                qmeta->__container = utils_ds_cpp_hash_create_container(UTILS_DS_CPP_HASH_KEY_INTEGER);
                break;
            default:
                free(qmeta);
                return -1;
        }                
        qmeta->data = NULL;
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;
        return -1;
    }

    // Save the meta pointer to global array
    utils_ds_set_meta(id, (void *)qmeta);

    return 0;

}

static int __utils_ds_hash_string_insert(UTILS_DS_ID id, void *key, uint16_t key_len, void *data) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    int ret_val = -1;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        ret_val = utils_ds_cpp_hash_insert_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_STRING, key, key_len, data);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;       
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return 0;
}

static int __utils_ds_hash_integer_insert(UTILS_DS_ID id, void *key, void *data) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    int ret_val = -1;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        ret_val = utils_ds_cpp_hash_insert_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_INTEGER, key, 0, data);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;       
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return ret_val;
}

static void* __utils_ds_hash_string_lookup(UTILS_DS_ID id, void *key, uint16_t key_len) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    void *data = NULL;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        data = utils_ds_cpp_hash_lookup_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_STRING, key, key_len);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;       
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return data;
}

static void* __utils_ds_hash_integer_lookup(UTILS_DS_ID id, void *key) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    void *data = NULL;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        data = utils_ds_cpp_hash_lookup_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_INTEGER, key, 0);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;       
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return data;
}

static int __utils_ds_hash_string_erase(UTILS_DS_ID id, void *key, uint16_t key_len) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);
    
    int ret_val = -1;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        ret_val = utils_ds_cpp_hash_erase_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_STRING, key, key_len);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;       
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return ret_val;
}

static int __utils_ds_hash_integer_erase(UTILS_DS_ID id, void *key) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);
    
    int ret_val = -1;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        ret_val = utils_ds_cpp_hash_erase_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_INTEGER, key, 0);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;       
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return ret_val;
}

static int __utils_ds_hash_reset(UTILS_DS_ID id) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META*)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);
    
    int ret_val = -1;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        switch(qmeta->type) {
            case UTILS_DS_HASH_KEY_STRING:
                ret_val = utils_ds_cpp_hash_reset_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_STRING);
                break;
            case UTILS_DS_HASH_KEY_INTEGER:
                ret_val = utils_ds_cpp_hash_reset_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_INTEGER);
                break;
            default:
                ret_val = -1;
        }
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;       
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);

    return ret_val;
}

static void __utils_ds_hash_destroy(UTILS_DS_ID id) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META*)utils_ds_get_meta(id);

    UTILS_DS_LOCK_DESTROY(qmeta);

    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        utils_ds_cpp_hash_destroy_container(qmeta->__container);
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;
    }

    // Start deleting meta for this id
    utils_ds_set_meta(id, NULL);
    memset(qmeta, 0, sizeof(__UTILS_HASH_META));
    free(qmeta);
}

static int __utils_ds_hash_get_size(UTILS_DS_ID id) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META*)utils_ds_get_meta(id);

    int size = 0;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        switch(qmeta->type) {
            case UTILS_DS_HASH_KEY_STRING:
                size = utils_ds_cpp_hash_get_size_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_STRING);
                break;
            case UTILS_DS_HASH_KEY_INTEGER:
                size = utils_ds_cpp_hash_get_size_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_INTEGER);
                break;
            default:
                break;
        }                
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;
    }

    return size;
}

static boolean __utils_ds_hash_isempty(UTILS_DS_ID id) {
    __UTILS_HASH_META *qmeta = (__UTILS_HASH_META*)utils_ds_get_meta(id);

    boolean isEmpty = FALSE;
    if(utils_ds_lib_mode == UTILS_DS_LIB_MODE_CPP) {
        switch(qmeta->type) {
            case UTILS_DS_HASH_KEY_STRING:
                isEmpty = utils_ds_cpp_hash_isempty_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_STRING);
                break;
            case UTILS_DS_HASH_KEY_INTEGER:
                isEmpty = utils_ds_cpp_hash_isempty_container(qmeta->__container, UTILS_DS_CPP_HASH_KEY_INTEGER);
                break;
             default:
                break;              
        }            
    } else if (utils_ds_lib_mode == UTILS_DS_LIB_MODE_STD) {
        UTILS_NOT_SUPPORTED;
    }

    return isEmpty;
}

