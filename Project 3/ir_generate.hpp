#include "type.hpp"
#include "unordered_map"
#include "three_address_code.hpp"

// 这部分更多内容请看three_address_code.hpp
// 主要修改了to_string()函数，同时添加了variable_address类，区分了v和t两个变量，这俩变量的id是自增的，你每次new就会自动加
// 把他所有数值都变成一个类，而不是用他的什么id来管理，写的时候注意一下，可以看一下我写的variable_address类
// 还改了label类，添加了一个静态变量labelCounter，用于生成唯一的label

tac::TAC* inter_exp(Node *node, bool single = false);
std::vector<tac::TAC*> inter_args(Node *node);

void inter_program(Node *root);
void inter_extDefList(Node *node);
void inter_extDecList(Node *node, Attribute * type);
void inter_extDef(Node *node);
Attribute *inter_specifier(Node *node);
Attribute *inter_type(Node *node);
Attribute *inter_structSpecifier(Node *node);
void inter_func(Node *node, Attribute *type);
void inter_compSt(Node *node);
void inter_defList(Node *node);
void inter_def(Node *node);
void inter_decList(Node *node, Attribute *type);
void inter_stmt(Node *node);
void inter_stmtList(Node *node);
void inter_dec(Node *node, Attribute *type);
tac::TAC* inter_varDec(Node *node, Attribute* type);
void inter_varList(Node *node);
void inter_paramDec(Node *node);

void inter_IF(tac::If* id, tac::Goto* gotoid, tac::Label* tbranch, tac::Label* fbranch);
void inter_WHILE(std::vector<int>* stat_vec, size_t end, tac::Label* target);
Attribute *checkType(Node *node);