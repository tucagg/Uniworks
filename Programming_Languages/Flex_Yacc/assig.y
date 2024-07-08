%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assig.h"
void yyerror(char *);
extern YYSTYPE yylval;
extern int yylex();
extern FILE *yyin;
%}

%union {
    double value;
    char* identifier;
    char val[10];
}

%token <value> VALUEF
%token <identifier> IDENTIFIER
%token KW_PLUS KW_MINUS KW_MULT KW_DIV
%token KW_AND KW_OR KW_NOT KW_EQUAL KW_LESS KW_NIL KW_LIST KW_APPEND KW_CONCAT KW_SET KW_DEF KW_FOR KW_IF KW_EXIT KW_LOAD KW_DISPLAY KW_TRUE KW_FALSE
%token OP_OP OP_CP OP_PLUS OP_MINUS OP_DIV OP_MULT OP_COMMA
%token NEWLINE

%type <value> EXP FUNCTION

%start PROGRAM

%%

PROGRAM:
    /* empty */
    | PROGRAM STATEMENT NEWLINE
    ;

STATEMENT:
    EXP { printf("%f\n", $1); }
    | FUNCTION { printf("#function\n"); }
    | KW_EXIT { exit(0); }
    ;

EXP:
    OP_OP KW_PLUS EXP EXP OP_CP { $$ = $3 + $4; }
    | OP_OP KW_MINUS EXP EXP OP_CP { $$ = $3 - $4; }
    | OP_OP KW_MULT EXP EXP OP_CP { $$ = $3 * $4; }
    | OP_OP KW_DIV EXP EXP OP_CP {
        if ($4 == 0) {
            yyerror("Division by zero");
            exit(1);
        }
        $$ = $3 / $4;
    }
    | OP_OP IDENTIFIER EXP OP_CP {
        printf("Applying function '%s'\n", $2);
    }
    | IDENTIFIER { }
    | VALUEF { $$ = $1; }
    ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
    yyin = stdin;
    yyparse();
    return 0;
}
