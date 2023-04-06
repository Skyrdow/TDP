#include "../AVL.h"
#include <iostream>

using namespace std;

 



// Ejemplo de uso
int main()
{
    AVL *tree = new AVL();
    tree->insert(new State(10, 31));
    tree->insert(new State(20, 31));
    tree->insert(new State(30, 31));
    tree->insert(new State(40, 31));
    tree->insert(new State(50, 31));
    tree->insert(new State(25, 31));
    cout << "Árbol AVL en inorder: " << endl;
    tree->printInorder();
    cout << endl;
    cout << "Buscar 10 en el árbol: " << tree->search(new State(10, 31)) << endl;
    tree->remove(new State(30, 31));
    cout << "Árbol AVL en orden ascendente después de eliminar 30: \n";
    tree->printInorder();
    cout << endl;
    return 0;
}