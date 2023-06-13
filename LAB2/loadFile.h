#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <stack>

#include "Node_Operation.h"
#include "Node_Number.h"
#include "Node_Variable.h"

using namespace std;
/// Código entregado por el profesor Pablo Román
class loadFile
{
private:
    bool isOperator(string token);
    bool isNumber(string token);
    bool isVariable(string token);
public:
    Node *readfile(const char *filename);
    loadFile();
    ~loadFile();
};