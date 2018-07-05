#include "ser.h"

int main(int argc, char const *argv[])
{
	int sock = 0;
	long port_num = atoi(argv[1]);
	struct sockaddr_in sAdrr;
	char buffer[1024];
	
	makeSocket(sock);
	memset(&sAdrr, '0', sizeof(sAdrr));
	memset(buffer, '0', sizeof(buffer));
	initServer(sAdrr, port_num);
	makeBind(sock, sAdrr);

	return 0;
}

// while (1) {
// 		char ans;
//     conf = accept(listenfd, (struct sockaddr*)NULL, NULL);

//     ans = getAns();
// 		strcpy(sendBuff, ans);

// 		write(conf, sendBuff, strlen(sendBuff));

// 		close(conf);
// 		sleep(1);
// 	}