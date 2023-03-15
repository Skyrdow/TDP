#include <iostream>
#include "Node.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int izq[4] = {1,2,3,4};
    int der[4] = {1,2,3,4};
    Node *n = new Node(izq, der, nullptr);
    return 0;
}
