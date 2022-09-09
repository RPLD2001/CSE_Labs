#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORTNO 9200
int main()
{
    int sd;
    int c, r;
    struct sockaddr_in sadd, cadd;
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    sadd.sin_family = AF_INET;
    sadd.sin_addr.s_addr = inet_addr("127.0.0.1");
    sadd.sin_port = htons(PORTNO);
    int result = bind(sd, (struct sockaddr *)&sadd, sizeof(sadd));
    int len = sizeof(cadd);
    int temp1 = recvfrom(sd, &c, sizeof(int), 0, (struct sockaddr *)&cadd, &len);
    printf("\nNumber of columns (Recieved from Client) %d\n", c);
    int temp2 = recvfrom(sd, &r, sizeof(int), 0, (struct sockaddr *)&cadd, &len);
    printf("\nNumber of rows (Recieved from Client) %d\n", r);
    int arr[r][c];
    int a[c];
    for (int i = 0; i < r; i++)
    {
        int temp3 = recvfrom(sd, a, sizeof(int) * c, 0, (struct sockaddr *)&cadd, &len);
        for (int j = 0; j < c; j++)
        {
            arr[i][j] = a[j];
        }
    }
    int temp4 = sendto(sd, arr, sizeof(arr), 0, (struct sockaddr *)&cadd, len);
    return 0;
}