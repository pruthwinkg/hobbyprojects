/*****************************************************************************
    Description : The purpose of this file is to define various common
                datastructures qhich might be required by various modules.

                All these data strcutures will be very genereic. i.e they will
                agnostic of what kind of data they hold
*****************************************************************************/

#include "data_structures_list.h"


/****************************************************************************/
/*                      Internal functions declaration                      */
/****************************************************************************/
static int __utils_ds_list_create_single(UTILS_DS_ID id, UTILS_LIST *list);
static int __utils_ds_list_create_double(UTILS_DS_ID id, UTILS_LIST *list);
static int __utils_ds_list_create_single_circular(UTILS_DS_ID id, UTILS_LIST *list);
static int __utils_ds_list_create_double_circular(UTILS_DS_ID id, UTILS_LIST *list);
static int __utils_ds_list_insert_single(UTILS_DS_ID id, void *data, uint32_t pos);
static int __utils_ds_list_insert_double(UTILS_DS_ID id, void *data, uint32_t pos);
static int __utils_ds_list_insert_single_circular(UTILS_DS_ID id, void *data, uint32_t pos);
static int __utils_ds_list_insert_double_circular(UTILS_DS_ID id, void *data, uint32_t pos);
static void* __utils_ds_list_remove_single(UTILS_DS_ID id, uint32_t pos);
static void* __utils_ds_list_remove_double(UTILS_DS_ID id, uint32_t pos);
static void* __utils_ds_list_remove_single_circular(UTILS_DS_ID id, uint32_t pos);
static void* __utils_ds_list_remove_double_circular(UTILS_DS_ID id, uint32_t pos);
static void* __utils_ds_list_lookup_at_pos_single(UTILS_DS_ID id, uint32_t pos);
static void* __utils_ds_list_lookup_at_pos_double(UTILS_DS_ID id, uint32_t pos);
static void* __utils_ds_list_lookup_at_pos_single_circular(UTILS_DS_ID id, uint32_t pos);
static void* __utils_ds_list_lookup_at_pos_double_circular(UTILS_DS_ID id, uint32_t pos);
static void __utils_ds_list_destroy_single(UTILS_DS_ID id, boolean delete_data);
static void __utils_ds_list_destroy_double(UTILS_DS_ID id, boolean delete_data);
static void __utils_ds_list_destroy_single_circular(UTILS_DS_ID id, boolean delete_data);
static void __utils_ds_list_destroy_double_circular(UTILS_DS_ID id, boolean delete_data);
static int __utils_ds_list_get_size(UTILS_DS_ID id);

/****************************************************************************/
/*                      List Public functions                               */
/****************************************************************************/
UTILS_DS_ID utils_ds_list_create(UTILS_LIST *list) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    UTILS_DS_ID id = utils_ds_get_id(UTILS_DS_LIST, list->type);
    switch(list->type) {
        case UTILS_LIST_SINGLE:
            if(__utils_ds_list_create_single(id, list) < 0) {
                goto err;
            }
            break;
        case UTILS_LIST_DOUBLE:
           if(__utils_ds_list_create_double(id, list) < 0) {
                goto err;
            }
            break;
        case UTILS_LIST_SINGLE_CIRCULAR:
            if(__utils_ds_list_create_single_circular(id, list) < 0) {
                goto err;
            }           
            break;
        case UTILS_LIST_DOUBLE_CIRCULAR:
            if(__utils_ds_list_create_double_circular(id, list) < 0) {
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

int utils_ds_list_insert_at_pos(UTILS_DS_ID id, void *data, uint32_t pos) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_LIST_SINGLE:
            if(__utils_ds_list_insert_single(id, data, pos) < 0) {
                return -1;
            }           
            break;
        case UTILS_LIST_DOUBLE:
            if(__utils_ds_list_insert_double(id, data, pos) < 0) {
                return -1;
            }           
            break;          
        case UTILS_LIST_SINGLE_CIRCULAR:
             if(__utils_ds_list_insert_single_circular(id, data, pos) < 0) {
                return -1;
            }       
            break;
        case UTILS_LIST_DOUBLE_CIRCULAR:
             if(__utils_ds_list_insert_double_circular(id, data, pos) < 0) {
                return -1;
            }           
            break;
        default:
            UTILS_LOG_ERROR("Invalid queue type\n");
            return -1;           
    }
    return 0;
}

int utils_ds_list_insert(UTILS_DS_ID id, void *data, boolean to_head) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;

    uint32_t pos = 0;

    if(to_head) {
        pos = 0;
    } else {
        pos = 0xFFFFFFFF;
    }

    return utils_ds_list_insert_at_pos(id, data, pos);
}

void* utils_ds_list_remove_at_pos(UTILS_DS_ID id, uint32_t pos) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
   
    void *data = NULL;
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_LIST_SINGLE:
            return __utils_ds_list_remove_single(id, pos);
        case UTILS_LIST_DOUBLE:
            return __utils_ds_list_remove_double(id, pos);
        case UTILS_LIST_SINGLE_CIRCULAR:
            return __utils_ds_list_remove_single_circular(id, pos);
        case UTILS_LIST_DOUBLE_CIRCULAR:
             return __utils_ds_list_remove_double_circular(id, pos);
        default:
            UTILS_LOG_ERROR("Invalid queue type\n");             
    }
    return NULL;
}

void* utils_ds_list_remove(UTILS_DS_ID id, boolean from_head) {
    if (utils_ds_initialized == FALSE) {
        return NULL;
    }
    if(id == 0) return NULL;

    uint32_t pos = 0;

    if(from_head) {
        pos = 0;
    } else {
        pos = 0xFFFFFFFF;
    }

    return utils_ds_list_remove_at_pos(id, pos);
}

void* utils_ds_list_lookup_at_pos(UTILS_DS_ID id, uint32_t pos) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
   
    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_LIST_SINGLE:
            return __utils_ds_list_lookup_at_pos_single(id, pos);
        case UTILS_LIST_DOUBLE:
            return __utils_ds_list_lookup_at_pos_double(id, pos);
        case UTILS_LIST_SINGLE_CIRCULAR:
            return __utils_ds_list_lookup_at_pos_single_circular(id, pos);
        case UTILS_LIST_DOUBLE_CIRCULAR:
            return __utils_ds_list_lookup_at_pos_double_circular(id, pos);
        default:
            UTILS_LOG_ERROR("Invalid queue type\n");             
    }
    return NULL;
}

/*
    Note : This function does a FULL cleanup if delete_data is set. It 
        will try to delete even the data associated with the list

    Success : Return the same id which was deleted
    Failure : 0 or -ve            
*/
int utils_ds_list_destroy(UTILS_DS_ID id, boolean delete_data) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;
    
    int temp = id;

    switch(UTILS_DS_GET_SUBTYPE(id)) {
        case UTILS_LIST_SINGLE:
            __utils_ds_list_destroy_single(id, delete_data);
            goto del_id;            
            break;
        case UTILS_LIST_DOUBLE:
             __utils_ds_list_destroy_double(id, delete_data);
            goto del_id;                       
            break;
        case UTILS_LIST_SINGLE_CIRCULAR:
            __utils_ds_list_destroy_single_circular(id, delete_data);
            goto del_id;                
            break;
        case UTILS_LIST_DOUBLE_CIRCULAR:
            __utils_ds_list_destroy_double_circular(id, delete_data);
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

int utils_ds_list_get_size(UTILS_DS_ID id) {
    if (utils_ds_initialized == FALSE) {
        return 0;
    }
    if(id == 0) return 0;

    return __utils_ds_list_get_size(id);
}

/*****************************************************************************/
/*                   List Internal Functions                                 */
/*****************************************************************************/
static int __utils_ds_list_create_single(UTILS_DS_ID id, UTILS_LIST *list) {
    return 0;
}

static int __utils_ds_list_create_double(UTILS_DS_ID id, UTILS_LIST *list) {
    __UTILS_LIST_META *qmeta = (__UTILS_LIST_META *)malloc(sizeof(__UTILS_LIST_META));
    memset(&qmeta->anchor, 0, sizeof(__UTILS_LIST_NODE));
    qmeta->anchor.list_type.doubly.prev = NULL;
    qmeta->anchor.list_type.doubly.next = NULL;

    qmeta->max_size = 0; // Non-circular doesnt have max-size
    qmeta->curr_size = 0;
    qmeta->lock.isProtected = list->isProtected;

    if(list->isProtected == TRUE) {
        UTILS_DS_LOCK_CREATE(qmeta);
    }

    // Save the meta pointer to global array
    utils_ds_set_meta(id, (void *)qmeta);

    return 0;
}

static int __utils_ds_list_create_single_circular(UTILS_DS_ID id, UTILS_LIST *list) {
    return 0;
}

static int __utils_ds_list_create_double_circular(UTILS_DS_ID id, UTILS_LIST *list) {
    __utils_ds_list_create_double(id, list);
    __UTILS_LIST_META *qmeta = (__UTILS_LIST_META *)utils_ds_get_meta(id);
    if(list->max_size == 0) {
        qmeta->max_size = 100; // Default max-size for circular list
    } else {
        qmeta->max_size = list->max_size; // Circular list have max-size
    }
    return 0;
}

static int __utils_ds_list_insert_single(UTILS_DS_ID id, void *data, uint32_t pos) {
    return 0;
}

static int __utils_ds_list_insert_double(UTILS_DS_ID id, void *data, uint32_t pos) {
    __UTILS_LIST_META *qmeta = (__UTILS_LIST_META *)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    if((pos != 0xFFFFFFFF) && (pos > qmeta->curr_size)) return -1;

    __UTILS_LIST_DOUBLE *node = (__UTILS_LIST_DOUBLE *)malloc(sizeof(__UTILS_LIST_DOUBLE));

    if(qmeta->curr_size == 0) { // List is empty
        qmeta->anchor.list_type.doubly.next = node;
        qmeta->anchor.list_type.doubly.prev = node;
        node->next = &qmeta->anchor.list_type.doubly;
        node->prev = &qmeta->anchor.list_type.doubly;
    } else if(pos == 0) { // insert to head         
        __UTILS_LIST_DOUBLE *head = qmeta->anchor.list_type.doubly.next;
        node->next = head;
        node->prev = &qmeta->anchor.list_type.doubly;
        head->prev = node;
        qmeta->anchor.list_type.doubly.next = node;
    } else if (pos == 0xFFFFFFFF) { // insert to tail
        __UTILS_LIST_DOUBLE *tail = qmeta->anchor.list_type.doubly.prev;
        node->next = &qmeta->anchor.list_type.doubly;
        node->prev = tail;
        tail->next = node;
        qmeta->anchor.list_type.doubly.prev = node;
    } else {
        __UTILS_LIST_DOUBLE *curr = &(qmeta->anchor.list_type.doubly);
        while(pos > 0) {
            curr = curr->next;
            pos--;
        }
        __UTILS_LIST_DOUBLE *next = curr->next;
        curr->next = node;
        node->next = next;
        node->prev = curr;
        next->prev = node;
    }

    node->data = data;
    qmeta->curr_size++;

    UTILS_DS_CHECK_UNLOCK(qmeta);    

    return 0;  
}

static int __utils_ds_list_insert_single_circular(UTILS_DS_ID id, void *data, uint32_t pos) {

}

static int __utils_ds_list_insert_double_circular(UTILS_DS_ID id, void *data, uint32_t pos) {
    __UTILS_LIST_META *qmeta = (__UTILS_LIST_META *)utils_ds_get_meta(id);

    // The difference between circular and non-circular is only max_size
    if(qmeta->curr_size >= qmeta->max_size) return -1;

    return __utils_ds_list_insert_double(id, data, pos);
}

static void* __utils_ds_list_remove_single(UTILS_DS_ID id, uint32_t pos) {
    return NULL;
}

static void* __utils_ds_list_remove_double(UTILS_DS_ID id, uint32_t pos) {
    __UTILS_LIST_META *qmeta = (__UTILS_LIST_META *)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    if((pos != 0xFFFFFFFF) && (pos > qmeta->curr_size)) return -1;
    if(qmeta->curr_size == 0) return -1; // List is empty

    void *data = NULL;
    if(pos == 0) { // remove from head         
        __UTILS_LIST_DOUBLE *head = qmeta->anchor.list_type.doubly.next;
        __UTILS_LIST_DOUBLE *next = head->next;
        qmeta->anchor.list_type.doubly.next = next;
        next->prev = head->prev;
        data = head->data;
        free(head);
    } else if (pos == 0xFFFFFFFF) { // remove from tail
        __UTILS_LIST_DOUBLE *tail = qmeta->anchor.list_type.doubly.prev;
        __UTILS_LIST_DOUBLE *prev = tail->prev;
        qmeta->anchor.list_type.doubly.prev = prev;
        prev->next = tail->next;
        data = tail->data;
        free(tail);
    } else {
        __UTILS_LIST_DOUBLE *curr = &(qmeta->anchor.list_type.doubly);
        while(pos > 0) {
            curr = curr->next;
            pos--;
        }
        __UTILS_LIST_DOUBLE *next = curr->next;
        curr->next = next->next;
        next->next->prev = curr;
        data = next->data;
        free(next);
    }

    qmeta->curr_size--;

    UTILS_DS_CHECK_UNLOCK(qmeta);    

    return data;  
}

static void* __utils_ds_list_remove_single_circular(UTILS_DS_ID id, uint32_t pos) {
    return NULL;
}

static void* __utils_ds_list_remove_double_circular(UTILS_DS_ID id, uint32_t pos) {
    return __utils_ds_list_remove_double(id, pos);
}

static void* __utils_ds_list_lookup_at_pos_single(UTILS_DS_ID id, uint32_t pos) {
    return NULL;
}

static void* __utils_ds_list_lookup_at_pos_double(UTILS_DS_ID id, uint32_t pos) {
    __UTILS_LIST_META *qmeta = (__UTILS_LIST_META *)utils_ds_get_meta(id);

    UTILS_DS_CHECK_LOCK(qmeta);

    if((pos != 0xFFFFFFFF) && (pos > qmeta->curr_size)) return -1;
    if(qmeta->curr_size == 0) return -1; // List is empty

    void *data = NULL;
    if(pos == 0) { // return head         
        __UTILS_LIST_DOUBLE *head = qmeta->anchor.list_type.doubly.next;
        data = head->data;
    } else if (pos == 0xFFFFFFFF) { // return tail
        __UTILS_LIST_DOUBLE *tail = qmeta->anchor.list_type.doubly.prev;
        data = tail->data;
    } else { // return at 'pos'
        __UTILS_LIST_DOUBLE *curr = &(qmeta->anchor.list_type.doubly);
        while(pos > 0) {
            curr = curr->next;
            pos--;
        }
        data = curr->data;
    }

    UTILS_DS_CHECK_UNLOCK(qmeta);    

    return data;  
}

static void* __utils_ds_list_lookup_at_pos_single_circular(UTILS_DS_ID id, uint32_t pos) {
    return NULL;
}

static void* __utils_ds_list_lookup_at_pos_double_circular(UTILS_DS_ID id, uint32_t pos) {
    return __utils_ds_list_lookup_at_pos_double(id, pos);
}

static void __utils_ds_list_destroy_single(UTILS_DS_ID id, boolean delete_data) {

}

static void __utils_ds_list_destroy_double(UTILS_DS_ID id, boolean delete_data) {
    __UTILS_LIST_META *qmeta = (__UTILS_LIST_META *)utils_ds_get_meta(id);     
    __UTILS_LIST_DOUBLE *next = NULL, *curr = NULL;
    
    curr = qmeta->anchor.list_type.doubly.next;
    for (uint32_t i = 0; i < qmeta->curr_size; i++) {            
        if(delete_data == TRUE) {
            free(curr->data);
        }
        next = curr->next;
        free(curr);
        curr = next;
    }

    UTILS_DS_LOCK_DESTROY(qmeta);

    // Start deleting meta for this id
    utils_ds_set_meta(id, NULL);
    
    free(qmeta);
}

static void __utils_ds_list_destroy_single_circular(UTILS_DS_ID id, boolean delete_data) {

}

static void __utils_ds_list_destroy_double_circular(UTILS_DS_ID id, boolean delete_data) {
    return __utils_ds_list_destroy_double(id, delete_data);
}

static int __utils_ds_list_get_size(UTILS_DS_ID id) {
    __UTILS_LIST_META *qmeta = (__UTILS_LIST_META *)utils_ds_get_meta(id);
    return qmeta->curr_size;
}
