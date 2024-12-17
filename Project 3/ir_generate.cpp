#include "ir_generate.hpp"
#include <typeinfo>
#include <assert.h>
vector<TAC *> tac_vector;
unordered_map<string, int> table;

/**
 * Program: ExtDefList
 */
void inter_program(Node *root)
{
    // printf("Inter_Program\n");
    inter_init();

    inter_extDefList(root->children[0]);
    // printf("HERE\n");
    for (int i = 1; i < tac_vector.size(); ++i)
    {
        fprintf(stdout, "%s\n", string(tac_vector[i]->to_string()).c_str());
    }
}

/**
 * ExtDefList: ExtDef ExtDefList | %empty
 */
void inter_extDefList(Node *node)
{
    // printf("inter_extDefList\n");

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

void inter_extDecList(Node *node, Attribute *type)
{
    // printf("inter_extDecList\n");
    TAC *tac = inter_varDec(node->children[0], type);
    while (node->children.size() > 1)
    {
        node = node->children[2];
        TAC *tac = inter_varDec(node->children[0], type);
    }
    putIR(tac->name, tac->generate_ID());
}

/**
 * Specifier: TYPE
 * Specifier: StructSpecifier
 */
Attribute *inter_specifier(Node *node)
{
    // printf("inter_specifier\n");
    Attribute *type;
    // printf("node->children.size() = %d\n", node->children.size());
    // printf("node->name = %s\n", node->name);
    if (node->children[0]->type == NodeType::Type)
    {
        type = inter_type(node->children[0]);
    }
    else{
        type = inter_structSpecifier(node->children[0]);
    }

    return type;
}

/**
 *
 */
Attribute *inter_type(Node *node)
{
    // printf("inter_type\n");
    return checkType(node);
}

/**
 * StructSpecifier: STRUCT ID LC DefList RC
 * StructSpecifier: STRUCT ID
 */
Attribute *inter_structSpecifier(Node *node){
    string name = get<string>(node->children[1]->getValue());
    Attribute* type = nullptr;
    ParamsList* param_ptr = new ParamsList("ID", new Attribute(Category::PRIMITIVE, NodeType::Int), nullptr);
    type = new Attribute(STRUCTURE, param_ptr);
    return type;
}

void inter_func(Node *node, Attribute *type)
{
    // printf("inter_func\n");
    string name = get<string>(node->children[0]->getValue());
    int funcid = genid(new TAC_Func(tac_vector.size(), name));
    putIR(name, funcid);
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

/**
 * StmtList: Stmt StmtList
 * StmtList: %empty
 */
void inter_stmtList(Node *node)
{
    // printf("inter_stmtList\n");
    while (node->children.size())
    {
        inter_stmt(node->children[0]);
        node = node->children[1];
    }
}

/**
 * DefList: Def DefList
 * DefList: %empty
 */
void inter_defList(Node *node)
{
    // printf("inter_defList\n");
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
    // printf("inter_decList\n");
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
vector<int> cont, br;

void inter_stmt(Node *node)
{
    // printf("inter_stmt\n");
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
    else if (type_to_string(node->children[0]->type).compare("RETURN") == 0)
    {
        int expid = inter_exp(node->children[1]);
        genid(new TAC_Return(tac_vector.size(), expid));
    }
    // IF
    else if (type_to_string(node->children[0]->type).compare("IF") == 0)
    {
        int expid = inter_exp(node->children[2]);
        // irStmt(node->child[4]);
        int tbranch = genid(new TAC_Label(tac_vector.size()));
        inter_stmt(node->children[4]);
        int jbranch;
        if (node->children.size() >= 6)
        {
            jbranch = genid(new TAC_GOTO(tac_vector.size(), genlist()));
        }
        int fbranch = genid(new TAC_Label(tac_vector.size()));
        inter_IF(expid, tbranch, fbranch);
        if (node->children.size() >= 6)
        {
            inter_stmt(node->children[6]);
            int jbranchto = genid(new TAC_Label(tac_vector.size()));
            *dynamic_cast<TAC_GOTO *>(tac_vector[jbranch])->label = jbranchto;
        }
    }
    // WHILE LP Exp RP Stmt
    else if (type_to_string(node->children[0]->type).compare("WHILE") == 0)
    {
        int cont_size = cont.size();
        int br_size = br.size();
        int loop_start = genid(new TAC_Label(tac_vector.size()));
        int expid = inter_exp(node->children[2]);
        int tbranch = genid(new TAC_Label(tac_vector.size()));
        inter_stmt(node->children[4]);
        int loopbranch = genid(new TAC_GOTO(tac_vector.size(), genlist(loop_start)));
        int fbranch = genid(new TAC_Label(tac_vector.size()));
        inter_IF(expid, tbranch, fbranch);
        inter_WHILE(&cont, cont_size, loop_start);
        inter_WHILE(&br, br_size, fbranch);
    }
    // WRITE LP Exp RP SEMI
    else if (type_to_string(node->children[0]->type).compare("WRITE") == 0)
    {
        int id = inter_exp(node->children[2]);
        genid(new TAC_Write(tac_vector.size(), id));
    }
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
    // printf("inter_dec\n");
    int expid = 0;
    if (node->children.size() > 1)
    {
        expid = inter_exp(node->children[2]);
    }
    TAC *tac = inter_varDec(node->children[0], type);
    if (expid)
    {
        dynamic_cast<TAC_Assign *>(tac)->val_address = expid;
    }
    putIR(tac->name, tac->generate_ID());
}

/**
 * VarDec: ID
 * VarDec: VarDec LB INT RB
 */
TAC *inter_varDec(Node *node, Attribute *type)
{
    vector<Node *> ast_vec;
    ast_vec.push_back(node);
    vector<int> int_vec;
    string name;
    while (!ast_vec.empty())
    {
        // printf("in the while loop\n");
        Node *top = ast_vec.back();
        if (top->children[0]->type == NodeType::Id)
        {
            name = get<string>(top->children[0]->getValue());
            // printf("name %s\n", name.c_str());
            ast_vec.pop_back();
            while (!ast_vec.empty())
            {
                Node *ast = ast_vec.back();
                ast_vec.pop_back();
                int size = formatPaser("INT", std::to_string(get<int>(ast->children[2]->getValue())));
                // printf("Size pushed = %d\n", size);
                int_vec.push_back(size);

            }
            // printf("The size of int_vec = %d\n", int_vec.size());
        }
        else
        {
            ast_vec.push_back(top->children[0]);
        }
    }
    // printf("out of the while loop\n");
    // if(type != nullptr){
    //     // printf("not null");
    // }
    // printf("null\n");
    if (int_vec.size())
    {
        // printf("here size !=1\n");
        return new TAC_Dec(tac_vector.size(), type, name, int_vec);
    }
    if(type!= nullptr && type->category == STRUCTURE){
        // printf("structure dectac\n");
        return new TAC_Dec(tac_vector.size(), type, name, {});
    }
    else
    {
        // printf("in else\n");
        TAC *tac = new TAC_Assign(tac_vector.size(), 0);
        tac->name = name;
        return tac;
    }
}

/**
 * Args: Exp COMMA Args
 * Args: Exp
 */
vector<int> inter_args(Node *node)
{
    // printf("inter_args\n");
    vector<int> args_vector;
    int exp_id = inter_exp(node->children[0]);
    if (typeid(*tac_vector[exp_id]) == typeid(TAC_Dec))
    {
        exp_id = genid(new TAC_AssignAddr(tac_vector.size(), exp_id));
    }
    args_vector.push_back(exp_id);
    while (node->children.size() > 1)
    {
        node = node->children[2];
        exp_id = inter_exp(node->children[0]);
        args_vector.push_back(exp_id);
        if (typeid(*tac_vector[exp_id]) != typeid(TAC_Dec))
        {
            exp_id = genid(new TAC_AssignAddr(tac_vector.size(), exp_id));
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
int inter_exp(Node *node, bool single)
{
    // printf("inter_exp\n");
    // READ LP RP
    if (type_to_string(node->children[0]->type).compare("READ") == 0)
    {
        // printf("Exp READ\n");
        TAC_Read *tac = new TAC_Read(tac_vector.size());
        int id = genid(tac);
        return id;
    }
    // INT | FLOAT | CHAR
    if (node->children[0]->type == NodeType::Int)
    {
        // value < 0, means not address
        // printf("Exp Type\n");
        // printf("In irExp, value = %d\n", node->children[0]->int_value);
        TAC_Assign *tac = new TAC_Assign(tac_vector.size(), -formatPaser(type_to_string(node->children[0]->type), std::to_string(get<int>(node->children[0]->getValue()))));
        int id = genid(tac);
        return id;
    }
    if (node->children[0]->type == NodeType::Float)
    {
        // value < 0, means not address
        // printf("Exp Type\n");
        // printf("In irExp, value = %d\n", node->children[0]->float_value);
        TAC_Assign *tac = new TAC_Assign(tac_vector.size(), -formatPaser(type_to_string(node->children[0]->type),std::to_string(get<float>(node->children[0]->getValue()))));
        int id = genid(tac);
        return id;
    }
    if (node->children[0]->type == NodeType::Char)
    {
        // value < 0, means not address
        // printf("Exp Type\n");
        // printf("In irExp, value = %s\n", node->children[0]->char_value);
        TAC_Assign *tac = new TAC_Assign(tac_vector.size(), -formatPaser(type_to_string(node->children[0]->type), get<string>(node->children[0]->getValue())));
        int id = genid(tac);
        return id;
    }

    // MINUS Exp | MINUS Exp %prec UMINUS
    if (type_to_string(node->children[0]->type).compare("MINUS") == 0)
    {
        // printf("Exp MINUS\n");
        int expid = inter_exp(node->children[1]);
        TAC_Arithmetic *tac = new TAC_Arithmetic(tac_vector.size(), Operator::MINUS_OP, 0, expid);
        int id = genid(tac);
        return id;
    }
    // NOT Exp
    if (type_to_string(node->children[0]->type).compare("NOT") == 0)
    {
        // printf("Exp NOT\n");
        int expid = inter_exp(node->children[1]);
        tac_vector[expid]->swap_flag ^= 1;
        return expid;
    }
    // ID LP Args RP
    // ID LP RP
    if (node->children[0]->type == NodeType::Id && node->children.size() > 1)
    {
        // printf("Exp ID LP ARGS RP\n");
        string name = get<string>(node->children[0]->getValue());
        if (type_to_string(node->children[2]->type).compare("Args") == 0)
        {
            auto id_vec = inter_args(node->children[2]);
            for (auto id : id_vec)
            {
                genid(new TAC_Arg(tac_vector.size(), id));
            }
        }
        int id = genid(new TAC_Call(tac_vector.size(), name));
        return id;
    }
    // ID
    if (node->children[0]->type == NodeType::Id)
    {
        // printf("Exp ID\n");
        string name = get<string>(node->children[0]->getValue());
        int id = getIR(name);
        int res_id = 0;
        if (single)
        {
            if (!id)
            {
                id = tac_vector.size();
                putIR(name, id);
            }
            res_id = genid(new TAC_Assign(id, 0));
        }
        else if (!id)
        {
            // specially
            res_id = genid(new TAC_Assign(tac_vector.size(), 0));
        }
        else
        {
            res_id = id;
        }
        // printf("END EXP ID\n");
        return res_id;
    }
    // Exp [{AND}|{OR}] Exp
    if (type_to_string(node->children[1]->type).compare("OR") == 0)
    {
        // printf("Exp OR\n");
        int lexpid = inter_exp(node->children[0]);
        int lswap_flag = tac_vector[lexpid]->swap_flag;
        int labelid = genid(new TAC_Label(tac_vector.size()));
        int rexpid = inter_exp(node->children[2]);
        int rswap_flag = tac_vector[rexpid]->swap_flag;
        if (lswap_flag)
        {
            *dynamic_cast<TAC_IF *>(tac_vector[lexpid])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<TAC_GOTO *>(tac_vector[lexpid + 1])->label = dynamic_cast<TAC_GOTO *>(tac_vector[rexpid + 1])->label;
            }
            else
            {
                dynamic_cast<TAC_GOTO *>(tac_vector[lexpid + 1])->label = dynamic_cast<TAC_IF *>(tac_vector[rexpid])->label;
            }
        }
        else
        {
            *dynamic_cast<TAC_GOTO *>(tac_vector[lexpid + 1])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<TAC_IF *>(tac_vector[lexpid])->label = dynamic_cast<TAC_GOTO *>(tac_vector[rexpid + 1])->label;
            }
            else
            {
                dynamic_cast<TAC_IF *>(tac_vector[lexpid])->label = dynamic_cast<TAC_IF *>(tac_vector[rexpid])->label;
            }
        }
        return rexpid;
    }
    if (type_to_string(node->children[1]->type).compare("AND") == 0)
    {
        // printf("Exp AND\n");
        int lexpid = inter_exp(node->children[0]);
        int lswap_flag = tac_vector[lexpid]->swap_flag;
        int labelid = genid(new TAC_Label(tac_vector.size()));
        int rexpid = inter_exp(node->children[2]);
        int rswap_flag = tac_vector[rexpid]->swap_flag;
        if (lswap_flag)
        {
            *dynamic_cast<TAC_GOTO *>(tac_vector[lexpid + 1])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<TAC_IF *>(tac_vector[lexpid])->label = dynamic_cast<TAC_IF *>(tac_vector[rexpid])->label;
            }
            else
            {
                dynamic_cast<TAC_IF *>(tac_vector[lexpid])->label = dynamic_cast<TAC_GOTO *>(tac_vector[rexpid + 1])->label;
            }
        }
        else
        {
            *dynamic_cast<TAC_IF *>(tac_vector[lexpid])->label = labelid;
            if (rswap_flag)
            {
                dynamic_cast<TAC_GOTO *>(tac_vector[lexpid + 1])->label = dynamic_cast<TAC_IF *>(tac_vector[rexpid])->label;
            }
            else
            {
                dynamic_cast<TAC_GOTO *>(tac_vector[lexpid + 1])->label = dynamic_cast<TAC_GOTO *>(tac_vector[rexpid + 1])->label;
            }
        }
        return rexpid;
    }
    // Exp [{LT}|{LE}|{GT}|{GE}|{NE}|{EQ}] Exp
    if (type_to_string(node->children[1]->type).compare("LT") == 0)
    {
    // printf("Exp LT\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        TAC_IF *iftac = new TAC_IF(tac_vector.size(), Operator::LT_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        TAC_GOTO *gototac = new TAC_GOTO(tac_vector.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    if (type_to_string(node->children[1]->type).compare("LE") == 0)
    {
    // printf("Exp LE\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        TAC_IF *iftac = new TAC_IF(tac_vector.size(), Operator::LE_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        TAC_GOTO *gototac = new TAC_GOTO(tac_vector.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    if (type_to_string(node->children[1]->type).compare("GT") == 0)
    {
    // printf("Exp GT\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        TAC_IF *iftac = new TAC_IF(tac_vector.size(), Operator::GT_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        TAC_GOTO *gototac = new TAC_GOTO(tac_vector.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    if (type_to_string(node->children[1]->type).compare("GE") == 0)
    {
    // printf("Exp GE\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        TAC_IF *iftac = new TAC_IF(tac_vector.size(), Operator::GE_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        TAC_GOTO *gototac = new TAC_GOTO(tac_vector.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    if (type_to_string(node->children[1]->type).compare("NE") == 0)
    {
    // printf("Exp NE\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        TAC_IF *iftac = new TAC_IF(tac_vector.size(), Operator::NE_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        TAC_GOTO *gototac = new TAC_GOTO(tac_vector.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    if (type_to_string(node->children[1]->type).compare("EQ") == 0)
    {
    // printf("Exp EQ\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        TAC_IF *iftac = new TAC_IF(tac_vector.size(), Operator::EQ_OP, lexpid, rexpid, genlist());
        int ifid = genid(iftac);
        TAC_GOTO *gototac = new TAC_GOTO(tac_vector.size(), genlist());
        int gotoid = genid(gototac);
        return ifid;
    }
    // Exp ASSIGN Exp
    if (type_to_string(node->children[1]->type).compare("ASSIGN") == 0)
    {
    // printf("Exp ASSIGN\n");
        int rightid = inter_exp(node->children[2]);
        int leftid = inter_exp(node->children[0], true);
        if (typeid(*tac_vector[leftid]) == typeid(TAC_Assign))
        {
            dynamic_cast<TAC_Assign *>(tac_vector[leftid])->val_address = rightid;
        }
        else
        {
            dynamic_cast<TAC_Copy *>(tac_vector[leftid])->val_address = rightid;
        }
        return rightid;
    }
    // Exp [{PLUS}|{MINUS}|{MUL}|{DIV}] Exp
    if (type_to_string(node->children[1]->type).compare("PLUS") == 0)
    {
    // printf("Exp PLUS\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        TAC_Arithmetic *tac = new TAC_Arithmetic(tac_vector.size(), Operator::PLUS_OP, lexpid, rexpid);
        int id = genid(tac);
        return id;
    }
    if (type_to_string(node->children[1]->type).compare("MINUS") == 0)
    {
    // printf("Exp MINUS\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        TAC_Arithmetic *tac = new TAC_Arithmetic(tac_vector.size(), Operator::MINUS_OP, lexpid, rexpid);
        int id = genid(tac);
        return id;
    }
    if (type_to_string(node->children[1]->type).compare("MUL") == 0)
    {
    // printf("Exp MUL\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        TAC_Arithmetic *tac = new TAC_Arithmetic(tac_vector.size(), Operator::MUL_OP, lexpid, rexpid);
        int id = genid(tac);
        return id;
    }
    if (type_to_string(node->children[1]->type).compare("DIV") == 0)
    {
    // printf("Exp DIV\n");
        int lexpid = inter_exp(node->children[0]);
        int rexpid = inter_exp(node->children[2]);
        TAC_Arithmetic *tac = new TAC_Arithmetic(tac_vector.size(), Operator::DIV_OP, lexpid, rexpid);
        int id = genid(tac);
        return id;
    }
    // Exp LB Exp RB
    if(type_to_string(node->children[1]->type).compare("LB") == 0){
    // printf("exp LB\n");
        vector<Node *> vec;
        vec.push_back(node);
        int id;
        while(!vec.empty()){
            Node *top = vec.back();
            if(top->children[0]->type==NodeType::Id){
                id = inter_exp(top);
                vec.pop_back();
                int typeSize = 4;
                vector<int> *suffix;
                if(typeid(*tac_vector[id]) == typeid(TAC_Dec)){
                    suffix = &(dynamic_cast<TAC_Dec *>(tac_vector[id])->suffix);
                    id = genid(new TAC_AssignAddr(tac_vector.size(), id));
                }else{
                    suffix = &(dynamic_cast<TAC_Param *>(tac_vector[id])->suffix);
                }
                int vec_size = vec.size();
                while(vec_size--){
                    Node *ast = vec.back();
                    vec.pop_back();
                    int offset = inter_exp(ast->children[2]);
                    offset = genid(new TAC_Arithmetic(tac_vector.size(), Operator::MUL_OP, offset, -(*suffix)[vec_size] * typeSize));
                    id = genid(new TAC_Arithmetic(tac_vector.size(), Operator::PLUS_OP, id, offset));
                }
            }else{
                vec.push_back(top->children[0]);
            }
        }
        if(single){
            return genid(new TAC_Copy(id, 0));
        }else{
            return genid(new TAC_AssignVal(tac_vector.size(), id));
        }
    }
    // Exp DOT ID
    if(type_to_string(node->children[1]->type).compare("DOT") == 0){
        // printf("EXP DOT ID\n");
        vector<Node *> vec;
        vec.push_back(node);
        int id;
        while(!vec.empty()){
            Node *top = vec.back();
            if(top->children[0]->type == NodeType::Id){
                id = inter_exp(top);
                // printf("get type\n");
                Attribute *type = tac_vector[id]->type;
                // printf("category %d\n", type->category);
                // printf("after get type\n");
                vec.pop_back();
                if(typeid(*tac_vector[id]) == typeid(TAC_Dec)){
                    id = genid(new TAC_AssignAddr(tac_vector.size(), id));
                }
                int vec_size = vec.size();
                while(vec_size--){
                    Node *ast = vec.back();
                    vec.pop_back();
                    string name = type_to_string(ast->children[2]->type);
                    int offset = getOffSet(type, name);
                    id = genid(new TAC_Arithmetic(tac_vector.size(), Operator::PLUS_OP, id, -offset));
                }
            }else if(top->children.size() == 3){
                vec.push_back(top->children[0]);
            }
        }
        if(single){
            return genid(new TAC_Copy(id, 0));
        }else{
            return genid(new TAC_AssignVal(tac_vector.size(), id));
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
    if (typeid(*tac) == typeid(TAC_Assign))
    {
        putIR(tac->name, genid(new TAC_Param(tac_vector.size(), type, {})));
    }
    else
    {
        putIR(tac->name, genid(new TAC_Param(tac_vector.size(), type, dynamic_cast<TAC_Dec *>(tac)->sizes)));
    }
}

void inter_init()
{
    // printf("inter_init\n");
    tac_vector.clear();
    tac_vector.push_back(new TAC());
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

void putIR(string name, int id)
{
    // printf("putIR: %d\n", id);
    table[name] = id;
}

int genid(TAC *tac)
{
    int index = tac_vector.size();
    tac_vector.push_back(tac);
    return index;
}

int *genlist(int id)
{
    int *label = new int(id);
    return label;
}

void inter_IF(int id, int tbranch, int fbranch)
{
    // printf("inter_IF\n");
    if (tac_vector[id]->swap_flag)
    {
        swap(tbranch, fbranch);
    }
    *dynamic_cast<TAC_IF *>(tac_vector[id])->label = tbranch;
    *dynamic_cast<TAC_GOTO *>(tac_vector[id + 1])->label = fbranch;
}

void inter_WHILE(vector<int> *stat_vec, int end, int target)
{
    // printf("inter_WHILE");
    while (stat_vec->size() > end)
    {
        int top = stat_vec->back();
        stat_vec->pop_back();
        *dynamic_cast<TAC_GOTO *>(tac_vector[top])->label = target;
    }
}

float formatPaser(string name, string value)
{
    if (name.compare("FLOAT") == 0)
    {
        return atof(value.c_str());
    }
    else if (name.compare("INT") == 0)
    {
        return atoi(value.c_str());
    }
    else
    {
        return atoi(value.c_str());
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