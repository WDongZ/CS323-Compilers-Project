#include "type.hpp"

Array::Array(Attribute *base, int size)
    : base(base), size(size) {}

Attribute::Attribute(Category category, NodeType nodetype)
    : category(category), nodetype(nodetype) {}

Attribute::Attribute(Category category, Array* array_ptr)
    : category(category), array_ptr(array_ptr) {}

Attribute::Attribute(Category category, ParamsList* params_ptr)
    : category(category), params_ptr(params_ptr) {}

ParamsList::ParamsList(std::string name, Attribute* global_type, ParamsList* next)
    : name(std::move(name)), global_type(global_type), next(next) {}

Attribute* getAttributePrimitive(Node* node) {
    switch (node->type) {
        case NodeType::Int:
            return new Attribute(Category::PRIMITIVE, NodeType::Int);
        case NodeType::Char:
            return new Attribute(Category::PRIMITIVE, NodeType::Char);
        case NodeType::Float:
            return new Attribute(Category::PRIMITIVE, NodeType::Float);
        default:
            printf("Error in get type primitive\n");
            return nullptr;
    }
}

bool AttributeCompare(Attribute* attribute1, Attribute* attribute2){

}