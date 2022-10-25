#include <iostream>
#include "Stmt.h"
using namespace std;


std::string StartObj::serialize(){
    return "Start " + to_string(numVars);
}

std::string ExitObj::serialize(){
    return "Exit";
}

std::string EndObj::serialize(){
    return "End";
}