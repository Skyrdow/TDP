#include "Node_Operation.h"

/// @brief Constructor con nodos hijos
/// @param operation Char operación [ +, -, *, ^ ]
/// @param left Nodo izquierdo a operar
/// @param right Nodo derecho a operar
Node_Operation::Node_Operation(char operation, Node *left, Node *right) {
    this->operation = operation;
    this->left = left;
    this->right = right;
    type = OPERATOR;
}

/// @brief Constructor sin nodos hijos, se dejan como nullptr para ser asignados luego
/// @param operation Char operación [ +, -, *, ^ ]
Node_Operation::Node_Operation(char operation) {
    this->operation = operation;
    left = nullptr;
    right = nullptr;
    type = OPERATOR;
}

/// @brief Destructor, destruye también sus nodos hijos
Node_Operation::~Node_Operation() {
    if (left !=nullptr) {
        delete left;
    }
    
    if (right != nullptr) { 
        delete right;
    }
}

/// @brief Imprime por consola la operación almacenada, sin los hijos
void Node_Operation::print() {
    std::cout << operation;
    std::cout << " ";
    this->left->print();
    this->right->print();
}

/// @brief Imprime el árbol de manera más visual
/// @param p Nodo a imprimir
/// @param indent Indentación
/// @author https://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
void Node_Operation::printAST(int indent)
{
    // No es necesario comprobar si los hijos son nulos
    left->printAST(indent+4);
    if (indent)
        std::cout << std::setw(indent) << ' ';
    std::cout << operation;
    std::cout << std::endl;
    right->printAST(indent+4);
}

/// @brief Crea un nuevo nodo idéntico, copiando el contenido
/// @param old Nodo a copiar
/// @return Nodo clonado
Node *Node_Operation::clone()
{
    return new Node_Operation(operation, 
                                left->clone(),
                                right->clone());
}

/// @brief Revisa si dos nodos son equivalentes, función virtual base usada para detectar errores
/// @param node Nodo a comparar
bool Node_Operation::equal(Node *node)
{
    if (!node->isNodeOperation())
        return false;

    Node_Operation *op_node = (Node_Operation *)node;
    // Revisar si es la misma operación
    if (this->operation != op_node->operation)
        return false;
    // Revisar si los nodos hijos son iguales
    if (this->left->equal(op_node->left) 
            && this->right->equal(op_node->right))
        return true;

    // Intercambiar hijos para operaciones conmutativas
    if (this->operation == '*' || this->operation == '+' )
        return this->left->equal(op_node->right) 
                    && this->right->equal(op_node->left);

    // No es la misma operación
    return false;
}
