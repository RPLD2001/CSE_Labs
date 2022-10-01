#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fptr1;
	char filename[100],c;
	int charcount,linecount;
	printf("Enter name of file to read from: ");
	scanf("%s",filename);
	fptr1=fopen(filename,"r");
	if(fptr1==NULL)
	{
		printf("Cannot open file");
	}
	c=fgetc(fptr1);
	while(c!=EOF)
	{
		if(c=='\0')
		{
			c=fgetc(fptr1);
			continue;
		}
		else if(c=='\n')
		{
			linecount++;
			c=fgetc(fptr1);
			continue;
		}
		charcount++;
		c=fgetc(fptr1);
	}
	printf("Number of characters is %d\n",charcount);
	printf("Number of lines is %d\n",linecount);
	return 0;


}