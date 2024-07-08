%{
    //definitions
%}
COMMENT [;]{2}.*
VALUEF [1-9][0-9]*b[1-9][0-9]*
IDENTIFIER [a-zA-Z][a-zA-Z0-9]*

%%
and     {printf("KW_AND\n");}
or      {printf("KW_OR\n");}
not     {printf("KW_NOT\n");}
equal   {printf("KW_EQUAL\n");}
less    {printf("KW_LESS\n");}
nil     {printf("KW_NIL\n");}
list    {printf("KW_LIST\n");}
append  {printf("KW_APPEND\n");}
concat  {printf("KW_CONCAT\n");}
set     {printf("KW_SET\n");}
def     {printf("KW_DEF\n");}
for     {printf("KW_FOR\n");}
if      {printf("KW_IF\n");}
exit    {printf("KW_EXIT\n"); return 0;}
load    {printf("KW_LOAD\n");}
display {printf("KW_DISPLAY\n");}
true    {printf("KW_TRUE\n");}
false   {printf("KW_FALSE\n");}


and+[a-zA-Z]*      {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
or+[a-zA-Z]*       {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
not+[a-zA-Z]*      {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
equal+[a-zA-Z]*    {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
less+[a-zA-Z]*     {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
nil+[a-zA-Z]*      {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
list+[a-zA-Z]*     {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
append+[a-zA-Z]*   {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
concat+[a-zA-Z]*   {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
set+[a-zA-Z]*      {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
def+[a-zA-Z]*      {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
for+[a-zA-Z]*      {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
if+[a-zA-Z]*       {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
exit+[a-zA-Z]*     {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
load+[a-zA-Z]*     {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
display+[a-zA-Z]*  {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
true+[a-zA-Z]*     {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}
false+[a-zA-Z]*    {printf("SYNTAX_ERROR '%s' cannot be tokenized.\n",yytext);return 0;}


{COMMENT}       {printf("COMMENT\n");}
{VALUEF}        {printf("VALUEF\n");}
{IDENTIFIER}    {printf("IDENTIFIER\n");}

[+]     {printf("OP_PLUS\n");}
[-]     {printf("OP_MINUS\n");}
[/]     {printf("OP_DIV\n");}
[*]     {printf("OP_MULT\n");}
[(]     {printf("OP_OP\n");}
[)]     {printf("OP_CP\n");}
[,]     {printf("OP_COMMA\n");}

[ \t\n]     {;}


. { printf("ERROR '%s' EXPRESSION DOES NOT MATCH! \n",yytext);}
%%

int yywrap() {}


int main()
{
    printf("Enter a string: ");
    yylex();

    return 0;
}