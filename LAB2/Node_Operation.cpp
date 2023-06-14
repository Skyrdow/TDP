#include "Node_Operation.h"

/// @brief Constructor con nodos hijos
/// @param operation Char operación [ +, -, *, ^ ]
/// @param left Nodo izquierdo a operar
/// @param right Nodo derecho a operar
Node_Operation::Node_Operation(char operation, Node *left, Node *right) {
    this->operation = operation;
    this->left = left;
    this->right = right;
    type = OPERATOR;
}

/// @brief Constructor sin nodos hijos, se dejan como nullptr para ser asignados luego
/// @param operation Char operación [ +, -, *, ^ ]
Node_Operation::Node_Operation(char operation) {
    this->operation = operation;
    left = nullptr;
    right = nullptr;
    type = OPERATOR;
}

/// @brief Destructor, destruye también sus nodos hijos
Node_Operation::~Node_Operation() {
    if (left !=nullptr) {
        delete left;
    }
    
    if (right != nullptr) { 
        delete right;
    }
}

/// @brief Imprime por consola la operación almacenada, sin los hijos
void Node_Operation::print() {
    std::cout << operation;
}
