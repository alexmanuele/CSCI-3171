#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void) {

	int sock = 0;
	int n = 0;
	char recBuff[1024];
	struct sockaddr_in serv_addr;

	memset(recBuff, '0', sizeof(recBuff));
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) <0) {
		printf("ERROR: cannot create socket socket\n");
		return 1;
	}

	serv_addr.sin_family = AF_INET;
  	serv_addr.sin_port = htons(5000);
  	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("ERROR: Connection failed\n");
		return 1;
	}

	while (n = read(sock, recBuff, sizeof(recBuff-1)) > 0) {
		recBuff[n] = 0;
		if (fputs(recBuff, stdout) == EOF) {
			printf("ERROR: fputs error\n");
		}
		{
			printf("\n");
		}
		if (n<0) {
			printf("ERROR: read\n");
		}
	}
	return 0;



	// sock: socket descriptor
	// domain: communication domain 
	// type: communication type
	// protocol: protocol value for IP == 0


	// int sock = socket(domain, type, protocol);
	// int setSocket(int sock, int level, int optname, const void *optval, socklen_t optlen);
	// int bind(int sock, const struct sockaddr *addr, socklen_t addrlen);
	// int listen(int sock, int backlog);
	// int new_socket = accept(int sock, struct sockaddr *addr, socklen_t *addrlen);
	// int connect(int sock, const struct sockaddr *addr, socklen_t addrlen);


}

// Create a socket with socket()
// Connect socket with connect()
// Send and receive data
	// Can be done with: 
		// read()/write()
		// send()/recv()