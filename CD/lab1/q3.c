#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
FILE *f1,*f2,*f3;
char ch[100],c1,c2;
printf("Enter first file name: ");
scanf("%s",ch);
f1=fopen(ch,"r");
printf("Enter second file name: ");
scanf("%s",ch);
f2=fopen(ch,"r");
printf("Enter name of output file: ");
scanf("%s",ch);
f3=fopen(ch,"w+");
if(f1==NULL)
{
printf("Error in opening file1");
exit(1);
}
if(f2==NULL)
{
printf("Error in opening file2");
exit(1);
}

c1=fgetc(f1);
c2=fgetc(f2);

while(c1!=EOF && c2!=EOF)
{
    while(c1!='\n')
    {
        fputc(c1,f3);
        c1=fgetc(f1);

    }
    fputc('\n',f3);
    while(c2!='\n')
    {
        fputc(c2,f3);
        c2=fgetc(f2);
    }
    fputc('\n',f3);
    c1=fgetc(f1);
    c2=fgetc(f2);
    }
    return 1;
}