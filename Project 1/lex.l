%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "Node.hpp"
    #include "syntax.tab.h"
    #define YYSTYPE Node
    int yycolno = 1;
    int has_error = 0;
    #define YY_USER_ACTION \
    yylloc.first_line = yylineno; \
    yylloc.first_column = yycolno; \
    yylloc.last_line = yylineno; \
    yylloc.last_column = yycolno + yyleng; \
    yycolno += yyleng;

%}

%option noyywrap
%option yylineno

INTEGER [0-9]+
FLOAT [0-9]+\.[0-9]+
CHARACTER ('.')|('\\x[0-9a-fA-F]{2}')
TYPE （"int"|"float"|"char"）
ID [a-zA-Z_][a-zA-Z0-9_]*
COMMENT "//".*$
MULTIPLE_COMMENT "/*"((("*"[^/])?)|[^*])*"*/"
INVALID_NUMBER ([+-]?0x[0-9a-zA-Z]*)|(00+)
ILLEGAL_TOKEN .+

%%
"struct" {return STRUCT;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"return" {return RETURN;}
"." {return DOT;}
";" {return SEMI;}
"," {return COMMA;}
"=" {return ASSIGN;}
"<" {return LT;}
"<=" {return LE;}
">" {return GT;}
">=" {return GE;}
"!=" {return NE;}
"==" {return EQ;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}
"(" {return LP;}
")" {return RP;}
"[" {return LB;}
"]" {return RB;}
"{" {return LC;}
"}" {return RC;}


{INTEGER} {yylval = new Node(Int, yytext, atoi(yytext)); return INTEGER;}
{FLOAT} {yylval = new Node(Float, yytext, atof(yytext)); return FLOAT;}
{CHARACTER} {yylval = new Node(Char, yytext); return CHAR;}
{ID} {yylval = new Node(Id, yytext); return ID;}
{TYPE} {yylval = new Node(Type, yytext); return TYPE;}

{COMMENT} {/* skip for comment */}
{MULTIPLE_COMMENT} {/* skip for comment */}

[ \t\r]+ { /* skip whitespace */ }
\n { curLine++; curCol = 1; }

{INVALID_NUMBER} { has_error = 1; fprintf(stderr, "Error: Invalid number at line %d: %s\n", yylineno, yytext); return INVALID_NUMBER; }
{ILLEGAL_TOKEN} { has_error = 1; fprintf(stderr, "Error: Illegal token at line %d: %s\n", yylineno, yytext); return ILLEGAL_TOKEN; }
%%

int yywrap() {
    return 1;
}