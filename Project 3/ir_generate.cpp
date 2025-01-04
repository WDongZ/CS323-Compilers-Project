#include "ir_generate.hpp"
#include <typeinfo>
#include <cassert>
#include <vector>
#include <fstream>

/**
 * Program: ExtDefList
 */
void program_ir(Node *root, const std::string& inputFilePath)
{
    // std::cout << *root << std::endl;

    std::string outputFilePath = inputFilePath;
    size_t lastDot = outputFilePath.find_last_of('.');
    if (lastDot != std::string::npos) {
        outputFilePath = outputFilePath.substr(0, lastDot) + ".ir";
    } else {
        outputFilePath += ".ir";
    }

    // 打开文件用于写入
    std::ofstream outFile(outputFilePath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << outputFilePath << " for writing." << std::endl;
        return;
    }

    extDefList_ir(root->children[0]);

    for (auto& i : tac::TAC::tac_list)
    {
        std::cout << *i << std::endl;
        outFile << *i << std::endl;
    }
}

void extDefList_ir(Node *node)
{
    while (node->children.size())
    {
        extDef_ir(node->children[0]);
        node = node->children[1];
    }
}

/**
 * ExtDef: Specifier ExtDecList SEMI
 *       | Specifier SEMI
 *       | Specifier FunDec CompSt
 */
void extDef_ir(Node *node)
{
    // printf("extDef_ir\n");
    Attribute *type = specifier_ir(node->children[0]);
    if (node->children[1]->type == NodeType::ExtDecList)
    {
        extDecList_ir(node->children[1], type);
    }
    if (node->children[1]->type == NodeType::FunDec)
    {
        func_ir(node->children[1], type);
        compSt_ir(node->children[2]);
    }
}

//ExtDecList -> VarDec
//    | VarDec COMMA ExtDecList

void extDecList_ir(Node *node, Attribute *type)
{
    tac::TAC *tac = varDec_ir(node->children[0], type); // TODO?
    assert(node->children.size() > 1); // no dec!!!
    // while (node->children.size() > 1)
    // {
        
    //     node = node->children[2];
    //     tac::TAC *tac = varDec_ir(node->children[0], type);
    //     std::cout << "inner extDecList_ir" << std::endl;
    // }
    std::cout << "extDecList_ir" << std::endl;
    std::cout << *node << std::endl;
    tac::add_var(node->children[0], static_cast<tac::VarableAddress*>(tac));
    tac::add_tac(tac);
}

//Specifier: TYPE
//Specifier: StructSpecifier

Attribute *specifier_ir(Node *node)
{
    Attribute *type;
    if (node->children[0]->type == NodeType::Type)
    {
        type = type_ir(node->children[0]);
    } else {
        std::cout << "specifier_ir" << " other type"<< *node << std::endl;
    }
    // TODO? 是否不判定使用结构和数组
    return type;
}

Attribute *type_ir(Node *node)
{
    return checkType(node);
}

/**
 * StructSpecifier: STRUCT ID LC DefList RC
 * StructSpecifier: STRUCT ID
 */


//FunDec -> ID LP VarList RP
//      | ID LP RP

void func_ir(Node *node, Attribute *type)
{
    std::string name = std::get<std::string>(node->children[0]->getValue());
    tac::TAC* func = new tac::Function(name);
    tac::add_tac(func);

    if (node->children[2]->type == NodeType::VarList)
    {
        varList_ir(node->children[2]);
    }
}

/**
 * CompSt: LC DefList StmtList RC
 */
void compSt_ir(Node *node)
{
    // printf("compSt_ir\n");
    defList_ir(node->children[1]);
    stmtList_ir(node->children[2]);
}


//  StmtList: Stmt StmtList

void stmtList_ir(Node *node)
{
    while (node->children.size())
    {
        stmt_ir(node->children[0]);
        node = node->children[1];
    }
}

//  DefList: Def DefList

void defList_ir(Node *node)
{
    while (node->children.size())
    {
        def_ir(node->children[0]);
        node = node->children[1];
    }
}

/**
 * Specifier DecList SEMI
 */
void def_ir(Node *node)
{
    // printf("def_ir\n");
    Attribute *type = specifier_ir(node->children[0]);
    decList_ir(node->children[1], type);
}

/**
 * DecList: Dec | Dec COMMA DecList
 */
void decList_ir(Node *node, Attribute *type)
{
    dec_ir(node->children[0], type);
    while (node->children.size() > 1)
    {
        node = node->children[2];
        dec_ir(node->children[0], type);
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

void stmt_ir(Node *node)
{
    // Exp SEMI
    if (node->children[0]->type == NodeType::Exp)
    {
        exp_ir(node->children[0]);
    }
    // CompSt
    else if (node->children[0]->type == NodeType::CompSt)
    {
        compSt_ir(node->children[0]);
    }
    // RETURN Exp SEMI
    else if (node->children[0]->type == NodeType::Return)
    {
        auto exps = exp_ir(node->children[1]);
        assert(exps->instructionType == "Variable");
        tac::TAC* tac_return = new tac::Return(static_cast<tac::VarableAddress*>(exps));
        tac::add_tac(tac_return);
    }
    // IF LP Exp RP Stmt (ELSE Stmt)
    // 可能有问题，主要在于else if部分
    else if (node->children[0]->type == NodeType::If)
    {
        auto expid = exp_ir(node->children[2]);
        assert(expid->instructionType == "IF");
        
        tac::Label* tbranch = static_cast<tac::If*>(expid)->label;
        tac::add_tac(tbranch);
        tac::Goto* jbranch = nullptr;

        stmt_ir(node->children[4]);
        if (node->children.size() >= 6)
        {
            // std::cout << "stmt_ir if else" << std::endl;
            jbranch = new tac::Goto(new tac::Label());
            tac::add_tac(jbranch);
        }
        auto fgoto = tac::TAC::tac_list[expid->line_code + 1];
        assert(fgoto->instructionType == "GOTO");
        tac::Label* fbranch = static_cast<tac::Goto*>(fgoto)->label; 
        tac::add_tac(fbranch);
        IF_ir(static_cast<tac::If*>(expid), static_cast<tac::Goto*>(fgoto) , tbranch, fbranch);
        if (node->children.size() >= 6)
        {
            stmt_ir(node->children[6]);
            tac::Label* jbranchto = new tac::Label();
            tac::add_tac(jbranchto);
            jbranch->label = jbranchto;
        }
    }
    // WHILE LP Exp RP Stmt
    // 跟着if一起改了一下
    else if (node->children[0]->type == NodeType::While)
    {
        size_t cont_size = cont.size();
        size_t br_size = br.size();

        tac::Label* loop_start = new tac::Label();
        tac::add_tac(loop_start);

        auto expid = exp_ir(node->children[2]);
        assert(expid->instructionType == "IF");
        expid = static_cast<tac::If*>(expid);

        tac::Label* tbranch = new tac::Label();
        tac::add_tac(tbranch);

        stmt_ir(node->children[4]);

        tac::Goto* loopbranch = new tac::Goto(loop_start);
        tac::add_tac(loopbranch);
        
        assert(expid->instructionType == "IF");
        auto fgoto = tac::TAC::tac_list[expid->line_code + 1];
        assert(fgoto->instructionType == "GOTO");
        tac::Label* fbranch = static_cast<tac::Goto*>(fgoto)->label;
        tac::add_tac(fbranch);
        IF_ir(static_cast<tac::If*>(expid), static_cast<tac::Goto *>(fgoto) , tbranch, fbranch);
        WHILE_ir(&cont, cont_size, loop_start);
        WHILE_ir(&br, br_size, fbranch);
    }
    // WRITE LP Exp RP SEMI // TODO 能不能读取read write？
    else if (node->children[0]->type == NodeType::Write)
    {
        auto id = exp_ir(node->children[2]);
        if (id->instructionType != "Variable") {
                std::cout << "id: " << id->instructionType << std::endl;
        }
        assert(id->instructionType == "Variable");
        tac::add_tac(new tac::Write(static_cast<tac::VarableAddress*>(id)));
    } else
    {
        assert(NULL);
    }
}

/**
 * Dec: VarDec
 * Dec: VarDec ASSIGN Exp
 */
void dec_ir(Node *node, Attribute *type)
{
    tac::VarableAddress* expid = nullptr;
    if (node->children.size() > 1)
    {
        auto exp = exp_ir(node->children[2]);
        assert(exp->instructionType == "Variable");
        expid = static_cast<tac::VarableAddress* >(exp);
    }
    tac::TAC *tac = varDec_ir(node->children[0], type);
    if (expid)
    {
        dynamic_cast<tac::Assign *>(tac)->right = expid;
    }
    tac::add_var(node->children[0], static_cast<tac::Assign* >(tac)->left);
    tac::add_tac(tac);
}

/**
 * VarDec: ID
 * VarDec: VarDec LB INT RB 不计划做数组
 */
tac::TAC *varDec_ir(Node *node, Attribute *type)
{
    tac::TAC *tac = new tac::Assign(new tac::VarableAddress(tac::VarableAddress::Type::VAR), new tac::VarableAddress(tac::VarableAddress::Type::TEMP));
    return tac;
}

/**
 * Args: Exp COMMA Args
 * Args: Exp
 */
std::vector<tac::TAC *> args_ir(Node *node)
{
    // printf("args_ir\n");
    std::vector<tac::TAC *> args_vector;
    auto exp_varia = exp_ir(node->children[0]);
    // 原本有这个tac是否为dec？
    assert(exp_varia->instructionType == "Variable");
    tac::add_tac(new tac::AssignAddr(new tac::VarableAddress(tac::VarableAddress::Type::TEMP), static_cast<tac::VarableAddress*>(exp_varia)));
    args_vector.push_back(exp_varia);
    while (node->children.size() > 1)
    {
        node = node->children[2];
        exp_varia = exp_ir(node->children[0]);
        args_vector.push_back(exp_varia);
        //原本有一个 if 判断tac为 dec？
        tac::add_tac(new tac::AssignAddr(new tac::VarableAddress(tac::VarableAddress::Type::TEMP), static_cast<tac::VarableAddress*>(exp_varia)));
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
tac::TAC* exp_ir(Node *node, bool single)
{
    // printf("exp_ir\n");
    // READ LP RP // TODO
   if (node->children[0]->type == NodeType::Read)
   {
       // printf("Exp READ\n");
       tac::VarableAddress* id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
       tac::Read *tac = new tac::Read(id);
       tac::add_tac(tac);
       return id;
   }
    // INT  // | FLOAT | CHAR
    if (node->children[0]->type == NodeType::Int)  // 不引用，创建一个
    {
        auto result = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);

        tac::Assign *tac = new tac::Assign(result, new tac::VarableAddress(std::get<int>(node->children[0]->getValue()))); // ??
        tac::add_tac(tac);
        return result;
    }// 只有整数基本类型变量 假设2

    // MINUS Exp | MINUS Exp %prec UMINUS
    if (node->children[0]->type == NodeType::Minus)
    {
        auto var = exp_ir(node->children[1]);
        auto result = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        assert(var->instructionType == "Variable");
        auto tac = new tac::Arithmetic(tac::Operator::MINUS, result, new tac::VarableAddress(0), static_cast<tac::VarableAddress*>(var));
        tac::add_tac(tac);
        return result;  // 非递归
    }
    // NOT Exp
    if (node->children[0]->type == NodeType::Not)
    {
        tac::TAC* exp_if = exp_ir(node->children[1]);
        exp_if->swap_flag ^= 1;
        return exp_if;
    }   // 递归
    // ID LP Args RP
    // ID LP RP
    if (node->children[0]->type == NodeType::Id && node->children.size() > 1)
    {
        // printf("Exp ID LP ARGS RP\n");
        std::string name = std::get<std::string>(node->children[0]->getValue());
        if (node->children[2]->type == NodeType::Args)
        {
            auto id_vec = args_ir(node->children[2]);
            for (auto& id : id_vec)
            {
                tac::add_tac(new tac::Arg(static_cast<tac::VarableAddress*>(id)));
            }
        }
        tac::VarableAddress* id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::add_tac(new tac::Call(id, new tac::Function(name)));
        return id;
    }
    // ID //TODO check
    if (node->children[0]->type == NodeType::Id)
    {
        std::string name = std::get<std::string>(node->children[0]->getValue());
        tac::VarableAddress* id = tac::find_var(node->children[0]);
        tac::TAC* res_id = nullptr;
        if (single)
        {
            if(!id){
                id = new tac::VarableAddress(tac::VarableAddress::Type::VAR);
                tac::var_save[name] = id;
            }
            res_id = new tac::Assign(id, new tac::VarableAddress(0));
            tac::add_tac(res_id);
        }
        else if (!id)
        {
            auto left = new tac::VarableAddress(tac::VarableAddress::Type::VAR);
            res_id = left;
            tac::add_tac(new tac::Assign(left, new tac::VarableAddress(0)));
        }
        else
        {
            res_id = id;
        }
        return res_id;
    }
    // Exp [{AND}|{OR}] Exp // TODO //这个地方需要改
    if (node->children[1]->type == NodeType::Or)
    {
        std::cout << "Exp OR" << std::endl;
        auto lexpid = exp_ir(node->children[0]);
        assert(lexpid->instructionType == "IF");
        int lswap_flag = lexpid->swap_flag;
        auto labelid = new tac::Label();
        tac::add_tac(labelid);
        auto rexpid= exp_ir(node->children[2]);
        assert(rexpid->instructionType == "IF");
        int rswap_flag = rexpid->swap_flag;
        if (lswap_flag)
        {
            auto gototac = tac::TAC::tac_list[lexpid->line_code + 1];
            assert(gototac->instructionType == "GOTO");
            tac::Goto * left_gototac = static_cast<tac::Goto *>(gototac);

            tac::If *iftac = static_cast<tac::If *>(lexpid);
            iftac->label = labelid;
            if (rswap_flag)
            {
                gototac = tac::TAC::tac_list[rexpid->line_code + 1];
                assert(gototac->instructionType == "GOTO");
                left_gototac->label = static_cast<tac::Goto *>(gototac)->label;
            }
            else
            {
                left_gototac->label = static_cast<tac::If *>(rexpid)->label;
            }
        }
        else
        {
            auto gototac = tac::TAC::tac_list[lexpid->line_code + 1];
            assert(gototac->instructionType == "GOTO");
            static_cast<tac::Goto *>(gototac)->label = labelid;

            tac::If *iftac = static_cast<tac::If *>(lexpid);
            if (rswap_flag)
            {
                gototac = tac::TAC::tac_list[rexpid->line_code + 1];
                assert(gototac->instructionType == "GOTO");
                iftac->label = static_cast<tac::Goto *>(gototac)->label;
            }
            else
            {
                iftac->label = static_cast<tac::If *>(rexpid)->label;
            }
        }
        return rexpid;
    }
    // Exp AND Exp
    if (node->children[1]->type == NodeType::And)
    {
        auto lexpid = exp_ir(node->children[0]);
        assert(lexpid->instructionType == "IF");
        int lswap_flag = lexpid->swap_flag;
        tac::Label * labelid = new tac::Label();
        tac::add_tac(labelid);
        
        auto rexpid = exp_ir(node->children[2]);
        assert(rexpid->instructionType == "IF");
        int rswap_flag = rexpid->swap_flag;
        if (lswap_flag)
        {
            tac::If *iftac = static_cast<tac::If *>(lexpid);

            auto gototac = tac::TAC::tac_list[lexpid->line_code + 1];
            assert(gototac->instructionType == "GOTO");
            static_cast<tac::Goto *>(gototac)->label = labelid;
            if (rswap_flag)
            {
                iftac->label = static_cast<tac::If *>(rexpid)->label;
            }
            else
            {
                gototac = tac::TAC::tac_list[rexpid->line_code + 1];
                assert(gototac->instructionType == "GOTO");
                iftac->label = static_cast<tac::Goto *>(gototac)->label;
            }
        }
        else
        {
            auto gototac = tac::TAC::tac_list[lexpid->line_code + 1];
            assert(gototac->instructionType == "GOTO");
            tac::Goto *left_gototac = static_cast<tac::Goto *>(gototac);

            static_cast<tac::If *>(lexpid)->label = labelid;
            if (rswap_flag)
            {
                left_gototac->label = static_cast<tac::If *>(rexpid)->label;
            }
            else
            {
                gototac = tac::TAC::tac_list[rexpid->line_code + 1];
                assert(gototac->instructionType == "GOTO");
                left_gototac->label = static_cast<tac::Goto *>(gototac)->label;
            }
        }
        return rexpid;
    }

    //到此为止
    // Exp [{LT}|{LE}|{GT}|{GE}|{NE}|{EQ}] Exp
    if (node->children[1]->type == NodeType::Lt)
    {
    // printf("Exp LT\n");
        auto lexpid = exp_ir(node->children[0]);
        auto rexpid = exp_ir(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::LT, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    if (node->children[1]->type == NodeType::Le)
    {
    // printf("Exp LE\n");
        auto lexpid = exp_ir(node->children[0]);
        auto rexpid = exp_ir(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::LE, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    if (node->children[1]->type == NodeType::Gt)
    {
        auto lexpid = exp_ir(node->children[0]);
        auto rexpid = exp_ir(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::GT, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    if (node->children[1]->type == NodeType::Ge)
    {
        auto lexpid = exp_ir(node->children[0]);
        auto rexpid = exp_ir(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::GE, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    if (node->children[1]->type == NodeType::Ne)
    {
        auto lexpid = exp_ir(node->children[0]);
        auto rexpid = exp_ir(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::NE, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    if (node->children[1]->type == NodeType::Eq)
    {
        auto lexpid = exp_ir(node->children[0]);
        auto rexpid = exp_ir(node->children[2]);
        tac::If *iftac = new tac::If(tac::Operator::EQ, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid), new tac::Label());
        tac::add_tac(iftac);
        tac::Goto *gototac = new tac::Goto(new tac::Label());
        tac::add_tac(gototac);
        return iftac;
    }
    // Exp ASSIGN Exp
    if (node->children[1]->type == NodeType::Assign)
    {
        auto rightid = exp_ir(node->children[2]);
        auto leftid = exp_ir(node->children[0], true);
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
    // Exp PLUS
        auto lexpid = exp_ir(node->children[0]);
        auto rexpid = exp_ir(node->children[2]);
        tac::VarableAddress * id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::Arithmetic *tac = new tac::Arithmetic( tac::Operator::PLUS, id, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid));
        tac::add_tac(tac);
        return id;
    }
    if (node->children[1]->type == NodeType::Minus)
    {
    // printf("Exp MINUS\n");
        auto lexpid = exp_ir(node->children[0]);
        auto rexpid = exp_ir(node->children[2]);
        tac::VarableAddress * id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::Arithmetic *tac = new tac::Arithmetic( tac::Operator::MINUS, id, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid));
        tac::add_tac(tac);
        return id;
    }
    if (node->children[1]->type == NodeType::Mul)
    {
    // printf("Exp MUL\n");
        auto lexpid = exp_ir(node->children[0]);
        auto rexpid = exp_ir(node->children[2]);
        tac::VarableAddress * id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::Arithmetic *tac = new tac::Arithmetic( tac::Operator::MUL, id, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid));
        tac::add_tac(tac);
        return id;
    }
    if (node->children[1]->type == NodeType::Div) {
        // printf("Exp DIV\n");
        auto lexpid = exp_ir(node->children[0]);
        auto rexpid = exp_ir(node->children[2]);
        tac::VarableAddress * id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::Arithmetic *tac = new tac::Arithmetic( tac::Operator::DIV, id, static_cast<tac::VarableAddress*>(lexpid), static_cast<tac::VarableAddress*>(rexpid));
        tac::add_tac(tac);
        return id;
    }
    // 删除 LB RB
    // Exp DOT ID // TODO
    if(node->children[1]->type == NodeType::Dot){
        // EXP DOT ID
        std::vector<Node*> vec;
        vec.push_back(node);
        tac::TAC * id = nullptr;
        while(!vec.empty()){
            Node *top = vec.back();
            if(top->children[0]->type == NodeType::Id){
                id = exp_ir(top);
                vec.pop_back();
                int vec_size = vec.size();
                while(vec_size--){
                    Node *ast = vec.back();
                    vec.pop_back();
                    std::string name = type_to_string(ast->children[2]->type);
                    tac::add_tac(new tac::Arithmetic(tac::Operator::PLUS, new tac::VarableAddress(tac::VarableAddress::Type::TEMP), static_cast<tac::VarableAddress *>(id), new tac::VarableAddress(0)));
                }
            }else if(top->children.size() == 3){
                vec.push_back(top->children[0]);
            }
        }
        if(single){
            tac::TAC * copy = new tac::Copy(static_cast<tac::VarableAddress *>(id), new tac::VarableAddress(0));
            tac::add_tac(copy);
            return copy;
        }else{
            tac::TAC * assign = new tac::AssignVal(new tac::VarableAddress(tac::VarableAddress::Type::TEMP), static_cast<tac::VarableAddress *>(id));
            tac::add_tac(assign);
            return assign;
        }
    }
    // LP Exp RP
    if (type_to_string(node->children[0]->type).compare("LP") == 0)
    {
    // printf("Exp LP EXP RP\n");
        return exp_ir(node->children[1]);
    }
    return nullptr;
}

/**
 * VarList: ParamDec COMMA VarList
 * VarList: ParamDec
 */
void varList_ir(Node *node)
{
    // printf("varList_ir\n");
    std::vector<Node *> vec = {node->children[0]};
    while (node->children.size() > 1)
    {
        node = node->children[2];
        vec.push_back(node->children[0]);
    }
    while (!vec.empty())
    {
        paramDec_ir(vec.back());
        vec.pop_back();
    }
}

/**
 * ParamDec: Specifier VarDec
 */
void paramDec_ir(Node *node)
{
    // printf("paramDec_ir\n");
    Attribute *type = specifier_ir(node->children[0]);
    tac::TAC *tac = varDec_ir(node->children[1], type);
    if (tac->instructionType == "ASSIGN")
    {
        tac::VarableAddress * id = new tac::VarableAddress(tac::VarableAddress::Type::TEMP);
        tac::Param * param = new tac::Param(id);
        tac::add_var(node, id);
        tac::add_tac(param);
    }
}

Attribute *checkType(Node *node)
{
    // printf("checkType\n");
    // DEBUG("checkType", node);
    switch (node->type)
    {
    case NodeType::Int:
        return new Attribute(Category::PRIMITIVE, NodeType::Int);
        break;
    case NodeType::Float:
        return new Attribute(Category::PRIMITIVE, NodeType::Float);
        break;
    case NodeType::Char:
        return new Attribute(Category::PRIMITIVE, NodeType::Char);
        break;
    default:
        return nullptr;
    }
}


void IF_ir(tac::If * iftac, tac::Goto* gototac, tac::Label* tbranch, tac::Label* fbranch)
{   
    if (iftac->swap_flag)
    {
        std::swap(tbranch, fbranch);
    }
    iftac->label = tbranch;
    gototac->label = fbranch;
}

void WHILE_ir(std::vector<int> *stat_vec, size_t end, tac::Label* target)
{
    while (stat_vec->size() > end)
    {
        int top = stat_vec->back();
        stat_vec->pop_back();
        dynamic_cast<tac::Goto *>(tac::TAC::tac_list[top])->label = target;
    }
}
