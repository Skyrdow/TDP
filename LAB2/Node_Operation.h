#pragma once
#include "Node.h"

/// @brief Nodo de tipo operación, almacena un char que 
/// representa la operación y 2 nodos para operar
class Node_Operation : public Node {
public:
    Node_Operation(char operation, Node *left, Node *right);
    Node_Operation(char operation); // caso de no conocer hijos
    ~Node_Operation();
    Node *left;
    Node *right;
    char operation;
    void print();
    void printAST(int indent);
    Node *clone();
    bool equal(Node *node);
};
