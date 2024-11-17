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
TYPE "int"|"float"|"char"
ID [a-zA-Z_][a-zA-Z0-9_]*
COMMENT "//".*$
MULTIPLE_COMMENT "/*"((("*"[^/])?)|[^*])*"*/"
INVALID_NUMBER ([+-]?0x[0-9a-zA-Z]*)|(00+)
ILLEGAL_TOKEN .+

%%
"if" {yylval = new Node(NodeType::If, yytext); return IF;}
"else" {yylval = new Node(NodeType::Else, yytext); return ELSE;}
"while" {yylval = new Node(NodeType::While, yytext); return WHILE;}
"return" {yylval = new Node(NodeType::Return, yytext); return RETURN;}
"." {yylval = new Node(NodeType::Dot, yytext); return DOT;}
";" {yylval = new Node(NodeType::Semi, yytext); return SEMI;}
"," {yylval = new Node(NodeType::Comma, yytext); return COMMA;}
"=" {yylval = new Node(NodeType::Assign, yytext); return ASSIGN;}
"<" {yylval = new Node(NodeType::Lt, yytext); return LT;}
"<=" {yylval = new Node(NodeType::Le, yytext); return LE;}
">" {yylval = new Node(NodeType::Gt, yytext); return GT;}
">=" {yylval = new Node(NodeType::Ge, yytext); return GE;}
"!=" {yylval = new Node(NodeType::Ne, yytext); return NE;}
"==" {yylval = new Node(NodeType::Eq, yytext); return EQ;}
"+" {yylval = new Node(NodeType::Plus, yytext); return PLUS;}
"-" {yylval = new Node(NodeType::Minus, yytext); return MINUS;}
"*" {yylval = new Node(NodeType::Mul, yytext); return MUL;}
"/" {yylval = new Node(NodeType::Div, yytext); return DIV;}
"&&" {yylval = new Node(NodeType::And, yytext); return AND;}
"||" {yylval = new Node(NodeType::Or, yytext); return OR;}
"!" {yylval = new Node(NodeType::Not, yytext); return NOT;}
"(" {yylval = new Node(NodeType::Lp, yytext); return LP;}
")" {yylval = new Node(NodeType::Rp, yytext); return RP;}
"[" {yylval = new Node(NodeType::Lb, yytext); return LB;}
"]" {yylval = new Node(NodeType::Rb, yytext); return RB;}
"{" {yylval = new Node(NodeType::Lc, yytext); return LC;}
"}" {yylval = new Node(NodeType::Rc, yytext); return RC;}


{INTEGER} {yylval = new Node(NodeType::Int, atoi(yytext)); return INTEGER;}
{FLOAT} {yylval = new Node(NodeType::Float, atof(yytext)); return FLOAT;}
{CHARACTER} {yylval = new Node(NodeType::Char, yytext); return CHAR;}
{TYPE} {yylval = new Node(NodeType::Type, yytext); return TYPE;}
{ID} {yylval = new Node(NodeType::Id, yytext); return ID;}


{COMMENT} {/* skip for comment */}
{MULTIPLE_COMMENT} {/* skip for comment */}

[ \t\r]+ { /* skip whitespace */ }
\n { yylineno++; yycolno = 1; }

{INVALID_NUMBER} { has_error = 1; fprintf(stderr, "Error: Invalid number at line %d: %s\n", yylineno, yytext); return INVALID_NUMBER; }
{ILLEGAL_TOKEN} { has_error = 1; fprintf(stderr, "Error: Illegal token at line %d: %s\n", yylineno, yytext); return ILLEGAL_TOKEN; }
%%

int yywrap() {
    return 1;
}