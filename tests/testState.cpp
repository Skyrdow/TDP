#include "../State.h"
#include <iostream>

int main()
{
    // Creamos un State con todos los objetos a la izquierda del río
    State *s1 = new State(0b00000000, 0b11111111);
    std::cout << "S1:" << std::endl;
    s1->print();
    std::cout << std::endl;
    
    // Movemos el item en posición 2 y 3
    State *s2 = s1->boatMove(0b00000110);
    std::cout << "S2:" << std::endl;
    s2->print();
    std::cout << std::endl;
    
    // Movemos de vuelta el item 2
    State *s3 = s2->boatMove(0b00000010);
    std::cout << "S3:" << std::endl;
    s3->print();
    std::cout << std::endl;

    
    // Hacer una copia del State
    State *sCopy = s1->copy();

    // Cambiar el valor del original
    s1->rightSide = 0b01010101;

    // Imprimir los valores de ambos
    std::cout << "Original: ";
    s1->print();
    std::cout << "Copia: ";
    sCopy->print();

    // Liberamos la memoria de los States creados con new
    delete sCopy;
    delete s1;
    delete s2;
    delete s3;
    
    return 0;
}
