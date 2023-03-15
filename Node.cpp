#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(int i[4], int d[4], Node *p)
{
    for (int j = 0; j < 4; j++)
    {
        izq[j] = i[j];
        der[j] = d[j];
    }
    previo = p;
}

void Node::print()
{
    for (int i = 0; i < 4; i++)
    {
        cout << "(" << izq[i] << "|" << der[i] << ")" << endl;
    }
}

void Node::printPrevious()
{
    this->print();
    Node *previousNode = previo;
    while (previousNode != nullptr)
    {
        previousNode->print();
        previousNode = previousNode->previo;
    }
}