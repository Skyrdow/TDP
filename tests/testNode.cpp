#include "../Node.h"
// #include "../State.h"
#include <iostream>

int main() {
    // Creamos un nodo raíz con un estado arbitrario
    State* rootState = new State(0, 7);
    Node* root = new Node(rootState);

    // Insertamos algunos nodos hijos en el árbol
    State* leftState = new State(1, 7);
    Node* left = new Node(leftState);
    root->left = left;

    State* rightState = new State(2, 7);
    Node* right = new Node(rightState);
    root->right = right;

    // Imprimimos los estados de los nodos
    std::cout << "Raiz: " << root->value->rightSide << std::endl;
    std::cout << "Izquierda: " << left->value->rightSide << std::endl;
    std::cout << "Derecha: " << right->value->rightSide << std::endl;

    // Destruimos el árbol
    root->deleteAll();

    return 0;
}
