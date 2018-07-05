#ifndef SER_H_
#define SER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

void makeSocket(int lf) {
	lf = socket(AF_INET, SOCK_STREAM, 0);
	if (lf < 0) {
		printf("Can't create socket\n");
	}
}

void initServer(struct sockaddr_in address, int pNum) {
	address.sin_family = AF_INET;    
	address.sin_addr.s_addr = htonl(INADDR_ANY); 
	address.sin_port = htons(pNum);  
}

void initClient(struct sockaddr_in address, int pNum) {
	address.sin_family = AF_INET;    
	address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	address.sin_port = htons(pNum);  
}

void makeBind(int lf, struct sockaddr_in address) {
	bind(lf, (struct sockaddr*)&address, sizeof(address));
}

void checkListenFDError(int lf) {
	if (listen(lf, 10) == -1) {
		printf("Connection failure\n");
		exit(1);
	}
}

void makeConnection(int socket, struct sockaddr_in address) {
	int flag = connect(socket, (struct sockaddr *)&address, sizeof(address));
	if (flag < 0) {
		printf("Connection Failed\n");
		exit(1);
	}
}

void readIn(int socket, char buff[]) {
	int n;
	while((n = read(socket, buff, sizeof(buff)-1)) > 0) {
	    buff[n] = 0;
	      
	    if(fputs(buff, stdout) == EOF) {
			printf("\n Error : Fputs error");
		}
    	printf("\n");
    	}
 		if( n < 0) {
      		printf("\n Read Error \n");
    	}
}
  
#endif