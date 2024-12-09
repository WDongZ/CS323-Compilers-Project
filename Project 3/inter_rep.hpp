#include "type.hpp"
#include "unordered_map"
#include <sstream>
using namespace std;

const int BASIC_SIZE = 4;

class TAC;
enum class Operator
{
    PLUS_OP,
    MINUS_OP,
    MUL_OP,
    DIV_OP,
    LE_OP,
    LT_OP,
    GE_OP,
    GT_OP,
    NE_OP,
    EQ_OP,
};

extern vector<TAC *> tac_vector;
extern unordered_map<string, int> table;

string addr2str(int addr)
{
    if (addr > 0) { return "t" + to_string(addr);}
    else { return "#" + to_string(-addr);}
}

string operator2str(Operator op)
{
    static const unordered_map<Operator, string> op_map = {
        {Operator::PLUS_OP, "+"}, {Operator::MINUS_OP, "-"}, {Operator::MUL_OP, "*"},
        {Operator::DIV_OP, "/"}, {Operator::LE_OP, "<="}, {Operator::LT_OP, "<"},
        {Operator::GE_OP, ">="}, {Operator::GT_OP, ">"}, {Operator::NE_OP, "!="},
        {Operator::EQ_OP, "=="}
    };
    auto it = op_map.find(op);
    if (it != op_map.end()) return it->second;
    exit(-2);
}

class TAC
{
public:
    int address;
    string name;
    Attribute *type;
    bool swap_flag = false;
    TAC()
    {
        swap_flag = false;
    }
    virtual string to_string()
    {
        return "";
    }
    virtual int generate_ID()
    {
        int ID = tac_vector.size();
        tac_vector.push_back(this);
        return ID;
    }
};

class TAC_Label : public TAC
{
public:
    TAC_Label(int address)
    {
        TAC::address = address;
    }
    string to_string()
    {
        ostringstream buffer;
        buffer << "LABEL label: " << TAC::address;
        return buffer.str();
    }
};

class TAC_Dec : public TAC
{
public:
    vector<int> sizes;
    vector<int> suffix;
    TAC_Dec(int address, Attribute *type, string name, vector<int> sizes)
    {
        TAC::address = address;
        TAC::type = type;
        TAC::name = name;
        this -> sizes = sizes;
        int offset = 1;
        for(int i = sizes.size() - 1; i >= 0; i--){
            suffix.push_back(offset);
            offset *= sizes[i];
        }
    }

    string to_string(){
        int size = 1;
        for(int i = 0; i < this->sizes.size(); i++){
            size *= this->sizes[i];
        }
        ostringstream buffer;
        buffer << "DEC t" << TAC::address << " " << BASIC_SIZE * size;
        return buffer.str();
    }
};

class TAC_Func: public TAC {
public:
    TAC_Func(int address, string name){
        TAC::address = address;
        TAC::name = name;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "FUNCTION " << TAC::name << " :";
        return buffer.str();
    }
};


class TAC_Assign: public TAC{
public:
    int val_address;
    TAC_Assign(int address, int val_address){
        TAC::address = address;
        this->val_address = val_address;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "t" << TAC::address << " := " << addr2str(val_address);
        return buffer.str();
    }
};

class TAC_AssignAddr: public TAC{
public:
    int assign_address;
    TAC_AssignAddr(int address, int assign_address){
        TAC::address = address;
        this->assign_address = assign_address;
    }
    string to_string(){
        std::ostringstream buffer;
        buffer << "t" << TAC::address << " := &t" << assign_address;
        return buffer.str();
    }
};

class TAC_AssignVal: public TAC{
public:
    int val_address;
    TAC_AssignVal(int address, int val_address){
        TAC::address = address;
        this->val_address = val_address;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "t" << TAC::address << " := *t" << val_address;
        return buffer.str();
    }
};


class TAC_Copy: public TAC{
public:
    int val_address;
    TAC_Copy(int address, int val_address){
        TAC::address = address;
        this->val_address = val_address;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "*t" << TAC::address << " := t" << val_address;
        return buffer.str();
    }
};

class TAC_Arithmetic: public TAC{
public:
    Operator op;
    int left_address;
    int right_address;
    TAC_Arithmetic(int address, Operator op, int left_address, int right_address){
        TAC::address = address;
        this->op = op;
        this->left_address = left_address;
        this->right_address = right_address;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "t" << TAC::address << " := " << addr2str(left_address) << " " << operator2str(op) << " " << addr2str(right_address);
        return buffer.str();
    }
};


class TAC_GOTO: public TAC{
public:
    int* label;
    TAC_GOTO(int address, int* label){
        TAC::address = address;
        this->label = label;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "GOTO label" << *label;
        return buffer.str();
    }
};

class TAC_IF: public TAC{
public:
    int* label;
    Operator op;
    int left_address;
    int right_address;
    TAC_IF(int address, Operator op, int left_address, int right_address, int* label){
        TAC::address = address;
        this->op = op;
        this->left_address = left_address;
        this->right_address = right_address;
        this->label = label;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "IF t" << left_address << " " << operator2str(op) << " t" << right_address << " GOTO label" << *label;
        return buffer.str();
    }
};

class TAC_Return: public TAC{
public:
    int return_address;
    TAC_Return(int address, int return_address){
        TAC::address = address;
        this->return_address = return_address;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "RETURN " << addr2str(return_address);
        return buffer.str();
    }
};


class TAC_Param: public TAC{
public:
    vector<int> sizes;
    vector<int> suffix;
    TAC_Param(int address, Attribute *type, vector<int> sizes){
        TAC::address = address;
        TAC::type = type;
        this->sizes = vector<int>();
        this->sizes.insert(this->sizes.end(), sizes.begin(), sizes.end());
        int totle = 1;
        for(int i = sizes.size() - 1; i >= 0; --i){
            suffix.push_back(totle);
            totle *= sizes[i];
        }
    }
    string to_string(){
        ostringstream buffer;
        buffer << "PARAM t" << TAC::address;
        return buffer.str();
    }
};

class TAC_Arg: public TAC{
public:
    int arg_address;
    TAC_Arg(int address, int arg_address){
        TAC::address = address;
        this->arg_address = arg_address;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "ARG t" << arg_address;
        return buffer.str();
    }
};

class TAC_Call: public TAC{
public:
    string label;
    TAC_Call(int address, string label){
        TAC::address = address;
        this->label = label;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "t" << TAC::address << " := CALL " << label;
        return buffer.str();
    }
};

class TAC_Read: public TAC{
public:
    TAC_Read(int address){
        TAC::address = address;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "READ t" << TAC::address;
        return buffer.str();
    }
};

class TAC_Write: public TAC{
public:
    int write_address;
    TAC_Write(int address, int write_address){
        TAC::address = address;
        this->write_address = write_address;
    }
    string to_string(){
        ostringstream buffer;
        buffer << "WRITE t" << write_address;
        return buffer.str();
    }
};


int inter_exp(Node *node, bool single = false);
vector<int> inter_args(Node *node);

void inter_init();
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
TAC* inter_varDec(Node *node, Attribute* type);
void inter_varList(Node *node);
void inter_paramDec(Node *node);

int getIR(string name);
void putIR(string name, int id);
int genid(TAC *tac);
int *genlist(int id = tac_vector.size() + 1);

void inter_IF(int id, int tbranch, int fbranch);
void inter_WHILE(vector<int>* stat_vec, int end, int target);
Attribute *checkType(Node *node);

float formatPaser(string name, string value);
int getOffSet(Attribute* global_type, string name);