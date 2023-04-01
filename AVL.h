#pragma once
#include "Node.h"
#include <iostream>

using namespace std;
class AVL
{
private:
    Node* root_;
    Node* right_rotation(Node* p);
    Node* left_rotation(Node* p);
    Node* maximum_node_of_tree(Node* node);
    unsigned int sub_tree_height(Node* node);
    Node* insert_(State *key, Node* node);
    Node* pop_(unsigned int key, Node* node);

public:
    AVL();
    ~AVL();
    void insert(State *key);
    void deleteState(unsigned int key);
    State *pop();
    bool searchValue(unsigned int value);
    bool search(Node *n, unsigned int value);
    bool isEmpty();
};