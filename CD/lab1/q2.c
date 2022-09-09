#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char buff[1024];
int i =0;
int main()
{
	FILE *fptr1,*fptr2;
	char filename[100],c;
	printf("Enter name of file to read from: ");
	scanf("%s",filename);
	fptr1=fopen(filename,"r");
	if(fptr1==NULL)
	{
		printf("Cannot open file");
		exit(1);
	}
	printf("Enter name of file to write to: ");
	scanf("%s",filename);
	fptr2=fopen(filename,"w");
	while(c!=EOF)
	{
		c=fgetc(fptr1);
		buff[i]=c;
		i++;
	}
	for(int j=(i-2);j>=0;j--)
	{
		c=buff[j];
		fputc(c,fptr2);
	}

	fseek(fptr1,0,SEEK_END);
	int size=ftell(fptr1);
	printf("The size of file is %d\n",size);

	return 0;

}	