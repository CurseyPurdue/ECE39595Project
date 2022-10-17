#include <iostream>
using namespace std;

class Stmt {
    public: 
        std::string op;
        int opcode;
        int addr;
        std::string str_token;
        
};

class VarStmt : public Stmt {
    public:
        std::string var_token;
};

class VarLengthStmt : public VarStmt {
    public:
        int length;
};

class LabelStmt : public Stmt {
    public:
        std::string label_token;

};

class IntStmt : public Stmt {
    public:
        int int_token;
};

class StrStmt : public Stmt {
    public:
        std::string str_token;
};