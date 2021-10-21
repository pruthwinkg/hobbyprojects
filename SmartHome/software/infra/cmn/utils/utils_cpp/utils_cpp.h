/*******************************************************************************
    Description: This file is used as a wrapper around the C++ functions.


*******************************************************************************/
#ifndef INCLUDE_UTILS_CPP_H__
#define INCLUDE_UTILS_CPP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "__data_structures_cpp.h"

/*******************************************************************************
                    Utils CPP library functions
********************************************************************************/
// Queues
void* utils_ds_cpp_queue_create_container(int size);
int utils_ds_cpp_queue_enqueue_container(void *container, void *data, bool isFront);
void* utils_ds_cpp_queue_dequeue_container(void *container, bool isFront);
int utils_ds_cpp_queue_insert_at_pos_container(void *container, int pos, void *data);
void* utils_ds_cpp_queue_lookup_at_pos_container(void *container, int pos);
void utils_ds_cpp_queue_destroy_container(void *container);

// Hash
void* utils_ds_cpp_hash_create_container(UTILS_DS_CPP_HASH_KEY_TYPE type);
int utils_ds_cpp_hash_insert_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type, void *key, int key_len, void *data);
int utils_ds_cpp_hash_erase_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type, void *key, int key_len);
void* utils_ds_cpp_hash_lookup_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type, void *key, int key_len);
int utils_ds_cpp_hash_reset_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type);
void utils_ds_cpp_hash_destroy_container(void *container);
int utils_ds_cpp_hash_get_size_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type);
bool utils_ds_cpp_hash_isempty_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_UTILS_CPP_H__ */
