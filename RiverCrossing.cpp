#include "RiverCrossing.h"
#include "State.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


RiverCrossing::RiverCrossing(){}

bool RiverCrossing::readProblemFile(const char *fileName)
{
    
    
    return true;
}

State *RiverCrossing::solve(const char *fileName)
{
    if (readProblemFile(fileName))
    {
        int totalItemsCount = driverCount+itemCount;
        State *currentState = new State(totalItemsCount);

    }
}
