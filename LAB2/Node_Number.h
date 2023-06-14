#pragma once
#include "Node.h"

/// @brief Nodo de tipo número, almacena el valor como número entero
class Node_Number : public Node {
    public:
        Node_Number(int value);
        ~Node_Number();
        int value;
        void print();
};

