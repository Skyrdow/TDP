#include "AST.h"

// Solo cuando ambos operandos son numeros
int AST::operate(char operation, int l, int r)
{
	switch(operation) {
		case '+': // OJO con los BREAK
			return l + r;
		case '-':
			return l - r;
		case '*':
			return l * r;
		case '^':
			if (r <= 0) // pow no admitida
				exit(2);
			return pow(l,r);
		default:
			cout << "Error" << endl;
			exit(1);
	}

}

bool AST::isNodeOperation(Node *node) {
	return node->type == OPERATOR;
}

bool AST::isNodeNumber(Node *node) {
	return node->type == NUMBER;
}

bool AST::isNodeVariable(Node *node) {
	return node->type == VARIABLE;
}

char AST::get_operation(Node *node) {
	Node_Operation *node_op = (Node_Operation *)node;
	return node_op->operation;
}
int AST::get_value(Node *node) {
	Node_Number *node_num = (Node_Number *)node;
	return node_num->value;
}
char AST::get_name(Node *node) {
	Node_Variable *node_var = (Node_Variable *)node;
	return node_var->name;
}

bool AST::equal(Node *node_1, Node *node_2)
{
	if (node_1->type != node_2->type)
		return false;
	if (isNodeOperation(node_1))
	{
		Node_Operation *op_node_1 = (Node_Operation *)node_1;
		Node_Operation *op_node_2 = (Node_Operation *)node_2;
		if (get_operation(node_1) != get_operation(node_2))
			return false;

		if (equal(op_node_1->left, op_node_2->left) 
			&& equal(op_node_1->right, op_node_2->right))
			return true;
		// operaciones conmutativas
		if (get_operation(node_1) == '*' || get_operation(node_1) == '+' )
			return equal(op_node_1->left, op_node_2->right) 
					&& equal(op_node_1->right, op_node_2->left);
		return false;
	}
	if (isNodeNumber(node_1))
		return get_value(node_1) == get_value(node_2);
	if (isNodeVariable(node_1))
		return (get_name(node_1) == get_name(node_2));
	exit(3);
}

char AST::get_var(Node *node)
{
	if (isNodeVariable(node))
		return get_name(node);
	if (isNodeNumber(node))
		return '\0';
	if (isNodeOperation(node))
	{
		Node_Operation *op_node = (Node_Operation *)node;
		char var_left = get_var(op_node->left);
		char var_right = get_var(op_node->right);
		if (var_left != '\0')
			return var_left;
		if (var_right != '\0')
			return var_right;
		return '\0';
	}
	exit(5);
}

Node *AST::sum_tree(Node * node)
{
	if (!isNodeOperation(node))
		return node;

	Node_Operation *op = (Node_Operation *)node;
	// revisar si es suma
	if (get_operation(op) == '+')
	{
		vector<Node *> elems;
		vector<Node *> elems_unicos; // elementos unicos
		get_sum_elements(op, elems);
		for (auto elem : elems)
		{
			bool is_unico = true;
			for (auto elem_unico : elems_unicos)
			{
				if (equal(elem, elem_unico))
					is_unico = false;
			}
			if (is_unico)
				elems_unicos.push_back(elem);
		}
		Node_Operation *sum_root = new Node_Operation('+', new Node_Number(0), new Node_Number(0));
		Node_Operation *sum_tail = sum_root;
		for (auto var_unica : elems_unicos) 
		{
			Node_Operation *sub_sum_root = new Node_Operation('+', new Node_Number(0), new Node_Number(0));
			Node_Operation *sub_sum_tail = sub_sum_root;
			for (int i = 0; i < elems.size(); i++)
			{
				if (equal(elems[i], var_unica))
				{
					delete sub_sum_tail->right;
					sub_sum_tail->right = new Node_Operation('+', elems[i], new Node_Number(0));
					sub_sum_tail = (Node_Operation *)sub_sum_tail->right;
				}
			}
			delete sum_tail->right;
			sum_tail->right = new Node_Operation('+', sub_sum_root, new Node_Number(0));
			sum_tail = (Node_Operation *)sum_tail->right;
		}
		return eval(sum_root);
	}
	return node;
}

void AST::get_sum_elements(Node *node, vector<Node *> &elems)
{
	if (!isNodeOperation(node))
		return elems.push_back(node);
	
	Node_Operation *op_node = (Node_Operation *)node;
	if (op_node->operation != '+')
		return elems.push_back(node);
	get_sum_elements(op_node->left, elems);
	get_sum_elements(op_node->right, elems);
}

Node *AST::simplify(Node *node)
{
	// No se puede hacer nada
	if (!isNodeOperation(node))
		return node;
	// cout << "----------" << endl;
	// printAST(node);
	// cout << "----------" << endl;
	Node_Operation *op_node = (Node_Operation *)node;
	Node *left = op_node->left;
	Node *right = op_node->right;
	switch(op_node->operation)
	{
		case '-':
			// a - a = 0 || a - 0 = a
			if (equal(left, right))
					return new Node_Number(0);
			if (isNodeNumber(right))
				if (((Node_Number *)right)->value == 0)
					return left;
			
			return node;
		case '+':
			// a + 0 = a
			if (isNodeNumber(left))
				if (((Node_Number *)left)->value == 0)
					return right;
			if (isNodeNumber(right))
				if (((Node_Number *)right)->value == 0)
					return left;
			
			// a + a = 2a
			if (equal(op_node->right, op_node->left))
			{
				delete op_node->left;
				op_node->left = new Node_Number(2);
				op_node->operation = '*';
				return op_node;
			}
			
			// a + n*a = n+1 * a
			if (isNodeOperation(op_node->left))
			{
				Node_Operation *left_op = ((Node_Operation*)op_node->left);
				if (get_operation(left_op) == '*')
				{
					if (equal(op_node->right, left_op->right))
					{
						op_node->operation = '*';
						left_op->operation = '+';
						delete left_op->right;
						left_op->right = new Node_Number(1);
						op_node->left = eval(left_op);
					}
					if (equal(op_node->right, left_op->left))
					{
						op_node->operation = '*';
						left_op->operation = '+';
						delete left_op->left;
						left_op->left = new Node_Number(1);
						op_node->left = eval(left_op);
					}
				}
			}
			if (isNodeOperation(op_node->right))
			{
				Node_Operation *right_op = ((Node_Operation*)op_node->right);
				if (get_operation(right_op) == '*')
				{
					if (equal(op_node->left, right_op->right))
					{
						op_node->operation = '*';
						right_op->operation = '+';
						delete right_op->right;
						right_op->right = new Node_Number(1);
						op_node->right = eval(right_op);
					}
					if (equal(op_node->left, right_op->left))
					{
						op_node->operation = '*';
						right_op->operation = '+';
						delete right_op->left;
						right_op->left = new Node_Number(1);
						op_node->right = eval(right_op);
					}
				}
			}
			
			// na + ma = (m+n)a
			if (isNodeOperation(op_node->left) && isNodeOperation(op_node->right))
			{
				if (get_operation(op_node->left) == '*' && get_operation(op_node->right) == '*')
				{
					Node_Operation *left_op = ((Node_Operation*)op_node->left);
					Node_Operation *right_op = ((Node_Operation*)op_node->right);
					if (equal(right_op->right, left_op->right))
					{
						Node *sum = eval(new Node_Operation('+', clone(right_op->left), clone(left_op->left)));
						return new Node_Operation('*', sum, clone(right_op->right));
					}
					if (equal(right_op->left, left_op->left))
					{
						Node *sum = eval(new Node_Operation('+', clone(right_op->right), clone(left_op->right)));
						return new Node_Operation('*', sum, clone(right_op->left));
					}
					if (equal(right_op->left, left_op->right))
					{
						Node *sum = eval(new Node_Operation('+', clone(right_op->right), clone(left_op->left)));
						return new Node_Operation('*', sum, clone(right_op->left));
					}
					if (equal(right_op->right, left_op->left))
					{
						Node *sum = eval(new Node_Operation('+', clone(right_op->left), clone(left_op->right)));
						return new Node_Operation('*', sum, clone(right_op->right));
					}
				}
			}
			return node;
		case '*':
			// a * 0 = 0 || a * 1 = a
			if (isNodeNumber(left))
			{
				if (((Node_Number *)left)->value == 0)
					return new Node_Number(0);
				if (((Node_Number *)left)->value == 1)
					return right;
			}
			if (isNodeNumber(right))
			{
				if (((Node_Number *)right)->value == 0)
					return new Node_Number(0);
				if (((Node_Number *)right)->value == 1)
					return left;
			}
			
			// 
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

Node *AST::operateNode(Node_Operation *op)
{
	Node_Number *l_number = ((Node_Number*)op->left);
	Node_Number *r_number = ((Node_Number*)op->right);
	int operation_result = operate(op->operation, l_number->value, r_number->value);
	Node_Number* num = new Node_Number(operation_result);
	// actualizando el link al padre
	delete op;  //----> OJO con esto

	// cout << "VALOR OPERACION: " << num->value << endl;
	return num;
}

Node *AST::replace_var(Node *node, vector<char> var_names, vector<int> var_values)
{
	char var_name = ((Node_Variable *)node)->name;
	for (int i = 0; i < var_names.size(); i++)
	{
		if (var_name == var_names[i])
			return new Node_Number(var_values[i]);
	}
	return node;
}

Node* AST::recursive_replace(Node* node, vector<char> var_names, vector<int> var_values)
{
	if (node->type == VARIABLE)
		return replace_var(node, var_names, var_values);
	
	if (isNodeOperation(node))
	{
		// evaluamos POSTORDER
		Node_Operation *op = (Node_Operation *)node;
		op->left = recursive_replace(op->left, var_names, var_values);
		op->right = recursive_replace(op->right, var_names, var_values);
		return node;
	} 
	if (node->type == NUMBER)
		return node;
	cout << "Error: se encontro algo distinto a operador o numero o variable" << endl;
	exit(1);
}

// solo evalua num op num y modifica el arbol!!!
Node* AST::eval(Node* node)
{
	if (node->type == OPERATOR) 
	{
		// evaluamos POSTORDER
		Node_Operation *op = (Node_Operation *)node;
		op->left = eval(op->left);
		op->right = eval(op->right);

		if (isNodeNumber(op->left) && isNodeNumber(op->right))
			return operateNode(op);
		return simplify(op);
	} 
	else if (node->type == VARIABLE || node->type == NUMBER)
		return node;
	cout << "Error: se encontro algo distinto a operador o numero o variable" << endl;
	exit(1);
}

Node *AST::clone(Node *old)
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

Node *AST::derive_sumsub(Node_Operation *op_node, char derive_var)
{
	op_node->left = derive(op_node->left, derive_var);
	op_node->right = derive(op_node->right, derive_var);
	return op_node;
}

Node *AST::derive_mult(Node_Operation *op_node, char derive_var)
{
	Node_Operation *right_multiplication = new Node_Operation('*');
	right_multiplication->left = op_node->left;
	right_multiplication->right = derive(clone(op_node->right), derive_var);

	// reusar el nodo original
	Node_Operation *left_multiplication = op_node;
	left_multiplication->left = derive(clone(op_node->left), derive_var);
	left_multiplication->right = op_node->right;

	return simplify(new Node_Operation('+', 
								simplify(left_multiplication),
								simplify(right_multiplication)));
}

Node *AST::derive_pow(Node_Operation *op_node, char derive_var)
{
	// op_node->left = op_node->left; comentado, se mantiene
	Node *old_right_node = op_node->right;

	int right_value = ((Node_Number *)op_node->right)->value;
	op_node->right = new Node_Number(right_value - 1);

	Node *left_derivative = derive(clone(op_node->left), derive_var);
	Node *right_mult = eval(new Node_Operation('*', op_node, left_derivative));
	return simplify(new Node_Operation('*', 
								eval(old_right_node),
								simplify(right_mult)));
}

Node *AST::derive_operation(Node_Operation *op_node, char derive_var)
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


Node *AST::derive(Node *node, char derive_var)
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
	return simplify(derive_operation((Node_Operation *) node, derive_var));
}


void AST::print(Node *node)
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

void AST::printAST(Node* p, int indent)
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

Node* AST::evaluate(Node* node)
{
	node = eval(node);
	// node = expand(node); función no implementada
	node = sum_tree(node);
	return node;
}

Node* AST::evaluate(Node* node, vector<char> var_names, vector<int> var_values)
{
	node = recursive_replace(node, var_names, var_values);
	return evaluate(node);
}

AST::AST(/* args */){}
AST::~AST(){}