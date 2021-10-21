/****************************************************************************
    Description: This uses the C++ dequeue library
*****************************************************************************/
#include <iostream>
#include <string>
#include <unordered_map>
#include "__data_structures_cpp.h"

using namespace std;

/****************************************************************************/
/*                      Functions Definitions                               */
/****************************************************************************/
extern "C" { /* Define all functions as C compatible */

void* utils_ds_cpp_hash_create_container(UTILS_DS_CPP_HASH_KEY_TYPE type) {
    switch(type) {
        case UTILS_DS_CPP_HASH_KEY_STRING:
        {
            unordered_map<string, void*> *utils_ds_hash = new unordered_map<string, void*>;
            return utils_ds_hash;
        }            
        case UTILS_DS_CPP_HASH_KEY_INTEGER:
        {
            unordered_map<int, void*> *utils_ds_hash = new unordered_map<int, void*>;
            return utils_ds_hash;
        }            
        default:
            return NULL;
    }
    return NULL;
}

int utils_ds_cpp_hash_insert_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type, void *key, int key_len, void *data) {
    if(container == NULL) return -1;
    if(key == NULL) return -1;

     switch(type) {
        case UTILS_DS_CPP_HASH_KEY_STRING:
        {
            unordered_map<string, void*> *utils_ds_hash = (unordered_map<string, void*> *)container;
            char *string_key = static_cast<char*>(key);
            string hash_key(string_key, key_len); 
            utils_ds_hash->insert({hash_key, data});
            return 0;
        }            
        case UTILS_DS_CPP_HASH_KEY_INTEGER:
        {
            unordered_map<int, void*> *utils_ds_hash = (unordered_map<int, void*> *)container;
            int hash_key = *(int *)key;
            utils_ds_hash->insert({hash_key, data});
            return 0;
        }            
        default:
            return -1;
    }
    return -1;
}

int utils_ds_cpp_hash_erase_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type, void *key, int key_len) {
    if(container == NULL) return -1;
    if(key == NULL) return -1;

    switch(type) {
        case UTILS_DS_CPP_HASH_KEY_STRING:
        {
            unordered_map<string, void*> *utils_ds_hash = (unordered_map<string, void*> *)container;
            char *string_key = static_cast<char*>(key);
            string hash_key(string_key, key_len); 
            utils_ds_hash->erase(hash_key);
            return 0;
        }            
        case UTILS_DS_CPP_HASH_KEY_INTEGER:
        {
            unordered_map<int, void*> *utils_ds_hash = (unordered_map<int, void*> *)container;
            int hash_key = *(int *)key;
            utils_ds_hash->erase(hash_key);
            return 0;
        }            
        default:
            return -1;
    }
    return -1;
}

// Caller needs to make sure that pos is valid
void* utils_ds_cpp_hash_lookup_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type, void *key, int key_len) {
    if(container == NULL) return NULL;
    if(key == NULL) return NULL;

    switch(type) {
        case UTILS_DS_CPP_HASH_KEY_STRING:
        {
            unordered_map<string, void*> *utils_ds_hash = (unordered_map<string, void*> *)container;
            char *string_key = static_cast<char*>(key);
            string hash_key(string_key, key_len);
            if(utils_ds_hash->find(hash_key) == utils_ds_hash->end()) {
                return NULL;
            }
            return utils_ds_hash->at(hash_key);
        }            
        case UTILS_DS_CPP_HASH_KEY_INTEGER:
        {
            unordered_map<int, void*> *utils_ds_hash = (unordered_map<int, void*> *)container;
            int hash_key = *(int *)key; 
            if(utils_ds_hash->find(hash_key) == utils_ds_hash->end()) {
                return NULL;
            }                
            return utils_ds_hash->at(hash_key);
        }            
        default:
            return NULL;
    }
    return NULL;
}

int utils_ds_cpp_hash_reset_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type) {
    if(container == NULL) return -1;
    
    switch(type) {
        case UTILS_DS_CPP_HASH_KEY_STRING:
        {
            unordered_map<string, void*> *utils_ds_hash = (unordered_map<string, void*> *)container;
            utils_ds_hash->clear();
            return 0;
        }            
        case UTILS_DS_CPP_HASH_KEY_INTEGER:
        {
            unordered_map<int, void*> *utils_ds_hash = (unordered_map<int, void*> *)container;
            utils_ds_hash->clear();
            return 0;
        }            
        default:
            return -1;
    }
   
    return -1;
}

void utils_ds_cpp_hash_destroy_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type) {
    if(container == NULL) return;

    switch(type) {
        case UTILS_DS_CPP_HASH_KEY_STRING:
        {
            unordered_map<string, void*> *utils_ds_hash = (unordered_map<string, void*> *)container;
            delete utils_ds_hash;
            return;
        }            
        case UTILS_DS_CPP_HASH_KEY_INTEGER:
        {
            unordered_map<int, void*> *utils_ds_hash = (unordered_map<int, void*> *)container;
            delete utils_ds_hash;
            return;
        }            
        default:
            return;
    }

    return;
}

int utils_ds_cpp_hash_get_size_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type) {
    if(container == NULL) return -1;

    switch(type) {
        case UTILS_DS_CPP_HASH_KEY_STRING:
        {
            unordered_map<string, void*> *utils_ds_hash = (unordered_map<string, void*> *)container;           
            return utils_ds_hash->size();
        }            
        case UTILS_DS_CPP_HASH_KEY_INTEGER:
        {
            unordered_map<int, void*> *utils_ds_hash = (unordered_map<int, void*> *)container;
            return utils_ds_hash->size();
        }            
        default:
            return -1;
    }

    return -1;

}

bool utils_ds_cpp_hash_isempty_container(void *container, UTILS_DS_CPP_HASH_KEY_TYPE type) {
    if(container == NULL) return true;

    switch(type) {
        case UTILS_DS_CPP_HASH_KEY_STRING:
        {
            unordered_map<string, void*> *utils_ds_hash = (unordered_map<string, void*> *)container;
            return utils_ds_hash->empty();
        }            
        case UTILS_DS_CPP_HASH_KEY_INTEGER:
        {
            unordered_map<int, void*> *utils_ds_hash = (unordered_map<int, void*> *)container;
            return utils_ds_hash->empty();
        }            
        default:
            return true;
    }

    return true;

}

} /* end of extern "C" */
