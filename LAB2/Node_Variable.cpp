#include "Node_Variable.h"

/// @brief Constructor
/// @param name Nombre de la variable
Node_Variable::Node_Variable(char name) {
    this->name = name;
    type = VARIABLE;
}

Node_Variable::~Node_Variable() {
}

/// @brief Imprime por consola el nombre de la variable almacenada
void Node_Variable::print() {
    std::cout << name;
}