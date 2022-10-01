#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *fa, *fb;
	char ca,file[100];
	printf("Enter name of file to read from:");
	scanf("%s",file);
	fa = fopen(file,"r");
	if(fa == NULL){
		printf("Cannot open file!\n");
		exit(0);
	}
	printf("Enter name of file to write to:");
	scanf("%s",file);
	fb = fopen(file, "w+");
	ca = getc(fa);
	while(ca != EOF){
		if(ca == ' ' || ca == '\t'){
			putc(' ',fb);
			while(ca == ' ' || ca == '\t')
				ca = getc(fa);
		}
		putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	return 0;
}




