#include "Node_Operation.h"
#include "Node_Number.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    Node_Operation *node = new Node_Operation('+', new Node_Number(2), new Node_Number(3));
    Node_Operation *node1 = (Node_Operation *)node->clone();
    cout << node->equal(node1) << endl;
    cout << node->operation << endl;
    cout << node->type << endl;
    cout << endl;

    node1->operation = '*';
    cout << node->operation << endl;
    cout << node->equal(node1) << endl;
    cout << endl;

    cout << node->isNodeNumber() << endl;
    cout << node->isNodeOperation() << endl;
    cout << node->isNodeVariable() << endl;
    node->printAST(0);

    return 0;
}
