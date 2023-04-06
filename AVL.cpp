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
    Node* temp = node->right;
    if (temp == nullptr) {
        return node;
    }
    node->right = temp->left;
    temp->left = node;

    node->height = 1 + max(height(node->left), height(node->right));
    temp->height = 1 + max(height(temp->left), height(temp->right));

    return temp;
}

// Rotación simple a la derecha
Node* AVL::rotateRight(Node* node) {
    Node* temp = node->left;
    if (temp == nullptr) {
        return node;
    }
    node->left = temp->right;
    temp->right = node;

    node->height = 1 + max(height(node->left), height(node->right));
    temp->height = 1 + max(height(temp->left), height(temp->right));

    return temp;
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
    rootLeft = nullptr;
    rootRight = nullptr;
}
// Insertar un valor en el árbol AVL
void AVL::insert(State *value) {
    if (value->currentBoatSide == State::boatSide::left)
    {
        this->rootLeft = insertNode(this->rootLeft, value);
    }
    if (value->currentBoatSide == State::boatSide::right)
    {
        this->rootRight = insertNode(this->rootRight, value);
    }
    
}

// Eliminar un valor del árbol AVL
void AVL::remove(State *value) {
    if (value->currentBoatSide == State::boatSide::left)
    {
        this->rootLeft = deleteNode(this->rootLeft, value->rightSide);
    }
    if (value->currentBoatSide == State::boatSide::right)
    {
        this->rootRight = deleteNode(this->rootRight, value->rightSide);
    }
}

// Buscar un valor en el árbol AVL
bool AVL::_search(int value, bool left) {
    Node *current;
    if (left)
        current = this->rootLeft;
    else
        current = this->rootRight;

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
bool AVL::search(State *value) {
    if (value->currentBoatSide == State::boatSide::left)
        return _search(value->rightSide, 1);
    else if (value->currentBoatSide == State::boatSide::right)
        return _search(value->rightSide, 0);
    return false;
}

State *AVL::pop(State::boatSide boatSide)
{
    if (boatSide == State::boatSide::left)
    {
        State *res = pop_(this->rootLeft);
        if (res == nullptr)
            return pop_(this->rootRight);
        return res;
    }
    if (boatSide == State::boatSide::right)
    {
        State *res = pop_(this->rootRight);
        if (res == nullptr)
            return pop_(this->rootLeft);
        return res;
    }
    return nullptr;
}
// Función principal para remover el nodo con el valor máximo del AVL
State *AVL::pop_(Node*& root) {
    if (root == nullptr)
        return nullptr;

    // Si el nodo actual es el máximo, lo eliminamos y devolvemos su valor
    if (root->right == nullptr) {
        State *value = root->value;
        Node* temp = root;
        root = root->left;
        delete temp;
        return value;
    }

    // De lo contrario, seguimos buscando el máximo en el subárbol derecho
    Node* parent = nullptr;
    Node* current = root;

    while (current->right != nullptr) {
        parent = current;
        current = current->right;
    }

    State *value = current->value;

    // Si el nodo a remover tiene un subárbol izquierdo, lo reemplazamos por este
    if (current->left != nullptr) {
        parent->right = current->left;
    } else {
        parent->right = nullptr;
    }

    // Balanceamos el árbol después de remover el nodo
    root = balance(root);

    // Liberamos la memoria del nodo removido
    delete current;

    return value;
}
// Función auxiliar para balancear el AVL después de remover un nodo
Node* AVL::balance(Node* root) {
    if (root == nullptr)
        return root;

    int bFactor = balanceFactor(root);

    // Rotación simple a la izquierda
    if (bFactor > 1 && balanceFactor(root->left) >= 0)
        return rotateRight(root);

    // Rotación doble a la izquierda
    if (bFactor > 1 && balanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Rotación simple a la derecha
    if (bFactor < -1 && balanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // Rotación doble a la derecha
    if (bFactor < -1 && balanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}
bool AVL::isEmpty()
{
    if (this->rootLeft == nullptr && this->rootRight == nullptr)
        return true;
    return false;
}

