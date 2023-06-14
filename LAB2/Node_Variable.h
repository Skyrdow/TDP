#pragma once
#include "Node.h"

/// @brief Nodo de tipo variable, almacena un char
class Node_Variable : public Node 
{
public:
    Node_Variable(char name);
    ~Node_Variable();
    char name;
    void print();
    Node *clone();
    void printAST(int indent);
    bool equal(Node *node);
};