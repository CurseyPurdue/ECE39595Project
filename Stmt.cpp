#include <iostream>
#include "Stmt.h"
using namespace std;

//stmtOps
std::string StartObj::serialize(){
    return "Start " + to_string(numVars);
}

std::string EndObj::serialize(){
    return "End";
}

std::string ExitObj::serialize(){
    return "Exit";
}

std::string PopObj::serialize(){
    return "Pop";
}

std::string DupObj::serialize(){
    return "Dup";
}

std::string SwapObj::serialize(){
    return "Swap";
}

std::string AddObj::serialize(){
    return "Add";
}

std::string NegateObj::serialize(){
    return "Negate";
}

std::string MulObj::serialize(){
    return "Mul";
}

std::string DivObj::serialize(){
    return "Div";
}

std::string PrintTOSObj::serialize(){
    return "PrintTOS";
}


//varStmtOps


//varLenStmtOps


//labelStmtOps
std::string LabelObj::serialize(){
    return "";
}

std::string JumpObj::serialize(){
    return "Jump, " + to_string(location);
}

std::string JumpZeroObj::serialize(){
    return "JumpZero, " + label + ", (" + to_string(location) + ")";
}

std::string JumpNZeroObj::serialize(){
    return "JumpNZero, " + label + ", (" + to_string(location) + ")";
}

//intStmtOps
std::string PushIObj::serialize(){
    return "PushI  (" + to_string(arg) + ")";
}

//strStmtOps
std::string PrintsObj::serialize(){
    return "Prints " + str;
}