#pragma once
#include "Node.h"

class Node_Variable : public Node {
    public:
        Node_Variable(char name);
        ~Node_Variable();
        char name;
        void print();
};