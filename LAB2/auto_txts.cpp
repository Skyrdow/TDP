#include "AST.h"

//! para imprimir linealmente reemplaza printAST por print_linear

/// @brief Programa principal que controla el menú
int main() {
	// Definiciones
	string nombreCarpeta = "txts/";
	string nombreArchivo;
	int opcion;
	loadFile *lf = new loadFile();
	Node *root = nullptr;
	AST *ast = new AST();

	vector<char> vectorChar;
	vector<int> vectorInt;

	vector<string> vectorNames;
    vectorNames.push_back("sub_1");
    vectorNames.push_back("sub_2");
    vectorNames.push_back("sub_3");
    vectorNames.push_back("add_1");
    vectorNames.push_back("add_2");
    vectorNames.push_back("add_3");
    vectorNames.push_back("add_4");
    vectorNames.push_back("add_5");
    vectorNames.push_back("add_6");
    vectorNames.push_back("add_7");
    vectorNames.push_back("add_8");
    vectorNames.push_back("add_9");
    vectorNames.push_back("mul_1");
    vectorNames.push_back("mul_2");
    vectorNames.push_back("pow_1");
    vectorNames.push_back("pow_2");
    vectorNames.push_back("pow_3");
    vectorNames.push_back("expr1");
    vectorNames.push_back("expr2");
    vectorNames.push_back("expr3");
    vectorNames.push_back("expr4");
    vectorNames.push_back("expr5");
    vectorNames.push_back("expr6");
    vectorNames.push_back("derv1");
    vectorNames.push_back("derv2");

	char caracter;
	int numero;
	int cantidad;
	for (auto name : vectorNames)
	{
		nombreArchivo = "txts/" + name + ".txt";
		cout << "txts/" + name + ".txt" << endl;
		root = lf->readfile(nombreArchivo.c_str());
		cout << "Archivo cargado: \n";
		ast->printAST(root);
		cout << "Evaluando: \n";
		root = ast->evaluate(root);
		ast->printAST(root);
		cout << endl;
	}
    return 0;
}