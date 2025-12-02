/*****************************************************************************
    Descritpion : This implements ID management for various apps. 
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "id_manager.h"

// Internal table to hold the UTILS_ID_MANAGER pointers
static UTILS_ID_MANAGER *id_mgr_table[MAX_TOKENS];
static int num_id_managers = 0;

UTILS_ID_MGR_ERR utils_id_mgr_init(uint32_t max_ids, uint32_t start_id, utils_id_mgr_token *token) {
    UTILS_ID_MANAGER *id_mgr = (UTILS_ID_MANAGER *)malloc(sizeof(UTILS_ID_MANAGER));
    if (id_mgr == NULL) {
        UTILS_LOG_ERROR("Failed to malloc ID_MANAGER");
        return UTILS_ID_MGR_INIT_FAILED;
    }

    int free_token = __utils_id_mgr_get_free_token_index();
    if (free_token < 0) {
        UTILS_LOG_ERROR("Max number of id_managers reached");
        free(id_mgr);
        return UTILS_ID_MGR_INIT_FAILED; // Out of tokens
    }

    pthread_mutex_init(&id_mgr->mutex, NULL);
    id_mgr->start_id = start_id; // First id.
    id_mgr->max_id = max_ids;// Last id
    id_mgr->num_ids_allocated = 0; //Initialize to 0
    id_mgr->used_ids = (boolean *)calloc(max_ids, sizeof(boolean)); // Max mids
    if(id_mgr->used_ids == NULL){
        UTILS_LOG_ERROR("Failed to init used_ids");
        pthread_mutex_destroy(&id_mgr->mutex);
        free(id_mgr);
        return UTILS_ID_MGR_INIT_FAILED;
    }
    id_mgr_table[free_token] = id_mgr;
    *token = free_token; // Return the index as the token
    num_id_managers++;

    UTILS_LOG_DEBUG("ID manager initialized with max_ids=%u, start_id=%u", max_ids, start_id);

    return UTILS_ID_MGR_SUCCESS;
}

utils_id_mgr_id utils_id_mgr_alloc(utils_id_mgr_token token) {
    utils_id_mgr_id id;
    int i = 0;

    //Check if the token is valid
    if (!__utils_id_mgr_is_valid_token(token)) {
        UTILS_LOG_ERROR("Invalid token passed");
        return UTILS_ID_MGR_INVALID_ID;
    }

    UTILS_ID_MANAGER *id_mgr = id_mgr_table[token];

    //Critical section starts
    pthread_mutex_lock(&id_mgr->mutex); 

    // Check for exhaustion before search
    if(id_mgr->num_ids_allocated == id_mgr->max_id) {
        pthread_mutex_unlock(&id_mgr->mutex);
        UTILS_LOG_ERROR("No available IDs left");
        return UTILS_ID_MGR_NO_IDS_LEFT;
    }

    //Find the next available ID
    for(i = 0; i < id_mgr->max_id; i++){
        if(id_mgr->used_ids[i] == FALSE) { //Find the next available ID
             id_mgr->used_ids[i] = TRUE; // mark as used
             id = i + id_mgr->start_id;
             id_mgr->num_ids_allocated++; //Increment the counter
             break;
        }
    }

    pthread_mutex_unlock(&id_mgr->mutex); //Critical section ends

    UTILS_LOG_TRACE("ID %u allocated", id);

    return id;
}

UTILS_ID_MGR_ERR utils_id_mgr_free(utils_id_mgr_token token, utils_id_mgr_id id) {
    // Check if the token is valid
    if (!__utils_id_mgr_is_valid_token(token)) {
        UTILS_LOG_ERROR("Invalid token passed");
        return UTILS_ID_MGR_INVALID_ID;
    }

    UTILS_ID_MANAGER *id_mgr = id_mgr_table[token];

    pthread_mutex_lock(&id_mgr->mutex); //Critical section starts

    // Mark the ID as unused
    if (id >= (id_mgr->max_id + id_mgr->start_id)) {
        UTILS_LOG_ERROR("Invalid ID passed %d", id);
        pthread_mutex_unlock(&id_mgr->mutex); //Critical section ends
        return UTILS_ID_MGR_INVALID_ID;
    }
    uint32_t index = id - id_mgr->start_id;
    if(id_mgr->used_ids[index] == FALSE) {
        UTILS_LOG_ERROR("ID %u already free. Cannot be freed again", id);
        pthread_mutex_unlock(&id_mgr->mutex); //Critical section ends
        return UTILS_ID_MGR_SUCCESS; // Return success because it is correct
    }
    
    id_mgr->used_ids[index] = FALSE;
    id_mgr->num_ids_allocated--; // Decrement the counter

    pthread_mutex_unlock(&id_mgr->mutex); //Critical section ends
    UTILS_LOG_TRACE("ID %u freed", id);
    return UTILS_ID_MGR_SUCCESS;
}

void utils_id_mgr_destroy(utils_id_mgr_token token) {
    //Check if the token is valid
    if (!__utils_id_mgr_is_valid_token(token)) {
        UTILS_LOG_ERROR("Invalid token passed");
        return;
    }

    UTILS_ID_MANAGER *id_mgr = id_mgr_table[token];
    id_mgr_table[token] = NULL;
    num_id_managers--;

    pthread_mutex_destroy(&id_mgr->mutex);
    free(id_mgr->used_ids);
    free(id_mgr);
    id_mgr_table[token] = NULL; // Clear the table entry
    UTILS_LOG_DEBUG("ID manager destroyed");
}

/*******************************************************************************/
/*              Internal Functions                                               */
/*******************************************************************************/
// Internal function to find a free slot in the token table
static int __utils_id_mgr_get_free_token_index() {
    // Early check
    if (num_id_managers == MAX_TOKENS) {
        return -1; // All tokens are used
    }
    
    for (int i = 0; i < MAX_TOKENS; i++) {
        if (id_mgr_table[i] == NULL) {
            return i; // Found a free slot
        }
    }
    return -1; // No free slots
}

static boolean __utils_id_mgr_is_valid_token(utils_id_mgr_token token) {
    if(token >= MAX_TOKENS) {
        return FALSE;
    }
    if (id_mgr_table[token] == NULL) {
        return FALSE;
    }
    return TRUE;
}