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
    Id
};

class Node {
private:
    // 不知道这个text为什么在int和float的时候也会赋值，所以就不合并了
    std::string text; 
    std::variant<int, float> value;
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
        : type(type), text(text), value(0) {}

    Node(NodeType type, const std::string& text, int intValue)
        : type(type), text(text), value(intValue) {}

    Node(NodeType type, const std::string& text, float floatValue)
        : type(type), text(text), value(floatValue) {}
    ~Node() {
        for (auto child : children) {
            delete child;
        }
    }
    // getter and setter
    const std::string& getText() const {
        return text;
    }

    std::variant<int, float> getValue() const {
        return value;
    }

    void setText(const std::string& newText) {
        text = newText;
    }

    void setValue(int intValue) {
        value = intValue;
    }
    void setValue(float floatValue) {
        value = floatValue;
    }

    // cout
    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
        os << "NodeType: " << node.type
           << ", Text: " << node.text
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