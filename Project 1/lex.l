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
"if" {yylval = new Node(If, yytext); return IF;}
"else" {yylval = new Node(Else, yytext); return ELSE;}
"while" {yylval = new Node(While, yytext); return WHILE;}
"return" {yylval = new Node(Return, yytext); return RETURN;}
"." {yylval = new Node(Dot, yytext); return DOT;}
";" {yylval = new Node(Semi, yytext); return SEMI;}
"," {yylval = new Node(Comma, yytext); return COMMA;}
"=" {yylval = new Node(Assign, yytext); return ASSIGN;}
"<" {yylval = new Node(Lt, yytext); return LT;}
"<=" {yylval = new Node(Le, yytext); return LE;}
">" {yylval = new Node(Gt, yytext); return GT;}
">=" {yylval = new Node(Ge, yytext); return GE;}
"!=" {yylval = new Node(Ne, yytext); return NE;}
"==" {yylval = new Node(Eq, yytext); return EQ;}
"+" {yylval = new Node(Plus, yytext); return PLUS;}
"-" {yylval = new Node(Minus, yytext); return MINUS;}
"*" {yylval = new Node(Mul, yytext); return MUL;}
"/" {yylval = new Node(Div, yytext); return DIV;}
"&&" {yylval = new Node(And, yytext); return AND;}
"||" {yylval = new Node(Or, yytext); return OR;}
"!" {yylval = new Node(Not, yytext); return NOT;}
"(" {yylval = new Node(Lp, yytext); return LP;}
")" {yylval = new Node(Rp, yytext); return RP;}
"[" {yylval = new Node(Lb, yytext); return LB;}
"]" {yylval = new Node(Rb, yytext); return RB;}
"{" {yylval = new Node(Lc, yytext); return LC;}
"}" {yylval = new Node(Rc, yytext); return RC;}


{INTEGER} {yylval = new Node(Int, atoi(yytext)); return INTEGER;}
{FLOAT} {yylval = new Node(Float, atof(yytext)); return FLOAT;}
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