#include "ser.h"

int main(int argc, char const *argv[]) {
	int sock = 0;
	int n = 0;
	int port_num = atoi(argv[1]);
	struct sockaddr_in serv_addr;
	struct hostnet *server;
	char buffer[64];
	char choice;
	int flag = 0;

	memset(buffer, '0', sizeof(buffer));
	memset(&serv_addr, '0', sizeof(serv_addr));	

	// Initialize socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("Socket ERROR\n");
		exit(1);
	}
	// Gets host name
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		printf("No Host ERROR\n");
		exit(1);
	}

	serv_addr.sin_family = AF_INET;    
	serv_addr.sin_port = htons(port_num); 
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Connect socket to server address
	if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("Connection ERROR");
		exit(1);
	}

	// Prompt user for input, write to server, and read/write server response
	while  (1) {
		while (flag == 0) {
			printf("Prisoner A, How do you plea?: \n");
			fgets(buffer, 64, stdin); 
			if (buffer[0] == 'B') {
				printf("Prisoner A has chosen betray\n");
				choice = buffer[0];
				flag = 1;
			} else if (buffer[0] == 'S') {
				printf("Prisoner A has chosen silence\n");
				flag = 1;
				choice = buffer[0];
			} else {
				printf("Invalid response\nTry again: \n");
			}
		}
		flag = 0; 
		n = write(sock, buffer, strlen(buffer));
		if (n < 0) {
			printf("Writing ERROR\n");
			exit(1);
		}
		n = read(sock, buffer, 64);
		if (n < 0) {
			printf("Read ERROR\n");
			exit(1);
		} else {
			printf("%s\n", buffer);
		}
	}
	close(sock);
	return 0;
}