%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "Node.hpp"
    #include "syntax.tab.h"
    extern YYSTYPE yylval;
    int has_error = 0;
    // using token = yy::parser::token;
    int yycolno = 1;
       #define YY_USER_ACTION \
       yylloc.first_line = yylineno; \
       yylloc.first_column = yycolno; \
       yylloc.last_line = yylineno; \
       yylloc.last_column = yycolno + yyleng; \
       yycolno += yyleng;
%}

%option noyywrap
%option yylineno
TYPE "int"|"float"|"char"
ID [a-zA-Z_][a-zA-Z0-9_]*
INTEGER [+-]?(0|[1-9][0-9]*)|0x(0|[1-9a-fA-F][0-9a-fA-F]*)
FLOAT (0|([1-9][0-9]*))\.[0-9]+
CHARACTER ('.')|('\\x[0-9a-fA-F]{2}')
INVALID_CHAR \'.*\'
WRONG_ID ({INTEGER}{ID})|{INVALID_CHAR}
COMMENT "//".*$
MULTIPLE_COMMENT "/*"((("*"[^/])?)|[^*])*"*/"
ILLEGAL_TOKEN [^\x20^\n^\x09]
INVALID_NUMBER ([+-]?0x[0-9a-zA-Z]*)|(0{2,}(\.[0-9]+)?)|0[0-9]+

%%
"if" {yylval.node = new Node(NodeType::If, yytext, yylineno); return IF;}
"else" {yylval.node = new Node(NodeType::Else, yytext, yylineno); return ELSE;}
"while" {yylval.node = new Node(NodeType::While, yytext, yylineno); return WHILE;}
"return" {yylval.node = new Node(NodeType::Return, yytext, yylineno); return RETURN;}
"struct" {yylval.node = new Node(NodeType::Struct, yytext, yylineno); return STRUCT;}
"." {yylval.node = new Node(NodeType::Dot, yytext, yylineno); return DOT;}
";" {yylval.node = new Node(NodeType::Semi, yytext, yylineno); return SEMI;}
"," {yylval.node = new Node(NodeType::Comma, yytext, yylineno); return COMMA;}
"=" {yylval.node = new Node(NodeType::Assign, yytext, yylineno); return ASSIGN;}
"<" {yylval.node = new Node(NodeType::Lt, yytext, yylineno); return LT;}
"<=" {yylval.node = new Node(NodeType::Le, yytext, yylineno); return LE;}
">" {yylval.node = new Node(NodeType::Gt, yytext, yylineno); return GT;}
">=" {yylval.node = new Node(NodeType::Ge, yytext, yylineno); return GE;}
"!=" {yylval.node = new Node(NodeType::Ne, yytext, yylineno); return NE;}
"==" {yylval.node = new Node(NodeType::Eq, yytext, yylineno); return EQ;}
"+" {yylval.node = new Node(NodeType::Plus, yytext, yylineno); return PLUS;}
"-" {yylval.node = new Node(NodeType::Minus, yytext, yylineno); return MINUS;}
"*" {yylval.node = new Node(NodeType::Mul, yytext, yylineno); return MUL;}
"/" {yylval.node = new Node(NodeType::Div, yytext, yylineno); return DIV;}
"&&" {yylval.node = new Node(NodeType::And, yytext, yylineno); return AND;}
"||" {yylval.node = new Node(NodeType::Or, yytext, yylineno); return OR;}
"!" {yylval.node = new Node(NodeType::Not, yytext, yylineno); return NOT;}
"(" {yylval.node = new Node(NodeType::Lp, yytext, yylineno); return LP;}
")" {yylval.node = new Node(NodeType::Rp, yytext, yylineno); return RP;}
"[" {yylval.node = new Node(NodeType::Lb, yytext, yylineno); return LB;}
"]" {yylval.node = new Node(NodeType::Rb, yytext, yylineno); return RB;}
"{" {yylval.node = new Node(NodeType::Lc, yytext, yylineno); return LC;}
"}" {yylval.node = new Node(NodeType::Rc, yytext, yylineno); return RC;}


{INTEGER} {yylval.node = new Node(NodeType::Int, atoi(yytext), yylineno); return INTEGER;}
{FLOAT} {yylval.node = new Node(NodeType::Float, strtof(yytext, nullptr), yylineno); return FLOAT;}
{CHARACTER} {yylval.node = new Node(NodeType::Char, yytext, yylineno); return CHAR;}
{TYPE} {yylval.node = new Node(NodeType::Type, yytext, yylineno); return TYPE;}
"read" {
    yylval.node = new Node(NodeType::Read, yytext, yylineno);
    return READ;
}
"write" {
    yylval.node = new Node(NodeType::Write, yytext, yylineno);
    return WRITE;
}
{WRONG_ID} {has_error=1; fprintf(stdout,"Error type A at Line %d: unknown lexeme %s\n",
               yylineno, yytext); return ID;}
{ID} {yylval.node = new Node(NodeType::Id, yytext, yylineno); return ID;}

{COMMENT} {/* skip for comment */}
{MULTIPLE_COMMENT} {/* skip for comment */}

[ \t\r]+ { /* skip whitespace */ }
\n { yycolno = 1; }

{INVALID_NUMBER} { has_error = 1; fprintf(stderr, "Error Type A: Invalid number at line %d: %s\n", yylineno, yytext); return INVALID; }
{ILLEGAL_TOKEN} { has_error = 1; fprintf(stderr, "Error Type A: Illegal token at line %d: %s\n", yylineno, yytext); return INVALID; }
%%
