#ifndef TYPE_HPP
#define TYPE_HPP

#include "Node.hpp"
#include <string>

enum Category {
    PRIMITIVE, ARRAY, STRUCTURE, FUNCTION
};

class Array;
class ParamsList;

class Attribute {
public:
    NodeType nodetype;
    Array* array_ptr = nullptr;
    ParamsList* params_ptr = nullptr;
    Category category;

    Attribute(Category category, NodeType nodetype);
    Attribute(Category category, Array* array_ptr);
    Attribute(Category category, ParamsList* params_ptr);
};

Attribute* getAttributePrimitive(Node* node);
Attribute* getAttributeInt();
Attribute* getAttributeChar();
Attribute* getAttributeFloat();

class Array {
public:
    Attribute *base;
    int size;
    Array(Attribute *base, int size);
};

class ParamsList {
public:
    std::string name;
    Attribute *global_type = nullptr;
    ParamsList* next = nullptr;
    ParamsList(std::string name, Attribute* global_type, ParamsList* next);
};

#endif