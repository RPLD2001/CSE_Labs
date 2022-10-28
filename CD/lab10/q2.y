%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}
%token IF ELSE ELSEIF OB CB RO ID SS CO
%%
stmt:IF OB ID RO ID CB stmet ELSE
	 ;
stmet: ELSEIF OB ID RO ID CB stmet
		 |
		 ;

%%

int yyerror(char* msg){
printf("Invalid Expression\n");
return 1;
}
void main()
{
printf("Enter the expression\n");
yyin=fopen("in.txt","r");
do
{
if(yyparse())
{
printf("\nFailure");
exit(0);}
}while(!feof(yyin));
printf("Success");
}