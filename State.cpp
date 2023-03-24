#include "State.h"

State::State(int stateSize)
{
    this->stateSize = stateSize;
    this->currentBoatSide = boatSide::left;
    this->rightSide = new int[stateSize];
    for (int i = 0; i < stateSize; i++)
    {
        this->rightSide[i] = 0;
    }
    this->previousState = nullptr;
}

State::State(int *right, int stateSize)
{
    this->stateSize = stateSize;
    this->currentBoatSide = boatSide::left; 
    this->rightSide = new int[stateSize];
    for (int i = 0; i < stateSize; i++)
    {
        this->rightSide[i] = right[i];
    }
    this->previousState = nullptr;
}

State::State(int *right, int stateSize, boatSide newBoatSide)
{
    this->stateSize = stateSize;
    this->currentBoatSide = newBoatSide;
    this->rightSide = new int[stateSize];
    for (int i = 0; i < stateSize; i++)
    {
        this->rightSide[i] = right[i];
    }
    this->previousState = nullptr;
}

State *State::copy()
{
    State *copyState = new State(this->rightSide, this->stateSize, this->currentBoatSide);
    return copyState;
}

void State::swapBoatSide()
{
    if (this->currentBoatSide == boatSide::left)
        this->currentBoatSide = boatSide::right;
    else if (this->currentBoatSide == boatSide::right)
        this->currentBoatSide = boatSide::left;
}

State *State::boatMove(int movingArray[], int arrLength)
{
    State *newState = this->copy();
    for (int i = 0; i < arrLength; i++)
    {
        int movingIndex = movingArray[i];
        newState->rightSide[movingIndex] = !this->rightSide[movingIndex];
    }
    newState->swapBoatSide();
    return newState;
}
