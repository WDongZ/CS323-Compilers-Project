#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
#include "type.hpp"

class SymbolTable
{
public:
    SymbolTable* parent;
    std::unordered_map<std::string, Attribute*> table;

    SymbolTable(SymbolTable *parent = nullptr)
        : parent(parent) {}
    void insert(const std::string& name, Attribute* attribute);
    Attribute* lookup(const std::string& name);
    void remove(const std::string& name);

};

class ScopeStack
{
public:
    SymbolTable* top;

    ScopeStack(SymbolTable *Top)
        : top(Top) {};

    void popScope();
    void pushScope();
    void insert(const std::string& name, Attribute* attribute);
    Attribute* lookup(const std::string& name);
    void remove(const std::string& name);
};


#endif