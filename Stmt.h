#ifndef STMT_H_
#define STMT_H_

#include <string>
#include <vector>

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

        //static list of strings of kinds of statements, so we don't have to regex 5000 times        

        std::string op = 0;
        int opcode = 0;

        Stmt(std::string _op) : op{_op} {}
        virtual std::string serialize(){return "STMT STRING";};
};


class StartObj : public Stmt{
    public:
        int numVars = 0; //num variables (for start)
        StartObj(std::string _op) : Stmt(_op) {opcode = OP_START_PROGRAM;};
        std::string serialize();

};

class ExitObj : public Stmt{
    public:
        ExitObj(std::string _op) : Stmt(_op) {opcode = OP_EXIT_PROGRAM;};
        std::string serialize();
};

class EndObj : public Stmt{
    public:
        EndObj(std::string _op) : Stmt(_op) {opcode = 666;};
        std::string serialize();
};

class PushIObj: public Stmt{
    public:
        int arg;
        PushIObj(std::string _op, int _arg) : Stmt(_op) {opcode = OP_PUSHI; arg = _arg;};
        std::string serialize();
};
#endif /* STMT_H_ */

