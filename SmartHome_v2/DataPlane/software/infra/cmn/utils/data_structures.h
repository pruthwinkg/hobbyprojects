/*******************************************************************************
    Description : Data structures heade file
                  Futute Request : TODO See if this file can be made as a 
                  wrapper for C++ STL. SO no need to change any other module,
                  if the interfaces are well defined

    TODO: USe BSD libraries and WRAP Utils library around it

    http://bxr.su/OpenBSD/sys/dev/pci/drm/include/linux/
                  
*******************************************************************************/

#ifndef INCLUDE_UTILS_DATASTRUCTURES_H__
#define INCLUDE_UTILS_DATASTRUCTURES_H__


#include "data_structures_list.h"
#include "data_structures_queue.h"
#include "data_structures_hash.h"
#include "data_structures_cache.h"


//#define UTILS_DS_MAX_ID             (100) // Max IDs support (soft limit)

/*******************************************************************************/
/*              Public Functions                                               */
/* Note : ALL the datastructures directly maintained by this library will be   */
/*        identified by a unique ID. Pass the same ID for all subsequent       */
/*        operation after its creation.                                        */
/*******************************************************************************/
// Common Functions
void utils_ds_init(UTILS_DS_LIB_MODE mode, uint16_t max_dsid);

// Queue Functions
UTILS_DS_ID utils_ds_queue_create(UTILS_QUEUE *queue);
int utils_ds_queue_enqueue(UTILS_DS_ID id, void *data);
void* utils_ds_queue_dequeue(UTILS_DS_ID id);
void* utils_ds_queue_lookup_at_pos(UTILS_DS_ID id, uint32_t pos);
int utils_ds_queue_destroy(UTILS_DS_ID id, boolean delete_data); // Deletes FULL queue
boolean utils_ds_queue_is_full(UTILS_DS_ID id);
boolean utils_ds_queue_is_empty(UTILS_DS_ID id);
uint32_t utils_ds_queue_get_count(UTILS_DS_ID id);

// Linked List functions
UTILS_DS_ID utils_ds_list_create(UTILS_LIST *list);
int utils_ds_list_insert(UTILS_DS_ID id, void *data, boolean to_head);
int utils_ds_list_insert_at_pos(UTILS_DS_ID id, void *data, uint32_t pos);
void* utils_ds_list_remove(UTILS_DS_ID id, boolean from_head);
void* utils_ds_list_remove_at_pos(UTILS_DS_ID id, uint32_t pos);
void* utils_ds_list_lookup_at_pos(UTILS_DS_ID id, uint32_t pos);
int utils_ds_list_destroy(UTILS_DS_ID id, boolean delete_data);
int utils_ds_list_get_size(UTILS_DS_ID id);

// Hash
UTILS_DS_ID utils_ds_hash_create(UTILS_HASH *hash);
int utils_ds_hash_insert(UTILS_DS_ID id, void *key, uint16_t key_len, void *data);
void* utils_ds_hash_lookup(UTILS_DS_ID id, void *key, uint16_t key_len);
int utils_ds_hash_erase(UTILS_DS_ID id, void *key, uint16_t key_len);
int utils_ds_hash_reset(UTILS_DS_ID id);
int utils_ds_hash_destroy(UTILS_DS_ID id);
int utils_ds_hash_get_size(UTILS_DS_ID id);
boolean utils_ds_hash_is_empty(UTILS_DS_ID id);

// Cache
UTILS_DS_ID utils_ds_cache_create(UTILS_CACHE *cache);
int utils_ds_cache_insert(UTILS_DS_ID id, void *data, void *key);
void* utils_ds_cache_get(UTILS_DS_ID id, void *key);
int utils_ds_cache_remove(UTILS_DS_ID id, void *data, void *key);
int utils_ds_cache_clear(UTILS_DS_ID id);
int utils_ds_cache_destroy(UTILS_DS_ID id);

/*****************************************************************************
                    Generic external utility Functions
*****************************************************************************/
boolean utils_is_int_in_array(int value, const int *array, int size);
int utils_get_max_int_in_array(const int *array, int size);
int utils_compare_structs(void *struct1, void *struct2, size_t size);

#endif /* INCLUDE_UTILS_DATASTRUCTURES_H__ */
