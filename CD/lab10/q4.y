%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}
%token NL NUMBER ID PLUS MINUS MUL DIV EXP NN
%%
stmt:stmt line
	 |
	 ;
line:NL
	|exp NL
	;
exp:NUMBER
	|exp exp PLUS
	|exp exp MINUS
	|exp exp MUL
	|exp exp DIV
	|exp exp EXP
	|exp exp NN
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