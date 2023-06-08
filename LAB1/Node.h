#pragma once
#include "State.h"
// Nodo AVL
class Node {
public:
    // Valor que almacena el nodo
    State *value;
    // Altura del nodo
    int height;
    // Nodo izquierdo
    Node* left;
    // Nodo derecho
    Node* right;

    // Constructor
    Node(State *value);
    // Destruye el nodo y sus hijos
    void deleteAll();
};