#include "Node.h"

class Node_Operation : public Node {
public:
    Node_Operation(char operation, Node *left, Node *right);
    Node_Operation(char operation); // caso de no conocer hijos
    ~Node_Operation();
    Node *left;
    Node *right;
    Node *parent;
    char operation;
    void print();
    void postprint(Node *p);
};
