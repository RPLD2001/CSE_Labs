%{
#include<stdio.h>
#include<stdlib.h>
#include "q2.tab.h"
%}

%%
"if" {return IF;}
"else" {return ELSE;}
"elseif" {return ELSEIF;}
"(" {return OB;}
")" {return CB;}
[<|>|=] {return RO;}
[a-zA-Z]+ {printf("%s\n",yytext);return ID;}
";" {return SS;}
"," {return CO;}
%%

int yywrap()
{
return 1;
}