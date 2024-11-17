%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "Node.hpp"
    #include "syntax.tab.hh"
    #define YYSTYPE Node*
    extern YYSTYPE yylval;
    int yycolno = 1;
    int has_error = 0;
    #define YY_USER_ACTION \
    yylloc.first_line = yylineno; \
    yylloc.first_column = yycolno; \
    yylloc.last_line = yylineno; \
    yylloc.last_column = yycolno + yyleng; \
    yycolno += yyleng;
    using token = yy::parser::token;
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
"if" {yylval = new Node(NodeType::If, yytext); return token::IF;}
"else" {yylval = new Node(NodeType::Else, yytext); return token::ELSE;}
"while" {yylval = new Node(NodeType::While, yytext); return token::WHILE;}
"return" {yylval = new Node(NodeType::Return, yytext); return token::RETURN;}
"." {yylval = new Node(NodeType::Dot, yytext); return token::DOT;}
";" {yylval = new Node(NodeType::Semi, yytext); return token::SEMI;}
"," {yylval = new Node(NodeType::Comma, yytext); return token::COMMA;}
"=" {yylval = new Node(NodeType::Assign, yytext); return token::ASSIGN;}
"<" {yylval = new Node(NodeType::Lt, yytext); return token::LT;}
"<=" {yylval = new Node(NodeType::Le, yytext); return token::LE;}
">" {yylval = new Node(NodeType::Gt, yytext); return token::GT;}
">=" {yylval = new Node(NodeType::Ge, yytext); return token::GE;}
"!=" {yylval = new Node(NodeType::Ne, yytext); return token::NE;}
"==" {yylval = new Node(NodeType::Eq, yytext); return token::EQ;}
"+" {yylval = new Node(NodeType::Plus, yytext); return token::PLUS;}
"-" {yylval = new Node(NodeType::Minus, yytext); return token::MINUS;}
"*" {yylval = new Node(NodeType::Mul, yytext); return token::MUL;}
"/" {yylval = new Node(NodeType::Div, yytext); return token::DIV;}
"&&" {yylval = new Node(NodeType::And, yytext); return token::AND;}
"||" {yylval = new Node(NodeType::Or, yytext); return token::OR;}
"!" {yylval = new Node(NodeType::Not, yytext); return token::NOT;}
"(" {yylval = new Node(NodeType::Lp, yytext); return token::LP;}
")" {yylval = new Node(NodeType::Rp, yytext); return token::RP;}
"[" {yylval = new Node(NodeType::Lb, yytext); return token::LB;}
"]" {yylval = new Node(NodeType::Rb, yytext); return token::RB;}
"{" {yylval = new Node(NodeType::Lc, yytext); return token::LC;}
"}" {yylval = new Node(NodeType::Rc, yytext); return token::RC;}


{INTEGER} {yylval = new Node(NodeType::Int, atoi(yytext)); return token::INTEGER;}
{FLOAT} {yylval = new Node(NodeType::Float, strtof(yytext, nullptr)); return token::FLOAT;}
{CHARACTER} {yylval = new Node(NodeType::Char, yytext); return token::CHAR;}
{TYPE} {yylval = new Node(NodeType::Type, yytext); return token::TYPE;}
{ID} {yylval = new Node(NodeType::Id, yytext); return token::ID;}

{COMMENT} {/* skip for comment */}
{MULTIPLE_COMMENT} {/* skip for comment */}

[ \t\r]+ { /* skip whitespace */ }
\n { yylineno++; yycolno = 1; }

{INVALID_NUMBER} { has_error = 1; fprintf(stderr, "Error: Invalid number at line %d: %s\n", yylineno, yytext); return token::INVALID_NUMBER; }
{ILLEGAL_TOKEN} { has_error = 1; fprintf(stderr, "Error: Illegal token at line %d: %s\n", yylineno, yytext); return token::ILLEGAL_TOKEN; }
%%

int yywrap() {
    return 1;
}