#include "RiverCrossing.h"
#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

RiverCrossing::RiverCrossing(){}

State *RiverCrossing::solve(const char *fileName)
{
    FileReader *fr = new FileReader();
    // leer el archivo, pasando las direcciones donde se almacenan las variables relevantes para el problema
    if (fr->read(leftRestrictionMatrix, rightRestrictionMatrix, &driverCount, &itemCount, &boatCount, &leftRestrictionCount, &rightRestrictionCount))
    {
        int totalItemsCount = driverCount+itemCount;
        State *currentState = new State(totalItemsCount);
        int move[2] = {2,3};
        currentState->print();
        State *s2State = currentState->boatMove(move, 2);
        s2State->print();
        cout << isValidState(s2State);
        return currentState;
    }
    return NULL;
}

bool RiverCrossing::isValidState(State *state)
{
    cout << "lrc" << leftRestrictionCount << "rrc" << rightRestrictionCount;
    for (int i = 0; i < leftRestrictionCount; i++)
    {
        if (state->rightSide == leftRestrictionMatrix[i])
            return false;
    }
    for (int i = 0; i < rightRestrictionCount; i++)
    {
        if (state->rightSide == rightRestrictionMatrix[i])
            return false;
    }
    return true;
}