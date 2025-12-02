#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>


#if LOCAL_COMM

#define SOCKET_FILE_PATH  "server.socket"


int main() {
    printf("This is Client example code\n");

    struct sockaddr_un addr;
    char buf[100];
    int fd,rc;
	int len = 0;
    
    if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_FILE_PATH); 
    len = sizeof(addr);

	if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		perror("connect error");
		exit(-1);
	}    

	while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
		if (write(fd, buf, rc) != rc) {
			if (rc > 0) fprintf(stderr,"partial write");
		  	else {
				perror("write error");
				exit(-1);
		  	}
		}
	}	

    return 0;
}

#else

int main(int argc, char *argv[]) {
    printf("This is Internet Client example code\n");

    struct sockaddr_in addr;
    struct hostent *server;
	int portno = 6001; // Server port number

    char buf[100];
    int fd,rc;
	int len = 0;
    
    if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(-1);
    }
    
    //server = gethostbyname(argv[1]);
    server = gethostbyname("localhost");

   	if (server == NULL) {
    	fprintf(stderr,"ERROR, no such host\n");
      	exit(0);
   	}
    
    printf("Server address : %s : %d\n", 
                    inet_ntoa(*(struct in_addr*) server->h_addr), portno);

    memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	memcpy((char *)&addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);	
	addr.sin_port = htons(portno);

	if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		perror("connect error");
		exit(-1);
	}    

	while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
		if (write(fd, buf, rc) != rc) {
			if (rc > 0) fprintf(stderr,"partial write");
		  	else {
				perror("write error");
				exit(-1);
		  	}
		}
	}	

    return 0;

}

#endif
