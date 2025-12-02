// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <sys/un.h>
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>

#define PORT 12345 
#define SOCKET_FILE_PATH "test.server.socket"

int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_un serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    char buf[1024] = {0};
    int rc = 0;  
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)  
    {   
        printf("\n Socket creation error \n"); 
        return -1; 
    }   

    serv_addr.sun_family = AF_UNIX; 
    strcpy(serv_addr.sun_path, SOCKET_FILE_PATH);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)  
    {   
        printf("\nConnection Failed \n"); 
        return -1; 
    }   

    send(sock , hello , strlen(hello) , 0 );  
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer );  


    while((rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        send(sock , buf , strlen(buf) , 0 );
        memset(buf, 0, sizeof(buf));
    }   
 
    return 0;  
} 
