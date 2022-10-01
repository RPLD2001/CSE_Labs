#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	pid_t pid;
	int status;
	pid=fork();

	switch(pid){
		case -1:
		printf("Error occured!\n");
		exit(0);
		case 0:
		printf("Executing Child process...\nNow,Exiting Child process\n");
		exit(0);
		default:
		wait(&status);
		printf("Executing parent process...\nChild status has returned:%d\nNow,Exiting parent process \n",status);
	}
}