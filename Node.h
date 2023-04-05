#pragma once
#include "State.h"
// Nodo AVL
class Node {
public:
    State *value;
    int height;
    Node* left;
    Node* right;

    Node(State *value);
};