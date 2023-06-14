#include "Node.h"

/// @brief Constructor de nodo sin tipo, usado para encontrar errores
Node::Node() {
    type = INVALID;
}

Node::~Node() {
}

/// @brief Función virtual, versión base usada para encontrar errores
void Node::print() {
    std::cout << "Invalid Node" << std::endl;
	exit(5);
}

/// @brief Función virtual, versión base usada para encontrar errores
void Node::printAST(int indent) {
    std::cout << "Invalid Node" << std::endl;
	exit(5);
}

/// @brief Función virtual, versión base usada para encontrar errores
Node *Node::clone() {
    std::cout << "Invalid Node" << std::endl;
	exit(5);
}

/// @brief Función de pertenencia para el tipo de nodo
bool Node::isNodeOperation() {
	return type == OPERATOR;
}

/// @brief Función de pertenencia para el tipo de nodo
bool Node::isNodeNumber() {
	return type == NUMBER;
}

/// @brief Función de pertenencia para el tipo de nodo
bool Node::isNodeVariable() {
	return type == VARIABLE;
}

/// @brief Revisa si dos nodos son equivalentes, función virtual base usada para detectar errores
/// @param node_1 Nodo 1 a comparar
/// @param node_2 Nodo 2 a comparar
bool equal(Node *node)
{
	exit(6);
}
