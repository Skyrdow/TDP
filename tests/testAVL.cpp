#include "../AVL.h"
#include <iostream>

using namespace std;

int main()
{
    AVL *avltree = new AVL();

    avltree->insert(new State(1));
    avltree->insert(new State(2));
    avltree->insert(new State(3));
    avltree->insert(new State(4));
    avltree->insert(new State(5));
    avltree->insert(new State(6));
    avltree->insert(new State(7));

    cout << avltree->pop()->rightSide << endl;
    // cout << avltree->pop() << endl;
    // cout << avltree->pop() << endl;
    // cout << avltree->pop() << endl;
  
    return 0;
}