%{
#include<stdio.h>
#include <iostream>
#include <string>
//#define YYSTYPE Node*
extern int yylex();
extern int yyparse();
extern FILE* yyin;
Node* root = NULL;

void yyerror(const std::string& s);
%}
%token INVALID
%token TYPE 
%token STRUCT IF ELSE WHILE FOR RETURN INCLUDE
%token DOT SEMI COLON COMMA ASSIGN LT LE GT GE NE EQ PLUS MINUS MUL DIV
%token AND OR NOT
%token LP RP LB RB LC RC
%token ID INTEGER FLOAT CHAR
%token SINGLE_LINE_COMMENT MULTI_LINE_COMMENT

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
Program : ExtDefList {  $$ = Node::makeNode("Program", {$1});root = $$;}
    ;
ExtDefList :            { $$ = Node::makeNode("ExtDefList"); }
    | ExtDef ExtDefList { $$ = Node::makeNode("ExtDefList", {$1,$2}); }
    ;

ExtDef : Specifier ExtDecList SEMI  { $$ = Node::makeNode("ExtDef",{$1,$2,$3});}
    | Specifier SEMI                { $$ = Node::makeNode("ExtDef",{$1,$2}); }
    | Specifier FunDec CompSt       { $$ = Node::makeNode("ExtDef",{$1,$2,$3}); }
    | Specifier ExtDecList error    { $$ = Node::makeNode("ExtDef"); has_error = 1;yyerror("Type B,Missing semicolon \';\'") ;}
    | Specifier error               { $$ = Node::makeNode("ExtDef");  has_error = 1; yyerror("Type B,Missing semicolon \';\'"); }
    | ExtDecList SEMI         { $$ = Node::makeNode("ExtDef"); has_error = 1; yyerror("Type B,Missing specifier \';\'"); }
    ;

ExtDecList : VarDec             { $$ = Node::makeNode("ExtDecList",{$1}); }
    | VarDec COMMA ExtDecList   { $$ = Node::makeNode("ExtDecList",{$1,$2,$3}); }
    ;

/* specifier */
Specifier : TYPE        { $$ = Node::makeNode("Specifier",{$1}); }
    | StructSpecifier   { $$ = Node::makeNode("Specifier",{$1}); }
    ;

StructSpecifier : STRUCT ID LC DefList RC   { $$ = Node::makeNode("StructSpecifier",{$1,$2,$3,$4,$5}); }
    | STRUCT ID                             { $$ = Node::makeNode("StructSpecifier",{$1,$2}); }
    | STRUCT ID LC DefList error            { $$ = Node::makeNode("StructSpecifier");  has_error = 1;yyerror("Type B,Missing closing curly braces \'}\'") ;}
    | STRUCT ID DefList RC                  { $$ = Node::makeNode("StructSpecifier");  has_error = 1; yyerror("Type B,Missing closing curly braces \'{\'") ; }
    ;

/* declarator */
VarDec : ID                 { $$ = Node::makeNode("VarDec",{$1}); }
    | VarDec LB INTEGER RB     { $$ = Node::makeNode("VarDec",{$1,$2,$3,$4}); }
    | VarDec LB INTEGER error  { $$ = Node::makeNode("VarDec"); has_error = 1;yyerror("Type B,Missing closing braces \']\'");}
    | VarDec INTEGER RB        { $$ = Node::makeNode("VarDec"); has_error = 1; yyerror("Type B,Missing closing braces \']\'");}
    | INVALID               { $$ = Node::makeNode("VarDec");  has_error = 1;}
    ;

FunDec : ID LP VarList RP   { $$ = Node::makeNode("FunDec",{$1,$2,$3,$4});}
    | ID LP RP              { $$ = Node::makeNode("FunDec",{$1,$2,$3}); }
    | ID LP VarList error   { $$ = Node::makeNode("FunDec"); has_error = 1;yyerror("Type B,Missing closing parenthesis \')\'") ;}
    | ID RP                 { $$ = Node::makeNode("FunDec"); has_error = 1;yyerror("Type B,Missing closing parenthesis \'(\'") ;}
    | ID LP error           { $$ = Node::makeNode("FunDec"); has_error = 1;yyerror("Type B,Missing closing parenthesis \')\'"); }
    | INVALID LP VarList RP   { $$ = Node::makeNode("FunDec"); has_error = 1; }
    | INVALID LP RP             { $$ = Node::makeNode("FunDec"); has_error = 1; }
    | INVALID LP VarList error   { $$ = Node::makeNode("FunDec"); has_error = 1; }
    | INVALID RP                 { $$ = Node::makeNode("FunDec"); has_error = 1; }
    | INVALID LP error           { $$ = Node::makeNode("FunDec"); has_error = 1; }
    ;

VarList : ParamDec COMMA VarList    { $$ = Node::makeNode("VarList",{$1,$2,$3}); }
    | ParamDec                      { $$ = Node::makeNode("VarList",{$1}); }
    ;

ParamDec : Specifier VarDec { $$ = Node::makeNode("ParamDec",{$1,$2});  }
    ;

/* statement */
CompSt : LC DefList StmtList RC { $$ = Node::makeNode("CompSt",{$1,$2,$3,$4}); }
    | LC DefList StmtList error { $$ = Node::makeNode("ParamDec"); has_error = 1;yyerror("Type B,Missing closing curly bracket \'}\'") ;}
    ;


StmtList :                      { $$ = Node::makeNode("StmtList");  }
    | Stmt StmtList             { $$ = Node::makeNode("StmtList",{$1,$2}); }
    | Stmt Def DefList StmtList { $$ = Node::makeNode("StmtList"); has_error = 1;yyerror("Type B,Missing specifier") ;}
    ;

Stmt : SEMI                                     { $$ = Node::makeNode("Stmt",{$1}); }
    | Exp SEMI                                  { $$ = Node::makeNode("Stmt",{$1,$2}); }
    | CompSt                                    { $$ = Node::makeNode("Stmt",{$1});}
    | RETURN Exp SEMI                           { $$ = Node::makeNode("Stmt",{$1,$2,$3});}
    | IF LP Exp RP Stmt  %prec LOWER_ELSE       { $$ = Node::makeNode("Stmt",{$1,$2,$3,$4,$5}); }
    | IF LP Exp RP Stmt ELSE Stmt               { $$ = Node::makeNode("Stmt",{$1,$2,$3,$4,$5,$6,$7});  }
    | WHILE LP Exp RP Stmt                      { $$ = Node::makeNode("Stmt",{$1,$2,$3,$4,$5});}
    | Exp error                                 { $$ = Node::makeNode("Stmt"); has_error = 1;yyerror("Type B,Missing semicolon \';\'") ;}
    | RETURN Exp error                          { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Missing semicolon \';\'") ; }
    | IF LP RP  %prec LOWER_ELSE                { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Missing condition \';\'") ; }
    | IF LP RP ELSE                             { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Missing condition \';\'") ; }
    | IF LP Exp RP error  %prec LOWER_ELSE      { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Expect Stmt after if") ; }
    | IF LP Exp RP error ELSE Stmt              { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Expect Stmt after if") ;  }
    | IF error Exp RP Stmt %prec LOWER_ELSE     { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Expected \'(\' after \'if\'") ; }
    | IF error Exp RP Stmt ELSE Stmt %prec ELSE { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Expected \'(\' after \'if\'") ; }
    | IF LP Exp error Stmt %prec LOWER_ELSE     { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Missing closing parenthesis \')\'") ; }
    | IF LP Exp error Stmt ELSE Stmt %prec ELSE { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Missing closing parenthesis \')\'") ;  }
    | WHILE error Exp RP Stmt                   { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Expected \'(\' after \'while\'") ; }
    | WHILE LP Exp error Stmt                   { $$ = Node::makeNode("Stmt"); has_error = 1; yyerror("Type B,Missing closing parenthesis \')\'") ; }
    | ELSE Stmt { $$ = Node::makeNode("Stmt"); has_error = 1;yyerror("Type B,Expected \'if\' before \'else\'"); }
    ;

/* local definition */
DefList :           { $$ = Node::makeNode("DefList"); }
    | Def DefList   { $$ = Node::makeNode("DefList",{$1,$2}); }
    ;

Def : Specifier DecList SEMI    { $$ = Node::makeNode("Def",{$1,$2,$3});  }
    | Specifier DecList error   { $$ = Node::makeNode("Def",{$1,$2}); has_error = 1;yyerror("Type B,Missing semicolon \';\'");}
    ;

DecList : Dec           { $$ = Node::makeNode("DecList",{$1}); }
    | Dec COMMA DecList { $$ = Node::makeNode("DecList",{$1,$2,$3}); }
    ;

Dec : VarDec            { $$ = Node::makeNode("Dec",{$1});}
    | VarDec ASSIGN Exp { $$ = Node::makeNode("Dec",{$1,$2,$3}); }
    ;

/* Expression */
Exp : Exp ASSIGN Exp    { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Exp AND Exp       { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Exp OR Exp        { $$ = Node::makeNode("Exp",{$1,$2,$3});}
    | Exp LT Exp        { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Exp LE Exp        { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Exp GT Exp        { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Exp GE Exp        { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Exp NE Exp        { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Exp EQ Exp        { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Exp PLUS Exp      { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Exp MINUS Exp     { $$ = Node::makeNode("Exp",{$1,$2,$3});}
    | Exp MUL Exp       { $$ = Node::makeNode("Exp",{$1,$2,$3});}
    | Exp DIV Exp       { $$ = Node::makeNode("Exp",{$1,$2,$3});}
    | LP Exp RP         { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | PLUS Exp          { $$ = Node::makeNode("Exp",{$1,$2});}
    | MINUS Exp         { $$ = Node::makeNode("Exp",{$1,$2}); }
    | NOT Exp           { $$ = Node::makeNode("Exp",{$1,$2}); }
    | ID LP Args RP     {  $$ = Node::makeNode("Exp",{$1,$2,$3,$4}); }
    | ID LP RP          { $$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Exp LB Exp RB     { $$ = Node::makeNode("Exp",{$1,$2,$3,$4});}
    | Exp DOT ID        {$$ = Node::makeNode("Exp",{$1,$2,$3}); }
    | Var               { $$ = Node::makeNode("Exp",{$1}); }
    | Exp ASSIGN error    { $$ = Node::makeNode("Exp"); has_error = 1;yyerror("Type B,Missing right operand");}
    | Exp AND error       { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand"); }
    | Exp OR error        { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand"); }
    | Exp LT error        { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand");}
    | Exp LE error        { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand");}
    | Exp GT error        { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand");}
    | Exp GE error        { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand");}
    | Exp NE error        { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand");}
    | Exp EQ error        { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand");}
    | Exp PLUS error      { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand");}
    | Exp MINUS error     { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand");}
    | Exp MUL error       { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand");}
    | Exp DIV error       { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing right operand");}
    // | INVALID           { $$ = Node::makeNode("Exp"); has_error = 1; }
    | Exp INVALID Exp   { $$ = Node::makeNode("Exp"); has_error = 1; }
    //| error Exp RP      { $$ = Node::makeNode("Exp"); has_error = 1;yyerror("Missing closing parenthesis \'(\'") ;}
    | LP Exp error      { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Missing closing parenthesis \')\'") ; }
    // | MINUS error Exp RP{ $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Missing closing parenthesis \'(\'") ; }
    // | MINUS LP Exp error{ $$ = Node::makeNode("Exp"); has_error = 1;  yyerror("Missing closing parenthesis \')\'") ; }
    // | ID error Args RP  { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Missing closing parenthesis \'(\'") ; }
    | ID LP Args error  {$$ = Node::makeNode("Exp"); has_error = 1;  yyerror("Missing closing parenthesis \')\'") ; }
    // | ID error RP       { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Missing closing parenthesis \'(\'") ; }
    | ID LP error       { $$ = Node::makeNode("Exp"); has_error = 1;  yyerror("Missing closing parenthesis \')\'") ; }
    // | Exp error Exp RB  { $$ = Node::makeNode("Exp"); has_error = 1;yyerror("Type B,Missing closing braces \'[\'") ;}
    | Exp LB Exp error  { $$ = Node::makeNode("Exp"); has_error = 1; yyerror("Type B,Missing closing braces \']\'") ; }
    ;

Args : Exp COMMA Args   { $$ = Node::makeNode("Args",{$1,$2,$3}); }
    | Exp               { $$ = Node::makeNode("Args",{$1}); }
    ;

Var : INTEGER          { $$ = $1; }
    // | PLUS INTEGER     { $$ = $2; }
    // | MINUS INTEGER    {
    //                     $$ = $2;
    //                     int ll = strlen($$->val);
    //                     $$->val = (char *)realloc($$->val, (ll + 2) * sizeof(char));
    //                     for(int i=ll;i>=1;i--){
    //                         $$->val[i] = $$->val[i-1];
    //                     }
    //                     $$->val[0]='-';
    //                 }
    | ID            { $$ = $1; }
    // | PLUS ID       { $$ = $2; }
    // | MINUS ID      {
    //                     $$ = $2;
    //                     int ll = strlen($$->val);
    //                     $$->val = (char *)realloc($$->val, (ll + 2) * sizeof(char));
    //                     for(int i=ll;i>=1;i--){
    //                         $$->val[i] = $$->val[i-1];
    //                     }
    //                     $$->val[0]='-';
    //                 }
    | FLOAT         { $$ = $1; }
    // | PLUS FLOAT    { $$ = $2; }
    // | MINUS FLOAT   {
    //                     $$ = $2;
    //                     int ll = strlen($$->val);
    //                     $$->val = (char *)realloc($$->val, (ll + 2) * sizeof(char));
    //                     for(int i=ll;i>=1;i--){
    //                         $$->val[i] = $$->val[i-1];
    //                     }
    //                     $$->val[0]='-';
    //                 }
    | CHAR          { $$ = $1; }
    // | PLUS CHAR     { $$ = $2; }
    // | MINUS CHAR    {
    //                     $$ = $2;
    //                     int ll = strlen($$->val);
    //                     $$->val = (char *)realloc($$->val, (ll + 2) * sizeof(char));
    //                     for(int i=ll;i>=1;i--){
    //                         $$->val[i] = $$->val[i-1];
    //                     }
    //                     $$->val[0]='-';
    //                 }
    | INVALID       { $$ = $1; }
    // | PLUS INVALID  { $$ = $2; }
    // | MINUS INVALID { $$ = $2; }
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