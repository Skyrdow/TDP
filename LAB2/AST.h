#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>

#include "Node_Operation.h"
#include "Node_Number.h"
#include "Node_Variable.h"
#include "loadFile.h"

using namespace std;

class AST
{
private:
    /* data */
public:
    AST(/* args */);
    ~AST();
    int operate(char operation, int l, int r);
    bool isNodeOperation(Node *node);
    bool isNodeNumber(Node *node);
    bool isNodeVariable(Node *node);
    char get_operation(Node *node);
    int get_value(Node *node);
    char get_name(Node *node);
    int get_pow(Node *node);
    bool equal(Node *node_1, Node *node_2);
    char get_var(Node *node);
    Node *simplify_var_pow(Node *node);
    Node *expand(Node *node);
    Node *simplify(Node * node);
    void get_sum_elements(Node *node, vector<Node *> &elems);
    Node *simplify_basic(Node *node);
    Node *operateNode(Node_Operation *op);
    Node *replace_var(Node *node, vector<char> var_names, vector<int> var_values);
    Node* recursive_replace(Node* node, vector<char> var_names, vector<int> var_values);
    Node* eval(Node* node);
    Node* eval(Node* node, vector<char> var_names, vector<int> var_values);
    Node *clone(Node *old);
    Node *derive_sumsub(Node_Operation *op_node, char derive_var);
    Node *derive_mult(Node_Operation *op_node, char derive_var);
    Node *derive_pow(Node_Operation *op_node, char derive_var);
    Node *derive_operation(Node_Operation *op_node, char derive_var);
    Node *derive(Node *node, char derive_var);
    void print(Node *node);
    void printAST(Node* p, int indent=0);
};