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

using namespace std;

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


// solo evalua num op num y modifica el arbol!!!
Node* eval(Node* node) {
    
    if (isNodeOperation(node)) {
            // evaluamos POSTORDER
        Node_Operation *op = (Node_Operation *)node;
        Node * l = eval(op->left);
        Node * r = eval(op->right);

        
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
            //delete op;  //----> OJO con esto

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

Node *Clone(Node *old)
{
  if (isNodeOperation(old))
  {
    Node_Operation *old_op = (Node_Operation *)old;
    Node_Operation *new_node = new Node_Operation(old_op->operation);
    new_node->left = Clone(old_op->left);
    new_node->right = Clone(old_op->right);
    return new_node;
  }
  if (old->type == NUMBER)
  {
    Node_Number *old_num = (Node_Number *)old;
    return new Node_Number(old_num->value);
  }
  if (old->type == VARIABLE)
  {
    Node_Variable *old_var = (Node_Variable *)old;
    return new Node_Variable(old_var->name);
  }
  return nullptr;
}

void print(Node *node)
{
  if (isNodeOperation(node))
  {
    Node_Operation *node_op = (Node_Operation *)node;
    cout << node_op->operation << " ";
    print(node_op->left);
    print(node_op->right);
  }
  if (node->type == NUMBER)
  {
    Node_Number *node_num = (Node_Number *) node;
    cout << node_num->value<< " ";
  }
  if (node->type == VARIABLE)
  {
    cout << "asd"; 
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

    cout << "Evaluacion: " << endl;
    print(root);
    eval(root);
    
    Node *root2 = Clone(root);
    print(root2);
    delete(root);
print(root2);

    cout << eval(root2) << endl;
//    root = eval_recursive(root);
//
    file.close();
    return 0;
}
