#include<math.h>
#include "State.h"
#include <iostream>
#include <bitset>

State::State(int stateSize)
{
    this->stateSize = stateSize;
    this->currentBoatSide = boatSide::left;
    this->rightSide = 0; // [0, 0, 0, ..., 0]
    this->previousState = nullptr;
}

State::State(int right, int stateSize)
{
    this->stateSize = stateSize;
    this->currentBoatSide = boatSide::left; 
    this->rightSide = right;
    this->previousState = nullptr;
}

State::State(int right, int stateSize, boatSide newBoatSide)
{
    this->stateSize = stateSize;
    this->currentBoatSide = newBoatSide;
    this->rightSide = right;
    this->previousState = nullptr;
}

void State::print()
{
    std::bitset<sizeof(int)*8> A = this->rightSide;//A will hold the binary representation of N 
    for(int i=0; i<sizeof(int)*8; i++)
    {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

State *State::copy()
{
    return new State(
        this->rightSide, 
        this->stateSize, 
        this->currentBoatSide);
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
    int movingItem; // potencia de 2 a mover
    int movingDirection; // R->L (-), L->R (+)
    for (int i = 0; i < arrLength; i++)
    {
        movingItem = 1 << movingArray[i] - 1;
        movingDirection = pow(-1, static_cast<int>(this->currentBoatSide)); // enum boatSide: L=0, R=1
        newState->rightSide = newState->rightSide + (movingItem * movingDirection);
    }
    newState->swapBoatSide();
    return newState;
}

