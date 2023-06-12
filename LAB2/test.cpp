#include "AST.h"

int main() {

	string filename = "expr1.txt";
	loadFile *lf = new loadFile(filename.c_str());
	Node *root = lf->readfile();
	AST *a = new AST();

	a->printAST(root);
	cout << endl;
	cout << "Evaluacion: " << endl;
	vector<char> vars = {'a'};
	vector<int> vals = {2};
	// root = derive(root, 'x');
	// printAST(root);
	root = a->simplify(root);
	a->printAST(root);
	return 0;
}