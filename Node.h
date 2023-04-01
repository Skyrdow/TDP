#pragma once
#include "State.h"
class Node
{
private:
public:
    State *key_;
    int height_;

    Node* left_node_;
    Node* right_node_;
    Node(State *key, Node* left_node=nullptr, Node* right_node=nullptr);
    ~Node();
};
