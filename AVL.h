#pragma once
#include "Node.h"
#include "AVL.h"
#include <iostream>
// Clase AVL
class AVL {
private:
    Node* root;
    int height(Node* node);
    int balanceFactor(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* insertNode(Node* node, State *value);
    Node* getMinNode(Node* node);
    Node* getMaxNode(Node* node);
    Node* deleteNode(Node* node, int value);
public:
    AVL();
    void insert(State *value);
    void remove(int value);
    bool search(int value);
    bool isEmpty();
    State *pop();
};


