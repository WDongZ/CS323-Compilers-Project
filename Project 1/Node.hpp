#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <variant>
#include <vector>
#include <iostream>
enum NodeType {
    Type,
    Int,
    Float,
    Char,
    Id,
    If,
    Else,
    While,
    Return,
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
    Args    
};

std::string to_string(NodeType type) {
    switch (type) {
        case Type: return "Type";
        case Int: return "Int";
        case Float: return "Float";
        case Char: return "Char";
        case Id: return "Id";
        case If: return "If";
        case Else: return "Else";
        case While: return "While";
        case Return: return "Return";
        case Dot: return "Dot";
        case Semi: return "Semi";
        case Comma: return "Comma";
        case Assign: return "Assign";
        case Lt: return "Lt";
        case Le: return "Le";
        case Gt: return "Gt";
        case Ge: return "Ge";
        case Ne: return "Ne";
        case Eq: return "Eq";
        case Plus: return "Plus";
        case Minus: return "Minus";
        case Mul: return "Mul";
        case Div: return "Div";
        case And: return "And";
        case Or: return "Or";
        case Not: return "Not";
        case Lp: return "Lp";
        case Rp: return "Rp";
        case Lb: return "Lb";
        case Rb: return "Rb";
        case Lc: return "Lc";
        case Rc: return "Rc";
        case Program: return "Program";
        case ExtDefList: return "ExtDefList";
        case ExtDef: return "ExtDef";
        case ExtDecList: return "ExtDecList";
        case Specifier: return "Specifier";
        case StructSpecifier: return "StructSpecifier";
        case VarDec: return "VarDec";
        case FunDec: return "FunDec";
        case VarList: return "VarList";
        case ParamDec: return "ParamDec";
        case CompSt: return "CompSt";
        case StmtList: return "StmtList";
        case Stmt: return "Stmt";
        case DefList: return "DefList";
        case Def: return "Def";
        case DecList: return "DecList";
        case Dec: return "Dec";
        case Exp: return "Exp";
        case Args: return "Args";
        default: return "Unknown";
    }
}

std::ostream &operator<<(std::ostream &os, NodeType type) {
    os << to_string(type);
    return os;
}
class Node {
private:
    std::variant<std::string, int, float> value;

    void printTree(std::ostream& os, int depth) const {
        os << std::string(depth * 4, ' ') << getText() << '\n';
        for (const auto& child : children) {
            child->printTree(os, depth + 1);
        }
    }
public:
    NodeType type;
    std::vector<Node *> children;
    // factory method
    static Node * makeNode(NodeType type){
        return new Node(type, to_string(type));
    }
    static Node * makeNode(NodeType type, std::initializer_list<Node *> children){
        Node * node = new Node(type, to_string(type));
        for(auto child : children){
            node->children.push_back(child);
        }
        return node;
    }
    // 构造函数
    Node(NodeType type, const std::string& text)
        : value(text), type(type) {}

    Node(NodeType type, int intValue)
        : value(intValue), type(type) {}

    Node(NodeType type, float floatValue)
        : value(floatValue), type(type) {}
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
                return std::to_string(std::get<int>(value));
            case NodeType::Float:
                return std::to_string(std::get<float>(value));
            default:
                return std::get<std::string>(value);
        }
    }
    // cout
    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
        node.printTree(os, 0);
        return os;
    }
};

#endif // NODE_HPP