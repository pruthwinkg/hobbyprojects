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

#define TEST_COMM_MGR_LIB_RECV_QUEUE_SIZE   (100)
#define TEST_COMM_MGR_LIB_SEND_QUEUE_SIZE   (100)

boolean comm_mgr_test_app_communication_on = FALSE;
INTERFACE_APP_CB intf_lib_app_cb;

uint8_t g_comm_mgr_lib_test_clients_num = 0;

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

    memset(&intf_lib_app_cb, 0, sizeof(INTERFACE_APP_CB));
    intf_lib_app_cb.text_cb = comm_mgr_lib_test_app_intf_text_cb;
    if(interface_lib_init(INTERFACE_LIB_SECURE_LEVEL_UNSECURE, &intf_lib_app_cb) != INTERFACE_LIB_SUCCESS) {
        COMM_MGR_LIB_TRACE("Failed to initialize the interface library");
    }

    COMM_MGR_LIB_TRACE("Starting the test of %s for %s\n", COMM_MGR_LIB_NAME, TEST_APP_NAME);


#ifdef TEST_UNIX_AF
    memset(&client, 0, sizeof(COMM_MGR_LIB_CLIENT));
    client.clientAf = COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM;
    client.advanced_en = FALSE;
    client.property = (COMM_MGR_LIB_CLIENT_PROPERTY*)malloc(sizeof(COMM_MGR_LIB_CLIENT_PROPERTY));
    client.property->app_cb = comm_mgr_lib_test_app_cb;
    client.property->comm_mgr_lib_recv_queue_size = TEST_COMM_MGR_LIB_RECV_QUEUE_SIZE;
    client.property->comm_mgr_lib_send_queue_size = TEST_COMM_MGR_LIB_SEND_QUEUE_SIZE;
    client.property->libInactivityTimeOut = COMM_MGR_LIB_DEFAULT_SELECT_TIMEOUT;
    COMM_MGR_LIB_DEBUG("Starting %s test for COMM_MGR_IPC_LIB_AF_UNIX", COMM_MGR_LIB_NAME);

    g_comm_mgr_lib_test_clients_num = 2;
    COMM_MGR_LIB_CLIENT_ID *cid = (COMM_MGR_LIB_CLIENT_ID *)malloc(sizeof(COMM_MGR_LIB_CLIENT_ID) * g_comm_mgr_lib_test_clients_num);
    
    cid[0] = comm_mgr_lib_create_client(&client);
    if(cid[0] == COMM_MGR_LIB_INVALID_CLIENT) { 
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x", COMM_MGR_LIB_NAME, rc);
        return -1;
    }

    // Create one more client for ancillary communciation
    client.advanced_en = TRUE;
    cid[1] = comm_mgr_lib_create_client(&client);
    if(cid[1] == COMM_MGR_LIB_INVALID_CLIENT) { 
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x", COMM_MGR_LIB_NAME, rc);
        return -1;
    }


    /* Create task handlers for this test app */	
    comm_mgr_test_app_workers[COMM_MGR_TEST_APP_TASK_ID_COMM].arg = (void *)&cid[0];
    comm_mgr_test_app_workers[COMM_MGR_TEST_APP_TASK_ID_ANC_COMM].arg = (void *)&cid[1];

    // These two workers can be loadshared
    comm_mgr_test_app_workers[COMM_MGR_TEST_APP_TASK_ID_HOUSEKEEPER].arg = (void *)cid;
    comm_mgr_test_app_workers[COMM_MGR_TEST_APP_TASK_ID_DATA_RECEIVER].arg = (void *)cid;
    
	if(utils_task_handlers_create(COMM_MGR_TEST_APP_TASK_ID_MAX, comm_mgr_test_app_workers, 
                                COMM_MGR_APP_LOCAL_EVENT_MAX, COMM_MGR_APP_GLOBAL_EVENT_MAX) < 0) {
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

    COMM_MGR_LIB_CLIENT_ID *cid = (uint16_t *)arg;

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
        if(!strncmp(buf, "file", 4)) { 
            if(comm_mgr_lib_send_data(cid[1], TEST_COMM_MGR_LIB_DST_UID, buf, strlen(buf)) != COMM_MGR_LIB_SUCCESS ) {
                COMM_MGR_LIB_ERROR("Failed to send the data");
            }
        } else {
            if(comm_mgr_lib_send_data(cid[0], TEST_COMM_MGR_LIB_DST_UID, buf, strlen(buf)) != COMM_MGR_LIB_SUCCESS ) {
                COMM_MGR_LIB_ERROR("Failed to send the data");
            }
        }
        memset(buf, 0, sizeof(buf));
    }
 
}

void *comm_mgr_test_app_data_receiver(void *arg) {
    if (arg == NULL) {
        COMM_MGR_LIB_ERROR("Invalid Client ID");
        return NULL;
    }   
    uint16_t *cid = (uint16_t *)arg;
    COMM_MGR_LIB_TRACE("%s ready to handle housekeeping tasks from Client ID %d", TEST_APP_NAME, cid);
  
    // The process thread should signal the response thread to go and read from protocol Queue
    boolean run_app_receiver_loop = TRUE;
    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;

    while(run_app_receiver_loop) {
       eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
       for (uint16_t i = 0; i < eventsRead; i++) {
            for (uint8_t j = 0; j < g_comm_mgr_lib_test_clients_num; j++) {
                if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                    comm_mgr_test_app_process_events(cid[j], FALSE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));    
                } else {
                    comm_mgr_test_app_process_events(cid[j], TRUE, UTILS_TASK_HANDLER_EVENT_GET(eventList[i]));
                }
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
            if(comm_msg->hdr.payloadSize) {
                COMM_MGR_LIB_PRINT("Payload : %s\n", comm_msg->payload);
            }

            comm_mgr_test_app_process_comm_msg(comm_msg); 
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
        if(utils_task_handlers_send_event(TRUE, app_ev, priority) < 0) {
            COMM_MGR_LIB_ERROR("Unable to send the event [%d]", app_ev);
        }
    }
}

/*

    For the interface library testing purpose, the payload is checked in a hardcoded fashion.
    <TODO> <TODO> We need to implement the SCOM/Overlay mechanism to make it generic across

*/
COMM_MGR_LIB_TEST_APP_ERR comm_mgr_test_app_process_comm_msg(COMM_MGR_MSG *comm_msg) {
    
    uint16_t word0 = *(uint16_t *)&(comm_msg->payload[0]);
    uint16_t req_uid = comm_msg->hdr.src_uid;
    uint16_t res_uid = comm_msg->hdr.dst_uid;
    uint16_t bufsize = comm_msg->hdr.payloadSize;
    char *buf = comm_msg->payload;

    if (word0 == 0xFACE) { // This is a interface message
        interface_lib_process_query(req_uid, res_uid, buf, bufsize);
    } else {
        COMM_MGR_LIB_DEBUG("Unknown type of payload");
    }

    return COMM_MGR_LIB_TEST_APP_SUCCESS;
}

/*
    Callback function for the Text type of Query from the Interface library.

    The response to the query needs to be filled in the buffer passed to us by the interface library. 
    The query format will be determined by the req_type. The response format is always determined by the
    callback we are getting. For example, in the below callback function we need to put the response
    back in regular text format.

    Also app needs to return the correct error codes. In case, if the response is to going to be too big to
    fit in the buffer passed by the interface library, then return INTERFACE_LIB_APP_RESPONSE_PENDING after 
    filling in partial response
*/
INTERFACE_LIB_ERR comm_mgr_lib_test_app_intf_text_cb(INTERFACE_LIB_QUERY_REQ_TYPE req_type, const char *query, 
                                                     char *buf, uint16_t bufsize) {
    
    if (query == NULL) {
        return INTERFACE_LIB_BAD_QUERY;
    }
    

    if (req_type == INTERFACE_LIB_QUERY_REQ_TYPE_TOKEN) {        
        uint16_t token = 0;
        uint8_t token_str_len = strlen(query);

        COMM_MGR_LIB_DEBUG("Received the token %s", query);

        return comm_mgr_lib_test_app_intf_process_token_query(token, buf, bufsize); 
    } else if (req_type == INTERFACE_LIB_QUERY_REQ_TYPE_FULL_QUERY) {
        return comm_mgr_lib_test_app_intf_process_full_query(query, buf, bufsize);
    } else {
        return INTERFACE_LIB_BAD_QUERY;
    }

    return INTERFACE_LIB_SUCCESS;
}

INTERFACE_LIB_ERR comm_mgr_lib_test_app_intf_process_token_query(uint16_t token, char *buf, uint16_t bufsize) {
    
    switch(token) {
        case 1:

        default:
            COMM_MGR_LIB_ERROR("Unknown token %d", token);
            return INTERFACE_LIB_BAD_QUERY;
    }
    return INTERFACE_LIB_SUCCESS;
}

INTERFACE_LIB_ERR comm_mgr_lib_test_app_intf_process_full_query(const char *query, char *buf, uint16_t bufsize) {

    return INTERFACE_LIB_SUCCESS;
}


#endif /* TEST_COMM_MGR_LIB */
