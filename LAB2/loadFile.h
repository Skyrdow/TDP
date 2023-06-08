#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <stack>
#include <vector>

#include "Node_Operation.h"
#include "Node_Number.h"
#include "Node_Variable.h"

// sstream es un stream de caracteres
using namespace std;
class loadFile
{
private:
    bool isOperator(string token);
    bool isNumber(string token);
    bool isVariable(string token);
    char *filename;
public:
    Node *readfile();
    loadFile(char *filename);
    ~loadFile();
};