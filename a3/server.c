#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	int listenfd = 0, conf = 0, numrv = 0, port_num;
	long port_num_long = 0;
	struct sockaddr_in serv_addr;
	char sendBuff[1025];
	char *p;

	port_num = atoi(argv[1]);
	printf("%d: \n", port_num);



	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("Socket Retieve Success\n");

	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET;    
  	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  	serv_addr.sin_port = htons(5000);  

  	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

  	if (listen(listenfd, 10) == -1) {
  		printf("ERROR: failed to connect\n");
  		return -1;
  	}

  	while (1) {
  		conf = accept(listenfd, (struct sockaddr*)NULL, NULL);

  		strcpy(sendBuff, "Message from server");
  		write(conf, sendBuff, strlen(sendBuff));

  		close(conf);
  		sleep(1);
  	}

	return 0;
}