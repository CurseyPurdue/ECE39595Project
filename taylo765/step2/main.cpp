#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include "VmStmt.h"
using namespace std;

vector<VM_Stmt*> instructionMemory;
vector<int> runtimeStack;
vector<int*> dataMemory;
vector<std::string> stringBuffer;
int stringBufferIdx = 0;
int pc = 0;

int getArgument(std::string line){
    regex getArgRegex("\\(([0-9]+)\\)");
    smatch getArgMatch;
    std::string var = "error";

    if(regex_search(line, getArgMatch, getArgRegex)){
        var = getArgMatch.str(1);
    }
    
    else{
        std::cout << "Get argument regex doesn't match" << std::endl; //no match!
        //exit (EXIT_FAILURE);
    } 
    //std::cout << var << std::endl;
    return std::stoi(var);
}

void checkStatement(std::string statementStr){
    //regex for op
    //regex for operand
    //create object
    //get statement
    
    regex opRegex("^(\\w+)");
    smatch match;
    std::string op = "";

    if(regex_search(statementStr, match, opRegex)){
        //cout << "Whole match : " << match.str(0) << endl;
        op = match.str(0);
    }
    else{
        //no match!
        std::cout << "Initial regex doesn't match" << std::endl;
        //exit (EXIT_FAILURE);
    }
 
    if(op == "Start"){ //start
        //create new VM_Stmt start ob
        //regex to get num vars
        regex stmtRegex("^(\\w+)\\s+(\\w)");
        smatch stmtMatch;
        std::string var = "error";

        if(regex_search(statementStr, stmtMatch, stmtRegex)){
            //op = intStmtMatch.str(1);
            var = stmtMatch.str(2);
        }
        
        else{
            std::cout << "regex doesn't match" << std::endl; //no match!
            //exit (EXIT_FAILURE);
        } 

        StartObj* object = new StartObj("Start", std::stoi(var));
        instructionMemory.push_back(object);
    }
    else if(op == "End"){
        //create end obj
        EndObj* object = new EndObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "Exit"){
        ExitObj* object = new ExitObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "Return"){
        ReturnObj* object = new ReturnObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "Pop"){
        PopObj* object = new PopObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "Dup"){
        DupObj* object = new DupObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "Swap"){
        SwapObj* object = new SwapObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "Add"){
        AddObj* object = new AddObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "Negate"){
        NegateObj* object = new NegateObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "Mul"){
        MulObj* object = new MulObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "Div"){
        DivObj* object = new DivObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "PrintTOS"){
        PrintTOSObj* object = new PrintTOSObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "PopScalar"){
        int argument = getArgument(statementStr);
        PopScalObj* object = new PopScalObj(op, argument);
        instructionMemory.push_back(object);
    }
    else if(op == "PushI"){
        int argument = getArgument(statementStr);
        PushIObj* object = new PushIObj(op, argument);
        instructionMemory.push_back(object);
    }
    else if(op == "Prints"){
        //parse string and add it to the string buffer
        regex strStmtRegex("^(\\w+)\\s+([^\"\\s]+)");
        smatch strStmtMatch;
        std::string str = "error";
        
        if(regex_search(statementStr, strStmtMatch, strStmtRegex)){
            //op = intStmtMatch.str(1);
            str = strStmtMatch.str(2);
            stringBuffer.push_back(str);
        }
        else{
            std::cout << "strStmtRegex doesn't match" << std::endl; //no match!
            //exit (EXIT_FAILURE);
        }
        //std::cout << statementStr << std::endl << str << std::endl;
        PrintsObj* object = new PrintsObj(op, str, stringBufferIdx);
        stringBufferIdx += 1;
        //std::cout << stringBuffer[0] << std::endl;
        instructionMemory.push_back(object);
    }
}

void execute(VM_Stmt* instr){
    std::string op = (*instr).op;

    if(op == "Start"){
        StartObj* currentStartObj = static_cast<StartObj*>(instr);
        int* globalScopeArr = new int((*currentStartObj).numVars);
        dataMemory.push_back(globalScopeArr);
    }
    else if(op == "Exit"){
        std::cout << "terminated normally" << std::endl;
    }
    else if(op == "PushI"){
        PushIObj* currentPushIObj= static_cast<PushIObj*>(instr);
        runtimeStack.push_back((*currentPushIObj).arg);
    }
    else if(op == "PrintTOS"){
        int tos = runtimeStack.back();
        runtimeStack.pop_back();
        std::cout << tos << std::endl;
    }
    else if(op == "Add"){
        int arg1 = runtimeStack.back();
        runtimeStack.pop_back();
        int arg2 = runtimeStack.back();
        runtimeStack.pop_back();
        int result = arg1 + arg2;
        runtimeStack.push_back(result);
    }
    else if(op == "Prints"){
        PrintsObj* currentPrintsObj = static_cast<PrintsObj*>(instr);
        std::cout << stringBuffer[(*currentPrintsObj).strIndex] << std::endl;
    }
}

int main(int argc, char** argv){
    std::string fn = argv[1];

    fstream f;
    std::string line;
    f.open(fn);
    
    int exit_hit = 0;

    if(f.is_open()){
        while(getline(f, line)){
            //take instrs from .out to instruction memory vector
            checkStatement(line);
            //modify check statement to assign operands to concrete stmt obj
        }
    }

    for(auto & element : instructionMemory){
        execute(element);
        //std::cout << element->serialize() << std::endl;
        //instantiate a stack
        //

        
    }
}