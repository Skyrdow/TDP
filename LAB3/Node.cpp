#include "Node.h"

Node::Node(Simplex *simplex, float lower)
{
    this->simplex = simplex;
    this->upper = simplex->getSolution()[0];
    this->lower = lower;
}

Node::~Node()
{
    delete(simplex);
}
