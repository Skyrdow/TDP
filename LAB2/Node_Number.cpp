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
    std::cout << " ";
}

/// @brief Imprime el árbol de manera más visual
/// @param p Nodo a imprimir
/// @param indent Indentación
/// @author https://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
void Node_Number::printAST(int indent)
{
    if (indent)
        std::cout << std::setw(indent) << ' ';
    print();
    std::cout << std::endl;
}

/// @brief Crea un nuevo nodo idéntico, copiando el contenido
/// @param old Nodo a copiar
/// @return Nodo clonado
Node *Node_Number::clone()
{
    return new Node_Number(value);
}

/// @brief Revisa si dos nodos son equivalentes, función virtual base usada para detectar errores
/// @param node Nodo a comparar
bool Node_Number::equal(Node *node)
{
    if (!node->isNodeNumber())
        return false;
    
    Node_Number *num_node = (Node_Number *)node;
    return this->value == num_node->value;
}
