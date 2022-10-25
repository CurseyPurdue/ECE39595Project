#include <iostream>
#include "Stmt.h"
using namespace std;


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

std::string PushIObj::serialize(){
    return "PushI  (" + to_string(arg) + ")";
}