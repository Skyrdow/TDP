#include "Node.h"

class Node_Number : public Node {
    public:
        Node_Number(int value);
        ~Node_Number();
        int value;
        void print();
};

