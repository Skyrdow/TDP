#include "RiverCrossing.h"
#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

RiverCrossing::RiverCrossing(){}

bool RiverCrossing::isValidState(State *checkState)
{
    unsigned int leftSide = ~(checkState->rightSide);
    cout << "2";
    for (int i = 0; i < leftRestrictionCount; i++)
    {
        if (leftSide == leftRestrictionMatrix[i])
            return false;
    }
    for (int i = 0; i < rightRestrictionCount; i++)
    {
        if (checkState->rightSide == rightRestrictionMatrix[i])
            return false;
    }
    return true;
}

State *RiverCrossing::solve(const char *fileName)
{
    FileReader *fr = new FileReader();
    // leer el archivo, pasando las direcciones donde se almacenan las variables relevantes para el problema
    if (fr->read(leftRestrictionMatrix, rightRestrictionMatrix, &driverCount, &itemCount, &boatCount, &leftRestrictionCount, &rightRestrictionCount))
    {
        int totalItemsCount = driverCount+itemCount;
        State *currentState = new State(totalItemsCount);
        int move[2] = {3,4};
        currentState->print();
        State *s2State = currentState->boatMove(move, 2);
        s2State->print();
        cout << "2";
        isValidState(s2State);
        cout << "1";
        return currentState;
    }
    return nullptr;
}
