#include "loadFile.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	loadFile *lf = new loadFile();
    string nombreArchivo = "txts/expr1.txt";
    Node *root = lf->readfile(nombreArchivo.c_str());
    root->printAST(0);
    return 0;
}
