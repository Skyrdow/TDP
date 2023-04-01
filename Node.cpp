#include "Node.h"

Node::Node(State *key, Node* left_node, Node* right_node)
{
    key_= key;
    left_node_ = left_node;
    right_node_ = right_node;
    height_ = 0;
}
Node::~Node()
{

}