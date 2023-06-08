#include "../Operation.h"
#include <iostream>

int main() {
    // Creamos un objeto Operation
    Operation op;
    op.rightSideCount = 5;
    op.result = 10;

    // Imprimimos los valores de los miembros del objeto
    std::cout << "rightSideCount: " << op.rightSideCount << std::endl;
    std::cout << "result: " << op.result << std::endl;

    // Destruimos el objeto
    // No se hace nada en el destructor de Operation
    return 0;
}
