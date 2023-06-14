#include "Node_Number.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    Node_Number *node = new Node_Number(3);
    Node_Number *node1 = (Node_Number *)node->clone();
    cout << node->equal(node1) << endl;
    cout << node->value << endl;
    cout << node->type << endl;
    cout << endl;

    node1->value = 2;
    cout << node->value << endl;
    cout << node->equal(node1) << endl;
    cout << endl;

    cout << node->isNodeNumber() << endl;
    cout << node->isNodeOperation() << endl;
    cout << node->isNodeVariable() << endl;
    node->printAST(0);

    return 0;
}
