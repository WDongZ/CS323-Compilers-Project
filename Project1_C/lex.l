%{
    #include "string.h"
    #include "stdlib.h"
    extern "C" int yylex();
    extern int has_error;
%}
%{
    #include"syntax.tab.h"
    int yycolumn = 1;
    #define YY_USER_ACTION \
    yylloc.first_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_line = yylineno; \
    yylloc.last_column = yycolumn + yyleng; \
    yycolumn += yyleng;
%}

%option yylineno

TYPE "int"|"float"|"char"
STRUCT "struct"
letter[a-zA-Z]
letter_[a-zA-Z_]
digit[0-9]
pos_digit[1-9]
hex_digit [0-9a-fA-F]

decimal [+-]?(0|{pos_digit}{digit}*)
hexadecimal [+-]?(0x)({hex_digit}+)

ID {letter_}+({letter_}|{digit})*
INT {decimal}|{hexadecimal}
FLOAT ({digit}+.{digit}+)
CHAR \'(\\x{hex_digit}{2}|.)\'
INVALID_CHAR \'.*\'
WRONG_ID ({INT}{ID})|{INVALID_CHAR}
COMMENT "//".*$
MULTIPLE_COMMENT "/*"((("*"[^/])?)|[^*])*"*/" 
ILLEGAL_TOKEN [^\x20^\n^\x09]
INVALID_NUMBER ([+-]?0x[0-9a-zA-Z]*)|(00+)


%%


{COMMENT} {/* skip for comment */}
{MULTIPLE_COMMENT} {/* skip for comment */}

{TYPE} {yylval.node_ptr = new Node(Type, yytext);
return TYPE;}

{STRUCT} {yylval.node_ptr = new Node("STRUCT");
return STRUCT;}


"if" {yylval.node_ptr = new Node("IF"); return IF;}
"else" { yylval.node_ptr = new Node("ELSE"); return ELSE;}
"while" {yylval.node_ptr = new Node("WHILE"); return WHILE;}
"return" {yylval.node_ptr = new Node("RETURN"); return RETURN;}
"." {yylval.node_ptr = new Node("DOT"); return DOT;}
";" {yylval.node_ptr = new Node("SEMI"); return SEMI;}
"," {yylval.node_ptr = new Node("COMMA"); return COMMA;}
"=" {yylval.node_ptr = new Node("ASSIGN"); return ASSIGN;}
"<" {yylval.node_ptr = new Node("LT"); return LT;}
"<=" {yylval.node_ptr = new Node("LE"); return LE;}
">" {yylval.node_ptr = new Node("GT"); return GT;}
">=" {yylval.node_ptr = new Node("GE"); return GE;}
"!=" {yylval.node_ptr = new Node("NE"); return NE;}
"==" {yylval.node_ptr = new Node("EQ"); return EQ;}
"+" {yylval.node_ptr = new Node("PLUS"); return PLUS;}
"-" {yylval.node_ptr = new Node("MINUS"); return MINUS;}
"*" {yylval.node_ptr = new Node("MUL"); return MUL;}
"/" {yylval.node_ptr = new Node("DIV"); return DIV;}
"&&" {yylval.node_ptr = new Node("AND"); return AND;}
"||" {yylval.node_ptr = new Node("OR"); return OR;}
"!" {yylval.node_ptr = new Node("NOT"); return NOT;}
"(" {yylval.node_ptr = new Node("LP"); return LP;}
")" {yylval.node_ptr = new Node("RP"); return RP;}
"[" {yylval.node_ptr = new Node("LB"); return LB;}
"]" {yylval.node_ptr = new Node("RB"); return RB;}
"{" {yylval.node_ptr = new Node("LC"); return LC;}
"}" {yylval.node_ptr = new Node("RC"); return RC;}
{INT} {yylval.node_ptr = new Node(Int, yytext, atoi(yytext)); return INT;}
{FLOAT} {yylval.node_ptr = new Node(Float, yytext, (float)atof(yytext)); return FLOAT;}
{CHAR} {yylval.node_ptr = new Node(Char, yytext); return CHAR;}
{WRONG_ID} {has_error=1; fprintf(stdout,"Error type A at Line %d: unknown lexeme %s\n",
               yylineno, yytext); return ID;}
{ID} {yylval.node_ptr = new Node(Id, yytext); return ID;}
[ \t\r]+ {}
"\n" { yycolumn = 1; }
{ILLEGAL_TOKEN} {has_error=1; fprintf(stdout,"Illegal token at Line %d: %s\n",
               yylineno, yytext); return ILLEGAL_TOKEN;}
{INVALID_NUMBER} {has_error=1; fprintf(stdout,"Invalid number at Line %d: %s\n",
               yylineno, yytext); return INVALID_NUMBER;}
%%
