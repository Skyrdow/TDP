#include "Node.h"
#define NULL 0

Node::Node(){};
Node::~Node()
{
    if (this->left != NULL)
        delete(this->left);
    if (this->right != NULL)
        delete(this->right);
    delete(this->data);
}