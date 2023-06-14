#include "AST.h"

// mirar todos los isnodeX

/// Función entregada por el profesor Pablo Román
/// @brief Opera los valores de los nodos
/// @param operation Char que representa la opearción a realizar
/// @param l Valor izquierdo
/// @param r Valor derecho
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

/// @brief Casteo y obtención de operación rápido
/// @param node Nodo a castear
/// @return Char que representa la operación.
/// No implementable en las clases nodo
char AST::get_operation(Node *node) {
	Node_Operation *node_op = (Node_Operation *)node;
	return node_op->operation;
}

/// @brief Casteo y obtención de número rápido
/// @param node Nodo a castear
/// @return Valor del número.
/// No implementable en las clases nodo
int AST::get_value(Node *node) {
	Node_Number *node_num = (Node_Number *)node;
	return node_num->value;
}

/// @brief Casteo y obtención de variable rápido
/// @param node Nodo a castear
/// @return Nombre de la variable.
/// No implementable en las clases nodo
char AST::get_name(Node *node) {
	Node_Variable *node_var = (Node_Variable *)node;
	return node_var->name;
}

/// @brief Ordena un árbol de sumas por elementos no expandibles
/// @param node Nodo raíz del árbol de sumas
/// @return Nodo raíz del nuevo árbol de sumas ordenado
Node *AST::sum_tree(Node * node)
{
	// Evitar errores revisando si el nodo raíz es una suma
	if (!node->isNodeOperation())
		return node;

	Node_Operation *op = (Node_Operation *)node;
	// revisar si es suma
	if (get_operation(op) != '+')
		return node;

	vector<Node *> elems; // Vector de todos los elementos
	vector<Node *> elems_unicos; // Vector de elementos unicos
	get_sum_elements(op, elems); // Obtener todos los elementos
	// Obtener los elementos únicos del árbol de sumas
	for (auto elem : elems)
	{
		bool is_unico = true;
		for (auto elem_unico : elems_unicos)
		{
			if (elem->equal(elem_unico))
				is_unico = false;
		}
		if (is_unico)
			elems_unicos.push_back(elem);
	}
	// Se comienza con un árbol + 0 0, luego se reemplazará uno de los 0s con un sub-árbol
	Node_Operation *sum_root = new Node_Operation('+', new Node_Number(0), new Node_Number(0));
	Node_Operation *sum_tail = sum_root;
	for (auto var_unica : elems_unicos) 
	{
		// Crear sub-árboles de elementos iguales
		Node_Operation *sub_sum_root = new Node_Operation('+', new Node_Number(0), new Node_Number(0));
		Node_Operation *sub_sum_tail = sub_sum_root;
		for (int i = 0; i < elems.size(); i++)
		{
			// Agregar todos los elementos iguales a su sub-árbol
			if (elems[i]->equal(var_unica))
			{
				delete sub_sum_tail->right;
				sub_sum_tail->right = new Node_Operation('+', elems[i], new Node_Number(0));
				sub_sum_tail = (Node_Operation *)sub_sum_tail->right;
			}
		}
		// Agregar el sub-árbol al árbol final
		delete sum_tail->right;
		sum_tail->right = new Node_Operation('+', sub_sum_root, new Node_Number(0));
		sum_tail = (Node_Operation *)sum_tail->right;
	}
	// Retornar el árbol final
	return eval(sum_root);
}

/// @brief Inserta todos los nodos que no sean el nodo '+'
/// @param node Raíz recursiva para recorrer todo el árbol
/// @param elems Referencia al vector de elementos
void AST::get_sum_elements(Node *node, vector<Node *> &elems)
{
	if (!node->isNodeOperation())
		return elems.push_back(node);
	
	Node_Operation *op_node = (Node_Operation *)node;
	if (op_node->operation != '+')
		return elems.push_back(node);
	// Si es un nodo ´+´, llamar recursivamente en sus hijos
	get_sum_elements(op_node->left, elems);
	get_sum_elements(op_node->right, elems);
}

/// @brief Casos de simplificación de la suma
/// @param node Nodo a simplificar
/// @return Nodo simplificado
Node *AST::simplify_sum(Node *node)
{
	//! Esta función es bastante larga
	Node_Operation *op_node = (Node_Operation *)node;
	Node *left = op_node->left;
	Node *right = op_node->right;

	// a + 0 = a
	if (left->isNodeNumber())
		if (((Node_Number *)left)->value == 0)
			return right;
	if (right->isNodeNumber())
		if (((Node_Number *)right)->value == 0)
			return left;
	
	// a + a = 2a
	if (op_node->right->equal(op_node->left))
	{
		delete op_node->left;
		op_node->left = new Node_Number(2);
		op_node->operation = '*';
		return op_node;
	}

	// a + n*a = n+1 * a
	if (op_node->left->isNodeOperation())
	{
		Node_Operation *left_op = ((Node_Operation*)op_node->left);
		if (get_operation(left_op) == '*')
		{
			if (op_node->right->equal(left_op->right))
			{
				op_node->operation = '*';
				left_op->operation = '+';
				delete left_op->right;
				left_op->right = new Node_Number(1);
				op_node->left = eval(left_op);
			}
			if (op_node->right->equal(left_op->left))
			{
				op_node->operation = '*';
				left_op->operation = '+';
				delete left_op->left;
				left_op->left = new Node_Number(1);
				op_node->left = eval(left_op);
			}
			return node;
		}
	}
	if (op_node->right->isNodeOperation())
	{
		Node_Operation *right_op = ((Node_Operation*)op_node->right);
		if (get_operation(right_op) == '*')
		{
			if (op_node->left->equal(right_op->right))
			{
				op_node->operation = '*';
				right_op->operation = '+';
				delete right_op->right;
				right_op->right = new Node_Number(1);
				op_node->right = eval(right_op);
			}
			if (op_node->left->equal(right_op->left))
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
	if (op_node->left->isNodeOperation() && op_node->right->isNodeOperation())
	{
		if (get_operation(op_node->left) == '*' && get_operation(op_node->right) == '*')
		{
			Node_Operation *left_op = ((Node_Operation*)op_node->left);
			Node_Operation *right_op = ((Node_Operation*)op_node->right);
			if (right_op->right->equal(left_op->right))
			{
				Node *sum = eval(new Node_Operation('+', right_op->left->clone(), left_op->left->clone()));
				return new Node_Operation('*', sum, right_op->right->clone());
			}
			if (right_op->left->equal(left_op->left))
			{
				Node *sum = eval(new Node_Operation('+', right_op->right->clone(), left_op->right->clone()));
				return new Node_Operation('*', sum, right_op->left->clone());
			}
			if (right_op->left->equal(left_op->right))
			{
				Node *sum = eval(new Node_Operation('+', right_op->right->clone(), left_op->left));
				return new Node_Operation('*', sum, right_op->left->clone());
			}
			if (right_op->right->equal(left_op->left))
			{
				Node *sum = eval(new Node_Operation('+', right_op->left->clone(), left_op->right->clone()));
				return new Node_Operation('*', sum, right_op->right->clone());
			}
		}
	}
	return node;
}

/// @brief Aplicar simplificaciones, de caso en caso
/// @param node Nodo a simplificar
Node *AST::simplify(Node *node)
{
	// No se puede hacer nada
	if (!node->isNodeOperation())
		return node;
	Node_Operation *op_node = (Node_Operation *)node;
	Node *left = op_node->left;
	Node *right = op_node->right;
	// Casos implementados de simplificación
	switch(op_node->operation)
	{
		case '-':
			// a - a = 0 || a - 0 = a
			if (left->equal(right))
					return new Node_Number(0);
			if (right->isNodeNumber())
				if (((Node_Number *)right)->value == 0)
					return left;
			return node;
		case '+':
			return simplify_sum(node);
		case '*':
			// a * 0 = 0 || a * 1 = a
			if (left->isNodeNumber())
			{
				if (((Node_Number *)left)->value == 0)
					return new Node_Number(0);
				if (((Node_Number *)left)->value == 1)
					return right;
			}
			if (right->isNodeNumber())
			{
				if (((Node_Number *)right)->value == 0)
					return new Node_Number(0);
				if (((Node_Number *)right)->value == 1)
					return left;
			}
			
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

/// @brief Realizar operación entre nodos de tipo número
/// @param op Nodo operación, del cual ya se sabe que sus hijos son números
/// @return Nodo operado.
/// Código entregado por Pablo Román
Node *AST::operateNode(Node_Operation *op)
{
	Node_Number *l_number = ((Node_Number*)op->left);
	Node_Number *r_number = ((Node_Number*)op->right);
	int operation_result = operate(op->operation, l_number->value, r_number->value);
	Node_Number* num = new Node_Number(operation_result);
	delete op;
	return num;
}

/// @brief Reemplaza un nodo que ya se sabe que es una variable por un número
/// @param node Nodo variable que va a ser reemplazado
/// @param var_names Vector que contiene los nombres de las variables a reemplazar
/// @param var_values Vector que contiene los valores de las variables a reemplazar
/// @return Nodo reemplazado, número si fue correctamente reemplazado, variable si no se encuentra en var_names.
/// Ambos vectores deben tener el mismo tamaño, 
/// y los valores y variables a reemplazar deben estar en la misma posición.
Node *AST::replace_var(Node *node, vector<char> var_names, vector<int> var_values)
{
	char var_name = ((Node_Variable *)node)->name;
	for (int i = 0; i < var_names.size(); i++)
	{
		if (var_name == var_names[i])
		{
			delete node;
			return new Node_Number(var_values[i]);
		}
	}
	return node;
}

/// @brief Recorre el árbol buscando nodos variables para reemplazar con valores
/// @param node Raíz recursiva
/// @param var_names Vector que contiene los nombres de las variables a reemplazar
/// @param var_values Vector que contiene los valores de las variables a reemplazar
/// Ambos vectores deben tener el mismo tamaño, 
/// y los valores y variables a reemplazar deben estar en la misma posición.
Node* AST::recursive_replace(Node* node, vector<char> var_names, vector<int> var_values)
{
	if (node->isNodeVariable())
		return replace_var(node, var_names, var_values);
	
	if (node->isNodeOperation())
	{
		// evaluamos POSTORDER
		Node_Operation *op = (Node_Operation *)node;
		op->left = recursive_replace(op->left, var_names, var_values);
		op->right = recursive_replace(op->right, var_names, var_values);
		return node;
	} 
	if (node->isNodeNumber())
		return node;
	cout << "Error: se encontro algo distinto a operador o numero o variable" << endl;
	exit(1);
}

/// @brief Evalúa recursivamente cada nodo del árbol
/// @param node Raíz recursiva para recorrer
/// @return Nodo operado y simplificado.
/// Código entregado por Pablo Román
Node* AST::eval(Node* node)
{
	if (node->isNodeOperation()) 
	{
		// evaluamos POSTORDER
		Node_Operation *op = (Node_Operation *)node;
		op->left = eval(op->left);
		op->right = eval(op->right);

		if (op->left->isNodeNumber() && op->right->isNodeNumber())
			return operateNode(op);
		return simplify(op);
	} 
	else if (node->isNodeVariable() || node->isNodeNumber())
		return node;
	cout << "Error: se encontro algo distinto a operador o numero o variable" << endl;
	exit(1);
}

/// @brief Derivación caso suma o resta
/// @param node Nodo a derivar 
/// @param derive_var Variable para derivar con respecto a ella
/// @return Nodo derivado
Node *AST::derive_sumsub(Node_Operation *op_node, char derive_var)
{
	op_node->left = derive(op_node->left, derive_var);
	op_node->right = derive(op_node->right, derive_var);
	return op_node;
}

/// @brief Derivación caso multiplicación
/// @param node Nodo a derivar 
/// @param derive_var Variable para derivar con respecto a ella
/// @return Nodo derivado
Node *AST::derive_mult(Node_Operation *op_node, char derive_var)
{
	Node_Operation *right_multiplication = new Node_Operation('*');
	right_multiplication->left = op_node->left;
	right_multiplication->right = derive(op_node->right->clone(), derive_var);

	// reusar el nodo original
	Node_Operation *left_multiplication = op_node;
	left_multiplication->left = derive(op_node->left->clone(), derive_var);
	left_multiplication->right = op_node->right;

	return simplify(new Node_Operation('+', 
								simplify(left_multiplication),
								simplify(right_multiplication)));
}

/// @brief Derivación caso potencia
/// @param node Nodo a derivar 
/// @param derive_var Variable para derivar con respecto a ella
/// @return Nodo derivado
Node *AST::derive_pow(Node_Operation *op_node, char derive_var)
{
	// op_node->left = op_node->left; comentado, se mantiene
	Node *old_right_node = op_node->right;

	int right_value = ((Node_Number *)op_node->right)->value;
	op_node->right = new Node_Number(right_value - 1);

	Node *left_derivative = derive(op_node->left->clone(), derive_var);
	Node *right_mult = eval(new Node_Operation('*', op_node, left_derivative));
	return simplify(new Node_Operation('*', 
								eval(old_right_node),
								simplify(right_mult)));
}

/// @brief Función envoltorio para las derivaciones de operaciones
/// @param node Nodo a derivar 
/// @param derive_var Variable para derivar con respecto a ella
/// @return Nodo derivado
Node *AST::derive_operation(Node *node, char derive_var)
{
	Node_Operation *op_node = (Node_Operation *)node;
	switch (op_node->operation)
	{
		// Caso suma y resta son iguales
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

/// @brief Derivar el árbol
/// @param node Raíz recursiva
/// @param derive_var Variable para derivar con respecto a ella
/// @return Nodo derivado
Node *AST::derive(Node *node, char derive_var)
{
	// Revisar primero casos simples
	if (!node->isNodeOperation())
	{
		if (node->isNodeVariable())
		{
			char var_name = ((Node_Variable *)node)->name;
			delete node;
			if (var_name == derive_var)
				return new Node_Number(1);
			return new Node_Number(0); // node_var->name != derive_var
		}
		if (node->isNodeNumber())
		{
			((Node_Number *)node)->value = 0;
			return node;
		}
	} // Casos de operaciones + simplificar
	return simplify(derive_operation((Node_Operation *) node, derive_var));
}

/// @brief Imprimir el árbol, en forma lineal
/// @param p Raíz del árbol a imprimir
void AST::print_linear(Node *node)
{
	node->print();
}

/// @brief Imprimir el árbol, en forma de árbol
/// @param p Raíz del árbol a imprimir
void AST::printAST(Node* p)
{
	p->printAST(0);
}

/// @brief Función envoltorio
/// @param node 
/// @return 
Node* AST::evaluate(Node* node)
{
	// node = expand(node); función no implementada por falta de tiempo (informe)
	node = sum_tree(node);
	node = eval(node);
	// node = factorize(node); nunca planeada, permitiría llegar a la menor cantidad de nodos posibles
	return node;
}

/// @brief Función envoltorio de evaluate con reemplazo
/// @param node Raíz del árbol a reemplazar
/// @param var_names Vector que contiene los nombres de las variables a reemplazar
/// @param var_values Vector que contiene los valores de las variables a reemplazar
/// Ambos vectores deben tener el mismo tamaño, 
/// y los valores y variables a reemplazar deben estar en la misma posición.
Node* AST::evaluate(Node* node, vector<char> var_names, vector<int> var_values)
{
	node = recursive_replace(node, var_names, var_values);
	return evaluate(node);
}

// Constructor y destructor
AST::AST(/* args */){}
AST::~AST(){}
