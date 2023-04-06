#include "State.h"
#include <iostream>
#include <bitset>

State::~State()
{

}

/// @brief Constructor de State, distintas versiones aplican valores por defecto
/// @param right numero entero sin signo que representa todos los objetos
/// @param stateSize tamaño del State
State::State(int right, unsigned int finalStateValue)
{
    this->finalStateValue = finalStateValue;
    this->currentBoatSide = boatSide::left; 
    this->rightSide = right;
    this->previousState = nullptr;
}

/// @brief Constructor de State, distintas versiones aplican valores por defecto
/// @param right numero entero sin signo que representa todos los objetos
/// @param stateSize tamaño del State
/// @param newBoatSide lado en el que se encuentra el bote
State::State(int right, unsigned int finalStateValue, boatSide newBoatSide)
{
    this->finalStateValue = finalStateValue;
    this->currentBoatSide = newBoatSide;
    this->rightSide = right;
    this->previousState = nullptr;
}

void State::printBits(unsigned int n) {
    char* p = (char*)&n;
    for (int i = 3; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            std::cout << ((*(p + i) >> j) & 1);
        }
    }
}

/// @brief Muestra por consola el State actual
void State::print()
{
    // A will hold the binary representation of N 
    if (this->previousState != nullptr)
        this->previousState->print();
    printBits(~this->rightSide & this->finalStateValue);
    std::cout << "|";
    printBits(this->rightSide);
    std::cout << std::endl;
}

/// @brief Copia los valores del State
/// @return State nuevo con los mismos valores
State *State::copy()
{
    return new State(
        this->rightSide, 
        this->finalStateValue,
        this->currentBoatSide);
}

/// @brief Cambia el lado del bote
void State::swapBoatSide()
{
    if (this->currentBoatSide == boatSide::left)
        this->currentBoatSide = boatSide::right;
    else if (this->currentBoatSide == boatSide::right)
        this->currentBoatSide = boatSide::left;
}

/// @brief Mueve los elementos de lado, sin preocuparse si el elemento se puede mover o si el State resultante será válido
/// @param movingArray arreglo con las posiciones de los objetos a mover
/// @param arrLength largo del arreglo
/// @return State nuevo con los elementos modificados
State *State::boatMove(int moving)
{
    State *newState = this->copy();
    unsigned int leftSide = ~this->rightSide & this->finalStateValue;
    unsigned int movedState;
    if (this->currentBoatSide == State::boatSide::right)
    {
        newState->rightSide = this->rightSide & ~moving;
    }
    if (this->currentBoatSide == State::boatSide::left)
    {
        newState->rightSide = ~(leftSide & ~moving) & this->finalStateValue;
    }
    newState->swapBoatSide();
    newState->previousState = this;
    return newState;
}

