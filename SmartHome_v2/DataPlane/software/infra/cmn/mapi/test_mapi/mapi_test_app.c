/*******************************************************************************
    Description: Test application to demonstrate the MAPI library usage
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "mapi.h"

#ifdef TEST_APP_1
#define TEST_COMM_MGR_LIB_SRC_UID   (1022) // Static UID
#define TEST_COMM_MGR_LIB_DST_UID   (1023) // Static UID
#define TEST_APP_NAME   "Test-app-1"
#endif

#ifdef TEST_APP_2
#define TEST_COMM_MGR_LIB_SRC_UID   (1023) // Static UID
#define TEST_COMM_MGR_LIB_DST_UID   (1022) // Static UID
#define TEST_APP_NAME   "Test-app-2"
#endif

void* test_app_mapi_startup_fn(void *arg);
void test_app_mapi_rcv_cb(char *buffer, uint32_t buflen);

void* test_app_mapi_startup_fn(void *arg) {
    if(arg == NULL) return NULL;
    mapiID mid = *(mapiID *)arg;
    MAPI_LIB_ERR rc = mapi_start_mid(mid);
    return NULL;
}

void test_app_mapi_rcv_cb(char *buffer, uint32_t buflen) {
    MAPI_LOG_TRACE("Received a packet from the MAPI library of len = %d", buflen);
    MAPI_MSG_HDR hdr = MAPI_GET_MSG_HDR(buffer);
    char *payload = MAPI_GET_MSG_PAYLOAD(buffer);
    MAPI_LOG_TRACE("Received a packet from the MAPI library with src_uid = %d, dst_uid = %d", hdr.src_uid, hdr.dst_uid);
}


void test_app_mapi_dgram(uint8_t num_mids, uint16_t *port_nums) {
    MAPI_USER_INFO user_info;
    user_info.sock_type = MAPI_LIB_SOCK_TYPE_SOCK_DGRAM;
    user_info.reuseaddr = TRUE;
    user_info.nonblockingIO = TRUE;
    user_info.use_epoll = FALSE;
    user_info.rcv_cb = test_app_mapi_rcv_cb;
    void *ret;
    MAPI_DEST_INFO dst_info;

    pthread_t *thread_id = (pthread_t *)malloc(sizeof(pthread_t) * num_mids);
    char buffer[512];
    int counter = 0;
    mapiID *mid = (mapiID *)malloc(sizeof(mapiID) * num_mids);

    for(int m = 0; m < num_mids; m++) {
        user_info.sub_mid = m;
        user_info.port_num = port_nums[m];
        mid[m] = mapi_create_mid(&user_info);
        if(mid[m] == MAPI_INVALID_ID) {
            MAPI_LOG_ERROR("Failed to test");
            return;
        }

        pthread_create(&thread_id[m], NULL, test_app_mapi_startup_fn, (void *)&mid[m]);

        dst_info.dst_sub_mid = m;
        dst_info.dst_ip = 0;
        dst_info.dst_port = 0;
        dst_info.dst_uid = TEST_COMM_MGR_LIB_DST_UID;
    }

    memset(buffer, 0, sizeof(buffer));
    while(counter < 10) {
        sleep(2);
        sprintf(buffer, "Testing MAPI - %d time, src_uid = %d, dst_uid = %d", 
                            counter, TEST_COMM_MGR_LIB_SRC_UID, TEST_COMM_MGR_LIB_DST_UID);
        MAPI_LOG_TRACE("Sending the data = %s, %d\n", buffer, strlen(buffer));
        if(mapi_send(mid[0], &dst_info, 0, buffer, strlen(buffer)) != MAPI_LIB_SUCCESS) {
            MAPI_LOG_ERROR("Failed to send the data");
        }
        counter++;
    }

    for(int m = 0; m < num_mids; m++) {
        mapi_destroy(mid[m]);
        pthread_cancel(thread_id[m]);
        pthread_join(thread_id[m], &ret);    
    }

    free(mid);
}

void test_app_mapi_stream(uint8_t num_mids, uint16_t *port_nums) {
    MAPI_USER_INFO user_info;
    user_info.sock_type = MAPI_LIB_SOCK_TYPE_SOCK_STREAM;
    user_info.reuseaddr = TRUE;
    user_info.nonblockingIO = TRUE;
    user_info.use_epoll = FALSE;
    user_info.rcv_cb = test_app_mapi_rcv_cb;
    void *ret;
    MAPI_DEST_INFO dst_info;

    pthread_t *thread_id = (pthread_t *)malloc(sizeof(pthread_t) * num_mids);
    char buffer[512];
    int counter = 0;
    mapiID *mid = (mapiID *)malloc(sizeof(mapiID) * num_mids);

    for(int m = 0; m < num_mids; m++) {
        user_info.sub_mid = m;
        user_info.port_num = port_nums[m];
        mid[m] = mapi_create_mid(&user_info);
        if(mid[m] == MAPI_INVALID_ID) {
            MAPI_LOG_ERROR("Failed to test");
            return;
        }
        MAPI_LOG_TRACE("Created MAPI ID = 0x%0x", mid[m]);

        pthread_create(&thread_id[m], NULL, test_app_mapi_startup_fn, (void *)&mid[m]);
    }
   
#ifdef TEST_APP_1   
    dst_info.dst_sub_mid = 0;
    dst_info.dst_ip = 0;
    dst_info.dst_port = 0;
    dst_info.dst_uid = TEST_COMM_MGR_LIB_DST_UID;

    mapi_set_stream_store_type(mid[0], MAPI_STREAM_STORE_QUEUE, 0);
    mapi_start_stream(mid[0], &dst_info);

    memset(buffer, 0, sizeof(buffer));

    while(counter < 10) {
        sleep(2);
        sprintf(buffer, "Testing MAPI - %d time, src_uid = %d, dst_uid = %d", 
                            counter, TEST_COMM_MGR_LIB_SRC_UID, TEST_COMM_MGR_LIB_DST_UID);
        if(mapi_send(mid[0], &dst_info, 0, buffer, strlen(buffer)) != MAPI_LIB_SUCCESS) {
            MAPI_LOG_ERROR("Failed to send the data");
        }
        counter++;
    }

    mapi_stop_stream(mid[0], &dst_info);

    for(int m = 0; m < num_mids; m++) {
        mapi_destroy(mid[m]);
        pthread_cancel(thread_id[m]);
        pthread_join(thread_id[m], &ret);    
    }   
#endif

#ifdef TEST_APP_2
    while(1);
#endif

    free(mid);
}

#define TEST_MAPI_DGRAM_NUM_MIDS    1
#define TEST_MAPI_STREAM_NUM_MIDS   1

#define MAPI_DGRAM_TEST 1
#define MAPI_STREAM_TEST 0


int main() {   

    mapi_init(LOG_LVL_DEBUG, TEST_COMM_MGR_LIB_SRC_UID, 0);

    MAPI_LOG_TRACE("Starting the test of %s for %s", MAPI_LIB_NAME, TEST_APP_NAME);

#if MAPI_DGRAM_TEST
    uint16_t port_nums[TEST_MAPI_DGRAM_NUM_MIDS] = {5000};
    test_app_mapi_dgram(TEST_MAPI_DGRAM_NUM_MIDS, port_nums);
#endif


#if MAPI_STREAM_TEST
#ifdef TEST_APP_1  
    uint16_t stream_port_nums[TEST_MAPI_STREAM_NUM_MIDS] = {8000};
#endif
#ifdef TEST_APP_2 
    uint16_t stream_port_nums[TEST_MAPI_STREAM_NUM_MIDS] = {8002};
#endif    

    test_app_mapi_stream(TEST_MAPI_STREAM_NUM_MIDS, stream_port_nums);
#endif

    return 0;
}


