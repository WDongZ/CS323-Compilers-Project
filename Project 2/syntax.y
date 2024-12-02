%{


#include <stdio.h>
#include <iostream>
#include <string>
#include "Node.hpp"
extern int yyparse();
extern int yylex();
extern FILE* yyin;
Node* root = nullptr;
void yyerror(const std::string& s);
int error=0;
%}

%locations
%union {
    Node* node;
}
%require "3.2"
%token<node> INVALID
%token<node> TYPE
%token<node> STRUCT IF ELSE WHILE FOR RETURN INCLUDE
%token<node> DOT SEMI COLON COMMA ASSIGN LT LE GT GE NE EQ PLUS MINUS MUL DIV
%token<node> AND OR NOT
%token<node> LP RP LB RB LC RC
%token<node> ID INTEGER FLOAT CHAR
%token<node> SINGLE_LINE_COMMENT MULTI_LINE_COMMENT
%type<node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args Var
%left INVALID
%right ASSIGN
%left OR
%left AND
%left LT LE GT GE EQ NE
%left PLUS MINUS
%left MUL DIV
%right NOT
%left DOT RP RB RC LP LB LC


%nonassoc LOWER_ELSE
%nonassoc ELSE

%%
/* high-level definition */
Program : ExtDefList {  $$ = Node::makeNode(NodeType::Program, {$1}, @$.first_line);if(error==0) {root = $$;std::cout << *root << std::endl;} }
    ;
ExtDefList :            { $$ = Node::makeNode(NodeType::ExtDefList, @$.first_line);}
    | ExtDef ExtDefList { $$ = Node::makeNode(NodeType::ExtDefList,{$1,$2}, @$.first_line); }
    ;

ExtDef : Specifier ExtDecList SEMI  { $$ = Node::makeNode(NodeType::ExtDef,{$1,$2,$3}, @$.first_line);}
    | Specifier SEMI                { $$ = Node::makeNode(NodeType::ExtDef,{$1,$2}, @$.first_line); }
    | Specifier FunDec CompSt       { $$ = Node::makeNode(NodeType::ExtDef,{$1,$2,$3}, @$.first_line); }
    | Specifier ExtDecList error    { $$ = Node::makeNode(NodeType::ExtDef, @$.first_line);error=1 ;yyerror("Type B,Missing semicolon \';\' at line " + std::to_string(@$.first_line));}
    | Specifier error               { $$ = Node::makeNode(NodeType::ExtDef, @$.first_line); error=1; yyerror("Type B,Missing semicolon \';\' at line " + std::to_string(@$.first_line)); }
    | ExtDecList SEMI         { $$ = Node::makeNode(NodeType::ExtDef, @$.first_line);error=1;   yyerror("Type B,Missing specifier \';\' at line " + std::to_string(@$.first_line)); }
    ;

ExtDecList : VarDec             { $$ = Node::makeNode(NodeType::ExtDecList,{$1}, @$.first_line); }
    | VarDec COMMA ExtDecList   { $$ = Node::makeNode(NodeType::ExtDecList,{$1,$2,$3}, @$.first_line); }
    ;

/* specifier */
Specifier : TYPE        { $$ = Node::makeNode(NodeType::Specifier,{$1}, @$.first_line); }
    | StructSpecifier   { $$ = Node::makeNode(NodeType::Specifier,{$1}, @$.first_line); }
    ;

StructSpecifier : STRUCT ID LC DefList RC   { $$ = Node::makeNode(NodeType::StructSpecifier,{$1,$2,$3,$4,$5}, @$.first_line); }
    | STRUCT ID                             { $$ = Node::makeNode(NodeType::StructSpecifier,{$1,$2}, @$.first_line); }
    | STRUCT ID LC DefList error            { $$ = Node::makeNode(NodeType::StructSpecifier, @$.first_line);error=1;   yyerror("Type B,Missing closing curly braces \'}\' at line " + std::to_string(@$.first_line));}
    | STRUCT ID DefList RC                  { $$ = Node::makeNode(NodeType::StructSpecifier, @$.first_line);  error=1;  yyerror("Type B,Missing closing curly braces \'{\' at line " + std::to_string(@$.first_line)); }
    ;

/* declarator */
VarDec : ID                 { $$ = Node::makeNode(NodeType::VarDec,{$1}, @$.first_line); }
    | VarDec LB INTEGER RB     { $$ = Node::makeNode(NodeType::VarDec,{$1,$2,$3,$4}, @$.first_line); }
    | VarDec LB INTEGER error  { $$ = Node::makeNode(NodeType::VarDec, @$.first_line);error=1;  yyerror("Type B,Missing closing braces \']\' at line " + std::to_string(@$.first_line));}
    | VarDec INTEGER RB        { $$ = Node::makeNode(NodeType::VarDec, @$.first_line); error=1;  yyerror("Type B,Missing closing braces \']\' at line " + std::to_string(@$.first_line));}
    | INVALID               { $$ = Node::makeNode(NodeType::VarDec, @$.first_line);  }
    ;

FunDec : ID LP VarList RP   { $$ = Node::makeNode(NodeType::FunDec,{$1,$2,$3,$4}, @$.first_line);}
    | ID LP RP              { $$ = Node::makeNode(NodeType::FunDec,{$1,$2,$3}, @$.first_line); }
    | ID LP VarList error   { $$ = Node::makeNode(NodeType::FunDec, @$.first_line);error=1;  yyerror("Type B,Missing closing parenthesis \')\' at line " + std::to_string(@$.first_line));}
    | ID RP                 { $$ = Node::makeNode(NodeType::FunDec, @$.first_line); error=1; yyerror("Type B,Missing closing parenthesis \'(\' at line " + std::to_string(@$.first_line));}
    | ID LP error           { $$ = Node::makeNode(NodeType::FunDec, @$.first_line); error=1; yyerror("Type B,Missing closing parenthesis \')\' at line " + std::to_string(@$.first_line)); }
    | INVALID LP VarList RP   { $$ = Node::makeNode(NodeType::FunDec, @$.first_line);  }
    | INVALID LP RP             { $$ = Node::makeNode(NodeType::FunDec, @$.first_line);  }
    | INVALID LP VarList error   { $$ = Node::makeNode(NodeType::FunDec, @$.first_line);  }
    | INVALID RP                 { $$ = Node::makeNode(NodeType::FunDec, @$.first_line);  }
    | INVALID LP error           { $$ = Node::makeNode(NodeType::FunDec, @$.first_line);  }
    ;

VarList : ParamDec COMMA VarList    { $$ = Node::makeNode(NodeType::VarList,{$1,$2,$3}, @$.first_line); }
    | ParamDec                      { $$ = Node::makeNode(NodeType::VarList,{$1}, @$.first_line); }
    ;

ParamDec : Specifier VarDec { $$ = Node::makeNode(NodeType::ParamDec,{$1,$2}, @$.first_line);  }
    ;

/* statement */
CompSt : LC DefList StmtList RC { $$ = Node::makeNode(NodeType::CompSt,{$1,$2,$3,$4}, @$.first_line); }
    | LC DefList StmtList error { $$ = Node::makeNode(NodeType::CompSt, @$.first_line);error=1;  yyerror("Type B,Missing closing curly bracket \'}\' at line " + std::to_string(@$.first_line));}
    ;


StmtList :                      { $$ = Node::makeNode(NodeType::StmtList, @$.first_line);  }
    | Stmt StmtList             { $$ = Node::makeNode(NodeType::StmtList,{$1,$2}, @$.first_line); }
    | Stmt Def DefList StmtList { $$ = Node::makeNode(NodeType::StmtList, @$.first_line); error=1; yyerror("Type B,Missing specifier at line " + std::to_string(@$.first_line));}
    ;

Stmt : SEMI                                     { $$ = Node::makeNode(NodeType::Stmt,{$1}, @$.first_line); }
    | Exp SEMI                                  { $$ = Node::makeNode(NodeType::Stmt,{$1,$2}, @$.first_line); }
    | CompSt                                    { $$ = Node::makeNode(NodeType::Stmt,{$1}, @$.first_line);}
    | RETURN Exp SEMI                           { $$ = Node::makeNode(NodeType::Stmt,{$1,$2,$3}, @$.first_line);}
    | IF LP Exp RP Stmt  %prec LOWER_ELSE       { $$ = Node::makeNode(NodeType::Stmt,{$1,$2,$3,$4,$5}, @$.first_line); }
    | IF LP Exp RP Stmt ELSE Stmt               { $$ = Node::makeNode(NodeType::Stmt,{$1,$2,$3,$4,$5,$6,$7}, @$.first_line);  }
    | WHILE LP Exp RP Stmt                      { $$ = Node::makeNode(NodeType::Stmt,{$1,$2,$3,$4,$5}, @$.first_line);}
    | Exp error                                 { $$ = Node::makeNode(NodeType::Stmt, @$.first_line);error=1;  yyerror("Type B,Missing semicolon \';\' at line " + std::to_string(@$.first_line));}
    | RETURN Exp error                          { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Missing semicolon \';\' at line " + std::to_string(@$.first_line)); }
    | IF LP RP  %prec LOWER_ELSE                { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Missing condition \';\' at line " + std::to_string(@$.first_line)); }
    | IF LP RP ELSE                             { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Missing condition \';\' at line " + std::to_string(@$.first_line)); }
    | IF LP Exp RP error  %prec LOWER_ELSE      { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Expect Stmt after if at line " + std::to_string(@$.first_line)); }
    | IF LP Exp RP error ELSE Stmt              { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Expect Stmt after if at line " + std::to_string(@$.first_line));  }
    | IF error Exp RP Stmt %prec LOWER_ELSE     { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Expected \'(\' after \'if\' at line " + std::to_string(@$.first_line)); }
    | IF error Exp RP Stmt ELSE Stmt %prec ELSE { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Expected \'(\' after \'if\' at line " + std::to_string(@$.first_line)); }
    | IF LP Exp error Stmt %prec LOWER_ELSE     { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Missing closing parenthesis \')\' at line " + std::to_string(@$.first_line)); }
    | IF LP Exp error Stmt ELSE Stmt %prec ELSE { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Missing closing parenthesis \')\' at line " + std::to_string(@$.first_line));  }
    | WHILE error Exp RP Stmt                   { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Expected \'(\' after \'while\' at line " + std::to_string(@$.first_line)); }
    | WHILE LP Exp error Stmt                   { $$ = Node::makeNode(NodeType::Stmt, @$.first_line); error=1;  yyerror("Type B,Missing closing parenthesis \')\' at line " + std::to_string(@$.first_line)); }
    | ELSE Stmt { $$ = Node::makeNode(NodeType::Stmt, @$.first_line);error=1;  yyerror("Type B,Expected \'if\' before \'else\' at line " + std::to_string(@$.first_line)); }
    | ASSIGN error{$$ = Node::makeNode(NodeType::Stmt, @$.first_line);error=1;  yyerror("Type B,Unexpected statement at line "+std::to_string(@$.first_line)); }
    ;

/* local definition */
DefList :           { $$ = Node::makeNode(NodeType::DefList, @$.first_line); }
    | Def DefList   { $$ = Node::makeNode(NodeType::DefList,{$1,$2}, @$.first_line); }
    ;

Def : Specifier DecList SEMI    { $$ = Node::makeNode(NodeType::Def,{$1,$2,$3}, @$.first_line);  }
    | Specifier DecList error   { $$ = Node::makeNode(NodeType::Def,{$1,$2}, @$.first_line);error=1;  yyerror("Type B,Missing semicolon \';\' at line " + std::to_string(@$.first_line));}
    ;

DecList : Dec           { $$ = Node::makeNode(NodeType::DecList,{$1}, @$.first_line); }
    | Dec COMMA DecList { $$ = Node::makeNode(NodeType::DecList,{$1,$2,$3}, @$.first_line); }
    ;

Dec : VarDec            { $$ = Node::makeNode(NodeType::Dec,{$1}, @$.first_line);}
    | VarDec ASSIGN Exp { $$ = Node::makeNode(NodeType::Dec,{$1,$2,$3}, @$.first_line); }
    ;

/* Expression */
Exp : Exp ASSIGN Exp    { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Exp AND Exp       { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Exp OR Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line);}
    | Exp LT Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Exp LE Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Exp GT Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Exp GE Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Exp NE Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Exp EQ Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Exp PLUS Exp      { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Exp MINUS Exp     { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line);}
    | Exp MUL Exp       { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line);}
    | Exp DIV Exp       { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line);}
    | LP Exp RP         { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | PLUS Exp          { $$ = Node::makeNode(NodeType::Exp,{$1,$2}, @$.first_line);}
    | MINUS Exp         { $$ = Node::makeNode(NodeType::Exp,{$1,$2}, @$.first_line); }
    | NOT Exp           { $$ = Node::makeNode(NodeType::Exp,{$1,$2}, @$.first_line); }
    | ID LP Args RP     {  $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3,$4}, @$.first_line); }
    | ID LP RP          { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Exp LB Exp RB     { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3,$4}, @$.first_line);}
    | Exp DOT ID        {$$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}, @$.first_line); }
    | Var               { $$ = Node::makeNode(NodeType::Exp,{$1}, @$.first_line); }
    | Exp ASSIGN error    { $$ = Node::makeNode(NodeType::Exp, @$.first_line); error=1; yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp AND error       { $$ = Node::makeNode(NodeType::Exp, @$.first_line); error=1;  yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line)); }
    | Exp OR error        { $$ = Node::makeNode(NodeType::Exp, @$.first_line); error=1;  yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line)); }
    | Exp LT error        { $$ = Node::makeNode(NodeType::Exp, @$.first_line); error=1;  yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp LE error        { $$ = Node::makeNode(NodeType::Exp, @$.first_line);  error=1; yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp GT error        { $$ = Node::makeNode(NodeType::Exp, @$.first_line); error=1;  yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp GE error        { $$ = Node::makeNode(NodeType::Exp, @$.first_line); error=1; yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp NE error        { $$ = Node::makeNode(NodeType::Exp, @$.first_line);error=1;  yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp EQ error        { $$ = Node::makeNode(NodeType::Exp, @$.first_line);error=1;  yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp PLUS error      { $$ = Node::makeNode(NodeType::Exp, @$.first_line); error=1; yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp MINUS error     { $$ = Node::makeNode(NodeType::Exp, @$.first_line);error=1;  yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp MUL error       { $$ = Node::makeNode(NodeType::Exp, @$.first_line);error=1;  yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp DIV error       { $$ = Node::makeNode(NodeType::Exp, @$.first_line);error=1;  yyerror("Type B,Missing right operand at line " + std::to_string(@$.first_line));}
    | Exp INVALID Exp   { $$ = Node::makeNode(NodeType::Exp, @$.first_line); }
    | LP Exp error      { $$ = Node::makeNode(NodeType::Exp, @$.first_line); error=1; yyerror("Missing closing parenthesis \')\' at line " + std::to_string(@$.first_line));}
    | ID LP Args error  {$$ = Node::makeNode(NodeType::Exp, @$.first_line); error=1;  yyerror("Missing closing parenthesis \')\'at line " + std::to_string(@$.first_line));}
    | ID LP error       { $$ = Node::makeNode(NodeType::Exp, @$.first_line);error=1;   yyerror("Missing closing parenthesis \')\'at line " + std::to_string(@$.first_line));}
    | Exp LB Exp error  { $$ = Node::makeNode(NodeType::Exp, @$.first_line);error=1;  yyerror("Type B,Missing closing braces \']\'at line " + std::to_string(@$.first_line));}
    ;

Args : Exp COMMA Args   { $$ = Node::makeNode(NodeType::Args,{$1,$2,$3}, @$.first_line);}
    | Exp               { $$ = Node::makeNode(NodeType::Args,{$1}, @$.first_line);}
    ;

Var : INTEGER          { $$ = $1;}
    | ID            { $$ = $1; }
    | FLOAT         { $$ = $1; }
    | CHAR          { $$ = $1;}
    | INVALID       { $$ = $1; }
    ;

%%

void yyerror(const std::string& s) {
    if (s != "syntax error") {
        std::cerr << "Error: "<<s << std::endl;
    }
}

int main() {
    yyin = stdin;
    do {
        yyparse();
    } while (!feof(yyin));
    return 0;
}