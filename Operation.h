#pragma once
#include "State.h"

class Operation
{
private:
    /* data */
public:
    int rightSideCount;
    unsigned int result;
    Operation(int rightSideCount);
    ~Operation();
};