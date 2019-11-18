// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 12345 

int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in6 serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    char buf[1024] = {0};
    int rc = 0;  
    if ((sock = socket(AF_INET6, SOCK_STREAM, 0)) < 0)  
    {   
        printf("\n Socket creation error \n"); 
        return -1; 
    }   

    serv_addr.sin6_family = AF_INET6; 
    serv_addr.sin6_port = htons(PORT); 
    
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET6, "::1", &serv_addr.sin6_addr.s6_addr)<=0) 
    {   
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    }   

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
