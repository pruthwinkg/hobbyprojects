#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

//#define LOCAL_COMM

#ifdef LOCAL_COMM 

#define SOCKET_FILE_PATH  "server.socket"

int main() {
    printf("This is Unix Server example code\n");

    struct sockaddr_un addr;
    int len = 0;
	char buf[100];
  	int fd,cl,rc;

    if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;   
    strcpy(addr.sun_path, SOCKET_FILE_PATH); 
    len = sizeof(addr);
    
    unlink(SOCKET_FILE_PATH);

    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind error");
        exit(-1);
    }

  	if (listen(fd, 5) == -1) {
    	perror("listen error");
    	exit(-1);
  	}

	printf("socket listening...\n");

	while(1) {
		if ( (cl = accept(fd, NULL, NULL)) == -1) {
      		perror("accept error");
      		continue;
    	}

    	while ( (rc=read(cl,buf,sizeof(buf))) > 0) {
      		printf("read %u bytes: %.*s\n", rc, rc, buf);
    	}	

		if (rc == -1) {
		  perror("read");
		  exit(-1);
		} else if (rc == 0) {
		  printf("EOF\n");
		  close(cl);
		}
	}
    return 0;
}

#else

int main() {
    printf("This is Internet Server example code\n");

    struct sockaddr_in addr;
    int len = 0;
	char buf[100];
  	int portno;    
  	int fd,cl,rc;

    if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(-1);
    }


    /* Initialize socket structure */
   	memset(&addr, 0, sizeof(addr)); 
   	portno = 5001;
   
   	addr.sin_family = AF_INET;
   	addr.sin_addr.s_addr = INADDR_ANY;
   	addr.sin_port = htons(portno);
    
	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind error");
        exit(-1);
    }

  	if (listen(fd, 5) == -1) {
    	perror("listen error");
    	exit(-1);
  	}

	printf("socket listening...\n");

	while(1) {
		if ( (cl = accept(fd, NULL, NULL)) == -1) {
      		perror("accept error");
      		continue;
    	}

    	while ( (rc=read(cl,buf,sizeof(buf))) > 0) {
      		printf("read %u bytes: %.*s\n", rc, rc, buf);
    	}	

		if (rc == -1) {
		  perror("read");
		  exit(-1);
		} else if (rc == 0) {
		  printf("EOF\n");
		  close(cl);
		}
	}

    return 0;
}



#endif
