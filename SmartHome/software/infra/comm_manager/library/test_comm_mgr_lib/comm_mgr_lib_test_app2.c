/*******************************************************************************
    Description : Comm manager client library
          Note  : Clients modules should spwan a thread for communications 
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "comm_mgr_lib_test_app.h"

// Do "make D=-DTEST_COMM_MGR_LIB" to generate the test app
#define TEST_COMM_MGR_LIB
#define TEST_UNIX_AF

#define TEST_COMM_MGR_LIB_SRC_UID   (1023) // Static UID
#define TEST_COMM_MGR_LIB_DST_UID   (1022) // Static UID

#define TEST_COMM_MGR_LIB_RECV_QUEUE_SIZE   (100)
#define TEST_COMM_MGR_LIB_SEND_QUEUE_SIZE   (100)

boolean comm_mgr_test_app_communication_on = FALSE;

#ifdef TEST_COMM_MGR_LIB

extern UTILS_TASK_HANDLER comm_mgr_test_app_workers[COMM_MGR_TEST_APP_TASK_ID_MAX];

int main() {
    COMM_MGR_LIB_CLIENT client;
    COMM_MGR_LIB_ERR rc = COMM_MGR_LIB_SUCCESS;
    char buf[8096];
    char recv_buf[4096];
    COMM_MGR_MSG *comm_msg;
    int len = 0;

    comm_mgr_lib_init(LOG_LVL_DEBUG, TEST_COMM_MGR_LIB_SRC_UID, FALSE);
    COMM_MGR_LIB_TRACE("Starting the test of %s for test-app-1\n", COMM_MGR_LIB_NAME);


#ifdef TEST_UNIX_AF
    memset(&client, 0, sizeof(COMM_MGR_LIB_CLIENT));
    client.clientAf = COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM;
    client.property = (COMM_MGR_LIB_CLIENT_PROPERTY*)malloc(sizeof(COMM_MGR_LIB_CLIENT_PROPERTY));
    client.property->app_cb = comm_mgr_lib_test_app_cb;
    client.property->comm_mgr_lib_recv_queue_size = TEST_COMM_MGR_LIB_RECV_QUEUE_SIZE;
    client.property->comm_mgr_lib_send_queue_size = TEST_COMM_MGR_LIB_SEND_QUEUE_SIZE;
    client.property->libInactivityTimeOut = COMM_MGR_LIB_DEFAULT_SELECT_TIMEOUT;
    COMM_MGR_LIB_DEBUG("Starting %s test for COMM_MGR_IPC_LIB_AF_UNIX", COMM_MGR_LIB_NAME);

    COMM_MGR_LIB_CLIENT_ID *cid = (COMM_MGR_LIB_CLIENT_ID *)malloc(sizeof(COMM_MGR_LIB_CLIENT_ID));
    
    *cid = comm_mgr_lib_create_client(&client);

    if(*cid == COMM_MGR_LIB_INVALID_CLIENT) { 
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x", COMM_MGR_LIB_NAME, rc);
        return -1;
    }


    /* Create task handlers for this test app */	
    comm_mgr_test_app_workers[COMM_MGR_TEST_APP_TASK_ID_COMM].arg = (void *)cid;
    comm_mgr_test_app_workers[COMM_MGR_TEST_APP_TASK_ID_HOUSEKEEPER].arg = (void *)cid;
    comm_mgr_test_app_workers[COMM_MGR_TEST_APP_TASK_ID_DATA_RECEIVER].arg = (void *)cid;
    
	if(utils_task_handlers_create(COMM_MGR_TEST_APP_TASK_ID_MAX, comm_mgr_test_app_workers, 
                                0, 0) < 0) {
		COMM_MGR_LIB_ERROR("Failed to create task handlers");
        goto err;
    }
    
    // Wait for all the task handlers to finish thier tasks
    utils_task_handlers_wait(COMM_MGR_TEST_APP_TASK_ID_MAX, comm_mgr_test_app_workers);

    if(rc != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x", COMM_MGR_LIB_NAME, rc);
    }
   
#else
    memset(&client, 0, sizeof(COMM_MGR_LIB_CLIENT));
    client.clientAf = COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM;
    client.server.h_name = "localhost";
    client.portNum = 5001;

    COMM_MGR_LIB_DEBUG("Starting %s test for COMM_MGR_IPC_LIB_AF_INET", COMM_MGR_LIB_NAME);

    cid = comm_mgr_lib_create_client(&client); 
    if(cid == COMM_MGR_LIB_INVALID_CLIENT) {
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_INET, rc = 0x%0x", COMM_MGR_LIB_NAME, rc);
        return -1;
    }
    
    COMM_MGR_LIB_DEBUG("Client created. Ready to send data");
    comm_mgr_lib_send_data(cid, "Hello. How r u", 20);
    while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        comm_mgr_lib_send_data(cid, buf, strlen(buf));
        memset(buf, 0, sizeof(buf));
    }
    if(rc != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_INET, rc = 0x%0x", COMM_MGR_LIB_NAME, rc);
    }


#endif

err:
    return 0;
}

// This task is purely for Communication purpose
void *comm_mgr_test_app_communication_handler(void *arg) {
    if(arg == NULL) {
        COMM_MGR_LIB_ERROR("Invalid cid");
        return NULL;
    }

    COMM_MGR_LIB_CLIENT_ID cid = *(uint16_t *)arg;

    COMM_MGR_LIB_ERR rc = COMM_MGR_LIB_SUCCESS;

    comm_mgr_test_app_communication_on = TRUE;
    rc = comm_mgr_lib_server_communicator(cid);
    comm_mgr_test_app_communication_on = FALSE;

    COMM_MGR_LIB_ERROR("Communication Manager Library - Server Communicator is exiting !!!!");
    return NULL;
}

// This task is for doing the house keeping tasks related to this app
// It can also request the data to be sent. It needs to notify the 
// Communication Handler
void *comm_mgr_test_app_housekeeper(void *arg) {
    if(arg == NULL) {
        COMM_MGR_LIB_ERROR("Invalid cid");
        return NULL;
    }

    COMM_MGR_LIB_CLIENT_ID cid = *(uint16_t *)arg;

    COMM_MGR_LIB_ERR rc = COMM_MGR_LIB_SUCCESS;
    char buf[8096];
    int len = 0;

    COMM_MGR_LIB_DEBUG("Client created, id = %d. Ready to send data", cid);

    fflush(STDIN_FILENO);
    while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        if (comm_mgr_test_app_communication_on == FALSE) {
            COMM_MGR_LIB_DEBUG("Communication System of this test app is not ON. Cannot send data. Exiting");
            break;
        }

        COMM_MGR_LIB_DEBUG("Sending data to dst_uid [%d], src_uid [%d]", 
                                    TEST_COMM_MGR_LIB_DST_UID, TEST_COMM_MGR_LIB_SRC_UID);
    
        if(comm_mgr_lib_send_data(cid, TEST_COMM_MGR_LIB_DST_UID, buf, strlen(buf)) != COMM_MGR_LIB_SUCCESS ) {
            COMM_MGR_LIB_ERROR("Failed to send the data : %s", buf);
        }
        memset(buf, 0, sizeof(buf));
    }
 
}

void *comm_mgr_test_app_data_receiver(void *arg) {
    if (arg == NULL) {
        COMM_MGR_LIB_ERROR("Invalid Client ID");
        return NULL;
    }   
    uint16_t cid = *(uint16_t *)arg;
    COMM_MGR_LIB_TRACE("Test-app-1 ready to handle housekeeping tasks from Client ID %d", cid);
  
    // The process thread should signal the response thread to go and read from protocol Queue
    boolean run_app_receiver_loop = TRUE;
    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;

    while(run_app_receiver_loop) {
       eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
       for (uint16_t i = 0; i < eventsRead; i++) {
            if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                comm_mgr_test_app_process_events(cid, FALSE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));    
            } else {
                comm_mgr_test_app_process_events(cid, TRUE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));
            }
       }
    }
}

COMM_MGR_LIB_TEST_APP_ERR comm_mgr_test_app_process_events(uint16_t cid, boolean isLocalMode, uint32_t event) {
    
    COMM_MGR_MSG *comm_msg;
    char buf[8096];
    
    COMM_MGR_APP_LOCAL_EVENT ev = (COMM_MGR_APP_LOCAL_EVENT)event;
    COMM_MGR_LIB_DEBUG("Processing the event = %d, mode = %s", 
                                            event, isLocalMode?"local":"global");

    switch(ev) {
        case COMM_MGR_APP_LOCAL_EVENT_DATA_RECV:
        {
            comm_msg = comm_mgr_lib_recv_data(cid);
           
            if (comm_msg == NULL) {
                COMM_MGR_LIB_ERROR("No data available from Communication Manager library");
                return COMM_MGR_LIB_TEST_APP_RECV_ERR; 
            }

            COMM_MGR_LIB_TRACE("Data received [%d]: msg_type [%d], submsg_type [%d], src_uid [%d], dst_uid [%d]", 
                                                        comm_msg->hdr.payloadSize, comm_msg->hdr.msg_type, comm_msg->hdr.submsg_type, 
                                                        comm_msg->hdr.src_uid, comm_msg->hdr.dst_uid);

            comm_mgr_print_msg_hdr(comm_msg, buf, sizeof(buf));
            COMM_MGR_LIB_PRINT("%s", buf);
        }
            break;        
        default:
           COMM_MGR_LIB_ERROR("Unknown app event");
           return COMM_MGR_LIB_TEST_APP_UNKNOWN_EVENT;
    }

    return COMM_MGR_LIB_TEST_APP_SUCCESS;
}

void comm_mgr_test_app_register_receiver_events(uint32_t taskID) {
    utils_task_handlers_register_event(COMM_MGR_APP_LOCAL_EVENT_DATA_RECV, taskID); 
}

/*
    Note : Do very minimal functionality here, since this runs in the context of
    the Library dedicated thread
*/
void comm_mgr_lib_test_app_cb(COMM_MGR_LIB_EVENT event) {
    COMM_MGR_APP_LOCAL_EVENT app_ev = COMM_MGR_APP_LOCAL_EVENT_MAX;
    boolean priority = FALSE;
    // Process the events first
    switch(event) {
        case COMM_MGR_LIB_EVENT_RECV_READY:
            COMM_MGR_LIB_DEBUG("Received the COMM_MGR_LIB_EVENT_RECV_READY from Comm Library"); 
            app_ev = COMM_MGR_APP_LOCAL_EVENT_DATA_RECV;
            break;
        default:
            COMM_MGR_LIB_ERROR("Invalid Communication Manager Library event");
            break;
    }

    // Enrich the information by optionally querying the COMM_MGR_LIB_STATUS
    //comm_mgr_lib_get_status();

    // Finally notify the other app-task handlers about this event (Send app specific events)
    if(app_ev != COMM_MGR_APP_LOCAL_EVENT_MAX) {
        utils_task_handlers_send_event(TRUE, app_ev, priority); 
    }
}

#endif /* TEST_COMM_MGR_LIB */
