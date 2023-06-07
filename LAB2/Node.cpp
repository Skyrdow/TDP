#include "Node.h"

Node::Node() {
    type = INVALID;
    parent = nullptr;
    visited = false;
}

Node::~Node() {
}

void Node::print() {
    std::cout << "Invalid Node" << std::endl;
}

