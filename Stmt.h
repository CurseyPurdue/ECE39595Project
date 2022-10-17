#ifndef STMT_H_
#define STMT_H_

#include <string>

class Stmt {
    public: 
        //opcodes!
        static const int OP_JUMP = 0x00000010; 
        static const int OP_JUMPZERO = 0x00000011;
        static const int OP_JUMPNZERO = 0x00000012;
        static const int OP_GOSUB = 0x00000013;
        static const int OP_RETURN = 0x00000014;
        static const int OP_ENTER_SUBROUTINE = 0x00000015;
        static const int OP_EXIT_SUBROUTINE = 0x00000016;
        static const int OP_START_PROGRAM = 0x00000017;
        static const int OP_EXIT_PROGRAM = 0x00000018;
        static const int OP_PUSHSCALAR = 0x00000020;
        static const int OP_PUSHARRAY = 0x00000021;
        static const int OP_PUSHI = 0x00000022;
        static const int OP_POPSCALAR = 0x00000030;
        static const int OP_POPARRAY = 0x00000031;
        static const int OP_POP = 0x00000032;
        static const int OP_DUP = 0x00000040;
        static const int OP_SWAP = 0x00000041;
        static const int OP_ADD = 0x00000050;
        static const int OP_NEGATE = 0x00000051;
        static const int OP_MUL = 0x00000052;
        static const int OP_DIV = 0x00000053;
        static const int OP_PRINTS = 0x00000060;
        static const int OP_PRINTTOS = 0x00000061;       
        
        std::string op;
        int opcode;
        int addr = 0; //address (for jumps and stuff)
        int numVars = 0; //num variables (for start)

        Stmt(std::string _op, int _opcode) : op{_op}, opcode{_opcode} {}
};

class VarStmt : public Stmt {
    public:
        std::string var_token;
        VarStmt(std::string _op, int _opcode, std::string _var_token) : Stmt(_op, _opcode), var_token(_var_token) {}
};

class VarLengthStmt : public VarStmt {
    public:
        int length;
        VarLengthStmt(std::string _op, int _opcode, std::string _var_token, int _length) : VarStmt(_op, _opcode, _var_token), length(_length) {}
};

class LabelStmt : public Stmt {
    public:
        std::string label_token;
        LabelStmt(std::string _op, int _opcode, std::string _label_token) : Stmt(_op, _opcode), label_token(_label_token) {}

};

class IntStmt : public Stmt {
    public:
        int int_token;
        IntStmt(std::string _op, int _opcode, int _int_token) : Stmt(_op, _opcode), int_token(_int_token) {}
};

class StrStmt : public Stmt {
    public:
        std::string str_token;
        StrStmt(std::string _op, int _opcode, std::string _str_token) : Stmt(_op, _opcode), str_token(_str_token) {}
};
#endif /* STMT_H_ */