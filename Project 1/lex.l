%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "Node.hpp"
    #include "syntax.tab.hh"
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
TYPE ("int"|"float"|"char")
ID [a-zA-Z_][a-zA-Z0-9_]*
COMMENT "//".*$
MULTIPLE_COMMENT "/*"((("*"[^/])?)|[^*])*"*/"
INVALID_NUMBER ([+-]?0x[0-9a-zA-Z]*)|(00+)
ILLEGAL_TOKEN .+

%%
"if" {yylval.node = new Node(NodeType::If, yytext); return token::IF;}
"else" {yylval.node = new Node(NodeType::Else, yytext); return token::ELSE;}
"while" {yylval.node = new Node(NodeType::While, yytext); return token::WHILE;}
"return" {yylval.node = new Node(NodeType::Return, yytext); return token::RETURN;}
"." {yylval.node = new Node(NodeType::Dot, yytext); return token::DOT;}
";" {yylval.node = new Node(NodeType::Semi, yytext); return token::SEMI;}
"," {yylval.node = new Node(NodeType::Comma, yytext); return token::COMMA;}
"=" {yylval.node = new Node(NodeType::Assign, yytext); return token::ASSIGN;}
"<" {yylval.node = new Node(NodeType::Lt, yytext); return token::LT;}
"<=" {yylval.node = new Node(NodeType::Le, yytext); return token::LE;}
">" {yylval.node = new Node(NodeType::Gt, yytext); return token::GT;}
">=" {yylval.node = new Node(NodeType::Ge, yytext); return token::GE;}
"!=" {yylval.node = new Node(NodeType::Ne, yytext); return token::NE;}
"==" {yylval.node = new Node(NodeType::Eq, yytext); return token::EQ;}
"+" {yylval.node = new Node(NodeType::Plus, yytext); return token::PLUS;}
"-" {yylval.node = new Node(NodeType::Minus, yytext); return token::MINUS;}
"*" {yylval.node = new Node(NodeType::Mul, yytext); return token::MUL;}
"/" {yylval.node = new Node(NodeType::Div, yytext); return token::DIV;}
"&&" {yylval.node = new Node(NodeType::And, yytext); return token::AND;}
"||" {yylval.node = new Node(NodeType::Or, yytext); return token::OR;}
"!" {yylval.node = new Node(NodeType::Not, yytext); return token::NOT;}
"(" {yylval.node = new Node(NodeType::Lp, yytext); return token::LP;}
")" {yylval.node = new Node(NodeType::Rp, yytext); return token::RP;}
"[" {yylval.node = new Node(NodeType::Lb, yytext); return token::LB;}
"]" {yylval.node = new Node(NodeType::Rb, yytext); return token::RB;}
"{" {yylval.node = new Node(NodeType::Lc, yytext); return token::LC;}
"}" {yylval.node = new Node(NodeType::Rc, yytext); return token::RC;}


{INTEGER} {yylval.node = new Node(NodeType::Int, atoi(yytext)); return token::INTEGER;}
{FLOAT} {yylval.node = new Node(NodeType::Float, atof(yytext)); return token::FLOAT;}
{CHARACTER} {yylval.node = new Node(NodeType::Char, yytext); return token::CHAR;}
{TYPE} {yylval.node = new Node(NodeType::Type, yytext); return token::TYPE;}
{ID} {yylval.node = new Node(NodeType::Id, yytext); return token::ID;}

{COMMENT} {/* skip for comment */}
{MULTIPLE_COMMENT} {/* skip for comment */}

[ \t\r]+ { /* skip whitespace */ }
\n { curLine++; curCol = 1; }

{INVALID_NUMBER} { has_error = 1; fprintf(stderr, "Error: Invalid number at line %d: %s\n", yylineno, yytext); return token::INVALID; }
{ILLEGAL_TOKEN} { has_error = 1; fprintf(stderr, "Error: Illegal token at line %d: %s\n", yylineno, yytext); return token::INVALID; }
%%

int yywrap() {
    return 1;
}