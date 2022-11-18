#ifndef STMT_H_
#define STMT_H_

#include <string>
#include <vector>

class VM_Stmt {
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

        VM_Stmt(std::string _op) : op{_op} {}
        virtual std::string serialize(){return "STMT STRING";};
};

//stmtOps
class StartObj : public VM_Stmt{
    public:
        int numVars = -1; //num variables (for start)
        StartObj(std::string _op, int _numVars) : VM_Stmt(_op) {opcode = OP_START_PROGRAM; numVars = _numVars;};
        std::string serialize();

};

class EndObj : public VM_Stmt{
    public:
        EndObj(std::string _op) : VM_Stmt(_op) {opcode = -1;};
        std::string serialize();
};

class ExitObj : public VM_Stmt{
    public:
        ExitObj(std::string _op) : VM_Stmt(_op) {opcode = OP_EXIT_PROGRAM;};
        std::string serialize();
};

class ReturnObj : public VM_Stmt{
    public:
        ReturnObj(std::string _op) : VM_Stmt(_op) {opcode = OP_RETURN;};
        std::string serialize();
};

class PopObj : public VM_Stmt{
    public:
        PopObj(std::string _op) : VM_Stmt(_op) {opcode = OP_POP;};
        std::string serialize();
};

class DupObj : public VM_Stmt{
    public:
        DupObj(std::string _op) : VM_Stmt(_op) {opcode = OP_DUP;};
        std::string serialize();
};

class SwapObj : public VM_Stmt{
    public:
        SwapObj(std::string _op) : VM_Stmt(_op) {opcode = OP_SWAP;};
        std::string serialize();
};

class AddObj : public VM_Stmt{
    public:
        AddObj(std::string _op) : VM_Stmt(_op) {opcode = OP_ADD;};
        std::string serialize();
};

class NegateObj : public VM_Stmt{
    public:
        NegateObj(std::string _op) : VM_Stmt(_op) {opcode = OP_NEGATE;};
        std::string serialize();
};

class MulObj : public VM_Stmt{
    public:
        MulObj(std::string _op) : VM_Stmt(_op) {opcode = OP_MUL;};
        std::string serialize();
};

class DivObj : public VM_Stmt{
    public:
        DivObj(std::string _op) : VM_Stmt(_op) {opcode = OP_DIV;};
        std::string serialize();
};

class PrintTOSObj : public VM_Stmt{
    public:
        PrintTOSObj(std::string _op) : VM_Stmt(_op) {opcode = OP_PRINTTOS;};
        std::string serialize();
};

//varVM_StmtOps
class DeclScalObj : public VM_Stmt{
    public:
        DeclScalObj(std::string _op) : VM_Stmt(_op) {opcode = -1;};
        std::string serialize();
};

class PopScalObj: public VM_Stmt{
    public:
        int location = -1; //num variables (for start)
        std::string var = "";
        //PopScalObj(std::string _op, std::string _var) : VM_Stmt(_op) {opcode = OP_POPSCALAR; var = _var; location = -1;};
        PopScalObj(std::string _op, int _location) : VM_Stmt(_op) {opcode = OP_POPSCALAR; location = _location;};
        std::string serialize();

};

class PopArrObj: public VM_Stmt{
    public:
        int location = -1; //num variables (for start)
        std::string var = "";
        //PopArrObj(std::string _op, std::string _var) : VM_Stmt(_op) {opcode = OP_POPARRAY; var = _var; location = -1;};
        PopArrObj(std::string _op, int _location) : VM_Stmt(_op) {opcode = OP_POPARRAY; location = _location;};
        std::string serialize();
};

class PushScalObj: public VM_Stmt{
    public:
        int location = -1; //num variables (for start)
        std::string var = "";
        //PushScalObj(std::string _op, std::string _var) : VM_Stmt(_op) {opcode = OP_PUSHSCALAR; var = _var; location = -1;};
        PushScalObj(std::string _op, int _location) : VM_Stmt(_op) {opcode = OP_PUSHSCALAR; location = _location;};
        std::string serialize();
};

class PushArrObj: public VM_Stmt{
    public:
        int location = -1; //num variables (for start)
        std::string var = "";
        //PushArrObj(std::string _op, std::string _var) : VM_Stmt(_op) {opcode = OP_PUSHARRAY; var = _var; location = -1;};
        PushArrObj(std::string _op, int _location) : VM_Stmt(_op) {opcode = OP_PUSHARRAY; location = _location;};
        std::string serialize();
};

//varLenVM_StmtOps
class DeclArrObj : public VM_Stmt{
    public:
        //int length;
        DeclArrObj(std::string _op) : VM_Stmt(_op) {opcode = -1;};
        std::string serialize();
};

//labelVM_StmtOps
class LabelObj : public VM_Stmt{
    public:
        LabelObj(std::string _op) : VM_Stmt(_op) {opcode = -1;};
        std::string serialize();
};

class GoSubObj : public VM_Stmt{
    public:
        std::string label;
        int location;
        //GoSubObj(std::string _op, std::string _label) : VM_Stmt(_op) {opcode = OP_GOSUB; label = _label; location = -1;};
        GoSubObj(std::string _op, int _location) : VM_Stmt(_op) {opcode = OP_GOSUB; location = _location;};
        std::string serialize();
};

class GoSubLabelObj : public VM_Stmt{
    public:
        //std::string label;
        int size;
        GoSubLabelObj(std::string _op, int _size) : VM_Stmt(_op) {opcode = OP_ENTER_SUBROUTINE;  size = _size;};
        std::string serialize();
};

class JumpObj : public VM_Stmt{
    public:
        //std::string label;
        int location;
        //JumpObj(std::string _op, std::string _label) : VM_Stmt(_op) {opcode = OP_JUMP; label = _label; location = -1;};
        JumpObj(std::string _op, int _location) : VM_Stmt(_op) {opcode = OP_JUMP; location = _location;};
        std::string serialize();
};

class JumpZeroObj : public VM_Stmt{
    public:
        //std::string label;
        int location;
        JumpZeroObj(std::string _op, int _location) : VM_Stmt(_op) {opcode = OP_JUMPZERO; location = _location;};
        std::string serialize();
};

class JumpNZeroObj : public VM_Stmt{
    public:
        //std::string label;
        int location;
        JumpNZeroObj(std::string _op, int _location) : VM_Stmt(_op) {opcode = OP_JUMPNZERO; location = _location;};
        std::string serialize();
};


//intVM_StmtOps
class PushIObj: public VM_Stmt{
    public:
        int arg;
        PushIObj(std::string _op, int _arg) : VM_Stmt(_op) {opcode = OP_PUSHI; arg = _arg;};
        std::string serialize();
        void execute();
};


//strVM_StmtOps
class PrintsObj: public VM_Stmt{
    public:
        int strIndex;
        //std::string str;
        //PrintsObj(std::string _op, std::string _str, int _strIndex) : VM_Stmt(_op) {opcode = OP_PUSHI; str = _str; strIndex = _strIndex;};
        PrintsObj(std::string _op, int _strIndex) : VM_Stmt(_op) {opcode = OP_PUSHI; strIndex = _strIndex;};
        std::string serialize();
};

#endif /* STMT_H_ */

