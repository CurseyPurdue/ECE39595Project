#include <iostream>
#include <fstream>
#include <regex>
#include "Stmt.h"
using namespace std;

std::vector<std::string> stmt_ops{"start",
                                "end",
                                "exit",
                                "return",
                                "pop",
                                "dup",
                                "swap",
                                "add",
                                "negate",
                                "mul",
                                "div",
                                "printtos",
};

std::vector<std::string> varStmt_ops{"declscal", 
                                "pushscal", 
                                "pusharr",
                                "popscal",
                                "poparr"
};

std::vector<std::string> varLenStmt_ops{"declarr"};

std::vector<std::string> labelStmt_ops{"label",
                                "gosublabel",
                                "jump",
                                "jumpzero",
                                "jumpnzero",
                                "gosub"
};

std::vector<std::string> intStmt_ops{"pushi"};
std::vector<std::string> strStmt_ops{"prints"};

//checks if statement and returns it in statement form if it's valid
Stmt checkStatement(std::string statement_str){
    //get statement
    regex opRegex("(\\w+)");
    smatch match;
    string op = "";

    if(regex_search(statement_str, match, opRegex)){
        //cout << "Whole match : " << match.str(0) << endl;
        op = match.str(0);
    }
    else{
        //no match!
        cout << "No match!" << endl;
        //return error
    }

    //Stmts
    //if std::find(op)
    if (std::find(std::begin(stmt_ops), std::end(stmt_ops), op) != std::end(stmt_ops)){
        //check if clean (nothing after op)
        

        //cout << "Matched!" << endl;

        if(op == "start"){
            return Stmt("Start", Stmt::OP_START_PROGRAM);
        }
        else if (op == "end"){
            //dont know what to do with this atm
        }
        else if (op == "exit"){
            return Stmt("Exit", Stmt::OP_EXIT_PROGRAM);
        }
        else if (op == "return"){
            return Stmt("Return", Stmt::OP_RETURN);
        }
        else if (op == "pop"){
            return Stmt("Pop", Stmt::OP_POP);
        }
        else if (op == "dup"){
            return Stmt("Dup", Stmt::OP_DUP);
        }
        else if (op == "swap"){
            return Stmt("Swap", Stmt::OP_SWAP);
        }
        else if (op == "add"){
            return Stmt("Add", Stmt::OP_ADD);
        }
        else if (op == "negate"){
            return Stmt("Negate", Stmt::OP_NEGATE);
        }
        else if (op == "mul"){
            return Stmt("Mul", Stmt::OP_MUL);
        }
        else if (op == "div"){
            return Stmt("Div", Stmt::OP_DIV);
        }
        else if (op == "printtos"){ //print top of stack
            return Stmt("PrintTOS", Stmt::OP_PRINTTOS);
        }
    }
    //VarStmts
    else if (std::find(std::begin(stmt_ops), std::end(stmt_ops), op) != std::end(stmt_ops)){
        //check if clean
        std::string var = "";

        if (op == "declscal"){
            return VarStmt("DeclScalar", 0, var);
        }
        else if (op == "pushscal"){
            return VarStmt("PushScalar", Stmt::OP_PUSHSCALAR, var);
        }
        else if (op == "pusharr"){
            return VarStmt("PushArray", Stmt::OP_PUSHARRAY, var);
        }
        else if (op == "popscal"){
            return VarStmt("PopScalar", Stmt::OP_POPSCALAR, var);
        }
        else if (op == "poparr"){
            return VarStmt("PopArray", Stmt::OP_POPARRAY, var);

        }
    }
    //VarLengthStmts
    else if (std::find(std::begin(varLenStmt_ops), std::end(varLenStmt_ops), op) != std::end(varLenStmt_ops)){
        //check if clean
        std::string var = "";
        int len = 0;

        if(op == "declarr"){
            return VarLengthStmt("DeclareArray", 0, var, 0);
        }
    }
    //LabelStmts
    else if (std::find(std::begin(labelStmt_ops), std::end(labelStmt_ops), op) != std::end(labelStmt_ops)){
        //check if clean
        std::string label = "";

        if(op == "label"){
            return LabelStmt("Label", 0, label);    
        }
        else if(op == "gosublabel"){
            return LabelStmt("GoSubLabel", Stmt::OP_ENTER_SUBROUTINE, label);    
        }
        else if(op == "jump"){
            return LabelStmt("Jump", Stmt::OP_JUMP, label);    
        }
        else if(op == "jumpzero"){
            return LabelStmt("JumpZero", Stmt::OP_JUMPZERO, label);    
        }
        else if(op == "jumpnzero"){
            return LabelStmt("JumpNZero", Stmt::OP_JUMPNZERO, label);    
        }
        else if(op == "gosub"){
            return LabelStmt("GoSub", Stmt::OP_GOSUB, label);    

        }
    }
    //IntStmts
    else if (std::find(std::begin(intStmt_ops), std::end(intStmt_ops), op) != std::end(intStmt_ops)){
        //check if clean (is it actually an int?)
        int integer = 0;

        if(op == "pushi"){
            return IntStmt("PushI", Stmt::OP_PUSHI, integer);    

        }
    }
    //StrStmts
    else if (std::find(std::begin(strStmt_ops), std::end(strStmt_ops), op) != std::end(strStmt_ops)){
        //check if clean (is it just one string?)
        regex strStmtRegex("\\s*(\\w+)\\s+(\\w+|\\d+)\\s*$");
        smatch strStmtMatch;
        std::string strStmtString = "";

        cout << statement_str << endl;

        if(regex_match(statement_str, strStmtMatch, strStmtRegex)){
            strStmtString = strStmtMatch.str(2);
        }
        else{
            //no match!
            cout << "No match!" << endl;
            //return error
        }

        if (op == "prints"){
            return StrStmt("Prints", Stmt::OP_PRINTS, strStmtString);
        }
    }
    else{
        //else error, op not recognized!

    }
    return Stmt("err", 0);
}




int main(int argc, char **argv) {
    string fn = argv[1];

    fstream f;
    string line;
    f.open(fn);

    if(f.is_open()){
        while(getline(f, line)){
            //add all parsed instructions to pre-instruction list first, checking input, etc
            checkStatement(line);

        }
        //for each item in pre instruction list
        //then go through instruction list and add stuff to symbol table, statement buffer, etc
        //do stuff like assign addresses,
        //check if var has been defined twice
        //add set total num of vars to start
        //etc
        f.close();
    }
    else cout << "Error opening input file";
    return 0;
}
