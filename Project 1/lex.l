%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "Node.hpp"
    #include "syntax.tab.h"
    extern YYSTYPE yylval;
    int has_error = 0;
    // using token = yy::parser::token;
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
"if" {yylval.node = new Node(NodeType::If, yytext); return IF;}
"else" {yylval.node = new Node(NodeType::Else, yytext); return ELSE;}
"while" {yylval.node = new Node(NodeType::While, yytext); return WHILE;}
"return" {yylval.node = new Node(NodeType::Return, yytext); return RETURN;}
"." {yylval.node = new Node(NodeType::Dot, yytext); return DOT;}
";" {yylval.node = new Node(NodeType::Semi, yytext); return SEMI;}
"," {yylval.node = new Node(NodeType::Comma, yytext); return COMMA;}
"=" {yylval.node = new Node(NodeType::Assign, yytext); return ASSIGN;}
"<" {yylval.node = new Node(NodeType::Lt, yytext); return LT;}
"<=" {yylval.node = new Node(NodeType::Le, yytext); return LE;}
">" {yylval.node = new Node(NodeType::Gt, yytext); return GT;}
">=" {yylval.node = new Node(NodeType::Ge, yytext); return GE;}
"!=" {yylval.node = new Node(NodeType::Ne, yytext); return NE;}
"==" {yylval.node = new Node(NodeType::Eq, yytext); return EQ;}
"+" {yylval.node = new Node(NodeType::Plus, yytext); return PLUS;}
"-" {yylval.node = new Node(NodeType::Minus, yytext); return MINUS;}
"*" {yylval.node = new Node(NodeType::Mul, yytext); return MUL;}
"/" {yylval.node = new Node(NodeType::Div, yytext); return DIV;}
"&&" {yylval.node = new Node(NodeType::And, yytext); return AND;}
"||" {yylval.node = new Node(NodeType::Or, yytext); return OR;}
"!" {yylval.node = new Node(NodeType::Not, yytext); return NOT;}
"(" {yylval.node = new Node(NodeType::Lp, yytext); return LP;}
")" {yylval.node = new Node(NodeType::Rp, yytext); return RP;}
"[" {yylval.node = new Node(NodeType::Lb, yytext); return LB;}
"]" {yylval.node = new Node(NodeType::Rb, yytext); return RB;}
"{" {yylval.node = new Node(NodeType::Lc, yytext); return LC;}
"}" {yylval.node = new Node(NodeType::Rc, yytext); return RC;}


{INTEGER} {yylval.node = new Node(NodeType::Int, atoi(yytext)); return INTEGER;}
{FLOAT} {yylval.node = new Node(NodeType::Float, strtof(yytext, nullptr)); return FLOAT;}
{CHARACTER} {yylval.node = new Node(NodeType::Char, yytext); return CHAR;}
{TYPE} {yylval.node = new Node(NodeType::Type, yytext); return TYPE;}
{ID} {yylval.node = new Node(NodeType::Id, yytext); return ID;}

{COMMENT} {/* skip for comment */}
{MULTIPLE_COMMENT} {/* skip for comment */}

[ \t\r]+ { /* skip whitespace */ }

%%
