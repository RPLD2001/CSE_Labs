#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc, char const* argv[]){
	if(argc<2){
		printf("Incorrect number of arguments");
		return 0;
	}
	struct stat file_stat;
	int return_value=stat(argv[1],&file_stat);
	if(return_value != 0){
		perror("stat");
		return 1;
	}
	printf("File:%s ----- Inode: %ld\n",argv[1],file_stat.st_ino);
	return 0;
}