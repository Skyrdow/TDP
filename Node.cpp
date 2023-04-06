#include "Node.h"

//! Autores:
//! Estructura AVL inicial: ChatGPT
//! Integración con el proyecto: Lucas Mesias

/// @brief Constructor de nodods
/// @param value Estado almacenado
Node::Node(State *value)
{
    this->value = value;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}

/// @brief Destructor del nodo y todos sus hijos
void Node::deleteAll()
{
    if (this->left != nullptr)
        this->left->deleteAll();
    if (this->right != nullptr)
        this->right->deleteAll();
    delete this->value;
    delete this;
}