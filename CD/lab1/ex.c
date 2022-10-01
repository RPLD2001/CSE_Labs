#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fptr1,*fptr2;
	char filename[100];
	char c;
	printf("Enter name of file to write from ");
	scanf("%s",filename);
	fptr1=fopen(filename,"r");
	if(fptr1==NULL)
	{
		printf("Cannot open file");
		exit(0);
	}
	printf("Enter name of file to be written to ");
	scanf("%s",filename);
	fptr2=fopen(filename,"w");
	c=fgetc(fptr1);
	while(c!=EOF)
	{
		fputc(c,fptr2);
		c=fgetc(fptr1);
	}
	printf("Content copied to %s",filename);
	fclose(fptr1);
	fclose(fptr2);

	return 0;

}