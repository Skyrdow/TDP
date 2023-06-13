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
}


bool Node::isNodeOperation() {
	return node->type == OPERATOR;
}

bool Node::isNodeNumber() {
	return node->type == NUMBER;
}

bool Node::isNodeVariable() {
	return node->type == VARIABLE;
}

char Node::get_operation() {
	Node_Operation *node_op = (Node_Operation *)node;
	return node_op->operation;
}
int Node::get_value() {
	Node_Number *node_num = (Node_Number *)node;
	return node_num->value;
}
char Node::get_name() {
	Node_Variable *node_var = (Node_Variable *)node;
	return node_var->name;
}