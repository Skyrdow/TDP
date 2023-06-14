#include <string>
#include <vector>
#include <cmath>

#include "Node_Operation.h"
#include "Node_Number.h"
#include "Node_Variable.h"
#include "loadFile.h"

using namespace std;

/// Clase Abstract Syntax Tree
class AST
{
private:
    int operate(char operation, int l, int r);
    // Operaciones de casteo rápido, no implementables en los objetos nodo
    char get_operation(Node *node);
    int get_value(Node *node);
    char get_name(Node *node);
    
    void get_sum_elements(Node *node, vector<Node *> &elems);
    Node *simplify_sum(Node *node);
    Node *simplify(Node *node);
    Node *operateNode(Node_Operation *op);
    Node *replace_var(Node *node, vector<char> var_names, vector<int> var_values);
    Node* recursive_replace(Node* node, vector<char> var_names, vector<int> var_values);
    Node *derive_sumsub(Node_Operation *op_node, char derive_var);
    Node *derive_mult(Node_Operation *op_node, char derive_var);
    Node *derive_pow(Node_Operation *op_node, char derive_var);
    Node *derive_operation(Node *node, char derive_var);
public:
    Node *derive(Node *node, char derive_var);
    void print_linear(Node *node);
    void printAST(Node* p);
    Node* evaluate(Node* node);
    Node* evaluate(Node* node, vector<char> var_names, vector<int> var_values);
    Node* eval(Node* node);
    Node *sum_tree(Node * node);
    AST(/* args */);
    ~AST();
};