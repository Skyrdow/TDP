#include "State.h"
#include <iostream>
#include <bitset>

/// @brief Constructor de State, distintas versiones aplican valores por defecto
/// @param stateSize cantidad de objetos
State::State(int stateSize)
{
    this->stateSize = stateSize;
    this->currentBoatSide = boatSide::left;
    this->rightSide = 0; // [0, 0, 0, ..., 0]
    this->previousState = nullptr;
}
/// @brief Constructor de State, distintas versiones aplican valores por defecto
/// @param right numero entero sin signo que representa todos los objetos
/// @param stateSize tamaño del State
State::State(int right, int stateSize)
{
    this->stateSize = stateSize;
    this->currentBoatSide = boatSide::left; 
    this->rightSide = right;
    this->previousState = nullptr;
}

/// @brief Constructor de State, distintas versiones aplican valores por defecto
/// @param right numero entero sin signo que representa todos los objetos
/// @param stateSize tamaño del State
/// @param newBoatSide lado en el que se encuentra el bote
State::State(int right, int stateSize, boatSide newBoatSide)
{
    this->stateSize = stateSize;
    this->currentBoatSide = newBoatSide;
    this->rightSide = right;
    this->previousState = nullptr;
}

/// @brief Muestra por consola el State actual
void State::print()
{
    // A will hold the binary representation of N 
    std::bitset<MAX_BITSIZE> A = this->rightSide;
    std::cout << A << std::endl;
}

/// @brief Copia los valores del State
/// @return State nuevo con los mismos valores
State *State::copy()
{
    return new State(
        this->rightSide, 
        this->stateSize, 
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
State *State::boatMove(int movingArray[], int arrLength)
{
    State *newState = this->copy();
    int movingItem; // potencia de 2 a mover
    int movingDirection; // R->L (-), L->R (+)
    for (int i = 0; i < arrLength; i++)
    {
        movingItem = 1 << movingArray[i] - 1;
        movingDirection = static_cast<int>(this->currentBoatSide) ? -1 : 1; // enum boatSide: L=0, R=1
        newState->rightSide = newState->rightSide + (movingItem * movingDirection);
    }
    newState->swapBoatSide();
    return newState;
}

