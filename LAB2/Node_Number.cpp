#include "Node_Number.h"

Node_Number::Node_Number(int value) {
    this->value = value;
    type = NUMBER;
}

Node_Number::~Node_Number() {
}

void Node_Number::print() {
    std::cout << value;
    //std::cout << "|" << this;
}