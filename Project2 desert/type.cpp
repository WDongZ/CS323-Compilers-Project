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
    if(attribute1 == nullptr || attribute2 == nullptr){
        return false;
    }
    if(attribute1->category == attribute2->category){
        if(attribute1->category == Category::PRIMITIVE && attribute1->nodetype == attribute2->nodetype){
            return true;
        }else if(attribute1->category == Category::ARRAY && AttributeCompare(attribute1->array_ptr->base, attribute2->array_ptr->base) && attribute1->array_ptr->size == attribute2->array_ptr->size){
            return true;
        }else if(attribute1->category == Category::STRUCTURE || attribute2->category == Category::FUNCTION){
            ParamsList* paramlist1 = attribute1->params_ptr;
            ParamsList* paramlist2 = attribute2->params_ptr;
            while(paramlist1!=nullptr && paramlist2 != nullptr){
                if(!AttributeCompare(paramlist1->global_type, paramlist2->global_type)){
                    return false;
                }
                paramlist1 = paramlist1->next;
                paramlist2 = paramlist2->next;
            }
            if(paramlist1 != nullptr || paramlist2 != nullptr){
                return false;
            }
            return true;
        }
    }
    return false;
}