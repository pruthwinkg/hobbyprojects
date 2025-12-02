#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>
#include "id_manager.h"

#define TEST_MAX_IDS 100
#define TEST_START_ID 10

// Helper function to check if an ID is present in the allocated IDs
static bool is_id_present(utils_id_mgr_id *ids, int num_ids, utils_id_mgr_id target_id) {
    for (int i = 0; i < num_ids; i++) {
        if (ids[i] == target_id) {
            return true;
        }
    }
    return false;
}

// Test Case 1: Basic Allocation and Deallocation
void test_basic_allocation_deallocation() {
    UTILS_LOG_TRACE("Starting test_basic_allocation_deallocation");
    utils_id_mgr_token token;
    UTILS_ID_MGR_ERR err = utils_id_mgr_init(TEST_MAX_IDS, TEST_START_ID, &token);
    assert(err == UTILS_ID_MGR_SUCCESS);

    utils_id_mgr_id id1 = utils_id_mgr_alloc(token);
    assert(id1 != UTILS_ID_MGR_INVALID_ID);
    assert(id1 == TEST_START_ID);

    utils_id_mgr_id id2 = utils_id_mgr_alloc(token);
    assert(id2 != UTILS_ID_MGR_INVALID_ID);
    assert(id2 == TEST_START_ID+1);

    err = utils_id_mgr_free(token, id1);
    assert(err == UTILS_ID_MGR_SUCCESS);

    utils_id_mgr_id id3 = utils_id_mgr_alloc(token);
    assert(id3 != UTILS_ID_MGR_INVALID_ID);
    assert(id3 == TEST_START_ID); // Should be reused

    err = utils_id_mgr_free(token, id2);
    assert(err == UTILS_ID_MGR_SUCCESS);
    err = utils_id_mgr_free(token, id3);
    assert(err == UTILS_ID_MGR_SUCCESS);

    utils_id_mgr_destroy(token);
    UTILS_LOG_TRACE("Completed test_basic_allocation_deallocation");
}

// Test Case 2: Exhaustion of IDs
void test_id_exhaustion() {
    UTILS_LOG_TRACE("Starting test_id_exhaustion");
    utils_id_mgr_token token;
    UTILS_ID_MGR_ERR err = utils_id_mgr_init(TEST_MAX_IDS, TEST_START_ID, &token);
    assert(err == UTILS_ID_MGR_SUCCESS);

    utils_id_mgr_id ids[TEST_MAX_IDS];
    for (int i = 0; i < TEST_MAX_IDS; i++) {
        ids[i] = utils_id_mgr_alloc(token);
        assert(ids[i] != UTILS_ID_MGR_INVALID_ID);
        assert(ids[i] == TEST_START_ID+i);
    }

    utils_id_mgr_id id_fail = utils_id_mgr_alloc(token);
    assert(id_fail == UTILS_ID_MGR_NO_IDS_LEFT); // Should fail

    for (int i = 0; i < TEST_MAX_IDS; i++) {
        err = utils_id_mgr_free(token, ids[i]);
        assert(err == UTILS_ID_MGR_SUCCESS);
    }
    utils_id_mgr_destroy(token);
    UTILS_LOG_TRACE("Completed test_id_exhaustion");
}

// Test Case 3: Invalid ID Deallocation
void test_invalid_id_deallocation() {
    UTILS_LOG_TRACE("Starting test_invalid_id_deallocation");
    utils_id_mgr_token token;
    UTILS_ID_MGR_ERR err = utils_id_mgr_init(TEST_MAX_IDS, TEST_START_ID, &token);
    assert(err == UTILS_ID_MGR_SUCCESS);

    utils_id_mgr_id id1 = utils_id_mgr_alloc(token);
    assert(id1 != UTILS_ID_MGR_INVALID_ID);

    err = utils_id_mgr_free(token, 9999); // Invalid ID
    assert(err == UTILS_ID_MGR_INVALID_ID);

    err = utils_id_mgr_free(token, id1);
    assert(err == UTILS_ID_MGR_SUCCESS);
    err = utils_id_mgr_free(token, id1); //Double free
    assert(err == UTILS_ID_MGR_SUCCESS);

    // Now allocate again
    utils_id_mgr_id id2 = utils_id_mgr_alloc(token);
    assert(id2 != UTILS_ID_MGR_INVALID_ID);
    assert(id2 == TEST_START_ID); // ID should be reused

    utils_id_mgr_destroy(token);
    UTILS_LOG_TRACE("Completed test_invalid_id_deallocation");
}

// Test Case 4: Multiple Id managers.
void test_multiple_id_managers() {
    UTILS_LOG_TRACE("Starting test_multiple_id_managers");
    utils_id_mgr_token token1, token2;
    UTILS_ID_MGR_ERR err = utils_id_mgr_init(TEST_MAX_IDS, TEST_START_ID, &token1);
    assert(err == UTILS_ID_MGR_SUCCESS);
    err = utils_id_mgr_init(TEST_MAX_IDS, TEST_START_ID+TEST_MAX_IDS, &token2);
    assert(err == UTILS_ID_MGR_SUCCESS);

    utils_id_mgr_id id1 = utils_id_mgr_alloc(token1);
    assert(id1 != UTILS_ID_MGR_INVALID_ID);
    assert(id1 == TEST_START_ID);
    utils_id_mgr_id id2 = utils_id_mgr_alloc(token2);
    assert(id2 != UTILS_ID_MGR_INVALID_ID);
    assert(id2 == TEST_START_ID+TEST_MAX_IDS);

    err = utils_id_mgr_free(token1, id1);
    assert(err == UTILS_ID_MGR_SUCCESS);
    err = utils_id_mgr_free(token2, id2);
    assert(err == UTILS_ID_MGR_SUCCESS);

    utils_id_mgr_destroy(token1);
    utils_id_mgr_destroy(token2);
    UTILS_LOG_TRACE("Completed test_multiple_id_managers");
}

// Test Case 5: Test with invalid token address
void test_invalid_token() {
    LOG_TRACE("Starting test_invalid_token_address");
    utils_id_mgr_token token;
    UTILS_ID_MGR_ERR err = utils_id_mgr_init(TEST_MAX_IDS, TEST_START_ID, &token);
    assert(err == UTILS_ID_MGR_SUCCESS);

    // Test with arbitrary invalid addresses
    utils_id_mgr_id id1 = utils_id_mgr_alloc(MAX_TOKENS+1);// Invalid token index
    assert(id1 == UTILS_ID_MGR_INVALID_ID);

    err = utils_id_mgr_free(MAX_TOKENS+1, id1); //Invalid token index
    assert(err == UTILS_ID_MGR_INVALID_ID);

    utils_id_mgr_destroy(token);
    LOG_TRACE("Completed test_invalid_token_address");
}

int main() {
    log_lib_init(NULL, LOG_LVL_DEBUG);
    test_basic_allocation_deallocation();
    test_id_exhaustion();
    test_invalid_id_deallocation();
    test_multiple_id_managers();
    test_invalid_token();
    return 0;
}