/*******************************************************************************
    Description : Comm manager client library
          Note  : Clients modules should spwan a thread for communications 
*******************************************************************************/
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "comm_mgr_lib.h"
#include "../comm_mgr_cmn.h"

COMM_MGR_LIB_ERR comm_mgr_lib_create_client(COMM_MGR_LIB_CLIENT *client) {
    struct sockaddr_un un_addr;
    struct sockaddr_in in_addr;
    int fd;

    if (client == NULL) {
        return COMM_MGR_LIB_INVALID_ARG;
    }

    client->__clientReady = 0;

    switch(client->clientAf) {
        case COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM:
            {
                if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
                    perror("socket error");
                    return COMM_MGR_LIB_SOCKET_CREATE_ERR;
                }
                memset(&un_addr, 0, sizeof(un_addr));
                un_addr.sun_family = AF_UNIX;
                strcpy(un_addr.sun_path, SOCKET_FILE_PATH); 

                if (connect(fd, (struct sockaddr*)&un_addr, sizeof(un_addr)) == -1) {
                    perror("connect error");
                    return COMM_MGR_LIB_CONNECT_ERR;
                } 
            }
            break;
        case COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM:
            {
                struct hostent *server = &(client->server);

                if (server == NULL) {
                    COMM_MGR_LIB_ERROR("Invalid Server\n");
                    return COMM_MGR_LIB_INVALID_ARG;
                }

                if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                    perror("socket error");
                    return COMM_MGR_LIB_SOCKET_CREATE_ERR;
                }
                
                if (server->h_name) { // If Only h_name is supplied
                    server = gethostbyname(server->h_name);
                }

                if (server == NULL) {
                    fprintf(stderr,"ERROR, no such host\n");
                    return COMM_MGR_LIB_BAD_SERVER;
                }
                                
                COMM_MGR_LIB_DEBUG("Server address : %s : %d\n", 
                                    inet_ntoa(*(struct in_addr*) server->h_addr), client->portNum);


                memset(&in_addr, 0, sizeof(in_addr));
                in_addr.sin_family = AF_INET;
                memcpy((char *)&in_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);	
                in_addr.sin_port = htons(client->portNum);

                if (connect(fd, (struct sockaddr*)&in_addr, sizeof(in_addr)) == -1) {
                    perror("connect error");
                    return COMM_MGR_LIB_CONNECT_ERR;
                }
            }    
            break;
        default:
            COMM_MGR_LIB_ERROR("Unknown AF type");
            return COMM_MGR_LIB_UNKNOWN_AF_TYPE;
            break;
    }
   
    client->__fd = fd;
    client->__clientReady = 1;
	
    return COMM_MGR_LIB_SUCCESS;    
}


COMM_MGR_LIB_ERR comm_mgr_lib_send_data(COMM_MGR_LIB_CLIENT *client, char *msg, int len) {
    struct hostent *server = &(client->server);

    if ((client == NULL) || (msg == NULL)) {
        return COMM_MGR_LIB_INVALID_ARG;
    }

    if(!client->__clientReady) {
        COMM_MGR_LIB_ERROR("Client is not yet created\n");
        return COMM_MGR_LIB_CLIENT_NOT_CREATED;
    }
 
    if (client->clientAf == COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM) {
        if (client->server.h_name) { // If Only h_name is supplied
            server = gethostbyname(server->h_name);
        }   
        COMM_MGR_LIB_DEBUG("Server address : %s : %d\n", 
                                        inet_ntoa(*(struct in_addr*) (server->h_addr)), client->portNum);
    } else {
        COMM_MGR_LIB_DEBUG("Sending via Unix Domain Socket\n");
    }
    COMM_MGR_LIB_DEBUG("Sending msg [%s] to fd [%d]\n", msg, client->__fd);

    if (send(client->__fd, msg, len, 0) == -1) {
        COMM_MGR_LIB_ERROR("Send error\n");
        return COMM_MGR_LIB_SEND_ERR;        
    }
    return COMM_MGR_LIB_SUCCESS;
}




#if 0

#ifdef TEST_COMM_MGR_LIB // To be passed via gcc

int main(int argc, char *argv[]) {
    COMM_MGR_LIB_CLIENT client;
    COMM_MGR_LIB_ERR rc = COMM_MGR_LIB_SUCCESS;
    char buf[4096];

#ifdef TEST_UNIX_AF
    memset(&client, 0, sizeof(COMM_MGR_LIB_CLIENT));
    client.clientAf = COMM_MGR_LIB_IPC_AF_UNIX_SOCK_STREAM;

    COMM_MGR_LIB_DEBUG("Starting comm_ger_lib test for COMM_MGR_IPC_LIB_AF_UNIX\n");

    rc = comm_mgr_lib_create_client(&client);
    if(rc != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Comm_mgr test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x\n", rc);
    }

    COMM_MGR_LIB_DEBUG("Client created. Ready to send data\n");
    while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        comm_mgr_lib_send_data(&client, buf, strlen(buf));
        memset(buf, 0, sizeof(buf));
    }
    if(rc != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Comm_mgr test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x\n", rc);
    }
   
#else
    memset(&client, 0, sizeof(COMM_MGR_LIB_CLIENT));
    client.clientAf = COMM_MGR_LIB_IPC_AF_INET_SOCK_STREAM;
    client.server.h_name = "localhost";
    client.portNum = 5001;

    COMM_MGR_LIB_DEBUG("Starting comm_ger_lib test for COMM_MGR_IPC_LIB_AF_INET\n");

    rc = comm_mgr_lib_create_client(&client); 
    if(rc != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Comm_mgr test failed for COMM_MGR_IPC_LIB_AF_INET, rc = 0x%0x\n", rc);
    }
    
    COMM_MGR_LIB_DEBUG("Client created. Ready to send data\n");
    comm_mgr_lib_send_data(&client, "Hello. How r u", 20);
    while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        comm_mgr_lib_send_data(&client, buf, strlen(buf));
        memset(buf, 0, sizeof(buf));
    }
    if(rc != COMM_MGR_LIB_SUCCESS) {
        COMM_MGR_LIB_ERROR("Comm_mgr test failed for COMM_MGR_IPC_LIB_AF_UNIX, rc = 0x%0x\n", rc);
    }


#endif
    return 0;
}

#endif

#endif
