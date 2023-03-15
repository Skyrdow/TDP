#include <iostream>
#include "Node.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int izq[4] = {1,2,3,4};
    int der[4] = {1,2,3,4};
    Node *n = new Node(izq, der, nullptr);
    Node *nodoNuevo = nullptr;

    for (int i = 0; i < 7; i++)
    {
        int izq1[4] = {1+i,2,3,4};
        int der1[4] = {1*i,2,3,4};
        Node *prevNode = nodoNuevo;
        nodoNuevo = new Node(izq1, der1, prevNode);
    }
    nodoNuevo->printPrevious();
    
    return 0;
}
