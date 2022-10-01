#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


char keywords[32][10] = {"auto", "double", "int", "struct",
"break", "else", "long","switch", "case", "enum", "register",
"typedef", "char","extern", "return", "union", "const", "float",
"short", "unsigned", "continue", "for", "signed", "void",
"default", "goto", "sizeof", "voltile", "do", "if", "static",
"while"};


int compare(char buffer[])
{
    for(int i=0;i<32;i++){
        if(strcmp(buffer, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}


int main()
{
    FILE* fa,*fb;
    char buffer[100],filename[50] ,c,C;
    printf("Enter the file name of the file to read from: ");
    scanf("%s", filename);
    fa = fopen(filename, "r");
   if(!fa)
    {
        printf("File cannot be opened\n");
        exit(1);
    }
     printf("Enter the name of file to write to: ");
    scanf("%s", filename);
    fb = fopen(filename, "w+");
    int i = 0;
    c=getc(fa);
    while(c != EOF)
    {
        if(isalpha(c) != 0)
        {
            buffer[i++]=c;
            while(isalpha(c) != 0)
            {
                c = fgetc(fa);
                if(isalpha(c) != 0)
                    buffer[i++] = c;
            }
            buffer[i] = '\0';
            if(compare(buffer) == 1)
            {
                for(int j=0;j<i;j++)
                {
                    C=toupper(buffer[j]);
                    fputc(C,fb);
                }
            }
            else
            {
                for(int j=0;j<i;j++)
                {
                    C=buffer[j];
                    fputc(C,fb);
                }
            }


           i = 0;
            buffer[0] = '\0';
        }
        else
        {
            fputc(c,fb);
            c=fgetc(fa);
        }    
    }


   fclose(fa);
    fclose(fb);


   return 0;
}