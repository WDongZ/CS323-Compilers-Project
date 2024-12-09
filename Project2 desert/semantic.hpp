#ifndef _SYMBOL_HPP
#define _SYMBOL_HPP

#include "type.hpp"
#include "Node.hpp"
#include <unordered_map>
#include <string>

void parseProgram(Node* program);
void parseExtDefList(Node* ext_def_list);
void parseExtDef(Node* ext_def);
void parseExtDecList(Node* ext_dec_list, Attribute* attribute);
void parseVarList(Node* var_list);
void parseCompSt(Node* comp_st, Attribute* attribute);
void parseStmtList(Node* stmt_list, Attribute* attribute);
void parseStmt(Node* stmt, Attribute* attribute);

ParamsList* parseVarDec(Node* var_dec, Attribute* attribute);
ParamsList* parseParamDec(Node* param_Dec, ParamsList* paramslist);
ParamsList* parseDefList(Node* def_list, ParamsList* paramslist);
ParamsList* parseDef(Node* def, ParamsList* paramslist);
ParamsList* parseDecList(Node* dec_list, ParamsList* paramslist, Attribute* attribute);
ParamsList* parseDec(Node* dec, ParamsList* paramslist, Attribute* attribute);

Attribute* parseExp(Node* exp);
Attribute* parseSpecifier(Node* specifier);
Attribute* parseFunDec(Node* fun_dec, Attribute* attribute);

Attribute* checkArgs(Node* node1, Attribute* func_type, Node* node2);
Attribute *checkAssign(Node *node1, Node *_ASSIGN, Node *node2);


#endif