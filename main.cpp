#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include "Stmt.h"
#include "TwoTuple.h"
using namespace std;

int end_stmt = 0;
//int pop_var = -1;
const std::vector<std::string> stmtOps = {"start",
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
                                "printtos"
};

const std::vector<std::string> varStmtOps = {"declscal", 
                                "pushscal", 
                                "pusharr",
                                "popscal",
                                "poparr"
};

const std::vector<std::string> varLenStmtOps = {"declarr"};

const std::vector<std::string> labelStmtOps{"label",
                                        "gosublabel",
                                        "jump",
                                        "jumpzero",
                                        "jumpnzero",
                                        "gosub"
};

const std::vector<std::string> intStmtOps{"pushi"};
const std::vector<std::string> strStmtOps{"prints"};

//instruction buffer, symbol table, and string buffer declaration
vector<Stmt*> instructionBuffer;
vector<std::string> stringBuffer;

vector<map<std::string, TwoTuple*>> symbolTable;
int instBufferReturnIndex = 0;
int globalVarCount = 0;
int varCount = 0;

Stmt* checkStatement(std::string statementStr){
    //get statement
    
    regex opRegex("(\\w+)");
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

    if (std::find(std::begin(stmtOps), std::end(stmtOps), op) != std::end(stmtOps)){
        //regex to check if okay
        if(op == "start"){
            //add top level symbol table
            std::map<std::string, TwoTuple*> base;
            symbolTable.push_back(base);

            StartObj* object = new StartObj("start");
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "end"){
            //go back through instruction buffer
            //for each unfilled jump, etc 
            //look up jump's label in symbol table map
            vector<Stmt*>::iterator it; 
            for(it = instructionBuffer.begin(); it != instructionBuffer.end(); it++){
                Stmt* currentObj = *it;

                if(currentObj->op == "start"){
                    StartObj* currentStartObj = static_cast<StartObj*>(currentObj);

                    if(currentStartObj->numVars == -1){ //if value not assigned
                        currentStartObj->numVars = globalVarCount;
                    }
                }
                if(currentObj->op == "jump"){
                    JumpObj* currentJumpObj = static_cast<JumpObj*>(currentObj);
                
                    if(currentJumpObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentJumpObj->label];
                        currentJumpObj->location = vals->location;
                    }
                }
                else if(currentObj->op == "jumpzero"){
                    JumpZeroObj* currentJumpObj = static_cast<JumpZeroObj*>(currentObj);
                
                    if(currentJumpObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentJumpObj->label];
                        currentJumpObj->location = vals->location;
                    }
                }
                else if(currentObj->op == "jumpnzero"){
                    JumpNZeroObj* currentJumpObj = static_cast<JumpNZeroObj*>(currentObj);
                
                    if(currentJumpObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentJumpObj->label];
                        currentJumpObj->location = vals->location;
                    }
                }
                else if(currentObj->op == "gosub"){
                    GoSubObj* currentGoSubObj = static_cast<GoSubObj*>(currentObj);
                
                    if(currentGoSubObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentGoSubObj->label];
                        currentGoSubObj->location = vals->location;
                    }
                }
                else if(currentObj->op == "popscal"){
                    PopScalObj* currentPopScalObj = static_cast<PopScalObj*>(currentObj);

                    if(currentPopScalObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentPopScalObj->var];
                        currentPopScalObj->location = vals->location;

                    }
                }   
                else if(currentObj->op == "pushscal"){
                    PushScalObj* currentPushScalObj = static_cast<PushScalObj*>(currentObj);

                    if(currentPushScalObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentPushScalObj->var];
                        currentPushScalObj->location = vals->location;
                    }
                }
                
            }

            
            end_stmt += 1;
            return new EndObj("end");
            //cout << "Need end type?" << endl;
            //return new StartObj("end (shouldn't be here)");
        }
        else if(op == "exit"){

            ExitObj* object = new ExitObj("exit");
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "return"){
            //push return onto instruction buffer
            ReturnObj* object = new ReturnObj("return");
            instructionBuffer.push_back(object);

            //std::cout << symbolTable.back().size() << std::endl;

            //when you hit a return, loop from 
            int count = instBufferReturnIndex;
            vector<Stmt*>::iterator it; 
            for(it = instructionBuffer.begin() + instBufferReturnIndex; it != instructionBuffer.end(); it++){
                Stmt* currentObj = *it;
                //std::cout << currentObj->op << std::endl;
                count += 1;

                if(currentObj->op == "jump"){
                    JumpObj* currentJumpObj = static_cast<JumpObj*>(currentObj);
                
                    if(currentJumpObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentJumpObj->label];
                        currentJumpObj->location = vals->location;
                    }
                }
                else if(currentObj->op == "jumpzero"){
                    JumpZeroObj* currentJumpObj = static_cast<JumpZeroObj*>(currentObj);
                
                    if(currentJumpObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentJumpObj->label];
                        currentJumpObj->location = vals->location;
                    }
                }
                else if(currentObj->op == "jumpnzero"){
                    JumpNZeroObj* currentJumpObj = static_cast<JumpNZeroObj*>(currentObj);
                
                    if(currentJumpObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentJumpObj->label];
                        currentJumpObj->location = vals->location;
                    }
                }
                else if(currentObj->op == "popscal"){
                    PopScalObj* currentPopScalObj = static_cast<PopScalObj*>(currentObj);

                    if(currentPopScalObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentPopScalObj->var];
                        currentPopScalObj->location = vals->location;
                    }
                }   
                else if(currentObj->op == "pushscal"){
                    PushScalObj* currentPushScalObj = static_cast<PushScalObj*>(currentObj);

                    if(currentPushScalObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentPushScalObj->var];
                        currentPushScalObj->location = vals->location;
                    }
                }
                
                else if(currentObj->op == "gosublabel"){ //SET SIZE OF GOSUBLABEL STACK FRAME
                    GoSubLabelObj* currentGoSubLabelObj = static_cast<GoSubLabelObj*>(currentObj);
                
                    if(currentGoSubLabelObj->size == -1){ //if value not assigned
                        currentGoSubLabelObj->size = varCount;
                    }
                }
                /*else if(currentObj->op == "gosub"){
                    GoSubObj* currentGoSubObj = static_cast<GoSubObj*>(currentObj);
                
                    if(currentGoSubObj->location == -1){ //if value not assigned
                        TwoTuple* vals = symbolTable.back()[currentGoSubObj->label];
                        currentGoSubObj->location = vals->location;
                    }
                }*/
            }
            instBufferReturnIndex = 0; //set instBufferReturnIndex = 0;
            symbolTable.pop_back(); //then pop off symbol table  

            return object;
        }
        else if(op == "pop"){
            PopObj* object = new PopObj("pop");
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "dup"){
            DupObj* object = new DupObj("dup");
            instructionBuffer.push_back(object);
            return object;        
        }
        else if(op == "swap"){
            SwapObj* object = new SwapObj("swap");
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "add"){
            AddObj* object = new AddObj("add");
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "negate"){
            NegateObj* object = new NegateObj("negate");
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "mul"){
            MulObj* object = new MulObj("mul");
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "div"){
            DivObj* object = new DivObj("div");
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "printtos"){
            PrintTOSObj* object = new PrintTOSObj("PrintTOS");
            instructionBuffer.push_back(object);
            return object; 
        }
    }
    
    else if (std::find(std::begin(varStmtOps), std::end(varStmtOps), op) != std::end(varStmtOps)){
        regex varStmtRegex("(\\w+)\\s+(\\w)");
        smatch varStmtMatch;
        std::string var = "error";

        if(regex_search(statementStr, varStmtMatch, varStmtRegex)){
            //op = intStmtMatch.str(1);
            var = varStmtMatch.str(2);
        }
        
        else{
            std::cout << "varStmtRegex doesn't match" << std::endl; //no match!
            //exit (EXIT_FAILURE);
        } 

        if(op == "declscal"){
            TwoTuple* data;
            
            if(symbolTable.size() == 1){ //if in top level use globalVarCount and add one to it
                data = new TwoTuple(globalVarCount, 1);
                globalVarCount += 1;
            }
            else{ //else use varCount (which can be reset per subroutine)
                data = new TwoTuple(varCount + globalVarCount, 1);
                varCount += 1;
            }

            std::pair<std::string, TwoTuple*> pair;  //add to symbol table
            pair.first = var;
            pair.second = data;
            symbolTable.back().insert(pair);

            //CHECK TO MAKE SURE THAT VAR isn't already used

            DeclScalObj* object = new DeclScalObj("declscalobj");
            //dont add to instruction buffer?
            return object;
        }
        else if(op == "popscal"){
            PopScalObj* object = new PopScalObj(op, var);
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "pushscal"){
            PushScalObj* object = new PushScalObj(op, var);
            instructionBuffer.push_back(object);
            return object;
        }
    }

    else if (std::find(std::begin(varLenStmtOps), std::end(varLenStmtOps), op) != std::end(varLenStmtOps)){
    
    }
    else if (std::find(std::begin(labelStmtOps), std::end(labelStmtOps), op) != std::end(labelStmtOps)){
        regex labelStmtRegex("(\\w+)\\s+(\\w+)");
        smatch labelStmtMatch;
        std::string label = "error";

        if(regex_search(statementStr, labelStmtMatch, labelStmtRegex)){
            //op = intStmtMatch.str(1);
            label = labelStmtMatch.str(2);
        }
        else{
            std::cout << "labelStmtRegex doesn't match" << std::endl; //no match!
            //exit (EXIT_FAILURE);
        } 

        if(op == "label"){
            //std::map<std::string, TwoTuple*> map;
            TwoTuple* data = new TwoTuple(instructionBuffer.size(), 0);
            std::pair<std::string, TwoTuple*> pair;
            //add to symbol table
            pair.first = label;
            pair.second = data;
            //map.insert(pair); // label = L1     <str - l1, location - 1, size - 0>
            symbolTable.back().insert(pair);

            //CHECK TO MAKE SURE THERE ISN'T ALREADY THAT VAR

            //std::cout << symbolTable.size() << std::endl;
            LabelObj* object = new LabelObj("label");
            //dont add to instruction buffer?
            return object;
        }
        else if(op == "jump"){
            JumpObj* object = new JumpObj("jump", label);
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "jumpzero"){
            JumpZeroObj* object = new JumpZeroObj("jumpzero", label);
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "jumpnzero"){
            JumpNZeroObj* object = new JumpNZeroObj("jumpnzero", label);
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "gosub"){
            GoSubObj* object = new GoSubObj("gosub", label);
            instructionBuffer.push_back(object);
            return object;
        }
        else if(op == "gosublabel"){
            //GoSubLabelObj* object = new GoSubLabelObj("gosublabel", label);
            //instructionBuffer.push_back(object);
            //set instruction buffer return index (for looking through returns)
            instBufferReturnIndex = instructionBuffer.size();

            //add a symbol in the top level symbol table
            TwoTuple* data = new TwoTuple(instructionBuffer.size(), 0);
            std::pair<std::string, TwoTuple*> pair;
            
            GoSubLabelObj* object = new GoSubLabelObj("gosublabel", label);
            instructionBuffer.push_back(object);
            //add to symbol table
            pair.first = label;
            pair.second = data;
            symbolTable.back().insert(pair);

            //create subroutine symbol table
            std::map<std::string, TwoTuple*> subroutine;
            symbolTable.push_back(subroutine);
            varCount = 0;//reset varCount

            return object;
        }
    }
    else if (std::find(std::begin(intStmtOps), std::end(intStmtOps), op) != std::end(intStmtOps)){

        regex intStmtRegex("(\\w+)\\s+([0-9]+)");  //regex to catch int and check
        smatch intStmtMatch;
        int arg = 666;

        if(regex_search(statementStr, intStmtMatch, intStmtRegex)){
            //op = intStmtMatch.str(1);
            arg = std::stoi(intStmtMatch.str(2));
        }
        else{
            //no match!
            std::cout << "intStmtRegex doesn't match" << std::endl;
            //exit (EXIT_FAILURE);
        }

        if(op == "pushi"){
            PushIObj* object = new PushIObj("pushi", arg);
            instructionBuffer.push_back(object);
            return object;
        }
    }
    else if (std::find(std::begin(strStmtOps), std::end(strStmtOps), op) != std::end(strStmtOps)){
        
        regex strStmtRegex("(\\w+)\\s+(\\w+)");
        smatch strStmtMatch;
        std::string str = "error";

        if(regex_search(statementStr, strStmtMatch, strStmtRegex)){
            //op = intStmtMatch.str(1);
            str = strStmtMatch.str(2);
        }
        else{
            std::cout << "strStmtRegex doesn't match" << std::endl; //no match!
            //exit (EXIT_FAILURE);
        }

        if(op == "prints"){
            //add str to string buffer
            stringBuffer.push_back(str);

            PrintsObj* object = new PrintsObj("prints", str, stringBuffer.size()-1); //str index at strbuffer size - 1
            instructionBuffer.push_back(object);
            return object;     
        }
        
    }
    else{
        //operation not found! failure
        cout << "Op doesn't match anywhere" << endl;

    }
    
    //return new StartObj("fail");

    return nullptr;
}

//vector<std::map<std::string, TwoTuple*>> symbolTable;

int main(int argc, char **argv) {
    string fn = argv[1];

    fstream f;
    std::string line;
    f.open(fn);

    if(f.is_open()){
        int instructionBufferCount = 0;

        while(getline(f, line)){
            //add all parsed instructions to pre-instruction list first, checking input, etc
            Stmt* currentStatement = checkStatement(line);
            if((currentStatement->serialize() == "End") && (end_stmt == 1)){
                
                //go through instruction buffer 
                //if label claimed go sub -> extra dynamic symbols 
                //JumpObj("jump", "L1", NULL) 
                //for element instruction buffer
                //      if any obj -> val == NULL
                            //for each in symbol table if (L1)
                break;
            }

        }
        
        //write to file
        fstream outputFile;
        outputFile.open("output0.txt", fstream::out);
        
        for(auto & element : instructionBuffer) {
            //cout << element->serialize() << endl;
            outputFile << element->serialize() << endl;
            //outputFile << "Hello\n";
            //std::cout << element->serialize() << std::endl;
        }
        //std::cout << instructionBuffer[0]->returnString() << std::endl;


        //std::cout << "end" << std::endl;

        
        //loop through each and print it
        f.close();
    }
    else cout << "Error opening input file";
    return 0;
}
