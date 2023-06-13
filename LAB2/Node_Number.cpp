#include "Node_Number.h"

/// @brief Constructor
/// @param value Número entero almacenado
Node_Number::Node_Number(int value) {
    this->value = value;
    type = NUMBER;
}

Node_Number::~Node_Number() {
}

/// @brief Imprime por consola el valor almacenado
void Node_Number::print() {
    std::cout << value;
    //std::cout << "|" << this;
}