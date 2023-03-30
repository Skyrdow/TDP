#include "AVL.h"
#include <iostream>

using namespace std;

int test()
{

    AVL b;
    int c, x;
    do
    {

        State *a;
        cout << "\n1.Display levelorder on newline";
        cout << "\n2.Insert";
        cout << "\n3.Delete\n";
        cout << "\n0.Exit\n";
        cout << "\nChoice: ";

        cin >> c;

        switch (c)
        {
        case 1:
            b.levelorder_newline();
            // to print the tree in level order
            break;

        case 2:
            cout << "\nEnter no. ";
            cin >> x;
            a = new State(x, 10);
            b.root = b.insert(b.root, a);
            break;
        case 3:
            cout << "\nWhat to delete? ";
            cin >> x;
            b.root = b.deleteNode(b.root, x);
            break;
        case 4:
            cout << "\nWhat to search? ";
            cin >> x;
            cout << (b.search(b.root, x) ? "true" : "false");
            break;

        case 0:
            break;
        }

    } while (c != 0);
    return 0;
}