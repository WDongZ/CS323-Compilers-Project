#include "symbol.hpp"
#include "semantic.hpp"
#include <iostream>
#include <string>
ScopeStack *stack;

void printDebugMsg(const std::string& msg){
    std::cout << msg << std::endl;
}

void parseProgram(Node *program)
{
    printDebugMsg("parseprogram done");
    stack = new ScopeStack(nullptr);
    stack->pushScope();
    parseExtDefList(program->children[0]);
    stack->popScope();
}

void parseExtDefList(Node *ext_def_list)
{
    printDebugMsg("ExtDefList");
    if (ext_def_list->children.size() == 0)
        return;
    Node *ext_def = ext_def_list->children[0];
    Node *ext_def_list1 = ext_def_list->children[1];
    parseExtDef(ext_def);
    parseExtDefList(ext_def_list1);
}

void parseExtDef(Node *ext_def) // 标记
{
    printDebugMsg("ExtDef");
    Node *specifier = ext_def->children[0];
    Attribute *attribute = parseSpecifier(specifier);
    Node *child = ext_def->children[1];

    if (child->type == ExtDecList)
    {
        Node *ext_dec_list = child;
        Node *_SEMI = ext_dec_list->children[0];
        parseExtDecList(ext_dec_list, attribute);
    }
    else if (child->type == FunDec)
    {
        stack->pushScope();
        Node *fun_dec = child;
        Node *comp_st = ext_def->children[0];
        Attribute *fun_dec_attribute = parseFunDec(fun_dec, attribute);

        if (fun_dec_attribute != nullptr)
        {
            std::string func_name = fun_dec_attribute->params_ptr->name;
            if (stack->lookup(func_name))
            {
                std::cout << "Error type 4 at line " << fun_dec->linec << ": redefine function: " << func_name << std::endl;
            }
            else
            {
                stack->top->insert(func_name, fun_dec_attribute);
                parseCompSt(comp_st, attribute);
            }
        }
    }
}

Attribute *parseSpecifier(Node *Specifier)
{ //
    printDebugMsg("specifier");
    int i = 0;
    Attribute *attribute = nullptr;
    Node *node = Specifier->children[0];
    if (node->type == NodeType::Type)
    { // 当node的节点类型是Type的时候
        if (node->getText() == "int")
        {
            attribute = new Attribute(Category::PRIMITIVE, NodeType::Int);
        }
        else if (node->getText() == "float")
        {
            attribute = new Attribute(Category::PRIMITIVE, NodeType::Float);
        }
        else
        {
            attribute = new Attribute(Category::PRIMITIVE, NodeType::Float);
        } // 判断节点类型Type的类型并且赋值给attribute
    }
    else if (node->type == NodeType::StructSpecifier)
    { // 如果节点类型是stuctSpecifier => STRUCT ID LC DefList RC || STRUCT ID
        Node *_struct = node->children[0];
        Node *struct_id = node->children[1];
        std::string struct_name = struct_id->getText();

        if (node->children.size() != 2)
        { // STRUCT ID LC DefList RC
            if (stack->lookup(struct_name) != nullptr)
            {
                std::cout << "Error type 15 at line " << struct_id->linec << ": redefine struct: " << struct_name << std::endl;
                return nullptr;
            }

            Node *_LC = node->children[2];
            Node *def_list = node->children[3];
            Node *_RC = node->children[4];

            ParamsList *params_ptr = parseDefList(def_list, nullptr);
            attribute = new Attribute(Category::STRUCTURE, params_ptr);
            stack->top->insert(struct_name, attribute);
        }
        else
        { // STRUCT ID
            if (stack->lookup(struct_name) == nullptr)
            {
                std::cout << "Error type 3 at line " << struct_id->linec << ": redefine variable: " << struct_name << std::endl; // 使用一个struct，但是并不存在这个struct
                return nullptr;
            }
            // if(stack->lookup(struct_name)->category != Category::STRUCTURE){
            //     std::cout << "Error type 3 at line " << struct_id->linec << ": redefine variable: " << struct_name << std::endl; //使用一个struct，标准存在这个名称，但是这个名称并不是一个struct
            // } 删除
            attribute = stack->top->lookup(struct_name);
        }
    }
    return attribute;
}

ParamsList *parseDefList(Node *def_list, ParamsList *paramslist) // 递归是否要使用参数i 然后调用i+1？
{
    printDebugMsg("deflist");
    if (def_list->children.size() == 0)
    { // 无参
        return paramslist;
    }
    Node *def = def_list->children[0];
    if (paramslist == nullptr)
    {
        paramslist = parseDef(def, paramslist);
    }
    else
    {
        paramslist->next = parseDef(def, paramslist);
    }
    parseDefList(def_list->children[1], paramslist);
    return paramslist;
}

ParamsList *parseDef(Node *def, ParamsList *paramslist)
{
    printDebugMsg("def");
    Node *specifier = def->children[0];
    Node *dec_list = def->children[1]; // def ->Specifier DecList SEMI

    Attribute *attribute = parseSpecifier(specifier);
    paramslist = parseDecList(dec_list, paramslist, attribute);

    return paramslist;
}

ParamsList *parseDecList(Node *dec_list, ParamsList *paramslist, Attribute *attribute) // DecList -> Dec | Dec COMMA DecList
{
    printDebugMsg("decList");
    Node *dec = dec_list->children[0];
    paramslist = parseDec(dec, paramslist, attribute);
    if (dec_list->children.size() != 1)
    {
        Node *_COMMA = dec_list->children[1];
        Node *dec_list1 = dec_list->children[2];
        paramslist = parseDecList(dec_list1, paramslist, attribute);
    }
    return paramslist;
}

ParamsList *parseDec(Node *dec, ParamsList *paramslist, Attribute *attribute) // Dec -> VarDec | Dec -> VarDec ASSIGN Exp
{
    printDebugMsg("dec");
    Node *var_dec = dec->children[0];
    ParamsList *var_dec_fields = parseVarDec(var_dec, attribute);
    if (dec->children.size() != 1)
    {
        Node *_ASSIGN = dec->children[1];
        Node *exp = dec->children[2];
        Attribute *exp_attribute = parseExp(exp);
        if (!AttributeCompare(attribute, exp_attribute))
        {
            std::cout << "Error type 5 at line " << var_dec->linec << ": unmatching type on both sides of assignment " << std::endl;
        }
    }
    return var_dec_fields;
}

ParamsList *parseVarDec(Node *var_dec, Attribute *attribute) // VarDec->ID | VarDec -> ID LP VarList RP
{
    printDebugMsg("vardec");
    Attribute *last_attribute = attribute;
    Node *next_node = nullptr;
    while (var_dec->children.size() == 4)
    {
        next_node = var_dec->children[0];
        Node *LP = var_dec->children[1];
        Node *int_node = var_dec->children[2];
        Node *RP = var_dec->children[3];

        Array *new_array = new Array(last_attribute, stoi(int_node->getText())); // 标记
        Attribute *new_attribute = new Attribute(Category::ARRAY, new_array);
        last_attribute = new_attribute;
        var_dec = next_node; //
    }
    Node *id = var_dec->children[0];
    ParamsList *result = new ParamsList(id->getText(), last_attribute, nullptr);
    if (stack->lookup(result->name) != nullptr)
    {
        std::cout << "Error type 3 at line " << id->linec << ": redefine variable: " << result->name << std::endl;
    }
    stack->top->insert(result->name, last_attribute);
    return result;
}

void parseVarList(Node *var_list, ParamsList *paramslist) // VarList -> ParamDec COMMA VarList | VarList -> ParamDec
{
    printDebugMsg("varlist");
    Node *param_dec = var_list->children[0];
    paramslist = parseParamDec(param_dec, paramslist);
    if (var_list->children.size() != 1)
    {
        Node *_COMMA = var_list->children[1];
        Node *var_list1 = var_list->children[2];
        parseVarList(var_list1, paramslist);
    }
}

ParamsList *parseParamDec(Node *param_dec, ParamsList *paramslist) // ParamDec -> Specifier VarDec
{
    printDebugMsg("paramDec");
    Node *specifier = param_dec->children[0];
    Attribute *specifier_attribute = parseSpecifier(specifier);
    if (specifier_attribute != nullptr)
    {
        Node *var_dec = param_dec->children[1];
        ParamsList *temp = parseVarDec(var_dec, specifier_attribute);
        paramslist->next = temp;
        paramslist = temp;
    }
    return paramslist; // 标记
}

Attribute *parseExp(Node *exp)
{ // 1. 3. 4.
    printDebugMsg("exp");
    Attribute *attribute = nullptr;
    if (exp->children.size() == 1)
    {
        Node *node1 = exp->children[0];
        if (node1->type == NodeType::Id)
        {
            if (stack->lookup(node1->getText()) == nullptr)
            {
                std::cout << "Error type 1 at line " << node1->linec << ": undefined variable: " << node1->getText() << std::endl;
            }
            else
            {
                attribute = stack->lookup(node1->getText());
            }
        }
        else if (node1->type == NodeType::Int)
        {
            return new Attribute(Category::PRIMITIVE, NodeType::Int);
        }
        else if (node1->type == NodeType::Float)
        {
            return new Attribute(Category::PRIMITIVE, NodeType::Float);
        }
        else if (node1->type == NodeType::Char)
        {
            return new Attribute(Category::PRIMITIVE, NodeType::Char);
        }
        else
        {
            return nullptr;
        }
    }
    else if (exp->children.size() == 2)
    { // MINUS NOT
        Node *node1 = exp->children[0];
        Node *node2 = exp->children[1];
        Attribute *exp_attribute = parseExp(node2);
        if (node1->type == NodeType::Not)
        {
            if (!(exp_attribute->category == Category::PRIMITIVE && exp_attribute->nodetype == NodeType::Int))
            {
                std::cout << "Error type 7 at line " << node1->linec << ": binary operation on non-number variables " << std::endl;
            }
            else
            {
                attribute == new Attribute(Category::PRIMITIVE, NodeType::Int);
            }
        }
        else if (node1->type == NodeType::Minus)
        {
            if (exp_attribute->category == Category::PRIMITIVE || exp_attribute->nodetype == NodeType::Char)
            {
                std::cout << "Error type 7 at line " << node1->linec << ": binary operation on non-number variables " << std::endl;
            }
            else
            {
                attribute == exp_attribute;
            }
        }
    }
    else if (exp->children.size() == 3)
    {
        Node *node1 = exp->children[0];
        Node *node2 = exp->children[1];
        Node *node3 = exp->children[2];
        if (node2->type == NodeType::Assign)
        {
            attribute = checkAssign(node1, node2, node3);
        }
        else if (node2->type == NodeType::Lt || node2->type == NodeType::Le || node2->type == NodeType::Ge || node2->type == NodeType::Gt ||
                 node2->type == NodeType::Ne || node2->type == NodeType::Eq || node2->type == NodeType::Plus || node2->type == NodeType::Minus ||
                 node2->type == NodeType::Mul || node2->type == NodeType::Div)
        {
            Attribute *node1_attribute = parseExp(node1);
            Attribute *node2_attribute = parseExp(node3);
            if (!AttributeCompare(node1_attribute, node2_attribute) || node1_attribute->category != Category::PRIMITIVE)
            {
                std::cout << "Error type 7 at line " << node1->linec << ": binary operation on non-number variables " << std::endl;
            }
            else
            {
                attribute = node1_attribute;
            }
        }
        else if (node2->type == NodeType::And || node2->type == NodeType::Or)
        {
            Attribute *node1_attribute = parseExp(node1);
            Attribute *node2_attribute = parseExp(node2);
            if (!AttributeCompare(node1_attribute, node2_attribute) || !(node1_attribute->category == Category::PRIMITIVE && node1_attribute->nodetype == NodeType::Int))
            {
                std::cout << "Error type 7 at line " << node1->linec << ": binary operation on non-number variables " << std::endl;
            }
            else
            {
                attribute = node1_attribute;
            }
        }
        else if (node2->type == NodeType::Dot)
        {
            Attribute *node1_attribute = parseExp(node1);
            if (node1_attribute->category != Category::STRUCTURE)
            {
                std::cout << "Error type 13 at line " << node1->linec << ": accessing with non-struct variable " << std::endl;
            }
            else
            {
                ParamsList *paramslist = nullptr;
                for (paramslist = node1_attribute->params_ptr; paramslist != nullptr; paramslist = paramslist->next)
                {
                    if (paramslist->name == node3->getText())
                        break;
                }
                if (paramslist == nullptr)
                {
                    std::cout << "Error type 14 at line " << node1->linec << ": no such member: " << node3->getText() << std::endl;
                }
                else
                {
                    attribute = paramslist->global_type;
                }
            }
        }
        else if (node1->type == NodeType::Lp)
        { // LP Exp RP
            attribute = parseExp(node2);
        }
        else if (node1->type == NodeType::Id)
        {
            if (stack->lookup(node1->getText()) == nullptr)
            {
                std::cout << "Error type 2 at line " << node1->linec << ": undefined function: " << node1->getText() << std::endl;
                return nullptr;
            }
            else if (stack->lookup(node1->getText())->category != Category::FUNCTION)
            {
                std::cout << "Error type 11 at line " << node1->linec << ": invoking non-function variable: " << node1->getText() << std::endl;
                return nullptr;
            }
            Attribute *func_attribute = stack->lookup(node1->getText());
            if (func_attribute->params_ptr->next == nullptr)
            {
                attribute = func_attribute->params_ptr->global_type;
            }
            else
            {
                std::cout << "Error type 9 at line " << node1->linec << ": invalid argument number for compares, " << node1->getText() << std::endl;
            }
        }
    }
    else if (exp->children.size() == 4)
    {
        Node *node1 = exp->children[0];
        Node *node2 = exp->children[1];
        Node *node3 = exp->children[2];
        Node *node4 = exp->children[3];
        if (node1->type == NodeType::Id) // ID LP Args RP
        {
            if (stack->lookup(node1->getText()) == nullptr)
            {
                std::cout << "Error type 2 at line " << node1->linec << ": undefined function: " << node1->getText() << std::endl;
                return nullptr;
            }
            else if (stack->lookup(node1->getText())->category != Category::FUNCTION)
            {
                std::cout << "Error type 11 at line " << node1->linec << ": invoking non-function variable: " << node1->getText() << std::endl;
                return nullptr;
            }
            Attribute *func_attribute = stack->lookup(node1->getText());
            attribute = checkArgs(node1, func_attribute, node3);
        }
        else if (node2->type == NodeType::Lb)
        { // Exp Lb EXP RB
            Attribute *node1_attribute = parseExp(node1);
            Attribute *node3_attribute = parseExp(node3);
            if (node1_attribute->category != Category::ARRAY)
            {
                std::cout << "Error type 10 at line " << node1->linec << ": indexing on non-array variable " << std::endl;
            }
            else if (!(node3_attribute->category == Category::PRIMITIVE && node1_attribute->nodetype == NodeType::Int))
            {
                std::cout << "Error type 12 at line " << node1->linec << ": indexing by non-integer " << std::endl;
                attribute = node1_attribute->array_ptr->base;
            }
            else
            {
                attribute = node1_attribute->array_ptr->base;
            }
        }
    }
    return attribute;
}

Attribute *parseFunDec(Node *fun_dec, Attribute *attribute) // ID LP VarList RP | ID LP RP
{
    printDebugMsg("fundec");
    Node *func_id = fun_dec->children[0];
    ParamsList *paramslist = new ParamsList(func_id->getText(), attribute, nullptr);
    Attribute *ans_attribute = new Attribute(Category::FUNCTION, paramslist);
    if (fun_dec->children.size() == 4)
    {
        Node *_LP = fun_dec->children[1];
        Node *var_list = fun_dec->children[2];
        Node *_RP = fun_dec->children[3];
        parseVarList(var_list, paramslist);
    }
    return ans_attribute;
}

void parseCompSt(Node *comp_st, Attribute *attribute) // LC DefList StmtList RC
{
    printDebugMsg("compst");
    Node *_LC = comp_st->children[0];
    Node *def_list = comp_st->children[1];
    Node *stmt_list = comp_st->children[2];
    Node *_RC = comp_st->children[3];
    parseDefList(def_list, nullptr);
    parseStmtList(stmt_list, attribute);
}

void parseStmtList(Node *stmt_list, Attribute *attribute) // stmt StmtList
{
    printDebugMsg("stmtlist");
    if (stmt_list->children.size() != 0)
    {
        Node *stmt = stmt_list->children[0];
        Node *stmt_list1 = stmt_list->children[1];
        parseStmt(stmt, attribute);
        parseStmtList(stmt_list1, attribute);
    }
}

void parseStmt(Node *stmt, Attribute *attribute)
{
    printDebugMsg("stmt");
    Node *node1 = stmt->children[0];
    if (node1->type == NodeType::Exp)
    {
        parseExp(node1);
    }
    else if (node1->type == NodeType::CompSt)
    {
        parseCompSt(node1, attribute);
    }
    else if (node1->type == NodeType::Return) // return exp semi
    {
        Node *exp = stmt->children[1];
        Attribute *exp_attribute = parseExp(exp);
        if (exp_attribute != nullptr && !AttributeCompare(attribute, exp_attribute))
        {
            std::cout << "Error type 8 at line " << node1->linec << ": icompatiable return type " << std::endl;
        }
    }
    else if (node1->type == NodeType::If) // if lp exp rp stmt
    {
        Node *_LP = stmt->children[1];
        Node *exp = stmt->children[2];
        Node *_RP = stmt->children[3];
        Node *stmt1 = stmt->children[4];
        Attribute *exp_attribute = parseExp(exp);
        if (exp_attribute != nullptr)
        {
            if (!(exp_attribute->category == Category::PRIMITIVE && exp_attribute->nodetype == NodeType::Int))
            {
                std::cout << "Error type 7 at line " << exp->linec << ": binary operation on non-number variables" << std::endl;
            }
            else
            {
                parseStmt(stmt1, attribute);
                if (stmt->children.size() == 7)
                { // if lp exp rp stmt else stmt
                    Node *_ELSE = stmt->children[6];
                    Node *stmt2 = stmt->children[7];
                    parseStmt(stmt2, attribute);
                }
            }
        }
    }
    else if (node1->type == NodeType::While) // while lp exp rp stmt
    {   
        Node* _LP = stmt->children[1];
        Node* exp = stmt->children[2];
        Attribute* exp_attribute = parseExp(exp);
        if(exp_attribute != nullptr) {
            if(!(exp_attribute->category == Category::PRIMITIVE && exp_attribute->nodetype == NodeType::Int)){
                std::cout << "Error type 7 at line " << exp->linec << ": binary operation on non-number variables" << std::endl;
            }else {
                Node* _RP = stmt->children[3];
                Node* stmt1 = stmt->children[4];
                parseStmt(stmt1, attribute);
            }
        }
    }
}

void parseExtDecList(Node *ext_dec_list, Attribute *attribute) // ExtDecList -> VarDec | ExtDecList -> VarDec COMMA ExtDecList
{
    printDebugMsg("ExtDecList");
    Node* var_dec = ext_dec_list->children[0];
    parseVarDec(var_dec, attribute);
    if(ext_dec_list->children.size()!= 1){
        Node* _COMMA = ext_dec_list->children[2];
        Node* ext_dec_list1 = ext_dec_list->children[3];
        parseExtDecList(ext_dec_list1, attribute);
    }
}

Attribute *checkArgs(Node *node1, Attribute *func_type, Node *node2)
{
    ParamsList *args = func_type->params_ptr->next;
    Attribute *attribute = nullptr;
    if (args == nullptr)
    {
        std::cout << "Error type 9 at line " << node2->linec << ": invalid argument number for compare, " << node2->getText() << std::endl;
    }
    Node *exp = node1->children[0];
    while (true)
    {
        Attribute *exp_attribute = parseExp(node1);
        if (exp_attribute != nullptr)
        {
            if (!AttributeCompare(exp_attribute, args->global_type))
            {
                std::cout << "Error type 9 at line " << node2->linec << ": invalid argument number for compare, " << node2->getText() << std::endl;
                break;
            }
            else if (args == nullptr && node1->children.size() == 1)
            {
                attribute = func_type->params_ptr->global_type;
                break;
            }
            else if (args != nullptr && node1->children.size() == 1)
            {
                std::cout << "Error type 9 at line " << node2->linec << ": invalid argument number for compare, " << node2->getText() << std::endl;
                break;
            }
            else if (args == nullptr && node1->children.size() != 1)
            {
                std::cout << "Error type 9 at line " << node2->linec << ": invalid argument number for compare, " << node2->getText() << std::endl;
                break;
            }
            Node *_COMMA = node1->children[1];
            node1 = node1->children[2];
            exp = node1->children[0];
        }
        else
        {
            break;
        }
    }
    return attribute;
}

Attribute *checkAssign(Node *node1, Node *_ASSIGN, Node *node2)
{
    Attribute *attribute = nullptr;
    Attribute *node1_attribute = parseExp(node1);
    Attribute *node2_attribute = parseExp(node2);
    bool flag = false;
    switch (node1->children.size())
    {
    case 1:
    { // ID 标识符
        Node *id = node1->children[0];
        if (id->type == NodeType::Id)
        {
            flag = true;
        }
        break;
    }
    case 3: // EXP dot id 结构成员
    {
        Node *exp = node1->children[0];
        Node *_DOT = node1->children[1];
        Node *id = node1->children[2];
        if (exp->type == NodeType::Exp && _DOT->type == NodeType::Dot && id->type == NodeType::Id)
        {
            flag = true;
        }
        break;
    }
    case 4: // EXP LB EXP RB 数组索引
    {
        Node *exp1 = node1->children[0];
        Node *exp2 = node1->children[2];
        Node *_LB = node1->children[1];
        Node *_RB = node1->children[3];
        if (exp1->type == NodeType::Exp && exp2->type == NodeType::Exp && _LB->type == NodeType::Lb && _RB->type == NodeType::Rb)
        {
            flag = true;
        }
        break;
    }
    default:
        break;
    }
    if (!flag)
    {
        std::cout << "Error type 6 at line " << node1->linec << ": left side in assignment is rvalue " << std::endl;
    }
    else if (!AttributeCompare(node1_attribute, node2_attribute))
    {
        std::cout << "Error type 5 at line " << node1->linec << ": unmatching type on both sides of assignment " << std::endl;
    }
    else
    {
        attribute = node1_attribute;
    }
    return attribute;
}