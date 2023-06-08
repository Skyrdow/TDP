#pragma once
#include "Node.h"
#include "AVL.h"
#include <iostream>
// Clase AVL
class AVL {
private:
    // Arbol de estados con el bote a la izquierda
    Node* rootLeft;
    // Arbol de estados con el bote a la derecha
    Node* rootRight;
    // Obtener la altura de un nodo
    int height(Node* node);
    // Obtener el factor de equilibrio de un nodo
    int balanceFactor(Node* node);
    // Rotación simple a la izquierda
    Node* rotateLeft(Node* node);
    // Rotación simple a la derecha
    Node* rotateRight(Node* node);
    // Rotación doble a la izquierda
    Node* rotateLeftRight(Node* node);
    // Rotación doble a la derecha
    Node* rotateRightLeft(Node* node);
    // Insertar un nodo en el árbol AVL
    Node* insertNode(Node* node, State *value);
    // Obtener el nodo con el valor mínimo en un subárbol
    Node* getMinNode(Node* node);
    // Obtener el nodo con el valor máximo en un subárbol
    Node* getMaxNode(Node* node);
    // Eliminar un nodo en el árbol AVL
    Node* deleteNode(Node* node, int value);
public:
    // Constructor
    AVL();
    // Destructor
    ~AVL();

    // Imprime el árbol en inorder
    void printInorder();
    void printInorder(Node* node);
    // Insertar un valor en el árbol AVL
    void insert(State *value);
    // Eliminar un valor del árbol AVL
    void remove(State *value);
    // Buscar un estado en su árbol correspondiente
    bool search(State *value);
    // Buscar un valor en uno de los árboles AVL
    bool _search(int value, bool left);
    // Revisa si el árbol está vacío
    bool isEmpty();
    // Obtener el nodo máximo y eliminarlo del árbol
    State *pop(State::boatSide boatSide);
    // Remover el nodo con el valor máximo del AVL
    State *pop_(Node*& node);
    // Función auxiliar para balancear el AVL después de remover un nodo
    Node *balance(Node *root);
};


