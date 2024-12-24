#include "ir_generate.hpp"
#include <typeinfo>
#include <cassert>

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
        int expid = inter_exp(node->children[1]);
        TAC* tac_return = new Return(new VarableAddress(VarableAddress::Type::TEMP));
        add_tac(tac_return);
    }
    // IF LP Exp RP Stmt (ELSE Stmt)
    else if (type_to_string(node->children[0]->type).compare("If") == 0)
    {
        int expid = inter_exp(node->children[2]);
        Label* tbranch = new Label();
        add_tac(tbranch);
        inter_stmt(node->children[4]);
        TAC* jbranch;
        if (node->children.size() >= 6)
        {
            jbranch = new Goto(new Label);
            add_tac(jbranch);
        }
        Label* fbranch = new Label();
        add_tac(fbranch);
        inter_IF(expid, tbranch, fbranch);
        if (node->children.size() >= 6)
        {
            inter_stmt(node->children[6]);
            Label* jbranchto = new Label();
            add_tac(jbranchto);
            jbranch->label = jbranchto;
        }
    }
    // WHILE LP Exp RP Stmt
    else if (type_to_string(node->children[0]->type).compare("While") == 0)
    {
        int cont_size = cont.size();
        int br_size = br.size();

        Label* loop_start = new Label();
        add_tac(loop_start);
        int expid = inter_exp(node->children[2]);

        Label* tbranch = new Label();
        add_tac(tbranch);

        inter_stmt(node->children[4]);

        Goto* loopbranch = new Goto(loop_start);
        add_tac(loopbranch);

        Label* fbranch = new Label();
        add_tac(fbranch);

        inter_IF(expid, tbranch, fbranch);
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
    int expid = 0;
    if (node->children.size() > 1)
    {
        expid = inter_exp(node->children[2]);
    }
    TAC *tac = inter_varDec(node->children[0], type);
    if (expid)
    {
        dynamic_cast<Assign *>(tac)->right = expid;
    }
}

/**
 * VarDec: ID
 */ // TODO 是否应该删除 LB RB相关的数组部分？
TAC *inter_varDec(Node *node, Attribute *type)
{
    TAC *tac = new Assign(new VarableAddress(VarableAddress::Type::), new VarableAddress(VarableAddress::Type::));
    tac->name = name;
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
    VarableAddress* exp_varia = inter_exp(node->children[0]);
    int exp_id = TAC::tac_list.size() - 2;
    if (typeid(TAC::tac_list[TAC::tac_list.size() - 2]) == typeid(Dec))
    {
        add_tac(new AssignAddr(new VarableAddress(VarableAddress::Type::TEMP), new VarableAddress(VarableAddress::Type::TEMP)));
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
            add_tac(new AssignAddr(new VarableAddress(VarableAddress::Type::TEMP), new VarableAddress(VarableAddress::Type::TEMP)));
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
//    if (type_to_string(node->children[0]->type).compare("Read") == 0)
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
    if (type_to_string(node->children[0]->type).compare("Not") == 0)
    {
        // exp
        // not exp or exp
        // if(!(!(exp)))
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
                add_tac(new Arg(new VarableAddress(VarableAddress::Type::TEMP)));
            }
        }
        VarableAddress* id = new VarableAddress(VarableAddress::Type::TEMP)
        add_tac(new Call(id, new Function(name)));
        return id;
    }
    // ID //TODO check
    if (node->children[0]->type == NodeType::Id)
    {
        string name = get<string>(node->children[0]->getValue());
        VarableAddress* res_id;
        if (single)
        {
            res_id = new VarableAddress(VarableAddress::Type::TEMP);
            add_tac(new Assign(, new VarableAddress(0)));
        }
        else
        {
            res_id = new VarableAddress(VarableAddress::Type::TEMP);
        }
        // printf("END EXP ID\n");
        return res_id;
    }
    // Exp [{AND}|{OR}] Exp
    if (type_to_string(node->children[1]->type).compare("Or") == 0)
    {
        // printf("Exp OR\n");
        inter_exp(node->children[0]);
        int lexpid = TAC::tac_list.size() - 2;
        int lswap_flag = TAC::tac_list[lexpid]->swap_flag;

        Label* labelid = new Label();
        add_tac(labelid);
        inter_exp(node->children[2]);
        int rexpid = TAC::tac_list[lexpid]->swap_flag;

        int rswap_flag = TAC::tac_list[rexpid]->swap_flag;
        if (lswap_flag)
        {
            *dynamic_cast<If *>(TAC::tac_list[lexpid])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<Goto *>(TAC::tac_list[lexpid + 1])->label = dynamic_cast<Goto *>(TAC::tac_list[rexpid + 1])->label;
            }
            else
            {
                dynamic_cast<Goto *>(TAC::tac_list[lexpid + 1])->label = dynamic_cast<If *>(TAC::tac_list[rexpid])->label;
            }
        }
        else
        {
            *dynamic_cast<Goto *>(TAC::tac_list[lexpid + 1])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<If *>(TAC::tac_list[lexpid])->label = dynamic_cast<Goto *>(TAC::tac_list[rexpid + 1])->label;
            }
            else
            {
                dynamic_cast<If *>(TAC::tac_list[lexpid])->label = dynamic_cast<If *>(TAC::tac_list[rexpid])->label;
            }
        }
        return rexpid;
    }
    if (type_to_string(node->children[1]->type).compare("And") == 0)
    {
        // printf("Exp AND\n");
        inter_exp(node->children[0]);
        int lexpid = int lexpid = TAC::tac_list.size() - 2;

        int lswap_flag = TAC::tac_list[lexpid]->swap_flag;
        int labelid = genid(new Label(TAC::tac_list.size()));
        int rexpid = inter_exp(node->children[2]);
        int rswap_flag = TAC::tac_list[rexpid]->swap_flag;
        if (lswap_flag)
        {
            *dynamic_cast<Goto *>(TAC::tac_list[lexpid + 1])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<If *>(TAC::tac_list[lexpid])->label = dynamic_cast<If *>(TAC::tac_list[rexpid])->label;
            }
            else
            {
                dynamic_cast<If *>(TAC::tac_list[lexpid])->label = dynamic_cast<Goto *>(TAC::tac_list[rexpid + 1])->label;
            }
        }
        else
        {
            *dynamic_cast<If *>(TAC::tac_list[lexpid])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<Goto *>(TAC::tac_list[lexpid + 1])->label = dynamic_cast<If *>(TAC::tac_list[rexpid])->label;
            }
            else
            {
                dynamic_cast<Goto *>(TAC::tac_list[lexpid + 1])->label = dynamic_cast<Goto *>(TAC::tac_list[rexpid + 1])->label;
            }
        }
        return rexpid;
    }
    // Exp [{LT}|{LE}|{GT}|{GE}|{NE}|{EQ}] Exp
    if (type_to_string(node->children[1]->type).compare("Lt") == 0)
    {
    // printf("Exp LT\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        If *iftac = new If(TAC::tac_list.size(), Operator::LT_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        Goto *gototac = new Goto(TAC::tac_list.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    if (type_to_string(node->children[1]->type).compare("Le") == 0)
    {
    // printf("Exp LE\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        If *iftac = new If(TAC::tac_list.size(), Operator::LE_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        Goto *gototac = new Goto(TAC::tac_list.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    if (type_to_string(node->children[1]->type).compare("Gt") == 0)
    {
    // printf("Exp GT\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        If *iftac = new If(TAC::tac_list.size(), Operator::GT_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        Goto *gototac = new Goto(TAC::tac_list.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    if (type_to_string(node->children[1]->type).compare("Ge") == 0)
    {
    // printf("Exp GE\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        If *iftac = new If(TAC::tac_list.size(), Operator::GE_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        Goto *gototac = new Goto(TAC::tac_list.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    if (type_to_string(node->children[1]->type).compare("Ne") == 0)
    {
    // printf("Exp NE\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        If *iftac = new If(TAC::tac_list.size(), Operator::NE_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        Goto *gototac = new Goto(TAC::tac_list.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    if (type_to_string(node->children[1]->type).compare("Eq") == 0)
    {
    // printf("Exp EQ\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        If *iftac = new If(TAC::tac_list.size(), Operator::EQ_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        Goto *gototac = new Goto(TAC::tac_list.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    // Exp ASSIGN Exp
    if (type_to_string(node->children[1]->type).compare("Assign") == 0)
    {
    // printf("Exp ASSIGN\n");
        int rightid = inter_exp(node->children[2]);
        int leftid = inter_exp(node->children[0], true);
        if (typeid(*TAC::tac_list[leftid]) == typeid(Assign))
        {
            dynamic_cast<Assign *>(TAC::tac_list[leftid])->val_address = rightid;
        }
        else
        {
            dynamic_cast<TAC_Copy *>(TAC::tac_list[leftid])->val_address = rightid;
        }
        return rightid;
    }
    // Exp [{PLUS}|{MINUS}|{MUL}|{DIV}] Exp
    if (type_to_string(node->children[1]->type).compare("Plus") == 0)
    {
    // printf("Exp PLUS\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        Arithmetic *tac = new Arithmetic(TAC::tac_list.size(), Operator::PLUS_OP, lexpid, rexpid);
        int id = genid(tac);
        return id;
    }
    if (type_to_string(node->children[1]->type).compare("Minus") == 0)
    {
    // printf("Exp MINUS\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        Arithmetic *tac = new Arithmetic(TAC::tac_list.size(), Operator::MINUS, lexpid, rexpid);
        int id = genid(tac);
        return id;
    }
    if (type_to_string(node->children[1]->type).compare("Mul") == 0)
    {
    // printf("Exp MUL\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        Arithmetic *tac = new Arithmetic(TAC::tac_list.size(), Operator::MUL_OP, lexpid, rexpid);
        int id = genid(tac);
        return id;
    }
    if (type_to_string(node->children[1]->type).compare("Div") == 0) {
        // printf("Exp DIV\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        Arithmetic *tac = new Arithmetic(TAC::tac_list.size(), Operator::DIV_OP, lexpid, rexpid);
        int id = genid(tac);
        return id;
    }
    // 删除 LB RB
    // Exp DOT ID
    if(type_to_string(node->children[1]->type).compare("Dot") == 0){
        // printf("EXP DOT ID\n");
        vector<Node *> vec;
        vec.push_back(node);
        int id;
        while(!vec.empty()){
            Node *top = vec.back();
            if(top->children[0]->type == NodeType::Id){
                id = inter_exp(top);
                // printf("get type\n");
                Attribute *type = TAC::tac_list[id]->type;
                // printf("category %d\n", type->category);
                // printf("after get type\n");
                vec.pop_back();
                if(typeid(*TAC::tac_list[id]) == typeid(TAC_Dec)){
                    id = genid(new AssignAddr(TAC::tac_list.size(), id));
                }
                int vec_size = vec.size();
                while(vec_size--){
                    Node *ast = vec.back();
                    vec.pop_back();
                    string name = type_to_string(ast->children[2]->type);
                    int offset = getOffSet(type, name);
                    id = genid(new Arithmetic(TAC::tac_list.size(), Operator::PLUS_OP, id, -offset));
                }
            }else if(top->children.size() == 3){
                vec.push_back(top->children[0]);
            }
        }
        if(single){
            return genid(new TAC_Copy(id, 0));
        }else{
            return genid(new AssignVal(TAC::tac_list.size(), id));
        }
    }
    // LP Exp RP
    if (type_to_string(node->children[0]->type).compare("LP") == 0)
    {
    // printf("Exp LP EXP RP\n");
        return inter_exp(node->children[1]);
    }
    return -1;
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
    TAC *tac = inter_varDec(node->children[1], type);
    if (typeid(*tac) == typeid(Assign))
    {
        putIR(tac->name, genid(new TAC_Param(TAC::tac_list.size(), type, {})));
    }
    else
    {
        putIR(tac->name, genid(new TAC_Param(TAC::tac_list.size(), type, dynamic_cast<TAC_Dec *>(tac)->sizes)));
    }
}

void inter_init()
{
    // printf("inter_init\n");
    TAC::tac_list.clear();
    TAC::tac_list.push_back(new TAC());
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

int getIR(string name)
{
    // printf("getIR: %d\n", table[name]);
    return table[name];
}

void putIR(string name, VarableAddress* id)
{
    table[name] = id;
}

int genid(TAC *tac)
{
    int index = TAC::tac_list.size();
    TAC::tac_list.push_back(tac);
    return index;
}

int *genlist(int id)
{
    int *label = new int(id);
    return label;
}

void inter_IF(int id, Label* tbranch, Label* fbranch)
{
    // printf("inter_IF\n");
    if (TAC::tac_list[id]->swap_flag)
    {
        Label* temp = tbranch;
        tbranch = fbranch;
        fbranch = temp;
    }
    *dynamic_cast<If *>(TAC::tac_list[id])->label = tbranch;
    *dynamic_cast<Goto *>(TAC::tac_list[id + 1])->label = fbranch;
}

void inter_WHILE(vector<int> *stat_vec, int end, Label* target)
{
    // printf("inter_WHILE");
    while (stat_vec->size() > end)
    {
        int top = stat_vec->back();
        stat_vec->pop_back();
        *dynamic_cast<Goto *>(TAC::tac_list[top])->label = target;
    }
}


int getOffSet(Attribute* global_type, string name){
    ParamsList* param_ptr = global_type->params_ptr;
    int offset=0;
    // printf("get off set \n");
    while(param_ptr->name != name){
        if(param_ptr->global_type->category == PRIMITIVE){
            offset += 4;
        }else{
            offset += 12;
        }
        param_ptr = param_ptr->next;
    }
    // printf("offset = %d\n", offset);
    return offset;
}