#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "type.hpp"
namespace tac
{
    enum class Operator
    {
        PLUS,
        MINUS,
        MUL,
        DIV,
        LE,
        LT,
        GE,
        GT,
        NE,
        EQ,
    };

    std::ostream& operator<<(std::ostream& os, const Operator& op);

    // TAC指令基类
    class TAC
    {
    public:
        std::string instructionType;
        bool swap_flag = false; // 不知道是什么意思，可能if会用一下，但据gpt说用来交换左右操作数？如果只在if利用，你就把这个单独放到if里
        size_t line_code = 0;
        TAC(const std::string& type): instructionType(type), swap_flag(false) {}
        virtual ~TAC() = default;
        virtual std::string to_string() const = 0;
        // 保存所有的TAC指令
        static std::vector<TAC *> tac_list;
    };
    // 简化添加tac_list的过程
    void add_tac(TAC *tac);

    std::ostream& operator<<(std::ostream& os, const TAC& tac);
    // 变量管理类，用于保存变量的地址和类型
    class VarableAddress: public TAC {
        public:
        // 分别表示临时变量、变量、常量
        enum class Type {
            TEMP,
            VAR,
            CONSTANT
        };
        // 保存不同类型的变量数量,用于生成唯一的变量地址
        static std::unordered_map<Type, int> varable_count;
        Type type;
        int value;
        // 常量
        VarableAddress(int value): TAC(std::string("Variable")),type(Type::CONSTANT),value(value) {}
        // 临时变量和变量的构造函数，根据类型从varable_count中获取当前的数量
        VarableAddress(Type type);
        std::string to_string() const override;
    };
    class Label : public TAC {
    public:
        int labeladdress;
        Label(): TAC(std::string("LABEL")), labeladdress(labelCounter++) {}

        std::string to_string() const override;
        // label计数器，用于生成唯一的label
        static int labelCounter;
    };
    class Function : public TAC {
    public:
        std::string name;
        Function(const std::string& name) : TAC(std::string("FUNCTION")), name(name) {}

        std::string to_string() const override;
    };
    // TODO: finish Dec class
    class Dec : public TAC {
    public:
        VarableAddress* var;
        std::vector<int> sizes;
        Dec() = default;

        std::string to_string() const override;
    };
    class Assign: public TAC {
    public:
        VarableAddress* left;
        VarableAddress* right;
        Assign(VarableAddress* left_address, VarableAddress* right_address) : TAC(std::string("ASSIGN")), left(left_address), right(right_address) {}
        // 析构函数，释放left和right的内存
        ~Assign() {
            delete left;
            left = nullptr;
            delete right;
            right = nullptr;
        }
        std::string to_string() const override;
    };
    class AssignAddr: public TAC {
    public:
        VarableAddress* left;
        VarableAddress* right;
        AssignAddr(VarableAddress* left_address, VarableAddress* right_address) : TAC(std::string("ASSIGNADDR")), left(left_address), right(right_address) {}
        ~AssignAddr() {
            delete left;
            left = nullptr;
            delete right;
            right = nullptr;
        }
        std::string to_string() const override;
    };
    class AssignVal: public TAC {
    public:
        VarableAddress* left;
        VarableAddress* right;
        AssignVal(VarableAddress* left_address, VarableAddress* right_address) : TAC(std::string("ASSIGNVAL")), left(left_address), right(right_address) {}
        ~AssignVal() {
            delete left;
            left = nullptr;
            delete right;
            right = nullptr;
        }
        std::string to_string() const override;
    };
    class Copy: public TAC {
    public:
        VarableAddress* left;
        VarableAddress* right;
        Copy(VarableAddress* left_address, VarableAddress* right_address) : TAC(std::string("COPY")), left(left_address), right(right_address) {}
        ~Copy() {
            delete left;
            left = nullptr;
            delete right;
            right = nullptr;
        }
        std::string to_string() const override;
    };
    class Arithmetic: public TAC {
    public:
        Operator op;
        VarableAddress* result;
        VarableAddress* op_left;
        VarableAddress* op_right;
        Arithmetic(Operator op, VarableAddress* result, VarableAddress* op_left, VarableAddress* op_right) : TAC(std::string("ARITHMETIC")), op(op), result(result), op_left(op_left), op_right(op_right) {}
        ~Arithmetic() {
            delete result;
            result = nullptr;
            delete op_left;
            op_left = nullptr;
            delete op_right;
            op_right = nullptr;
        }
        std::string to_string() const override;
    };
    class Goto: public TAC {
    public:
        Label * label;
        Goto(Label * label) : TAC(std::string("GOTO")), label(label) {}
        ~Goto() {
            delete label;
            label = nullptr;
        }
        std::string to_string() const override;
    };
    class If: public TAC {
    public:
        Operator op;
        VarableAddress* left;
        VarableAddress* right;
        Label* label;
        If(Operator op, VarableAddress* left, VarableAddress* right, Label * label) : TAC(std::string("IF")), op(op), left(left), right(right), label(label) {}
        ~If() {
            delete left;
            left = nullptr;
            delete right;
            right = nullptr;
            delete label;
            label = nullptr;
        }
        std::string to_string() const override;
    };
    class Return: public TAC {
    public:
        VarableAddress* value;
        Return(VarableAddress* value) : TAC(std::string("RETURN")), value(value) {}
        ~Return() {
            delete value;
            value = nullptr;
        }
        std::string to_string() const override;
    };
    class Param: public TAC {
    public:
        VarableAddress* var;
        Param(VarableAddress* var) : TAC(std::string("PARAM")), var(var) {}
        ~Param() {
            delete var;
            var = nullptr;
        }
        std::string to_string() const override;
    };
    class Arg: public TAC {
    public:
        VarableAddress* right;
        Arg(VarableAddress* right) : TAC(std::string("ARG")), right(right) {}
        ~Arg() {
            delete right;
            right = nullptr;
        }
        std::string to_string() const override;
    };
    class Call: public TAC {
    public:
        VarableAddress* result;
        Function * function;
        Call(VarableAddress* result, Function * function) : TAC(std::string("CALL")), result(result), function(function) {}
        ~Call() {
            delete result;
            result = nullptr;
            delete function;
            function = nullptr;
        }
        std::string to_string() const override;
    };
    class Read: public TAC {
    public:
        VarableAddress* var;
        Read(VarableAddress* var) : TAC(std::string("READ")), var(var) {}
        ~Read() {
            delete var;
            var = nullptr;
        }
        std::string to_string() const override;
    };
    class Write: public TAC {
    public:
        VarableAddress* var;
        Write(VarableAddress* var) : TAC(std::string("WRITE")), var(var) {}
        ~Write() {
            delete var;
            var = nullptr;
        }
        std::string to_string() const override;
    };
}