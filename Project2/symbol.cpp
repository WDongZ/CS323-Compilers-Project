#include "symbol.hpp"

void SymbolTable::insert(const std::string& name, Attribute* attribute)
{
    if(table.find(name) == table.end()){
        table[name] = attribute;
    }
}

void SymbolTable::remove(const std::string& name)
{
    if(table.find(name) != table.end()){
        table.erase(name);
    }
}

Attribute* SymbolTable::lookup(const std::string& name)
{
    if(table.find(name) != table.end()){
        return table[name];
    }else{
        return nullptr;
    }
}

void ScopeStack::popScope(){
    if(top == nullptr){
        return;
    }else{
        top = top->parent;
    }
}

void ScopeStack::pushScope(){
    SymbolTable* new_scope = new SymbolTable(top);
    top = new_scope;
}

void ScopeStack::insert(const std::string& name, Attribute* attribute){
    top->insert(name, attribute);
}

void ScopeStack::remove(const std::string& name){
    top->remove(name);
}

Attribute* ScopeStack::lookup(const std::string& name)
{
    SymbolTable* current_scope = top;
    while (current_scope != nullptr) {
        Attribute* result = current_scope->lookup(name);
        if (result != nullptr) {
            return result;
        }
        current_scope = current_scope->parent;
    }
    return nullptr;
}
