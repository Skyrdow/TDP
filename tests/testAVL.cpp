#include "../AVL.h"
#include <iostream>

using namespace std;


// Ejemplo de uso
int main()
{
    AVL *tree = new AVL();
    tree->insert(new State(10));
    tree->insert(new State(20));
    tree->insert(new State(30));
    tree->insert(new State(40));
    tree->insert(new State(50));
    tree->insert(new State(25));
    cout << "Árbol AVL en orden ascendente: "<<
    tree->search(10);
    tree->remove(30);
    cout << "Árbol AVL en orden ascendente después de eliminar 30: ";
    return 0;
}