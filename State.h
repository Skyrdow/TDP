#pragma once
#define MAX_BITSIZE 32
class State
{
private:
public:
    enum class boatSide {left = 0, right = 1};
    boatSide currentBoatSide;
    // Se usa la representación [0,0,1] = izq(1,2) y der(3)
    // y se transforma a entero para evitar recorrer matrices
    unsigned int rightSide; 
    int stateSize;
    State *previousState;

    State(int stateSize);
    State(int right, int stateSize);
    State(int right, int stateSize, boatSide newBoatSide);
    ~State();
    
    State *boatMove(int moving);
    State *copy();
    void print();
    void printPath();

    void swapBoatSide();
};
