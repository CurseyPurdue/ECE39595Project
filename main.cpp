#include <iostream>
#include <fstream>
#include <regex>
#include "Stmt.h"
#include "StartStmt.h"
using namespace std;

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



int getNumLines(std::string fn);

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

    //if (std::find(std::begin(stmtOps), std::end(stmtOps), op) != std::end(stmtOps)){
        //regex to check if okay
    
    //std::cout << op << std::endl;



    if(op == "start"){
        return new StartObj("start");
    }
    else if(op == "exit"){
        return new ExitObj("exit");
    }
    else if(op == "end"){
        cout << "Need end type?" << endl;
        return new StartObj("end (shouldn't be here)");
    }

    //}
    else{
        cout << "Op doesn't match anywhere" << endl;

        //exit (EXIT_FAILURE);
    }
    
    //return new StartObj("fail");

    //return nullptr;
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

StartObj test(){
    return StartObj("test2");
}

int main(int argc, char **argv) {
    string fn = argv[1];

    fstream f;
    std::string line;
    f.open(fn);

    if(f.is_open()){
        //get number of lines in file
        //int numLines = getNumLines(fn);

        //std::cout << numLines << std::endl;
        //create instruction buffer of size numLines
        //Stmt instructionBuffer[numLines]; //ptr[0] = new Stmt("start") ptr[0] -> returnString
        vector<Stmt*> instructionBuffer;
        int instructionBufferCount = 0;

        while(getline(f, line)){
            //add all parsed instructions to pre-instruction list first, checking input, etc
            Stmt* currentStatement = checkStatement(line);
            instructionBuffer.push_back(currentStatement);
            //instructionBufferCount += 1;
            //std::cout << currentStatement->returnString() << std::endl;
        }
        
        for(auto & element : instructionBuffer) {
            std::cout << element->serialize() << std::endl;
        }
        //std::cout << instructionBuffer[0]->returnString() << std::endl;


        std::cout << "end" << std::endl;

        
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