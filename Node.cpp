#include "Node.h"

Node::Node(State *value)
{
    this->value = value;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}