#include <stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fa, *fb;
	char ca, cb;
	char file[100];
	printf("Enter name of file to read from: ");
	scanf("%s",file);
	fa = fopen(file, "r");
	if (fa == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}
	printf("Enter name of file to write to: ");
	scanf("%s",file);
	fb = fopen(file, "w");
	ca = getc(fa);
	while (ca != EOF)
	{
		if (ca == ' ')
		{
			putc(ca, fb);
			while (ca == ' ')
				ca = getc(fa);
		}
		if (ca == '/')
		{
			cb = getc(fa);
			if (cb == '/')
			{
				while (ca != '\n')
					ca = getc(fa);
			}
			else if (cb == '*')
			{
				do { 	while (ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				} while (ca != '/');
			}
			else
			{
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}
