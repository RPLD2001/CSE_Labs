#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<stdlib.h>
#define PORTNO 10200
int main()
{
	int sockfd,newsockfd,portno,clilen,n=1;
	struct sockaddr_in seraddr,cliaddr;
	int i,valur;

	sockfd=socket(AF_INET,SOCK_STREAM,0);

	seraddr.sin_family=AF_INET;
	seraddr.sin_addr.s_addr=inet_addr("172.16.59.34");
	seraddr.sin_port=htons(PORTNO);
	bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));

	listen(sockfd,5);
	while(1){
		char buffer[256];
		printf("server waiting");

		clilen=sizeof(cliaddr);
		newsockfd=accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);

		n=read(newsockfd,buffer,sizeof(buffer));
		printf("\nMessage from Client%s\n",buffer);
		n=write(newsockfd,buffer,sizeof(buffer));
	}

}