#include "type.hpp"

Array::Array(GlobalType *base, int size)
    : base(base), size(size) {}

GlobalType::GlobalType(Category category, NodeType nodetype)
    : category(category), nodetype(nodetype) {}

GlobalType::GlobalType(Category category, Array* array_ptr)
    : category(category), array_ptr(array_ptr) {}

GlobalType::GlobalType(Category category, ParamsList* params_ptr)
    : category(category), params_ptr(params_ptr) {}

ParamsList::ParamsList(std::string name, GlobalType* global_type, ParamsList* next)
    : name(std::move(name)), global_type(global_type), next(next) {}

GlobalType* getGlobalTypePrimitive(Node* node) {
    switch (node->type) {
        case NodeType::Int:
            return new GlobalType(Category::PRIMITIVE, NodeType::Int);
        case NodeType::Char:
            return new GlobalType(Category::PRIMITIVE, NodeType::Char);
        case NodeType::Float:
            return new GlobalType(Category::PRIMITIVE, NodeType::Float);
        default:
            printf("Error in get type primitive\n");
            return nullptr;
    }
}