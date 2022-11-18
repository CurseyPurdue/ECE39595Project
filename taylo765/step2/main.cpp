#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include "VmStmt.h"
using namespace std;

vector<VM_Stmt*> instructionMemory;
vector<int> runtimeStack;
vector<int*> dataMemory;
vector<int> returnAddressStack;
vector<std::string> stringBuffer;
int stringBufferIdx = 0;
int pc = 0;

std::string getArgument(std::string line){
    //regex getArgRegex("\\(([0-9]+)\\)");
    regex getArgRegex("([0-9]+)");
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
    return var;
}

std::string getSecondArg(std::string line){
    regex strStmtRegex("^(\\w+)\\s+([^\"\\s]+)");
    smatch strStmtMatch;
    std::string str = "error";
    
    if(regex_search(line, strStmtMatch, strStmtRegex)){
        //op = intStmtMatch.str(1);
        str = strStmtMatch.str(2);
        //stringBuffer.push_back(str);
    }
    else{
        std::cout << "strStmtRegex doesn't match" << std::endl; //no match!
        //exit (EXIT_FAILURE);
    }
    return str;
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
        /*regex stmtRegex("^(\\w+)\\s+(\\w)");
        smatch stmtMatch;
        std::string var = "error";

        if(regex_search(statementStr, stmtMatch, stmtRegex)){
            //op = intStmtMatch.str(1);
            var = stmtMatch.str(2);
        }
        
        else{
            std::cout << "regex doesn't match" << std::endl; //no match!
            //exit (EXIT_FAILURE);
        } */

        int var = std::stoi(getArgument(statementStr));

        //std::cout << var << std::endl;
        StartObj* object = new StartObj("Start", var);
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
        int argument = std::stoi(getArgument(statementStr));
        PopScalObj* object = new PopScalObj(op, argument);
        instructionMemory.push_back(object);
    }
    else if(op == "PushScalar"){
        int argument = std::stoi(getArgument(statementStr));
        PushScalObj* object = new PushScalObj(op, argument);
        instructionMemory.push_back(object);
    }
    else if(op == "PopArray"){
        int argument = std::stoi(getArgument(statementStr));
        PopArrObj* object = new PopArrObj(op, argument);
        instructionMemory.push_back(object);
    }
    else if(op == "PushArray"){
        int argument = std::stoi(getArgument(statementStr));
        PushArrObj* object = new PushArrObj(op, argument);
        instructionMemory.push_back(object);
    }
    else if(op == "PushI"){
        int argument = std::stoi(getArgument(statementStr));
        PushIObj* object = new PushIObj(op, argument);
        instructionMemory.push_back(object);
    }
    else if(op == "Prints"){
        //parse string and add it to the string buffer
        /*regex strStmtRegex("^(\\w+)\\s+([^\"\\s]+)");
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
        }*/
        //std::string str = getSecondArg(statementStr);
        
        //stringBuffer.push_back(str);
        int idx = std::stoi(getArgument(statementStr));
        //std::cout << idx << std::endl;
        //std::cout << statementStr << std::endl << str << std::endl;
        PrintsObj* object = new PrintsObj(op, idx);
        //stringBufferIdx += 1;
        //std::cout << stringBuffer[0] << std::endl;
        instructionMemory.push_back(object);
    }
    else if(op == "Jump"){
       int location = std::stoi(getArgument(statementStr));
       JumpObj* object = new JumpObj(op, location);
       instructionMemory.push_back(object);
    }
    else if(op == "GoSub"){
        int arg = std::stoi(getArgument(statementStr));
        GoSubObj* object = new GoSubObj(op, arg);
        instructionMemory.push_back(object);
    }
    else if(op == "GoSubLabel"){
        int arg = std::stoi(getArgument(statementStr));
        GoSubLabelObj* object = new GoSubLabelObj(op, arg);
        instructionMemory.push_back(object);
    }
    else if(op == "Return"){
        ReturnObj* object = new ReturnObj(op);
        instructionMemory.push_back(object);
    }
    else if(op == "JumpZero"){
        int arg = std::stoi(getArgument(statementStr));
        JumpZeroObj* object = new JumpZeroObj(op, arg);
        instructionMemory.push_back(object);
    }
    else if(op == "JumpNZero"){
        int arg = std::stoi(getArgument(statementStr));
        JumpNZeroObj* object = new JumpNZeroObj(op, arg);
        instructionMemory.push_back(object);
    }
    else{
        stringBuffer.push_back(statementStr);
    }
}

void execute(VM_Stmt* instr){
    std::string op = (*instr).op;

    if(op == "Start"){
        StartObj* currentStartObj = static_cast<StartObj*>(instr);
        int* globalScopeArr = new int((*currentStartObj).numVars);
        dataMemory.push_back(globalScopeArr);
        pc += 1;
    }
    else if(op == "Exit"){
        std::cout << "terminated normally" << std::endl;
        pc += 1;
    }
    else if(op == "PushI"){
        PushIObj* currentPushIObj= static_cast<PushIObj*>(instr);
        runtimeStack.push_back((*currentPushIObj).arg);
        pc += 1;
    }
    else if(op == "PrintTOS"){
        int tos = runtimeStack.back();
        runtimeStack.pop_back();
        std::cout << tos << std::endl;
        pc += 1;
    }
    else if(op == "Add"){
        int arg1 = runtimeStack.back();
        runtimeStack.pop_back();
        int arg2 = runtimeStack.back();
        runtimeStack.pop_back();
        int result = arg1 + arg2;
        runtimeStack.push_back(result);
        pc += 1;
    }
    else if(op == "Prints"){
        PrintsObj* currentPrintsObj = static_cast<PrintsObj*>(instr);
        std::cout << stringBuffer[(*currentPrintsObj).strIndex] << std::endl;
        pc += 1;
    }
    else if(op == "Div"){
        int arg1 = runtimeStack.back();
        runtimeStack.pop_back();
        int arg2 = runtimeStack.back();
        runtimeStack.pop_back();
        int result = arg1 / arg2;
        runtimeStack.push_back(result);
        pc += 1;
    }
    else if(op == "Dup"){
        int arg = runtimeStack.back();
        runtimeStack.push_back(arg);
        pc += 1;
    }
    else if(op == "Mul"){
        int arg1 = runtimeStack.back();
        runtimeStack.pop_back();
        int arg2 = runtimeStack.back();
        runtimeStack.pop_back();
        int result = arg1 * arg2;
        runtimeStack.push_back(result);
        pc += 1;
    }
    else if(op == "Negate"){
        int arg = runtimeStack.back();
        runtimeStack.pop_back();
        int result = arg * -1;
        runtimeStack.push_back(result);
        pc += 1;
    }
    else if(op == "Pop"){
        runtimeStack.pop_back();
        pc += 1;
    }
    else if(op == "Swap"){
        int arg1 = runtimeStack.back();
        runtimeStack.pop_back();
        int arg2 = runtimeStack.back();
        runtimeStack.pop_back();
        runtimeStack.push_back(arg1);
        runtimeStack.push_back(arg2);
        pc += 1;
    }
    else if(op == "Jump"){
        JumpObj* currentJumpObj = static_cast<JumpObj*>(instr);
        pc = (*currentJumpObj).location;
    }
    else if(op == "GoSub"){
        returnAddressStack.push_back(pc + 1);
        GoSubObj* currentGoSubObj = static_cast<GoSubObj*>(instr);
        pc = (*currentGoSubObj).location;
    }
    else if(op == "GoSubLabel"){
        GoSubLabelObj* currentGoSubLabelObj = static_cast<GoSubLabelObj*>(instr);
        int* localScopeArr = new int((*currentGoSubLabelObj).size);
        dataMemory.push_back(localScopeArr);
        pc += 1;
    }
    else if(op == "Return"){
        ReturnObj* currentReturnObj = static_cast<ReturnObj*>(instr);
        pc = returnAddressStack.back();
        returnAddressStack.pop_back(); //???
        dataMemory.pop_back();
    }
    else if(op == "PopScalar"){
        PopScalObj* currentPopScalObj = static_cast<PopScalObj*>(instr);
        int popped_val = runtimeStack.back();
        //std::cout << popped_val << std::endl;
        runtimeStack.pop_back();
        dataMemory.back()[(*currentPopScalObj).location] = popped_val;
        pc += 1;
    }
    else if(op == "PushScalar"){
        PushScalObj* currentPushScalObj = static_cast<PushScalObj*>(instr);
        int val = dataMemory.back()[(*currentPushScalObj).location];
        runtimeStack.push_back(val);
        pc += 1;
    }
    else if(op == "PopArray"){
        PopArrObj* currentPopArrObj = static_cast<PopArrObj*>(instr);
        int idx = runtimeStack.back();
        runtimeStack.pop_back();
        int e = idx + (*currentPopArrObj).location;
        int val = runtimeStack.back();
        runtimeStack.pop_back();
        dataMemory.back()[e] = val;
        pc += 1;
    }
    else if(op == "PushArray"){
        PushArrObj* currentPushArrObj = static_cast<PushArrObj*>(instr);
        int e = (*currentPushArrObj).location + runtimeStack.back();
        runtimeStack.pop_back();
        runtimeStack.push_back(dataMemory.back()[e]);
        pc += 1;
    }
    else if(op == "JumpZero"){
        JumpZeroObj* currentJumpZeroObj = static_cast<JumpZeroObj*>(instr);
        int zeroOrNah = runtimeStack.back();
        runtimeStack.pop_back();
        if(zeroOrNah == 0){
            pc = (*currentJumpZeroObj).location;
        }
        else{
            pc += 1;
        }
    }
    else if(op == "JumpNZero"){
        JumpNZeroObj* currentJumpNZeroObj = static_cast<JumpNZeroObj*>(instr);
        int zeroOrNah = runtimeStack.back();
        runtimeStack.pop_back();
        if(zeroOrNah != 0){
            pc = (*currentJumpNZeroObj).location;
        }
        else{
            pc += 1;
        }
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

    /*for(auto & element : instructionMemory){
        //execute(element);
        std::cout << element->serialize() << std::endl;
        //instantiate a stack
        //

        
    }*/
    for(int i = 0; i < instructionMemory.size(); i = pc){ //i = pc){
        execute(instructionMemory[i]);
        //std::cout << instructionMemory[i] << std::endl;
    }
}