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
#include <netdb.h> 

// There was an attempt to make ser.c and cli.c much prettier with the following
// It was not a successful attempt :(

void makeSocket(int lf) {
	lf = socket(AF_INET, SOCK_STREAM, 0);
	if (lf < 0) {
		printf("Can't create socket\n");
	} else {
		printf("Socket Success\n");
	}
}

void initServer(struct sockaddr_in address, int pNum) {
	address.sin_family = AF_INET;    
	address.sin_addr.s_addr = htonl(INADDR_ANY); 
	address.sin_port = htons(5000);  
}

void initClient(struct sockaddr_in address, int pNum) {
	address.sin_family = AF_INET;    
	address.sin_port = htons(5000); 
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
}

void makeBind(int lf, struct sockaddr_in address) {
	bind(lf, (struct sockaddr*)&address, sizeof(address));
}

void checkListenFDError(int lf) {
	if (listen(lf, 5) == -1) {
		printf("Connection failure\n");
		exit(1);
	}
}

void makeConnection(int socket, struct sockaddr_in address) {
	if (connect(socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
		printf("Connection Failed\n");
		exit(1);
	}
}

void acceptWrite(int cfd, char buff[]) {
	cfd = accept(cfd, (struct sockaddr*)NULL, NULL);

	// make prison logic and send answer to buff
	strcpy(buff, "message from server");
	write(cfd, buff, strlen(buff));
	close(cfd);
	sleep(1);
}
  

#endif