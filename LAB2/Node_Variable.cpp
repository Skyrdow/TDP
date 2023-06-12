#include "Node_Variable.h"

Node_Variable::Node_Variable(char name) {
    this->name = name;
    this->pow = 1;
    type = VARIABLE;
}
Node_Variable::Node_Variable(char name, int pow) {
    this->name = name;
    this->pow = pow;
    type = VARIABLE;
}

Node_Variable::~Node_Variable() {
}

void Node_Variable::print() {
    std::cout << name;
    //std::cout << "|" << this;
}