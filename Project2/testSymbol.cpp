#include <stdio.h>
#include "symbol.hpp"

int main()
{

    ScopeStack *stack = new ScopeStack(nullptr);
    stack->pushScope();

    Attribute* attri1 = new Attribute(Category::PRIMITIVE, NodeType::Int);
    stack->insert("a1", attri1);
    Attribute* a2 = new Attribute(Category::PRIMITIVE, NodeType::Float);
    stack->insert("a2", a2);
    
    stack->pushScope();
    Attribute* a3 = new Attribute(Category::ARRAY, NodeType::And);
    Attribute* a4 = new Attribute(Category::FUNCTION, NodeType::Char);
    stack->insert("a3", a3);
    stack->insert("a4", a4);

    if(stack->lookup("a1") != nullptr){
        std::cout << "a1 exists" << std::endl;
    }
    if(stack->lookup("a3") != nullptr){
        std::cout << "a3 exists" << std::endl;
    }

    stack->popScope();
    if(stack->lookup("a1") != nullptr){
        std::cout << "a1 exists" << std::endl;
    }
    if(stack->lookup("a3") != nullptr){
        std::cout << "a3 exists" << std::endl;
    }else{
        std::cout << "a3 pops" << std::endl;
    }


}
