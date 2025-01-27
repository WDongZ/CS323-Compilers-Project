#include "type.hpp"
#include "unordered_map"
#include "three_address_code.hpp"

// 这部分更多内容请看three_address_code.hpp
// 主要修改了to_string()函数，同时添加了variable_address类，区分了v和t两个变量，这俩变量的id是自增的，你每次new就会自动加
// 把他所有数值都变成一个类，而不是用他的什么id来管理，写的时候注意一下，可以看一下我写的variable_address类
// 还改了label类，添加了一个静态变量labelCounter，用于生成唯一的label

tac::TAC* exp_ir(Node *node, bool single = false);
std::vector<tac::TAC*> args_ir(Node *node);

void program_ir(Node *root, const std::string& inputFilePath);
void extDefList_ir(Node *node);
void extDecList_ir(Node *node, Attribute * type);
void extDef_ir(Node *node);
Attribute *specifier_ir(Node *node);
Attribute *type_ir(Node *node);
Attribute *structSpecifier_ir(Node *node);
void func_ir(Node *node, Attribute *type);
void compSt_ir(Node *node);
void defList_ir(Node *node);
void def_ir(Node *node);
void decList_ir(Node *node, Attribute *type);
void stmt_ir(Node *node);
void stmtList_ir(Node *node);
void dec_ir(Node *node, Attribute *type);
tac::TAC* varDec_ir(Node *node, Attribute* type);
void varList_ir(Node *node);
void paramDec_ir(Node *node);

void IF_ir(tac::If* id, tac::Goto* gotoid, tac::Label* tbranch, tac::Label* fbranch);
void WHILE_ir(std::vector<int>* stat_vec, size_t end, tac::Label* target);
Attribute *checkType(Node *node);