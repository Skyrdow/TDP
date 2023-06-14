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
    std::cout << " ";
}


/// @brief Imprime el árbol de manera más visual
/// @param p Nodo a imprimir
/// @param indent Indentación
/// @author https://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
void Node_Variable::printAST(int indent)
{
    if (indent)
        std::cout << std::setw(indent) << ' ';
    print();
    std::cout << std::endl;
}

/// @brief Crea un nuevo nodo idéntico, copiando el contenido
/// @param old Nodo a copiar
/// @return Nodo clonado
Node *Node_Variable::clone()
{
    return new Node_Variable(name);
}

/// @brief Revisa si dos nodos son equivalentes, función virtual base usada para detectar errores
/// @param node Nodo a comparar
bool Node_Variable::equal(Node *node)
{
    if (!node->isNodeVariable())
        return false;
    
    Node_Variable *var_node = (Node_Variable *)node;
    return this->name == var_node->name;
}