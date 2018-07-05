#include "ser.h"

int main(int argc, char const *argv[])
{
	int sock = 0;
	char buffer[1024];
	struct sockaddr_in sAddr;

	makeSocket(sock);
	memset(buffer, '0', sizeof(buffer));
	memset(sAddr, '0', sizeof(sAddr));
	makeConnection(sock, sAddr);
	

	return 0;
}