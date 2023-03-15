#include "Node.h"

Node::Node(int i[4], int d[4], Node *p)
{
    for (int j = 0; j < 4; j++)
    {
        izq[j] = i[j];
        der[j] = d[j];
    }
    previo = p;
}
