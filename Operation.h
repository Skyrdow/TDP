#pragma once
#include "State.h"

class Operation
{
private:
    /* data */
public:
    // Cantidad de 1s en el lado derecho
    int rightSideCount;
    // Representación del lado derecho
    unsigned int result;
    Operation(unsigned int num);
    ~Operation();
};