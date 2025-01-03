#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <variant>
#include <vector>
#include <iostream>
enum class NodeType {
    Type,
    Int,
    Float,
    Char,
    Id,
    If,
    Else,
    While,
    Return,
    Struct,
    Dot,
    Semi,
    Comma,
    Assign,
    Lt,
    Le,
    Gt,
    Ge,
    Ne,
    Eq,
    Plus,
    Minus,
    Mul,
    Div,
    And,
    Or,
    Not,
    Lp,
    Rp,
    Lb,
    Rb,
    Lc,
    Rc,
    Program,
    ExtDefList,
    ExtDef,
    ExtDecList,
    Specifier,
    StructSpecifier,
    VarDec,
    FunDec,
    VarList,
    ParamDec,
    CompSt,
    StmtList,
    Stmt,
    DefList,
    Def,
    DecList,
    Dec,
    Exp,
    Args,
    Read,
    Write
};

inline std::string type_to_string(NodeType type) {
    switch (type) {
        case NodeType::Type: return "Type";
        case NodeType::Int: return "Int";
        case NodeType::Float: return "Float";
        case NodeType::Char: return "Char";
        case NodeType::Id: return "Id";
        case NodeType::If: return "If";
        case NodeType::Else: return "Else";
        case NodeType::While: return "While";
        case NodeType::Return: return "Return";
        case NodeType::Dot: return "Dot";
        case NodeType::Semi: return "Semi";
        case NodeType::Comma: return "Comma";
        case NodeType::Assign: return "Assign";
        case NodeType::Struct: return "Struct";
        case NodeType::Lt: return "Lt";
        case NodeType::Le: return "Le";
        case NodeType::Gt: return "Gt";
        case NodeType::Ge: return "Ge";
        case NodeType::Ne: return "Ne";
        case NodeType::Eq: return "Eq";
        case NodeType::Plus: return "Plus";
        case NodeType::Minus: return "Minus";
        case NodeType::Mul: return "Mul";
        case NodeType::Div: return "Div";
        case NodeType::And: return "And";
        case NodeType::Or: return "Or";
        case NodeType::Not: return "Not";
        case NodeType::Lp: return "LP";
        case NodeType::Rp: return "RP";
        case NodeType::Lb: return "LB";
        case NodeType::Rb: return "RB";
        case NodeType::Lc: return "LC";
        case NodeType::Rc: return "RC";
        case NodeType::Program: return "Program";
        case NodeType::ExtDefList: return "ExtDefList";
        case NodeType::ExtDef: return "ExtDef";
        case NodeType::ExtDecList: return "ExtDecList";
        case NodeType::Specifier: return "Specifier";
        case NodeType::StructSpecifier: return "StructSpecifier";
        case NodeType::VarDec: return "VarDec";
        case NodeType::FunDec: return "FunDec";
        case NodeType::VarList: return "VarList";
        case NodeType::ParamDec: return "ParamDec";
        case NodeType::CompSt: return "CompSt";
        case NodeType::StmtList: return "StmtList";
        case NodeType::Stmt: return "Stmt";
        case NodeType::DefList: return "DefList";
        case NodeType::Def: return "Def";
        case NodeType::DecList: return "DecList";
        case NodeType::Dec: return "Dec";
        case NodeType::Exp: return "Exp";
        case NodeType::Args: return "Args";
        case NodeType::Read: return "Read";
        case NodeType::Write: return "Write";
        default: {
            std::cerr << "Unknown NodeType" << std::endl;
            return "Unknown";
        }
    }
}

inline std::ostream &operator<<(std::ostream &os, NodeType type) {
    os << type_to_string(type);
    return os;
}
class Node {
private:
    std::variant<std::string, int, float> value;
    void printTree(std::ostream& os, int depth) const {
        os << std::string(depth * 4, ' ') << getText() << " (" << linec << ")"<< '\n';
        for (const auto& child : children) {
            child->printTree(os, depth + 1);
        }
    }
public:
    NodeType type;
    size_t linec = 0;
    std::vector<Node *> children;
    // factory method
    static Node * makeNode(NodeType type, size_t linec){
        return new Node(type, type_to_string(type), linec);
    }
    static Node * makeNode(NodeType type, std::initializer_list<Node *> children, size_t linec){
        Node * node = new Node(type, type_to_string(type), linec);
        for(auto child : children){
            node->children.push_back(child);
        }
        return node;
    }
    // 构造函数
    Node(NodeType type, const std::string& text, size_t linec)
        : value(text), type(type), linec(linec) {}

    Node(NodeType type, int intValue, size_t linec)
        : value(intValue), type(type), linec(linec) {}

    Node(NodeType type, float floatValue, size_t linec)
        : value(floatValue), type(type), linec(linec) {}
    ~Node() {
        for (auto child : children) {
            delete child;
        }
    }
    // getter and setter
    std::variant<std::string, int, float> getValue() const {
        return value;
    }

    void setValue(int intValue) {
        value = intValue;
    }
    void setValue(float floatValue) {
        value = floatValue;
    }
    void setValue(const std::string& text) {
        value = text;
    }

    std::string getText() const {
        switch (type) {
            case NodeType::Int:
                return "INT: " + std::to_string(std::get<int>(value));
            case NodeType::Float:
                return "FLOAT" + std::to_string(std::get<float>(value));
            case NodeType::Char:
                return std::string("CHAR: ") + "'" + std::get<std::string>(value) + "'";
            case NodeType::Id:
                return "ID: " + std::get<std::string>(value);
            case NodeType::Type:
                return "TYPE: " + std::get<std::string>(value);
            default:
                return type_to_string(type);
        }
    }
    // cout
    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
        node.printTree(os, 0);
        return os;
    }
};

#endif // NODE_HPP