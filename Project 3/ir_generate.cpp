#include "ir_generate.hpp"
#include <typeinfo>
#include <cassert>
#include <vector>

std::unordered_map<std::string, tac::VarableAddress*> table;
/**
 * Program: ExtDefList
 */
void inter_program(Node *root)
{
    inter_init();

    inter_extDefList(root->children[0]);

    for (int i = 1; i < tac::TAC::tac_list.size(); ++i)
    {
        std::cout << tac::TAC::tac_list[i] << std::endl;
    }
}

void inter_extDefList(Node *node)
{
    while (node->children.size())
    {
        inter_extDef(node->children[0]);
        node = node->children[1];
    }
}

/**
 * ExtDef: Specifier ExtDecList SEMI
 *       | Specifier SEMI
 *       | Specifier FunDec CompSt
 */
void inter_extDef(Node *node)
{
    // printf("inter_extDef\n");
    Attribute *type = inter_specifier(node->children[0]);
    if (type_to_string(node->children[1]->type).compare("ExtDecList") == 0)
    {
        inter_extDecList(node->children[1], type);
    }
    if (type_to_string(node->children[1]->type).compare("FunDec") == 0)
    {
        inter_func(node->children[1], type);
        inter_compSt(node->children[2]);
    }
}

//ExtDecList -> VarDec
//    | VarDec COMMA ExtDecList

void inter_extDecList(Node *node, Attribute *type)
{
    tac::TAC *tac = inter_varDec(node->children[0], type); // TODO?
    while (node->children.size() > 1)
    {
        node = node->children[2];
        tac::TAC *tac = inter_varDec(node->children[0], type);
    }
}
// put IR 将tac的名字与其地址放在一个table里面？

//Specifier: TYPE
//Specifier: StructSpecifier

Attribute *inter_specifier(Node *node)
{
    Attribute *type;
    if (node->children[0]->type == NodeType::Type)
    {
        type = inter_type(node->children[0]);
    }
    // TODO? 是否不判定使用结构和数组
    return type;
}

Attribute *inter_type(Node *node)
{
    return checkType(node);
}

/**
 * StructSpecifier: STRUCT ID LC DefList RC
 * StructSpecifier: STRUCT ID
 */
//Attribute *inter_structSpecifier(Node *node){
//    string name = get<string>(node->children[1]->getValue());
//    Attribute* type = nullptr;
//    ParamsList* param_ptr = new ParamsList("ID", new Attribute(Category::PRIMITIVE, NodeType::Int), nullptr);
//    type = new Attribute(STRUCTURE, param_ptr);
//    return type;
//}

//FunDec -> ID LP VarList RP
//      | ID LP RP

void inter_func(Node *node, Attribute *type)
{
    std::string name = std::get<std::string>(node->children[0]->getValue());
    tac::TAC* func = new tac::Function(name);
    tac::add_tac(func);

    if (type_to_string(node->children[2]->type).compare("VarList") == 0)
    {
        inter_varList(node->children[2]);
    }
}

/**
 * CompSt: LC DefList StmtList RC
 */
void inter_compSt(Node *node)
{
    // printf("inter_compSt\n");
    inter_defList(node->children[1]);
    inter_stmtList(node->children[2]);
}


//  StmtList: Stmt StmtList

void inter_stmtList(Node *node)
{
    while (node->children.size())
    {
        inter_stmt(node->children[0]);
        node = node->children[1];
    }
}

//  DefList: Def DefList

void inter_defList(Node *node)
{
    while (node->children.size())
    {
        inter_def(node->children[0]);
        node = node->children[1];
    }
}

/**
 * Specifier DecList SEMI
 */
void inter_def(Node *node)
{
    // printf("inter_def\n");
    Attribute *type = inter_specifier(node->children[0]);
    inter_decList(node->children[1], type);
}

/**
 * DecList: Dec | Dec COMMA DecList
 */
void inter_decList(Node *node, Attribute *type)
{
    inter_dec(node->children[0], type);
    while (node->children.size() > 1)
    {
        node = node->children[2];
        inter_dec(node->children[0], type);
    }
}

/**
 * Stmt: Exp SEMI
 * Stmt: CompSt
 * Stmt: RETURN Exp SEMI
 * Stmt: IF LP Exp RP Stmt
 * Stmt: IF LP Exp RP Stmt ELSE Stmt
 * Stmt: WHILE LP Exp RP Stmt
 * WRITE LP Exp RP SEMI
 */
std::vector<int> cont, br;

void inter_stmt(Node *node)
{
    // Exp SEMI
    if (type_to_string(node->children[0]->type).compare("Exp") == 0)
    {
        inter_exp(node->children[0]);
    }
    // CompSt
    else if (type_to_string(node->children[0]->type).compare("CompSt") == 0)
    {
        inter_compSt(node->children[0]);
    }
    // RETURN Exp SEMI
    else if (type_to_string(node->children[0]->type).compare("Return") == 0)
    {
        auto expid = inter_exp(node->children[1]);
        tac::TAC* tac_return = new tac::Return(new tac::VarableAddress(tac::VarableAddress::Type::TEMP));
        add_tac(tac_return);
    }
    // IF LP Exp RP Stmt (ELSE Stmt)
    else if (type_to_string(node->children[0]->type).compare("If") == 0)
    {
        auto expid = inter_exp(node->children[2]);
        assert(expid->instructionType == "IF");
        tac::Label* tbranch = new tac::Label();
        add_tac(tbranch);
        inter_stmt(node->children[4]);
        tac::Goto* jbranch;
        if (node->children.size() >= 6)
        {
            jbranch = new tac::Goto(new tac::Label());
            add_tac(jbranch);
        }
        tac::Label* fbranch = new tac::Label();
        add_tac(fbranch);
        inter_IF(static_cast<tac::If*>(expid), jbranch , tbranch, fbranch);
        if (node->children.size() >= 6)
        {
            inter_stmt(node->children[6]);
            tac::Label* jbranchto = new tac::Label();
            add_tac(jbranchto);
            jbranch->label = jbranchto;
        }
    }
    // WHILE LP Exp RP Stmt
    else if (type_to_string(node->children[0]->type).compare("While") == 0)
    {
        int cont_size = cont.size();
        int br_size = br.size();

        tac::Label* loop_start = new tac::Label();
        add_tac(loop_start);
        auto expid = inter_exp(node->children[2]);
        assert(expid->instructionType == "IF");
        expid = static_cast<tac::If*>(expid);

        tac::Label* tbranch = new tac::Label();
        add_tac(tbranch);

        inter_stmt(node->children[4]);

        tac::Goto* loopbranch = new tac::Goto(loop_start);
        add_tac(loopbranch);

        tac::Label* fbranch = new tac::Label();
        add_tac(fbranch);

        inter_IF(static_cast<tac::If>(expid), loopbranch, tbranch, fbranch);
        inter_WHILE(&cont, cont_size, loop_start);
        inter_WHILE(&br, br_size, fbranch);
    }
    // WRITE LP Exp RP SEMI // TODO 能不能读取read write？
//    else if (type_to_string(node->children[0]->type).compare("Write") == 0)
//    {
//        int id = inter_exp(node->children[2]);
//        add_tac(new Write(TAC::tac_list.size(), id));
//    }
    else
    {
        assert(NULL);
    }
}

/**
 * Dec: VarDec
 * Dec: VarDec ASSIGN Exp
 */
void inter_dec(Node *node, Attribute *type)
{
    tac::VarableAddress* expid = 0;
    if (node->children.size() > 1)
    {
        expid = static_cast<tac::VarableAddress* >(inter_exp(node->children[2]));
    }
    tac::TAC *tac = inter_varDec(node->children[0], type);
    if (expid)
    {
        dynamic_cast<tac::Assign *>(tac)->right = expid;
    }
}

/**
 * VarDec: ID
 */ // TODO 是否应该删除 LB RB相关的数组部分？
tac::TAC *inter_varDec(Node *node, Attribute *type)
{
    tac::TAC *tac = new tac::Assign(new tac::VarableAddress(tac::VarableAddress::Type::TEMP), new tac::VarableAddress(tac::VarableAddress::Type::TEMP));
    return tac;
}

/**
 * Args: Exp COMMA Args
 * Args: Exp
 */
vector<int> inter_args(Node *node)
{
    // printf("inter_args\n");
    vector<int> args_vector;
    tac::VarableAddress* exp_varia = inter_exp(node->children[0]);
    int exp_id = TAC::tac_list.size() - 2;
    if (typeid(TAC::tac_list[TAC::tac_list.size() - 2]) == typeid(Dec))
    {
        add_tac(new tac::AssignAddr(new tac::VarableAddress(VarableAddress::Type::TEMP), new tac::VarableAddress(VarableAddress::Type::TEMP)));
    }
    args_vector.push_back(exp_id);
    while (node->children.size() > 1)
    {
        node = node->children[2];
        exp_varia = inter_exp(node->children[0]);
        exp_id = TAC::tac_list.size() - 2;
        args_vector.push_back(exp_id);
        if (typeid(TAC::tac_list[exp_id]) != typeid(Dec))
        {
            add_tac(new tac::AssignAddr(new tac::VarableAddress(VarableAddress::Type::TEMP), new tac::VarableAddress(VarableAddress::Type::TEMP)));
        }
    }
    return args_vector;
}

/**
 * Exp: Exp ASSIGN Exp
 *    | Exp [{AND}|{OR}] Exp
 *    | Exp [{LT}|{LE}|{GT}|{GE}|{NE}|{EQ}] Exp
 *    | Exp [{PLUS}|{MINUS}|{MUL}|{DIV}] Exp
 *    | LP Exp RP
 *    | MINUS Exp | MINUS Exp %prec UMINUS
 *    | NOT Exp
 *    | ID LP Args RP
 *    | ID LP RP
 *    | ID
 *    | Exp LB Exp RB
 *    | Exp DOT ID
 *    | INT | FLOAT | CHAR
 *    | READ LP RP
 */
tac::TAC* inter_exp(Node *node, bool single)
{
    // printf("inter_exp\n");
    // READ LP RP // TODO
//    if (node->children[0]->type == NodeType::Read)
//    {
//        // printf("Exp READ\n");
//        TAC_Read *tac = new TAC_Read(TAC::tac_list.size());
//        int id = genid(tac);
//        return id;
//    }
    // INT  // | FLOAT | CHAR
    if (node->children[0]->type == NodeType::Int)  // 不引用，创建一个
    {
        auto result = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);

        tac::Assign *tac = new tac::Assign(result, new tac::VarableAddress(std::get<int>(node->children[0]->getValue()))); // ??
        add_tac(tac);
        return result;
    }// 只有整数基本类型变量 假设2

    // MINUS Exp | MINUS Exp %prec UMINUS
    if (node->children[0]->type == NodeType::Minus)
    {
        auto var = inter_exp(node->children[1]);
        auto result = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        assert(var->instructionType == "Variable");
        auto tac = new tac::Arithmetic(tac::Operator::MINUS, result, new tac::VarableAddress(0), static_cast<tac::VarableAddress*>(var));
        add_tac(tac);
        return result;  // 非递归
    }
    // NOT Exp
    if (node->children[0]->type == NodeType::Not)
    {
        tac::TAC* exp_if = inter_exp(node->children[1]);
        exp_if->swap_flag ^= 1;
        return exp_if;
    }   // 递归
    // ID LP Args RP
    // ID LP RP
    if (node->children[0]->type == NodeType::Id && node->children.size() > 1)
    {
        // printf("Exp ID LP ARGS RP\n");
        std::string name = std::get<std::string>(node->children[0]->getValue());
        if (type_to_string(node->children[2]->type).compare("Args") == 0)
        {
            auto id_vec = inter_args(node->children[2]);
            for (auto id : id_vec)
            {
                add_tac(new tac::Arg(new tac::VarableAddress(tac::VarableAddress::Type::TEMP)));
            }
        }
        tac::VarableAddress* id = new tac::VarableAddress(VarableAddress::Type::TEMP);
        add_tac(new tac::Call(id, new tac::Function(name)));
        return id;
    }
    // ID //TODO check
    if (node->children[0]->type == NodeType::Id)
    {
        string name = get<string>(node->children[0]->getValue());
        tac::VarableAddress* id = getIR(name);
        tac::VarableAddress* res_id;
        if (single)
        {
            if(!id){
                id = new tac::VarableAddress(tac::VarableAddress::Type::VAR);
                putIR(name, id);
            }
            tac::add_tac(new tac::Assign(id, new tac::VarableAddress(0)));
        }
        else if (!id)
        {
            res_id = new tac::VarableAddress(tac::VarableAddress::Type::VAR);
            tac::add_tac(new tac::Assign(res_id, new tac::arableAddress(0)));
        }
        else
        {
            res_id = new tac::VarableAddress(VarableAddress::Type::VAR);
        }
        return res_id;
    }
    // Exp [{AND}|{OR}] Exp // TODO
    if (node->children[1]->type == NodeType::Or)
    {
        // printf("Exp OR\n");
        auto lexpid = inter_exp(node->children[0]);
        assert(lexpid->instructionType == "Variable");
        int lswap_flag = tac::TAC::tac_list[lexpid]->swap_flag;
        tac::Label* labelid = new tac::Label();
        add_tac(labelid);
        auto rexpid= inter_exp(node->children[2]);
        assert(rexpid->instructionType == "Variable");
        int rswap_flag = tac::TAC::tac_list[rexpid]->swap_flag;
        if (lswap_flag)
        {
            *dynamic_cast<tac::If *>(tac::TAC::tac_list[lexpid])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<tac::Goto *>(tac::TAC::tac_list[lexpid + 1])->label = dynamic_cast<Goto *>(tac::TAC::tac_list[rexpid + 1])->label;
            }
            else
            {
                dynamic_cast<tac::Goto *>(tac::TAC::tac_list[lexpid + 1])->label = dynamic_cast<If *>(tac::TAC::tac_list[rexpid])->label;
            }
        }
        else
        {
            *dynamic_cast<tac::Goto *>(tac::TAC::tac_list[lexpid + 1])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<tac::If *>(tac::TAC::tac_list[lexpid])->label = dynamic_cast<Goto *>(tac::TAC::tac_list[rexpid + 1])->label;
            }
            else
            {
                dynamic_cast<tac::If *>(tac::TAC::tac_list[lexpid])->label = dynamic_cast<If *>(tac::TAC::tac_list[rexpid])->label;
            }
        }
        return rexpid;
    }
    if (node->children[1]->type == NodeType::And)
    {
        inter_exp(node->children[0]);
        int lexpid =  tac::TAC::tac_list.size() - 2;

        int lswap_flag = tac::TAC::tac_list[lexpid]->swap_flag;
        tac::Label * labelid = new tac::Label();
        add_tac(labelid);
        int rexpid = inter_exp(node->children[2]);
        int rswap_flag = tac::TAC::tac_list[rexpid]->swap_flag;
        if (lswap_flag)
        {
            *dynamic_cast<tac::Goto *>(tac::TAC::tac_list[lexpid + 1])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<tac::If *>(tac::TAC::tac_list[lexpid])->label = dynamic_cast<tac::If *>(TAC::tac_list[rexpid])->label;
            }
            else
            {
                dynamic_cast<tac::If *>(tac::TAC::tac_list[lexpid])->label = dynamic_cast<tac::Goto *>(TAC::tac_list[rexpid + 1])->label;
            }
        }
        else
        {
            *dynamic_cast<tac::If *>(tac::TAC::tac_list[lexpid])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<tac::Goto *>(tac::TAC::tac_list[lexpid + 1])->label = dynamic_cast<tac::If *>(TAC::tac_list[rexpid])->label;
            }
            else
            {
                dynamic_cast<tac::Goto *>(tac::TAC::tac_list[lexpid + 1])->label = dynamic_cast<tac::Goto *>(TAC::tac_list[rexpid + 1])->label;
            }
        }
        return rexpid;
    }
    // Exp [{LT}|{LE}|{GT}|{GE}|{NE}|{EQ}] Exp
    if (node->children[1]->type == NodeType::Lt)
    {
    // printf("Exp LT\n");
        auto lexpid = inter_exp(node->children[0]);
        auto rexpid = inter_exp(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::LT, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        return iftac;
    }
    if (node->children[1]->type == NodeType::Le)
    {
    // printf("Exp LE\n");
        auto lexpid = inter_exp(node->children[0]);
        auto rexpid = inter_exp(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::LE, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    if (node->children[1]->type == NodeType::Gt)
    {
        auto lexpid = inter_exp(node->children[0]);
        auto rexpid = inter_exp(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::GT, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    if (node->children[1]->type == NodeType::Ge)
    {
        auto lexpid = inter_exp(node->children[0]);
        auto rexpid = inter_exp(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::GE, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    if (node->children[1]->type == NodeType::Ne)
    {
        auto lexpid = inter_exp(node->children[0]);
        auto rexpid = inter_exp(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::NE, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    if (node->children[1]->type == NodeType::Eq)
    {
        auto lexpid = inter_exp(node->children[0]);
        auto rexpid = inter_exp(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::EQ, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    // Exp ASSIGN Exp
    if (node->children[1]->type == NodeType::Assign)
    {
    // printf("Exp ASSIGN\n");
        auto rightid = inter_exp(node->children[2]);
        auto leftid = inter_exp(node->children[0], true);
        if (leftid->instructionType == "ASSIGN")
        {
            dynamic_cast<tac::Assign *>(leftid)->right = static_cast<tac::VarableAddress *>(rightid);
        }
        else
        {
            dynamic_cast<tac::Copy *>(leftid)->right = static_cast<tac::VarableAddress *>(rightid);
        }
        return rightid;
    }
    // Exp [{PLUS}|{MINUS}|{MUL}|{DIV}] Exp
    if (node->children[1]->type == NodeType::Plus)
    {
    // printf("Exp PLUS\n");
        auto lexpid = inter_exp(node->children[0]);
        auto rexpid = inter_exp(node->children[2]);
        tac::VarableAddress * id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::Arithmetic *tac = new tac::Arithmetic( tac::Operator::PLUS, id, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid));
        tac::add_tac(tac);
        return id;
    }
    if (node->children[1]->type == NodeType::Minus)
    {
    // printf("Exp MINUS\n");
        auto lexpid = inter_exp(node->children[0]);
        auto rexpid = inter_exp(node->children[2]);
        tac::VarableAddress * id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::Arithmetic *tac = new tac::Arithmetic( tac::Operator::MINUS, id, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid));
        tac::add_tac(tac);
        return id;
    }
    if (node->children[1]->type == NodeType::Mul)
    {
    // printf("Exp MUL\n");
        auto lexpid = inter_exp(node->children[0]);
        auto rexpid = inter_exp(node->children[2]);
        tac::VarableAddress * id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::Arithmetic *tac = new tac::Arithmetic( tac::Operator::MUL, id, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid));
        tac::add_tac(tac);
        return id;
    }
    if (node->children[1]->type == NodeType::Div) {
        // printf("Exp DIV\n");
        auto lexpid = inter_exp(node->children[0]);
        auto rexpid = inter_exp(node->children[2]);
        tac::VarableAddress * id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::Arithmetic *tac = new tac::Arithmetic( tac::Operator::DIV, id, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid));
        tac::add_tac(tac);
        return id;
    }
    // 删除 LB RB
    // Exp DOT ID // TODO
    if(node->children[1]->type == NodeType::Dot){
        // printf("EXP DOT ID\n");
        std::vector<Node*> vec;
        vec.push_back(node);
        tac::TAC * id;
        while(!vec.empty()){
            Node *top = vec.back();
            if(top->children[0]->type == NodeType::Id){
                id = inter_exp(top);
                vec.pop_back();
                int vec_size = vec.size();
                while(vec_size--){
                    Node *ast = vec.back();
                    vec.pop_back();
                    string name = type_to_string(ast->children[2]->type);
                    tac::add_tac(new tac::Arithmetic(tac::Operator::PLUS, new tac::VarableAddress(tac::VarableAddress::Type::TEMP), static_cast<tac::VarableAddress *>(id), new tac::VarableAddress(0)));
                }
            }else if(top->children.size() == 3){
                vec.push_back(top->children[0]);
            }
        }
        if(single){
            add_tac(new tac::Copy(static_cast<tac::VarableAddress *>(id), new tac::VarableAddress(0)));
            
        }else{
            add_tac(new tac::AssignVal(new tac::VarableAddress(tac::VarableAddress::Type::TEMP), static_cast<tac::VarableAddress *>(id)));
        }
    }
    // LP Exp RP
    if (type_to_string(node->children[0]->type).compare("LP") == 0)
    {
    // printf("Exp LP EXP RP\n");
        return inter_exp(node->children[1]);
    }
    return nullptr;
}

/**
 * VarList: ParamDec COMMA VarList
 * VarList: ParamDec
 */
void inter_varList(Node *node)
{
    // printf("inter_varList\n");
    vector<Node *> vec = {node->children[0]};
    while (node->children.size() > 1)
    {
        node = node->children[2];
        vec.push_back(node->children[0]);
    }
    while (!vec.empty())
    {
        inter_paramDec(vec.back());
        vec.pop_back();
    }
}

/**
 * ParamDec: Specifier VarDec
 */
void inter_paramDec(Node *node)
{
    // printf("inter_paramDec\n");
    Attribute *type = inter_specifier(node->children[0]);
    tac::TAC *tac = inter_varDec(node->children[1], type);
    if (tac->instructionType == "ASSIGN")
    {
        tac::VarableAddress * id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::Param * param = new tac::Param(id);
        putIR(tac->instructionType, id);
        tac::add_tac(param);
    }
}

void inter_init()
{
    // printf("inter_init\n");
    tac::TAC::tac_list.clear();
    //tac::TAC::tac_list.push_back(new tac::TAC());
    table.clear();
    cont.clear();
    br.clear();
}

Attribute *checkType(Node *node)
{
    // printf("checkType\n");
    // DEBUG("checkType", node);
    if (node->type == NodeType::Int)
    {
        return new Attribute(Category::PRIMITIVE, NodeType::Int);
    }
    if (node->type == NodeType::Float)
    {
        return new Attribute(Category::PRIMITIVE, NodeType::Float);
    }
    if (node->type == NodeType::Char)
    {
        return new Attribute(Category::PRIMITIVE, NodeType::Char);
    }
    return nullptr;
}

tac::VarableAddress* getIR(string name)
{
    // printf("getIR: %d\n", table[name]);
    return table[name];
}

void putIR(string name, tac::VarableAddress* id)
{
    table[name] = id;
}


void inter_IF(tac::If * id, tac::Goto* gotoid, tac::Label* tbranch, tac::Label* fbranch)
{
    // printf("inter_IF\n");
    if (id->swap_flag)
    {
        tac::Label* temp = tbranch;
        tbranch = fbranch;
        fbranch = temp;
    }
    id->label = tbranch;
    gotoid->label = fbranch;
}

void inter_WHILE(vector<int> *stat_vec, int end, tac::Label* target)
{
    // printf("inter_WHILE");
    while (stat_vec->size() > end)
    {
        int top = stat_vec->back();
        stat_vec->pop_back();
        dynamic_cast<tac::Goto *>(tac::TAC::tac_list[top])->label = target;
    }
}
