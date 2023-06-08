#pragma once
class State
{
private:
public:
    enum class boatSide {left = 0, right = 1};
    // Indicador del lado en el que se encuentra el bote
    boatSide currentBoatSide;

    // Se usa la representación 1 = [0,0,1] = izq(1,2) y der(3)
    // y se transforma a entero para evitar recorrer matrices
    unsigned int rightSide; 
    // Se precalcula el valor final
    unsigned int finalStateValue; 
    // Estado del que proviene el actual
    State *previousState;

    // Constructor de State, distintas versiones aplican valores por defecto
    State(int right, unsigned int finalStateValue);
    State(int right, unsigned int finalStateValue, boatSide newBoatSide);
    // Mueve los elementos de lado
    State *boatMove(int moving);
    // Copia los valores del State
    State *copy();
    // Muestra por consola el State actual
    void print();
    // Función para imprimir en binario un número entero sin signo
    void print32Bits(unsigned int n);
    // Cambia el lado del bote
    void swapBoatSide();
};
