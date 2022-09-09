#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORTNO 9200
int main()
{
    int sd;
    struct sockaddr_in address;
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    char buf[25], buf1[25];

    int r, c, i, j;
    printf("Enter no of columns\n");
    scanf("%d", &c);
    printf("Enter no of rows\n");
    scanf("%d", &r);
    int arr[r][c];
    printf("Enter elements in the Matrix\n");
    int len = sizeof(address);
    int temp1 = sendto(sd, &c, sizeof(int), 0, (struct sockaddr *)&address, len);
    int temp2 = sendto(sd, &r, sizeof(int), 0, (struct sockaddr *)&address, len);
    for (i = 0; i < r; i++)
    {
        printf("Enter Row %d Elements\n", i + 1);
        for (j = 0; j < c; j++)
        {
            scanf("%d", &arr[i][j]);
        }
        int temp3 = sendto(sd, arr[i], sizeof(int) * c, 0, (struct sockaddr *)&address, len);
    }
    int temp4 = recvfrom(sd, arr, sizeof(arr), 0, (struct sockaddr *)&address, &len);
    printf("Matrix recieved from server: \n");
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}