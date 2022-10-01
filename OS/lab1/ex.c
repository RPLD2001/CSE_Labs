#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main()
{	
	int fd;
	char buffer[50];
	char msg[50]="Hello students";
	fd=open("lab1.txt",O_RDWR);
	printf("File descriptor:%d",fd);

	 if(fd!=-1)
	{
		write(fd,msg,sizeof(msg));
		lseek(fd,0,SEEK_SET);
		read(fd,buffer,sizeof(msg));
		printf("\nThe content is %s",buffer);
		close(fd);
	}

	return 0;
}
