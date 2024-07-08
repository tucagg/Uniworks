%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assig.h"
extern YYSTYPE yylval;
void yyerror(char *);
%}


COMMENT [;]{2}.*
VALUEF [1-9][0-9]*f1
IDENTIFIER [a-zA-Z][a-zA-Z0-9]*

%%

"and"     {return KW_AND;}
"or"      {return KW_OR;}
"not"     {return KW_NOT;}
"equal"   {return KW_EQUAL;}
"less"    {return KW_LESS;}
"nil"     {return KW_NIL;}
"list"    {return KW_LIST;}
"append"  {return KW_APPEND;}
"concat"  {return KW_CONCAT;}
"set"     {return KW_SET;}
"def"     {return KW_DEF;}
"for"     {return KW_FOR;}
"if"      {return KW_IF;}
"exit"    {return KW_EXIT;}
"load"    {return KW_LOAD;}
"display" {return KW_DISPLAY;}
"true"    {return KW_TRUE;}
"false"   {return KW_FALSE;}

and+[a-zA-Z]*      {printf("SYNTAX_ERROR cannot be tokenized.\n");}
or+[a-zA-Z]*       {printf("SYNTAX_ERROR cannot be tokenized.\n");}
not+[a-zA-Z]*      {printf("SYNTAX_ERROR cannot be tokenized.\n");}
equal+[a-zA-Z]*    {printf("SYNTAX_ERROR cannot be tokenized.\n");}
less+[a-zA-Z]*     {printf("SYNTAX_ERROR cannot be tokenized.\n");}
nil+[a-zA-Z]*      {printf("SYNTAX_ERROR cannot be tokenized.\n");}
list+[a-zA-Z]*     {printf("SYNTAX_ERROR cannot be tokenized.\n");}
append+[a-zA-Z]*   {printf("SYNTAX_ERROR cannot be tokenized.\n");}
concat+[a-zA-Z]*   {printf("SYNTAX_ERROR cannot be tokenized.\n");}
set+[a-zA-Z]*      {printf("SYNTAX_ERROR cannot be tokenized.\n");}
def+[a-zA-Z]*      {printf("SYNTAX_ERROR cannot be tokenized.\n");}
for+[a-zA-Z]*      {printf("SYNTAX_ERROR cannot be tokenized.\n");}
if+[a-zA-Z]*       {printf("SYNTAX_ERROR cannot be tokenized.\n");}
exit+[a-zA-Z]*     {printf("SYNTAX_ERROR cannot be tokenized.\n");}
load+[a-zA-Z]*     {printf("SYNTAX_ERROR cannot be tokenized.\n");}
display+[a-zA-Z]*  {printf("SYNTAX_ERROR cannot be tokenized.\n");}
true+[a-zA-Z]*     {printf("SYNTAX_ERROR cannot be tokenized.\n");}
false+[a-zA-Z]*    {printf("SYNTAX_ERROR cannot be tokenized.\n");}

{COMMENT}       { /* ignore comments */ }
{VALUEF}        {yylval.value = atof(yytext); return VALUEF;}
{IDENTIFIER}    {yylval.identifier = strdup(yytext); return IDENTIFIER;}


"+"     {return OP_PLUS;}
"-"     {return OP_MINUS;}
"/"     {return OP_DIV;}
"*"     {return OP_MULT;}
"("     {return OP_OP;}
")"     {return OP_CP;}
","     {return OP_COMMA;}

[ \t\n]     {;}

. { yyerror("ERROR EXPRESSION DOES NOT MATCH!\n");}

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a string: ");
    yylex();
    return 0;
}
