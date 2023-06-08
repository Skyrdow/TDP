#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <stack>
#include <vector>
#include <cmath>


#include "Node_Operation.h"
#include "Node_Number.h"
#include "Node_Variable.h"
#include "loadFile.h"

using namespace std;


// Solo cuando ambos operandos son numeros
int operate(char operation, int l, int r)
{
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

Node *simplify_basic(Node *node)
{
	// No se puede hacer nada
	if (!isNodeOperation(node))
		return node;
	Node_Operation *op_node = (Node_Operation *)node;
	Node *left = op_node->left;
	Node *right = op_node->right;
	switch(op_node->operation)
	{
		case '-':
			// a - a = 0
			if (left->type == NUMBER && left->type == NUMBER)
				if (((Node_Number *)right)->value == ((Node_Number *)left)->value)
					return new Node_Number(0);
			if (left->type == VARIABLE && left->type == VARIABLE)
				if (((Node_Variable *)right)->name == ((Node_Variable *)left)->name)
					return new Node_Number(0);
		case '+':
			// a + 0 = a || a - 0 = a
			if (left->type == NUMBER)
				if (((Node_Number *)left)->value == 0)
					return right;
			if (right->type == NUMBER)
				if (((Node_Number *)right)->value == 0)
					return left;
			return node;
		case '*':
			// a * 0 = 0 || a * 1 = a
			if (left->type == NUMBER)
			{
				if (((Node_Number *)left)->value == 0)
					return new Node_Number(0);
				if (((Node_Number *)left)->value == 1)
					return right;
			}
			if (right->type == NUMBER)
				if (((Node_Number *)right)->value == 0)
					return new Node_Number(0);
				if (((Node_Number *)right)->value == 1)
					return left;
			return node;
		case '^':
			// 0 ^ a = 0
			if (left->type == NUMBER)
				if (((Node_Number *)left)->value == 0)
					return new Node_Number(0);
			// a ^ 1 = a || a ^ 0 = 1
			if (right->type == NUMBER)
				if (((Node_Number *)right)->value == 0)
					return new Node_Number(1);
				if (((Node_Number *)right)->value == 1)
					return left;
			return node;
		default:
			cout << "Error" << endl;
			exit(1);
	}
}

Node *operateNode(Node_Operation *op)
{
	Node_Number *l_number = ((Node_Number*)op->left);
	Node_Number *r_number = ((Node_Number*)op->right);
	int operation_result = operate(op->operation, l_number->value, r_number->value);
	Node_Number* num = new Node_Number(operation_result);
	// actualizando el link al padre
	delete op;  //----> OJO con esto

	cout << "VALOR OPERACION: " << num->value << endl;
	return num;
}


Node* eval(Node* node, vector<char> var_names, vector<int> var_values)
{
	if (node->type == VARIABLE)
	{
		char var_name = ((Node_Variable *)node)->name;
		for (int i = 0; i < var_names.size(); i++)
		{
			if (var_name == var_names[i])
				return new Node_Number(var_values[i]);
		}
		return node;
	}
	if (isNodeOperation(node))
	{
		// evaluamos POSTORDER
		Node_Operation *op = (Node_Operation *)node;
		op->left = eval(op->left, var_names, var_values);
		op->right = eval(op->right, var_names, var_values);
		op->left = simplify_basic(op->left);
		op->right = simplify_basic(op->right);

		if (op->left->type == NUMBER && op->right->type == NUMBER)
			return operateNode(op);
		return op;
	} 
	if (node->type == NUMBER)
		return node;
	cout << "Error: se encontro algo distinto a operador o numero o variable" << endl;
	exit(1);
}

// solo evalua num op num y modifica el arbol!!!
Node* eval(Node* node)
{
	if (node->type == OPERATOR) 
	{
		// evaluamos POSTORDER
		Node_Operation *op = (Node_Operation *)node;
		op->left = eval(op->left);
		op->right = eval(op->right);
		op->left = simplify_basic(op->left);
		op->right = simplify_basic(op->right);

		if (op->left->type == NUMBER && op->right->type == NUMBER)
			return operateNode(op);
		return op;
	} 
	else if (node->type == VARIABLE || node->type == NUMBER)
		return node;
	cout << "Error: se encontro algo distinto a operador o numero o variable" << endl;
	exit(1);
}

Node *clone(Node *old)
{
	if (old->type == OPERATOR)
	{
		Node_Operation *old_op = (Node_Operation *) old;
		return new Node_Operation(old_op->operation,
									clone(old_op->left),
									clone(old_op->right));
	}
	if (old->type == NUMBER)
	{
		Node_Number *old_num = (Node_Number *) old;
		return new Node_Number(old_num->value);
	}
	if (old->type == VARIABLE)
	{
		Node_Variable *old_var = (Node_Variable *) old;
		return new Node_Variable(old_var->name);
	}
	cout<<"BIG PROBLEM"<< endl;
	exit(1);
}


Node *derive(Node *node, char derive_var);

Node *derive_sumsub(Node_Operation *op_node, char derive_var)
{
	op_node->left = derive(op_node->left, derive_var);
	op_node->right = derive(op_node->right, derive_var);
	return op_node;
}

Node *derive_mult(Node_Operation *op_node, char derive_var)
{
	// reusar el nodo original
	Node_Operation *right_multiplication = new Node_Operation('*');
	right_multiplication->left = op_node->left;
	right_multiplication->right = derive(clone(op_node->right), derive_var);

	Node_Operation *left_multiplication = op_node;
	left_multiplication->left = derive(clone(op_node->left), derive_var);
	left_multiplication->right = op_node->right;

	return new Node_Operation('+', left_multiplication, right_multiplication);
}

Node *derive_pow(Node_Operation *op_node, char derive_var)
{
	if (op_node->right <= 0)
	{
		cout << "Potencia negativa" << endl;
		exit(1);
	}
	// op_node->left = op_node->left; comentado, se mantiene
	Node *old_right_node = op_node->right;

	int right_value = ((Node_Number *)op_node->right)->value;
	op_node->right = new Node_Number(right_value - 1);

	Node *left_derivative = derive(clone(op_node->left), derive_var);
	Node_Operation *right_mult = new Node_Operation('*', op_node, left_derivative);
	return new Node_Operation('*', old_right_node, right_mult);
}

Node *derive_operation(Node_Operation *op_node, char derive_var)
{
	switch (op_node->operation)
	{
		case '+':
		case '-':
			return derive_sumsub(op_node, derive_var);
		case '*':
			return derive_mult(op_node, derive_var);
		case '^':
			return derive_pow(op_node, derive_var);
		default:
			cout << "Error" << endl;
			exit(1);
	}
}


Node *derive(Node *node, char derive_var)
{
	if (node->type != OPERATOR)
	{
		if (node->type == VARIABLE)
		{
			char var_name = ((Node_Variable *)node)->name;
			delete node;
			if (var_name == derive_var)
				return new Node_Number(1);
			return new Node_Number(0); // node_var->name != derive_var
		}
		if (node->type == NUMBER)
		{
			((Node_Number *)node)->value = 0;
			return node;
		}
	} // node->type == OPERATOR
	return derive_operation((Node_Operation *) node, derive_var);
}


void print(Node *node)
{
	cout << " ";
	if (node->type == OPERATOR)
	{
		Node_Operation *node_op = (Node_Operation *)node;
		node_op->print();
		print(node_op->left);
		print(node_op->right);
	}
	else
		node->print();
}

void printAST(Node* p, int indent=0)
{
    if (p == NULL) return;

	if (p->type == OPERATOR)
	{
		Node_Operation *op = (Node_Operation *) p;
		if(op->left) 
			printAST(op->left, indent+4);
		if (indent)
			std::cout << std::setw(indent) << ' ';
		p->print();
		std::cout << std::endl;
		if(op->right)
			printAST(op->right, indent+4);
	} 
	else
	{
		if (indent)
			std::cout << std::setw(indent) << ' ';
		p->print();
		std::cout << std::endl;
	}
}

int main() {

	const char* filename = "expr1.txt";
	char* mutableFilename = const_cast<char*>(filename);
	loadFile *lf = new loadFile(mutableFilename);
	Node *root = lf->readfile();
	

	printAST(root);
	cout << "Evaluacion: " << endl;
	// vector<char> vars = {'x', 'y'};
	// vector<int> vals = {1, 2};
	// root = derive(root, 'x');
	// printAST(root);
	root = eval(root);
	printAST(root);
	return 0;
}
