%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    char c;
%}

%%
[A-Z] {
    c=tolower(yytext[0]);
    fprintf(yyout,"%c",c);
}
\/\/(.*) {
    fprintf(yyout,"%s",yytext);
};		
\/\*(.*\n)*.*\*\/  {
    fprintf(yyout,"%s",yytext);
};	
%%

int yywrap()
{}

int main() 
{ 
    yyin=fopen("input.c","r");
    yyout=fopen("out.c","w");
    yylex();
    return 0; 
}