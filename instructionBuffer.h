#ifndef INSTRUCTIONBUFFER_H__
#define INSTRUCTIONBUFFER_H__
#include "Stmt.h"
#include <vector>
using namespace std;

class ibuffer{
    public:
        static std::vector<Stmt*> instructionBuffer;
};

#endif