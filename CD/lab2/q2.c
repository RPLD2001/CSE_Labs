#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char filename[50], c;
    FILE *f1, *f2;
    printf("Enter the file name of the file to read from: ");
    scanf("%s", filename);
    f1 = fopen(filename, "r");
    if (!f1)
    {
        printf("File cannot be opened \n");
        exit(0);
    }
    printf("Enter the name of file to write to: ");
    scanf("%s", filename);
    f2 = fopen(filename, "w+");
    c = getc(f1);

   int q=0;
   while(c!=EOF)
   {

       if(c=='"'){
           q++;
       }

       if(c=='#')

       {

           if(q%2!=0){
           }

           else{

               while(c!='\n')
               {
                   c=getc(f1);
               }

           }
       }
       putc(c,f2);
       c=getc(f1);
   }
   fclose(f1);
   fclose(f2);
}