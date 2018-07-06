#include "ser.h"

int main(int argc, char const *argv[])
{
	int sock = 0, newSock = 0, n = 0;
	int cfd = 0;
	long port_num = atoi(argv[1]);
	struct sockaddr_in sAddr, cAddr;
	socklen_t clilen;
	char buffer[64];
	int random = 0;
	char response;

	// Initialize socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	// Check socket was initialized
	if (sock < 0) {
		printf("Socket ERROR\n");
		exit(1);
	}

	//  Add more info to in address
	sAddr.sin_family = AF_INET;	
	sAddr.sin_addr.s_addr = INADDR_ANY;
	sAddr.sin_port = htons(port_num);

	// Bind sock and sockaddr
	if (bind(sock, (struct sockaddr *) &sAddr, sizeof(sAddr)) < 0) {
		printf("Binding ERROR\n");
		exit(1);
	}

	// Listen for input
	if (listen(sock, 5) == -1) {
		printf("Listen ERROR\n");
		exit(1);
	}

	clilen = sizeof(cAddr);
    newSock = accept(sock, (struct sockaddr *) &cAddr, &clilen);
	// While loop to accept input from client and write back server's response
	while(1) {
		if (newSock < 0) {
			printf("Accept ERROR\n");
			exit(1);
		}
		n = read(newSock, buffer, 1024);
		if (n < 0) {
			printf("Read ERROR\n");
			exit(1);
		} 

		random = rand() % 35565 + 1;

		if (random % 2 == 0) {
			response = 'B';
		} else {
			response = 'S';
		}

		if (response == 'B' && buffer[0] == 'B')  {
			// both betray 
			strcpy(buffer, "Prisoner A and Prisoner B both receive 2 years in prison");
		} else if (response == 'S' && buffer[0] == 'S') {
			// both silent 
			strcpy(buffer, "Prisoner A and Prisoner B both receive 1 year in prison\n");
		} else if (response == 'S' && buffer[0] == 'B') {
			// Pris A betrayed Pris B did not
			strcpy(buffer, "Prisoner A walks free, Prisoner B receives 3 years in prison\n");
		} else {
			// Pris B betrayed 
			strcpy(buffer, "Prisoner A receives 3 years in prison, Prisoner B walks free\n");
		}
		n = write(newSock, buffer, sizeof(buffer));

		if (n < 0) {
			printf("Write ERROR\n");
			exit(1);
	 	}
	 	n = read(newSock, buffer, 1024);
		if (n < 0) {
			printf("Read ERROR\n");
			exit(1);
		} 
	}
 	close(newSock);
 	close(sock);

	return 0;
}
