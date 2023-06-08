#include "Node_Operation.h"

Node_Operation::Node_Operation(char operation, Node *left, Node *right) {
    this->operation = operation;
    this->left = left;
    this->right = right;
    type = OPERATOR;
}

Node_Operation::Node_Operation(char operation) {
    this->operation = operation;
    left = nullptr;
    right = nullptr;
    type = OPERATOR;
}

Node_Operation::~Node_Operation() {
    if (left !=nullptr) {
        delete left;
    }
    
    if (right != nullptr) { 
        delete right;
    }
}

void Node_Operation::print() {
    std::cout << operation;
    //std::cout << "|" << this;
}
