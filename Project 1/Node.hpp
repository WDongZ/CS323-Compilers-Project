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

class Node {
private:
    std::variant<std::string, int, float> value;
public:
    NodeType type;
    std::vector<Node *> children;
    // factory method
    static Node * makeNode(NodeType type){
        return new Node(type, "");
    }
    static Node * makeNode(NodeType type, std::initializer_list<Node *> children){
        Node * node = new Node(type, "");
        for(auto child : children){
            node->children.push_back(child);
        }
        return node;
    }
    // 构造函数
    Node(NodeType type, const std::string& text)
        : type(type), value(text) {}

    Node(NodeType type, int intValue)
        : type(type), value(intValue) {}

    Node(NodeType type, float floatValue)
        : type(type), value(floatValue) {}
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
    // cout
    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
        os << "NodeType: " << node.type
           << ", Value: ";

        std::visit([&os](auto &&arg) {
            os << arg;
        }, node.value);

        if (!node.children.empty()) {
            os << ", Children: [";
            for (size_t i = 0; i < node.children.size(); ++i) {
                if (node.children[i]) {
                    os << *node.children[i];
                }
                if (i != node.children.size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
        }

        return os;
    }
};

#endif // NODE_HPP