#include <iostream>
#include "VmStmt.h"
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

std::string ReturnObj::serialize(){
    return "Return";
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
std::string DeclScalObj::serialize(){
    return "";
}

std::string DeclArrObj::serialize(){
    return "";
}

std::string PopScalObj::serialize(){
    return "PopScalar " + var + ", (" + to_string(location) + ")";
    //return "";
}

std::string PopArrObj::serialize(){
    return "PopArr " + var + ", (" + to_string(location) + ")";
    //return "";
}

std::string PushScalObj::serialize(){
    return "PushScalar " + var + ", (" + to_string(location) + ")";
    //return "";
}

std::string PushArrObj::serialize(){
    return "PushArray " + var + ", (" + to_string(location) + ")";
    //return "";
}

//varLenStmtOps


//labelStmtOps
std::string LabelObj::serialize(){
    return "";
}

std::string GoSubObj::serialize(){
    return "GoSub " + label + "(" + to_string(location) + ")";
}

std::string GoSubLabelObj::serialize(){
    return "GoSubLabel " + label;
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