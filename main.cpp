#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include "Stmt.h"
#include "TwoTuple.h"
using namespace std;

int end_stmt = 0;

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
        //return error
    }

    if (std::find(std::begin(stmtOps), std::end(stmtOps), op) != std::end(stmtOps)){
        //regex to check if okay
        if(op == "start"){
            return new StartObj("start");
        }
        else if(op == "end"){
            end_stmt += 1;
            return new EndObj("end");
            //cout << "Need end type?" << endl;
            //return new StartObj("end (shouldn't be here)");
        }
        else if(op == "exit"){
            return new ExitObj("exit");
        }
        else if(op == "return"){

        }
        else if(op == "pop"){
            return new PopObj("pop");
        }
        else if(op == "dup"){
            return new DupObj("dup");
        }
        else if(op == "swap"){
            return new SwapObj("swap");
        }
        else if(op == "add"){
            return new AddObj("add");
        }
        else if(op == "negate"){
            return new NegateObj("negate");
        }
        else if(op == "mul"){
            return new MulObj("mul");
        }
        else if(op == "div"){
            return new DivObj("div");
        }
        else if(op == "printtos"){
            return new PrintTOSObj("printtos");
        }
    }
    
    else if (std::find(std::begin(varStmtOps), std::end(varStmtOps), op) != std::end(varStmtOps)){
    
    }
    else if (std::find(std::begin(varLenStmtOps), std::end(varLenStmtOps), op) != std::end(varLenStmtOps)){
    
    }
    else if (std::find(std::begin(labelStmtOps), std::end(labelStmtOps), op) != std::end(labelStmtOps)){
    
    }
    else if (std::find(std::begin(intStmtOps), std::end(intStmtOps), op) != std::end(intStmtOps)){
        //regex to catch int and check
        //std::string pushi = op;
        //regex intStmtRegex("(?<=op\\s)[0-9]{0,16}");
        regex intStmtRegex("(\\w+)\\s+([0-9])");
        smatch intStmtMatch;
        int arg = 666;

        if(regex_search(statementStr, intStmtMatch, intStmtRegex)){
            //cout << "Whole match : " << match.str(0) << endl;
            //std::cout << intStmtMatch.str(1) << std::endl;
            //std::cout << std::stoi(intStmtMatch.str(2)) << std::endl;

            //op = intStmtMatch.str(1);
            arg = std::stoi(intStmtMatch.str(2));
        }
        else{
            //no match!
            std::cout << "intStmtRegex doesn't match" << std::endl;
            //exit (EXIT_FAILURE);
            //return error
        }

        if(op == "pushi"){
            return new PushIObj("pushi", arg);
        }
    }
    else if (std::find(std::begin(strStmtOps), std::end(strStmtOps), op) != std::end(strStmtOps)){

    }
    else{
        //operation not found! failure
        cout << "Op doesn't match anywhere" << endl;

    }
    
    //return new StartObj("fail");

    return nullptr;
}

int getNumLines(std::string fn){
    fstream f;
    std::string line;
    f.open(fn);

    int numLines = 0;
    while(!f.eof()){
        getline(f, line);
        numLines++;
    }

    return numLines;
}

//instruction buffer, symbol table, and string buffer declaration
vector<Stmt*> instructionBuffer;
vector<std::string> stringBuffer;
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
                break;
            }
            instructionBuffer.push_back(currentStatement);
            //instructionBufferCount += 1;
            //std::cout << currentStatement->returnString() << std::endl;
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

        
        //for each item in pre instruction list
        //then go through instruction list and add stuff to symbol table, statement buffer, etc
        //do stuff like assign addresses,
        //check if var has been defined twice
        //add set total num of vars to start
        //etc

        //loop through each and print it
        f.close();
    }
    else cout << "Error opening input file";
    return 0;
}

/*first test case

start
exit
end

*/