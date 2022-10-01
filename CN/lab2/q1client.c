#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#define PORTNO 10200

int len,result,sockfd,n=1;
struct sockaddr_in address;
char ch[256],buf[256];

void CreateSocket()
{
//create a socket for the client
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    //name the socket as agreed with the server
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=htonl(INADDR_ANY);
    address.sin_port=htons(PORTNO);
    len=sizeof(address);
}

void ConnectToServer()
{
    //connect your socket to the server's socket
    result=connect(sockfd,(struct sockaddr *)&address,len);
    if(result==-1)
    {
    perror("\nCLIENT ERROR");
    exit(1);
    }
}

void ClientTask()
{
    //You can now read and write via sockfd (Logic for problem mentioned here)
    printf("\nENTER STRING\t");
    gets(ch);
    ch[strlen(ch)]='\0';
    write(sockfd,ch,strlen(ch));
    printf("STRING SENT BACK FROM SERVER IS .....");
    while(n)
    {
        n=read(sockfd,buf,sizeof(buf));
        puts(buf);
    }
}

int main()
{
    CreateSocket();
    ConnectToServer();
    ClientTask();
}