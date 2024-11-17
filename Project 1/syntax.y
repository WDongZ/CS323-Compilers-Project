%{
#include<stdio.h>
#include "lex.yy.c"
#include <iostream>
#include <string>
#include "Node.hpp"
extern int yylex();
extern int yyparse();
extern FILE* yyin;
Node* root = nullptr;

void yyerror(const std::string& s);
%}
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
Program : ExtDefList {  $$ = Node::makeNode(NodeType::Program, {$1});root = $$;}
    ;
ExtDefList :            { $$ = Node::makeNode(NodeType::ExtDefList);}
    | ExtDef ExtDefList { $$ = Node::makeNode(NodeType::ExtDefList,{$1,$2}); }
    ;

ExtDef : Specifier ExtDecList SEMI  { $$ = Node::makeNode(NodeType::ExtDef,{$1,$2,$3});}
    | Specifier SEMI                { $$ = Node::makeNode(NodeType::ExtDef,{$1,$2}); }
    | Specifier FunDec CompSt       { $$ = Node::makeNode(NodeType::ExtDef,{$1,$2,$3}); }
    | Specifier ExtDecList error    { $$ = Node::makeNode(NodeType::ExtDef); yyerror("Type B,Missing semicolon \';\'") ;}
    | Specifier error               { $$ = Node::makeNode(NodeType::ExtDef);   yyerror("Type B,Missing semicolon \';\'"); }
    | ExtDecList SEMI         { $$ = Node::makeNode(NodeType::ExtDef);  yyerror("Type B,Missing specifier \';\'"); }
    ;

ExtDecList : VarDec             { $$ = Node::makeNode(NodeType::ExtDecList,{$1}); }
    | VarDec COMMA ExtDecList   { $$ = Node::makeNode(NodeType::ExtDecList,{$1,$2,$3}); }
    ;

/* specifier */
Specifier : TYPE        { $$ = Node::makeNode(NodeType::Specifier,{$1}); }
    | StructSpecifier   { $$ = Node::makeNode(NodeType::Specifier,{$1}); }
    ;

StructSpecifier : STRUCT ID LC DefList RC   { $$ = Node::makeNode(NodeType::StructSpecifier,{$1,$2,$3,$4,$5}); }
    | STRUCT ID                             { $$ = Node::makeNode(NodeType::StructSpecifier,{$1,$2}); }
    | STRUCT ID LC DefList error            { $$ = Node::makeNode(NodeType::StructSpecifier);  yyerror("Type B,Missing closing curly braces \'}\'") ;}
    | STRUCT ID DefList RC                  { $$ = Node::makeNode(NodeType::StructSpecifier);   yyerror("Type B,Missing closing curly braces \'{\'") ; }
    ;

/* declarator */
VarDec : ID                 { $$ = Node::makeNode(NodeType::VarDec,{$1}); }
    | VarDec LB INTEGER RB     { $$ = Node::makeNode(NodeType::VarDec,{$1,$2,$3,$4}); }
    | VarDec LB INTEGER error  { $$ = Node::makeNode(NodeType::VarDec); yyerror("Type B,Missing closing braces \']\'");}
    | VarDec INTEGER RB        { $$ = Node::makeNode(NodeType::VarDec);  yyerror("Type B,Missing closing braces \']\'");}
    | INVALID               { $$ = Node::makeNode(NodeType::VarDec);  }
    ;

FunDec : ID LP VarList RP   { $$ = Node::makeNode(NodeType::FunDec,{$1,$2,$3,$4});}
    | ID LP RP              { $$ = Node::makeNode(NodeType::FunDec,{$1,$2,$3}); }
    | ID LP VarList error   { $$ = Node::makeNode(NodeType::FunDec); yyerror("Type B,Missing closing parenthesis \')\'") ;}
    | ID RP                 { $$ = Node::makeNode(NodeType::FunDec); yyerror("Type B,Missing closing parenthesis \'(\'") ;}
    | ID LP error           { $$ = Node::makeNode(NodeType::FunDec); yyerror("Type B,Missing closing parenthesis \')\'"); }
    | INVALID LP VarList RP   { $$ = Node::makeNode(NodeType::FunDec);  }
    | INVALID LP RP             { $$ = Node::makeNode(NodeType::FunDec);  }
    | INVALID LP VarList error   { $$ = Node::makeNode(NodeType::FunDec);  }
    | INVALID RP                 { $$ = Node::makeNode(NodeType::FunDec);  }
    | INVALID LP error           { $$ = Node::makeNode(NodeType::FunDec);  }
    ;

VarList : ParamDec COMMA VarList    { $$ = Node::makeNode(NodeType::VarList,{$1,$2,$3}); }
    | ParamDec                      { $$ = Node::makeNode(NodeType::VarList,{$1}); }
    ;

ParamDec : Specifier VarDec { $$ = Node::makeNode(NodeType::ParamDec,{$1,$2});  }
    ;

/* statement */
CompSt : LC DefList StmtList RC { $$ = Node::makeNode(NodeType::CompSt,{$1,$2,$3,$4}); }
    | LC DefList StmtList error { $$ = Node::makeNode(NodeType::CompSt); yyerror("Type B,Missing closing curly bracket \'}\'") ;}
    ;


StmtList :                      { $$ = Node::makeNode(NodeType::StmtList);  }
    | Stmt StmtList             { $$ = Node::makeNode(NodeType::StmtList,{$1,$2}); }
    | Stmt Def DefList StmtList { $$ = Node::makeNode(NodeType::StmtList); yyerror("Type B,Missing specifier") ;}
    ;

Stmt : SEMI                                     { $$ = Node::makeNode(NodeType::Stmt,{$1}); }
    | Exp SEMI                                  { $$ = Node::makeNode(NodeType::Stmt,{$1,$2}); }
    | CompSt                                    { $$ = Node::makeNode(NodeType::Stmt,{$1});}
    | RETURN Exp SEMI                           { $$ = Node::makeNode(NodeType::Stmt,{$1,$2,$3});}
    | IF LP Exp RP Stmt  %prec LOWER_ELSE       { $$ = Node::makeNode(NodeType::Stmt,{$1,$2,$3,$4,$5}); }
    | IF LP Exp RP Stmt ELSE Stmt               { $$ = Node::makeNode(NodeType::Stmt,{$1,$2,$3,$4,$5,$6,$7});  }
    | WHILE LP Exp RP Stmt                      { $$ = Node::makeNode(NodeType::Stmt,{$1,$2,$3,$4,$5});}
    | Exp error                                 { $$ = Node::makeNode(NodeType::Stmt); yyerror("Type B,Missing semicolon \';\'") ;}
    | RETURN Exp error                          { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing semicolon \';\'") ; }
    | IF LP RP  %prec LOWER_ELSE                { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing condition \';\'") ; }
    | IF LP RP ELSE                             { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing condition \';\'") ; }
    | IF LP Exp RP error  %prec LOWER_ELSE      { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expect Stmt after if") ; }
    | IF LP Exp RP error ELSE Stmt              { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expect Stmt after if") ;  }
    | IF error Exp RP Stmt %prec LOWER_ELSE     { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expected \'(\' after \'if\'") ; }
    | IF error Exp RP Stmt ELSE Stmt %prec ELSE { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expected \'(\' after \'if\'") ; }
    | IF LP Exp error Stmt %prec LOWER_ELSE     { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing closing parenthesis \')\'") ; }
    | IF LP Exp error Stmt ELSE Stmt %prec ELSE { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing closing parenthesis \')\'") ;  }
    | WHILE error Exp RP Stmt                   { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expected \'(\' after \'while\'") ; }
    | WHILE LP Exp error Stmt                   { $$ = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing closing parenthesis \')\'") ; }
    | ELSE Stmt { $$ = Node::makeNode(NodeType::Stmt); yyerror("Type B,Expected \'if\' before \'else\'"); }
    ;

/* local definition */
DefList :           { $$ = Node::makeNode(NodeType::DefList); }
    | Def DefList   { $$ = Node::makeNode(NodeType::DefList,{$1,$2}); }
    ;

Def : Specifier DecList SEMI    { $$ = Node::makeNode(NodeType::Def,{$1,$2,$3});  }
    | Specifier DecList error   { $$ = Node::makeNode(NodeType::Def,{$1,$2}); yyerror("Type B,Missing semicolon \';\'");}
    ;

DecList : Dec           { $$ = Node::makeNode(NodeType::DecList,{$1}); }
    | Dec COMMA DecList { $$ = Node::makeNode(NodeType::DecList,{$1,$2,$3}); }
    ;

Dec : VarDec            { $$ = Node::makeNode(NodeType::Dec,{$1});}
    | VarDec ASSIGN Exp { $$ = Node::makeNode(NodeType::Dec,{$1,$2,$3}); }
    ;

/* Expression */
Exp : Exp ASSIGN Exp    { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Exp AND Exp       { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Exp OR Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3});}
    | Exp LT Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Exp LE Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Exp GT Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Exp GE Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Exp NE Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Exp EQ Exp        { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Exp PLUS Exp      { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Exp MINUS Exp     { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3});}
    | Exp MUL Exp       { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3});}
    | Exp DIV Exp       { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3});}
    | LP Exp RP         { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | PLUS Exp          { $$ = Node::makeNode(NodeType::Exp,{$1,$2});}
    | MINUS Exp         { $$ = Node::makeNode(NodeType::Exp,{$1,$2}); }
    | NOT Exp           { $$ = Node::makeNode(NodeType::Exp,{$1,$2}); }
    | ID LP Args RP     {  $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3,$4}); }
    | ID LP RP          { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Exp LB Exp RB     { $$ = Node::makeNode(NodeType::Exp,{$1,$2,$3,$4});}
    | Exp DOT ID        {$$ = Node::makeNode(NodeType::Exp,{$1,$2,$3}); }
    | Var               { $$ = Node::makeNode(NodeType::Exp,{$1}); }
    | Exp ASSIGN error    { $$ = Node::makeNode(NodeType::Exp); yyerror("Type B,Missing right operand");}
    | Exp AND error       { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand"); }
    | Exp OR error        { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand"); }
    | Exp LT error        { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
    | Exp LE error        { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
    | Exp GT error        { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
    | Exp GE error        { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
    | Exp NE error        { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
    | Exp EQ error        { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
    | Exp PLUS error      { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
    | Exp MINUS error     { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
    | Exp MUL error       { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
    | Exp DIV error       { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
    // | INVALID           { $$ = Node::makeNode(NodeType::Exp);  }
    | Exp INVALID Exp   { $$ = Node::makeNode(NodeType::Exp);  }
    //| error Exp RP      { $$ = Node::makeNode(NodeType::Exp); yyerror("Missing closing parenthesis \'(\'") ;}
    | LP Exp error      { $$ = Node::makeNode(NodeType::Exp);  yyerror("Missing closing parenthesis \')\'") ; }
    // | MINUS error Exp RP{ $$ = Node::makeNode(NodeType::Exp);  yyerror("Missing closing parenthesis \'(\'") ; }
    // | MINUS LP Exp error{ $$ = Node::makeNode(NodeType::Exp);   yyerror("Missing closing parenthesis \')\'") ; }
    // | ID error Args RP  { $$ = Node::makeNode(NodeType::Exp);  yyerror("Missing closing parenthesis \'(\'") ; }
    | ID LP Args error  {$$ = Node::makeNode(NodeType::Exp);   yyerror("Missing closing parenthesis \')\'") ; }
    // | ID error RP       { $$ = Node::makeNode(NodeType::Exp);  yyerror("Missing closing parenthesis \'(\'") ; }
    | ID LP error       { $$ = Node::makeNode(NodeType::Exp);   yyerror("Missing closing parenthesis \')\'") ; }
    // | Exp error Exp RB  { $$ = Node::makeNode(NodeType::Exp); yyerror("Type B,Missing closing braces \'[\'") ;}
    | Exp LB Exp error  { $$ = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing closing braces \']\'") ; }
    ;

Args : Exp COMMA Args   { $$ = Node::makeNode(NodeType::Args,{$1,$2,$3}); }
    | Exp               { $$ = Node::makeNode(NodeType::Args,{$1}); }
    ;

Var : INTEGER          { $$ = $1; }
    | ID            { $$ = $1; }
    | FLOAT         { $$ = $1; }
    | CHAR          { $$ = $1; }
    | INVALID       { $$ = $1; }
    ;

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