#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <stack>
#include <cmath>

#include "Node_Operation.h"
#include "Node_Number.h"
#include "Node_Variable.h"



// sstream es un stream de caracteres
using namespace std;


bool isOperator(string token) {
    return token == "+" || token == "-" || token == "*" || token == "^";
}

bool isNumber(string token) {
    return token[0] >= '0' && token[0] <= '9';
}

bool isVariable(string token) {
    return (token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z');
}

bool isNodeOperation(Node *node) {
    return node->type == OPERATOR;
}


int eval_int(Node* node);
// Solo cuando ambos operandos son numeros
int operate(char operation, int l, int r) {
        switch(operation) {
            case '+': // OJO con los BREAK
                return l + r;
            case '-':
                return l - r;
            case '*':
                return l * r;
            case '^':
                return pow(l,r);
            default:
                cout << "Error" << endl;
                exit(1);
        }

}


// retorna un entero en forma recursiva y suponiendo no hay variables
int  eval_int(Node *node) {
    if (isNodeOperation(node)) {
        int l = eval_int(((Node_Operation*)node)->left);
        int r = eval_int(((Node_Operation*)node)->right);
        return operate(((Node_Operation*)node)->operation, l, r);
    } else if (node->type == NUMBER) {
        return ((Node_Number*)node)->value;
    } else {
        cout << "Error: se encontro algo distinto a operador o numero" << endl;
        exit(1);
    }
}

// solo evalua num op num y modifica el arbol!!!
Node* eval_recursive(Node* node) {
    
    if (isNodeOperation(node)) {
            // evaluamos POSTORDER
        Node_Operation *op = (Node_Operation *)node;
        Node * l = eval_recursive(op->left);
        Node * r = eval_recursive(op->right);

        
        if (l->type == NUMBER && r->type == NUMBER) {
            Node_Number* num = new Node_Number(operate(op->operation, 
                                                       ((Node_Number*)l)->value, 
                                                       ((Node_Number*)r)->value));
            // actualizando el link al padre
            num->parent = op->parent;
            Node_Operation *parent = (Node_Operation *)op->parent;
            // actualizando el izq o derecho del padre
            if (op->parent!=nullptr && parent->left==op) {
                parent->left = num;
            } else if (op->parent!=nullptr && parent->right==op) {
                parent->right = num;
            }
            delete op;  //----> OJO con esto

            cout << "VALOR OPERACION: " << num->value << endl;
            return num;
        } else {
            op->left = l;
            op->right = r;
            return op;
        }
    } else if (node->type == NUMBER) {
        return node;
    } else if (node->type == VARIABLE) {
        return node;
    } else {
        cout << "Error: se encontro algo distinto a operador o numero o variable" << endl;
        exit(1);
    }
}

Node* eval_iterative(Node* node) {
    stack<Node*> pila;
    pila.push(node);
    Node *current = node;
    while (!pila.empty()) {
        Node* top = pila.top();
        
        if (isNodeOperation(top)) {
            Node_Operation* op = (Node_Operation*)top;
            Node* l = op->left;
            Node* r = op->right; 

            if (l->type==NUMBER && r->type==NUMBER) { // ambos son numeros
               Node_Number* num = new Node_Number(operate(op->operation, 
                                                       ((Node_Number*)l)->value, 
                                                       ((Node_Number*)r)->value));
                // actualizando el link al padre
                num->parent = op->parent;
                Node_Operation *parent = (Node_Operation *)op->parent;
                // actualizando el izq o derecho del padre
                if (op->parent!=nullptr && parent->left==op) {
                    parent->left = num;
                } else if (op->parent!=nullptr && parent->right==op) {
                    parent->right = num;
                }
                current = num;
                pila.pop();

            } else if ((l->type != OPERATOR) && (r->type != OPERATOR)) { // ambos son numeros o variables
                pila.pop();
                op->visited = true;
                current = op;
            } else if ((l->type == OPERATOR) && (l->visited == true)) { // el izquierdo es operador y ya fue visitado
                pila.pop();
                op->visited = true;
                current = op;
            } else if ((r->type == OPERATOR) && (r->visited == true)) { // el derecho es operador y ya fue visitado
                pila.pop();
                op->visited = true;
                current = op;
            } else { // ambos son operadores y no han sido visitados
                pila.push(l);
                pila.push(r);
            }
        } else { // es un numero o variable
            pila.pop();
            current = top;
        }

    }
    return(current);
}

void postorder(Node * p, int indent=0)
{
    if(p != NULL && isNodeOperation(p)) {
        if(((Node_Operation *)p)->left) postorder(((Node_Operation *)p)->left, indent+4);
        if(((Node_Operation *)p)->right) postorder(((Node_Operation *)p)->right, indent+4);
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        p->print();
    }
}

int main() {
    
    ifstream file("expr1.txt");
    if (!file.is_open()) {
        cout << "Could not open file " << endl;
        return 1;
    }
    Node_Operation *op = nullptr; 
    Node_Number *num = nullptr;
    Node_Variable *var = nullptr;
    Node* node= nullptr;
    Node* root=nullptr;

    string line, token;
    stringstream ss;

    stack<Node_Operation*> pila;

    if (getline(file, line, '\n')) {
        cout << line << endl;
        ss << line;
        // si stream ss es "+ * - 1 2 3"
        // el primer get line obtiene "+" 
        while(getline(ss, token, ' ')) {
            cout << token << endl;

            // 1) creamos el nodo dependiendo del token
            if (isOperator(token)) {
                cout << "Es un operador" << token << endl;
                node = new Node_Operation(token[0]);
                if (!pila.empty()) { 
                    ((Node_Operation*)node)->parent = pila.top();
                } else {
                    ((Node_Operation*)node)->parent = nullptr;
                }

            } else if (isNumber(token)) {
                cout << "Es un numero: " << token << endl;
                int valor = stoi(token);
                node = new Node_Number(valor);

            } else if (isVariable(token)) {
                cout << "Es un identificador: " << token << endl;
                char name= token[0];
                node = new Node_Variable(name);
            }

            // 2) si es el primer nodo es la raiz
            if (root == nullptr) {
                root = node;
            }

            // 3) dependiendo del top del stack se agrega a la izquierda o derecha
            if (!pila.empty()) {
                // asignacion del padre
                node->parent = pila.top();    

                if (pila.top()->left == nullptr) {  
                    pila.top()->left = node;
                                } else 
                if (pila.top()->right == nullptr){
                        pila.top()->right = node;
                        pila.pop();
                } else {
                        cout << "Error" << endl;
                        exit(1);
                }
            }

            // 4) si es un operador se agrega a la pila
            if (node->type == OPERATOR) {
                    pila.push((Node_Operation*)node);
                
            }

        }
    } else {
        cout << "Could not read line" << endl;
        return 1;
    }

    root->print();

    cout << "Evaluacion: " << endl;
//    cout << eval_int(root) << endl;
//    root = eval_recursive(root);
//
    postorder(root);
    root = eval_iterative(root);    
    root->print();
    postorder(root);
    delete root;

    file.close();
    return 0;
}
