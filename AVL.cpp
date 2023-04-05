#include "Node.h"
#include "AVL.h"
#include <iostream>
using namespace std;

// Obtener la altura de un nodo
int AVL::height(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return node->height;
    }
}

// Obtener el factor de equilibrio de un nodo
int AVL::balanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return height(node->left) - height(node->right);
    }
}

// Rotación simple a la izquierda
Node* AVL::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    node->height = 1 + max(height(node->left), height(node->right));
    newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

    return newRoot;
}

// Rotación simple a la derecha
Node* AVL::rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    node->height = 1 + max(height(node->left), height(node->right));
    newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

    return newRoot;
}

// Rotación doble a la izquierda
Node* AVL::rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

// Rotación doble a la derecha
Node* AVL::rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// Insertar un nodo en el árbol AVL
Node* AVL::insertNode(Node* node, State *value) {
    if (node == nullptr) {
        return new Node(value);
    } else if (value->rightSide < node->value->rightSide) {
        node->left = insertNode(node->left, value);
    } else if (value->rightSide > node->value->rightSide) {
        node->right = insertNode(node->right, value);
    } else {
        return node; // No se permiten valores duplicados
    }

    // Actualizar la altura del nodo
    node->height = 1 + max(height(node->left), height(node->right));

    // Verificar el balance del árbol
    int bf = balanceFactor(node);
    if (bf > 1 && value->rightSide < node->left->value->rightSide) { // Rotación simple a la derecha
        return rotateRight(node);
    } else if (bf > 1 && value->rightSide > node->left->value->rightSide) { // Rotación doble a la derecha
        return rotateLeftRight(node);
    } else if (bf < -1 && value->rightSide > node->right->value->rightSide) { // Rotación simple a la izquierda
        return rotateLeft(node);
    } else if (bf < -1 && value->rightSide < node->right->value->rightSide) { // Rotación doble a la izquierda
        return rotateRightLeft(node);
    }
return node;
}

// Obtener el nodo con el valor mínimo en un subárbol
Node* AVL::getMinNode(Node* node)
{
    Node* current = node;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}
// Obtener el nodo con el valor máximo en un subárbol
Node* AVL::getMaxNode(Node* node)
{
    Node* current = node;
    while (current->right != nullptr)
    {
        current = current->right;
    }
    return current;
}

// Eliminar un nodo en el árbol AVL
Node* AVL::deleteNode(Node* node, int value)
{
    if (node == nullptr)
    {
        return node;
    } 
    else if (value < node->value->rightSide)
    {
        node->left = deleteNode(node->left, value);
    } 
    else if (value > node->value->rightSide)
    {
        node->right = deleteNode(node->right, value);
    } 
    else
    {
        if (node->left == nullptr || node->right == nullptr)
        { // Caso 1: el nodo tiene 0 o 1 hijo
            Node* temp = node->left ? node->left : node->right;
            if (temp == nullptr) { // Caso 1a: el nodo no tiene hijos
                temp = node;
                node = nullptr;
            } else { // Caso 1b: el nodo tiene 1 hijo
                *node = *temp;
            }
            delete temp;
        } 
        else
        { // Caso 2: el nodo tiene 2 hijos
            Node* temp = getMinNode(node->right);
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->value->rightSide);
        }
    }

    // Si el árbol está vacío después de eliminar el nodo, retornar nullptr
    if (node == nullptr)
    {
        return node;
    }

    // Actualizar la altura del nodo
    node->height = 1 + max(height(node->left), height(node->right));

    // Verificar el balance del árbol
    int bf = balanceFactor(node);
    if (bf > 1 && balanceFactor(node->left) >= 0) { // Rotación simple a la derecha
        return rotateRight(node);
    } else if (bf > 1 && balanceFactor(node->left) < 0) { // Rotación doble a la derecha
        return rotateLeftRight(node);
    } else if (bf < -1 && balanceFactor(node->right) <= 0) { // Rotación simple a la izquierda
        return rotateLeft(node);
    } else if (bf < -1 && balanceFactor(node->right) > 0) { // Rotación doble a la izquierda
        return rotateRightLeft(node);
    }

    return node;
}

AVL::AVL()
{
root = nullptr;
}
// Insertar un valor en el árbol AVL
void AVL::insert(State *value) {
    this->root = insertNode(root, value);
}

// Eliminar un valor del árbol AVL
void AVL::remove(int value) {
    this->root = deleteNode(this->root, value);
}

// Buscar un valor en el árbol AVL
bool AVL::search(int value) {
    Node* current = root;
    while (current != nullptr) {
        if (current->value->rightSide == value) {
            return true;
        } else if (value < current->value->rightSide) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

State *AVL::pop()
{
    State *max = getMaxNode(this->root)->value;
    this->remove(max->rightSide);
    return max;
}
bool AVL::isEmpty()
{
    if (this->root == nullptr)
        return true;
    return false;
}

