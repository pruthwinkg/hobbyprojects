/*******************************************************************************
    Description : Comm manager client library
          Note  : Clients modules should spwan a thread for communications 
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "comm_mgr_lib.h"
#include "comm_mgr_cmn.h"

// Do "make D=-DTEST_COMM_MGR_LIB" to generate the test app
#define TEST_COMM_MGR_LIB
#define TEST_UNIX_AF

#define TEST_COMM_MGR_LIB_UID   (10000)

#ifdef TEST_COMM_MGR_LIB

int main() {
    COMM_MGR_LIB_CLIENT client;
    COMM_MGR_LIB_ERR rc = COMM_MGR_LIB_SUCCESS;
    char buf[8096];
    char recv_buf[4096];
    COMM_MGR_MSG *comm_msg;
    int len = 0;

    comm_mgr_lib_init(LOG_LVL_DEBUG, TEST_COMM_MGR_LIB_UID);
    COMM_MGR_LIB_TRACE("Starting the test of %s\n", COMM_MGR_LIB_NAME);
#ifdef TEST_UNIX_AF
    memset(&client, 0, sizeof(COMM_MGR_LIB_CLIENT));
    client.clientAf = COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM;

    COMM_MGR_LIB_DEBUG("Starting %s test for COMM_MGR_IPC_LIB_AF_UNIX", COMM_MGR_LIB_NAME);

    COMM_MGR_LIB_CLIENT_ID cid = comm_mgr_lib_create_client(&client);

    if(cid == COMM_MGR_LIB_INVALID_CLIENT) { 
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x", COMM_MGR_LIB_NAME, rc);
        return -1;
    }

    COMM_MGR_LIB_DEBUG("Client created, id = %d. Ready to send data", cid);
    fflush(STDIN_FILENO);
    while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        if(comm_mgr_lib_send_data(cid, 1, buf, strlen(buf)) != COMM_MGR_LIB_SUCCESS ) {
            COMM_MGR_LIB_ERROR("Failed to send the data : %s", buf);
        }
        
        memset(buf, 0, sizeof(buf));
#if 1
       len = comm_mgr_lib_recv_data(cid, recv_buf, sizeof(recv_buf));
       if(len < 0) {
            COMM_MGR_LIB_ERROR("Failed to recv the data : %s", recv_buf);
            continue;
       }

       comm_msg = comm_mgr_get_msg(recv_buf, len);
       
       if (comm_msg == NULL) {
            COMM_MGR_LIB_ERROR("Received invalid data from Communication Manager");
            continue;
       }

       COMM_MGR_LIB_TRACE("Data received [%d]: msg_type [%d], submsg_type [%d], src_uid [%d], dst_uid [%d]", 
                                                    len, comm_msg->hdr.msg_type, comm_msg->hdr.submsg_type, 
                                                    comm_msg->hdr.src_uid, comm_msg->hdr.dst_uid);

       comm_mgr_print_msg_hdr(comm_msg, buf, sizeof(buf));
       COMM_MGR_LIB_PRINT("%s", buf); 

#endif       
    }
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
    return 0;
}

#endif
