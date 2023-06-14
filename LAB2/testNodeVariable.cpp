#include "Node_Variable.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    Node_Variable *node = new Node_Variable('b');
    Node_Variable *node1 = (Node_Variable *)node->clone();
    cout << node->equal(node1) << endl;
    cout << node->name << endl;
    cout << node->type << endl;
    cout << endl;

    node1->name = 'x';
    cout << node->name << endl;
    cout << node->equal(node1) << endl;
    cout << endl;

    cout << node->isNodeNumber() << endl;
    cout << node->isNodeOperation() << endl;
    cout << node->isNodeVariable() << endl;
    node->printAST(0);

    return 0;
}
