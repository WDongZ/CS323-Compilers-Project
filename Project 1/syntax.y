%{
#include<stdio.h>
#include <iostream>
#include <string>

extern int yylex();
extern int yyparse();
extern FILE* yyin;


void yyerror(const std::string& s);
%}

%%
%%

void yyerror(const std::string& s) {
    std::cerr << "Error: " << s << std::endl;
}

int main() {
    yyin = stdin;
    do {
        yyparse();
    } while (!feof(yyin));
    return 0;
}