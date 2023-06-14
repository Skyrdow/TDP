#ifndef _NODE_H_
#define _NODE_H_

#pragma once
#include <iostream>
#include <iomanip>

// Clase básica para crear el resto de nodos desde esta defición
class Node {
// Definición de tipos de nodo
#define NUMBER 0
#define OPERATOR 1
#define VARIABLE 2
#define INVALID 3

public:
    Node();
    ~Node();
    int type;
    bool isNodeOperation();
    bool isNodeNumber();
    bool isNodeVariable();
    virtual void print() = 0;
    virtual void printAST(int indent) = 0;
    virtual Node *clone() = 0;
    virtual bool equal(Node *node) = 0;
};

#endif
