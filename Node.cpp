#include "Node.h"

Node::Node(State *value)
{
    this->boatLeft = 0;
    this->boatRight = 0;
    this->value = value;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}