/*******************************************************************************
    Description : Comm manager client library
          Note  : Clients modules should spwan a thread for communications 
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../comm_mgr_lib.h"
#include "../../comm_mgr_cmn.h"

// Do "make D=-DTEST_COMM_MGR_LIB" to generate the test app
#define TEST_COMM_MGR_LIB
#define TEST_UNIX_AF

#ifdef TEST_COMM_MGR_LIB

int main() {
    COMM_MGR_LIB_CLIENT client;
    COMM_MGR_LIB_ERR rc = COMM_MGR_LIB_SUCCESS;
    char buf[4096];

    COMM_MGR_LIB_TRACE("Starting the test of %s\n", COMM_MGR_LIB_NAME);

#ifdef TEST_UNIX_AF
    memset(&client, 0, sizeof(COMM_MGR_LIB_CLIENT));
    client.clientAf = COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM;

    COMM_MGR_LIB_DEBUG("Starting %s test for COMM_MGR_IPC_LIB_AF_UNIX\n", COMM_MGR_LIB_NAME);

    rc = comm_mgr_lib_create_client(&client);
    if(rc != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x\n", COMM_MGR_LIB_NAME, rc);
    }

    COMM_MGR_LIB_DEBUG("Client created. Ready to send data\n");
    while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        comm_mgr_lib_send_data(&client, buf, strlen(buf));
        memset(buf, 0, sizeof(buf));
    }
    if(rc != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x\n", COMM_MGR_LIB_NAME, rc);
    }
   
#else
    memset(&client, 0, sizeof(COMM_MGR_LIB_CLIENT));
    client.clientAf = COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM;
    client.server.h_name = "localhost";
    client.portNum = 5001;

    COMM_MGR_LIB_DEBUG("Starting %s test for COMM_MGR_IPC_LIB_AF_INET\n", COMM_MGR_LIB_NAME);

    rc = comm_mgr_lib_create_client(&client); 
    if(rc != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_INET, rc = 0x%0x\n", COMM_MGR_LIB_NAME, rc);
    }
    
    COMM_MGR_LIB_DEBUG("Client created. Ready to send data\n");
    comm_mgr_lib_send_data(&client, "Hello. How r u", 20);
    while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        comm_mgr_lib_send_data(&client, buf, strlen(buf));
        memset(buf, 0, sizeof(buf));
    }
    if(rc != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("%s test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x\n", COMM_MGR_LIB_NAME, rc);
    }


#endif
    return 0;
}

#endif
