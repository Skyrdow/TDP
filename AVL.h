#pragma once
#include "Node.h"
#include "AVL.h"
#include <iostream>
// Clase AVL
class AVL {
private:
    Node* rootLeft;
    Node* rootRight;
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
    ~AVL();
    void printInorder();
    void printInorder(Node* node);
    void insert(State *value);
    void remove(State *value);
    bool search(State *value);
    bool _search(int value, bool left);
    bool isEmpty();
    State *pop(State::boatSide boatSide);
    State *pop_(Node*& node);
    Node *balance(Node *root);
};


