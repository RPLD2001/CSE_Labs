#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define PORTNO 8900

int len, result, sockfd, n = 1;
char ch[256], buf[256];
struct sockaddr_in address;


void CreateClientSocket()
{

    // Create a socket for the client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Name the socket as agreed with the server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    len = sizeof(address);
    // Connect your socket to the server’s socket
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
}

void PerformClientTask()
{

    // You can now read and write via sockfd (Logic for problem mentioned here)
    printf("\nENTER STRING\t");
    gets(ch);
    ch[strlen(ch)] = '\0';
    write(sockfd, ch, strlen(ch));
    printf("STRING SENT BACK FROM SERVER IS .....");
    while (n)
    {
        n = read(sockfd, buf, sizeof(buf));
        puts(buf);
    }
}

int main()
{
    CreateClientSocket();
    PerformClientTask();

    return 0;
}