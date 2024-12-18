#include "three_address_code.hpp"
std::ostream& tac::operator<<(std::ostream& os, const Operator& op)
{
    switch (op)
    {
        case tac::Operator::PLUS: os << "+"; break;
        case tac::Operator::MINUS: os << "-"; break;
        case tac::Operator::MUL: os << "*"; break;
        case tac::Operator::DIV: os << "/"; break;
        case tac::Operator::LE: os << "<="; break;
        case tac::Operator::LT: os << "<"; break;
        case tac::Operator::GE: os << ">="; break;
        case tac::Operator::GT: os << ">"; break;
        case tac::Operator::NE: os << "!="; break;
        case tac::Operator::EQ: os << "=="; break;
        default: os << "unknown"; break;
    }
    return os;
}
// 静态变量，保存所有的TAC指令
std::vector<tac::TAC *> tac::TAC::tac_list;
// 添加TAC指令到tac_list
void tac::add_tac(TAC *tac)
{
    TAC::tac_list.push_back(tac);
}
// 静态变量，保存不同类型的变量数量
std::unordered_map<tac::VarableAddress::Type, int> tac::VarableAddress::varable_count;
tac::VarableAddress::VarableAddress(Type type) : type(type)
{
    value = ++varable_count[type];
}
// 重载输出流,输出VarableAddress
std::ostream& tac::operator<<(std::ostream& os, const VarableAddress& address)
{
    switch (address.type)
    {
        case tac::VarableAddress::Type::TEMP: os << "t"; break;
        case tac::VarableAddress::Type::VAR: os << "v"; break;
        case tac::VarableAddress::Type::CONSTANT: os << "#"; break;
        default: os << "unknown variable address"; break;
    }
    os << address.value;
    return os;
}
// 重载输出流,调用to_string()来输出
std::ostream &tac::operator<<(std::ostream& os, const TAC& tac)
{
    os << tac.to_string();
    return os;
}
// label指令
int tac::Label::labelCounter = 0;

std::string tac::Label::to_string() const
{
    std::stringstream ss;
    ss << "LABEL label" << labeladdress << " :";
    std::string message = ss.str();
    return message;
}
// Dec指令
std::string tac::Dec::to_string() const
{
    std::stringstream ss;
    ss << "DEC " << var;
    for (int size : sizes)
    {
        ss << "[" << size << "]";
    }
    std::string message = ss.str();
    return message;
}
// function指令
std::string tac::Function::to_string() const
{
    std::stringstream ss;
    ss << "FUNCTION " << name << " :";
    std::string message = ss.str();
    return message;
}
// assign指令
std::string tac::Assign::to_string() const
{
    std::stringstream ss;
    ss << left << " := " << right;
    std::string message = ss.str();
    return message;
}
// assignaddr指令
std::string tac::AssignAddr::to_string() const
{
    std::stringstream ss;
    ss << left << " := &" << right;
    std::string message = ss.str();
    return message;
}
// assignval指令
std::string tac::AssignVal::to_string() const
{
    std::stringstream ss;
    ss << left << " := *" << right;
    std::string message = ss.str();
    return message;
}
// copy指令
std::string tac::Copy::to_string() const
{
    std::stringstream ss;
    ss << "*" << left << " := " << right;
    std::string message = ss.str();
    return message;
}
// arithmetic指令
std::string tac::Arithmetic::to_string() const
{
    std::stringstream ss;
    ss << result << " := " << op_left << " " << op << " " << op_right;
    std::string message = ss.str();
    return message;
}
// goto指令
std::string tac::Goto::to_string() const
{
    std::stringstream ss;
    ss << "GOTO label" << label->labeladdress;
    std::string message = ss.str();
    return message;
}
// if 指令
std::string tac::If::to_string() const
{
    std::stringstream ss;
    ss << "IF " << left << " " << op << " " << right << " GOTO label" << label->labeladdress;
    std::string message = ss.str();
    return message;
}
// return指令
std::string tac::Return::to_string() const
{
    std::stringstream ss;
    ss << "RETURN " << value;
    std::string message = ss.str();
    return message;
}
// arg指令
std::string tac::Arg::to_string() const
{
    std::stringstream ss;
    ss << "ARG " << right;
    std::string message = ss.str();
    return message;
}
// call指令
std::string tac::Call::to_string() const
{
    std::stringstream ss;
    ss << "t" << result << " := CALL " << function->name;
    std::string message = ss.str();
    return message;
}
// read指令
std::string tac::Read::to_string() const
{
    std::stringstream ss;
    ss << "READ " << var;
    std::string message = ss.str();
    return message;
}
// write指令
std::string tac::Write::to_string() const
{
    std::stringstream ss;
    ss << "WRITE " << var;
    std::string message = ss.str();
    return message;
}
// int main () {
//     // test Assign
    
//     tac::Assign assign(tac::VarableAddress::Type::TEMP, tac::VarableAddress::Type::VAR);
//     std::cout << assign << std::endl;
// }
