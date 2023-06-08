#include "Node_Variable.h"

Node_Variable::Node_Variable(char name) {
    this->name = name;
    type = VARIABLE;
}

Node_Variable::~Node_Variable() {
}

void Node_Variable::print() {
    std::cout << name;
    //std::cout << "|" << this;
}