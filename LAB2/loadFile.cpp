#include "loadFile.h"

loadFile::loadFile(const char *filename)
{
    this->filename = filename;
}

loadFile::~loadFile()
{
}

bool loadFile::isOperator(string token) {
    return token == "+" || token == "-" || token == "*" || token == "^";
}

bool loadFile::isNumber(string token) {
    return token[0] >= '0' && token[0] <= '9';
}

bool loadFile::isVariable(string token) {
    return (token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z');
}

Node *loadFile::readfile() {
    
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file " << endl;
        exit(2);
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
        //cout << line;
        ss << line;
        // si stream ss es "+ * - 1 2 3"
        // el primer get line obtiene "+" 
        while(getline(ss, token, ' ')) {
            //cout << token << endl;

            // 1) creamos el nodo dependiendo del token
            if (isOperator(token)) {
                //cout << "Es un operador" << token << endl;
                node = new Node_Operation(token[0]);

            } else if (isNumber(token)) {
                //cout << "Es un numero: " << token << endl;
                int valor = stoi(token);
                node = new Node_Number(valor);

            } else if (isVariable(token)) {
                //cout << "Es un identificador: " << token << endl;
                char name= token[0];
                node = new Node_Variable(name);
            }

            // 2) si es el primer nodo es la raiz
            if (root == nullptr) {
                root = node;
            }

            // 3) dependiendo del top del stack se agrega a la izquierda o derecha
            if (!pila.empty()) {
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
    }
    file.close();
    return root;
}
