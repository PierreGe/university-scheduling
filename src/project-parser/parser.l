%{
#include <stdio.h>
#include "parser.hpp"
%}

%%
[0-9]+              yylval.number = atoi(yytext); return NUMBER;
","                 return COMMA;
";"                 return SEMICOLON;
"/*"[^"*/"]*"*/"    /* ignore multi-line comments */
"//"[^\r\n]*(\r\n)? /* ignore single-line comments */
[ \t\r\n]+          /* ignore whitespace */
%%
