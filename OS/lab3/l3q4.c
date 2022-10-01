#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	pid_t pid;
	int status;
	pid=fork();
	switch(pid){
		case -1:printf("Error occured!\n");
		exit(-1);
		case 0: printf("Executing child process\nNow,Exiting child process\n");
		default: sleep(5);
		printf("Executing parent process \nChild Status has returned:%d\nNow,Exiting parent process\n",status);

	}return 0;
}