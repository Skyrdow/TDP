#include "Node_Variable.h"

Node_Variable::Node_Variable(char name) {
    this->name = name;
    type = VARIABLE;
    parent = nullptr;
    visited = false;
}

Node_Variable::~Node_Variable() {
}

void Node_Variable::print() {
    std::cout << name << std::endl;
}