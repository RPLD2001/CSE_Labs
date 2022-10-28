%{
	#include<stdio.h>
	#include<stdlib.h>
	#include "q4.tab.h"
%}
%%
[0-9] {printf("%s\n",yytext);return NUMBER;}
\n {return NL;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"^" {return EXP;}
"n" {return NN;}
%%
int yywrap()
{
	return 1;
}