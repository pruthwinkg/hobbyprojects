/*******************************************************************************
    Description : ID manager heade file
    
    Note : This implements ID management for various apps. Currently  it generates 
           only simple sequential integer IDs. 
           
           TODO: It can be extended to generate complex IDs as well.

*******************************************************************************/

#ifndef INCLUDE_UTILS_IDMANAGER_H__
#define INCLUDE_UTILS_IDMANAGER_H__

#include "smarthome_essentials.h"
#include "logging.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define UTILS_LOG_ERROR  LOG_ERROR
#define UTILS_LOG_TRACE  LOG_TRACE
#define UTILS_LOG_DEBUG  LOG_DEBUG

#define MAX_TOKENS  (10) // Max ID managers per app

typedef uint32_t utils_id_mgr_id;
typedef uint8_t utils_id_mgr_token;

typedef enum {
    UTILS_ID_MGR_SUCCESS = 0,
    UTILS_ID_MGR_INIT_FAILED = -1,
    UTILS_ID_MGR_NO_IDS_LEFT = -2,
    UTILS_ID_MGR_INVALID_ID = -3
} UTILS_ID_MGR_ERR;

typedef struct {
    pthread_mutex_t mutex;      // Mutex for thread safety
    utils_id_mgr_id   start_id;        // start ID to be allocated
    utils_id_mgr_id   max_id;         // Maximum id allowed
    utils_id_mgr_id  num_ids_allocated; // Number of IDs allocated
    boolean     *used_ids;      // Array to track used IDs
} UTILS_ID_MANAGER;

/*******************************************************************************/
/*              Internal Functions                                               */
/*******************************************************************************/
static int __utils_id_mgr_get_free_token_index();
static boolean __utils_id_mgr_is_valid_token(utils_id_mgr_token token);


/*******************************************************************************/
/*              Public Functions                                               */
/*******************************************************************************/


/**
 * @brief Initializes the ID manager.
 *
 * @param max_ids The maximum number of IDs that can be allocated.
 * @param start_id The ID to start allocating from.
 * @param token The token to be used for future operations. Used if the app needs 
 *  to manage multiple ID managers for generating different types of IDs.
 * @return ID_MGR_SUCCESS on success, an error code otherwise.
 */
UTILS_ID_MGR_ERR utils_id_mgr_init(uint32_t max_ids, uint32_t start_id, utils_id_mgr_token *token);

/**
 * @brief Allocates a new unique ID.
 *
 * @return A unique ID on success, ID_MGR_INVALID_ID on failure.
 */
utils_id_mgr_id utils_id_mgr_alloc(utils_id_mgr_token token);

/**
 * @brief Deallocates an ID, making it available for reuse.
 *
 * @param id The ID to deallocate.
 * @return ID_MGR_SUCCESS on success, ID_MGR_INVALID_ID if the ID is invalid.
 */
UTILS_ID_MGR_ERR utils_id_mgr_free(utils_id_mgr_token token, utils_id_mgr_id id);

/**
 * @brief Destroys the ID manager.
 */
void utils_id_mgr_destroy(utils_id_mgr_token token);


#endif /* INCLUDE_UTILS_IDMANAGER_H__ */