#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
	pid_t pid;
	int status;
	pid=fork();
	switch(pid){
		case -1:
		printf("Error occured!");
		case 0: 
		printf("Executing child process of main program.\n");
		execlp("./l3q1","l3q1",NULL);
		exit(0);
		default:
		wait(&status);
		printf("\nExecuting parent process of main program.\nChild Status has returned:%d\nNow,Exiting parent process of main program\n",status);
	}
}