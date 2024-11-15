#ifndef NODE_HPP
#define NODE_HPP

#include <string>

enum NodeType {
    Type,
    Int,
    Float,
    Char,
    Id
};

class Node {
public:
    NodeType type;
    std::string text;
    int intValue;
    float floatValue;

    // 构造函数
    Node(NodeType type, const std::string& text)
        : type(type), text(text), intValue(0), floatValue(0.0) {}

    Node(NodeType type, const std::string& text, int intValue)
        : type(type), text(text), intValue(intValue), floatValue(0.0) {}

    Node(NodeType type, const std::string& text, float floatValue)
        : type(type), text(text), intValue(0), floatValue(floatValue) {}
};

#endif // NODE_HPP