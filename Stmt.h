#ifndef STMT_H_
#define STMT_H_

#include <string>

class Stmt {
    public:        
        int opcode;
        std::string str_token;
};

class Var_Stmt : public Stmt {
    public:
        std::string var_token;
};

class Var_Length_Stmt : public Var_Stmt {
    public:
        int length;
};

class Label_Stmt : public Stmt {
    public:
        std::string label_token;

};

class Int_Stmt : public Stmt {
    public:
        int int_token;
};
#endif /* STMT_H_ */