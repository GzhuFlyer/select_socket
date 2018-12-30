#include <stdio.h>
//#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT 1234

int main(void)
{
	int sockfd;
	struct sockaddr_in my_addr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd != -1)
		printf("create the socket fd is :%d\n",sockfd);
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bzero(&(my_addr.sin_zero),sizeof(my_addr.sin_zero));

	int ret = bind(sockfd,(struct sockaddr*)&my_addr,sizeof(my_addr));
	if(ret != -1){
		printf("bind success\n");
	}
//	else{
//		while(1 + bind(sockfd,(struct sockaddr*)&my_addr,sizeof(my_addr)));
//	}


	int opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));  //设置socket属性

	ret = listen(sockfd,5);
	if(ret != -1)
		printf("listen success\n");
//-----------------------------------------------------------------------


	int fd_accept[1];
	fd_set r_fd;
	struct timeval tv;
	FD_ZERO(&r_fd);
	FD_SET(sockfd,&r_fd);
	tv.tv_sec = 3;
	tv.tv_usec = 500;
	struct sockaddr_in client_addr;
	int length = sizeof(client_addr);

	char buf[1024];

	while(1)
	{
		int seRet = select(sockfd+1,&r_fd,NULL,NULL,&tv);
		printf("----2------>\n");
		int newsocket = accept(sockfd,(struct sockaddr*)&client_addr,&length);
		printf("----3------>\n");
		if(newsocket != -1)
		{
			printf("accept success!\n");
		}

		int n;
		n = read(newsocket,buf,1024);
		printf("------->%s\n",buf);
		write(newsocket,buf,n);
		printf("----1------>\n");

	}
	close(sockfd);




	return 0;
}




