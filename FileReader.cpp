#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include "FileReader.h"

using namespace std;

// Código original: Pablo Román  "testLoad.cpp"

FileReader::FileReader(/* args */){}

FileReader::~FileReader(){}

void FileReader::printBits(int N)
{
    std::bitset<sizeof(int)*8> A = N; //A will hold the binary representation of N 
    for(int i=0; i<sizeof(int)*8; i++)
    {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

void FileReader::fillRestrMatrix(unsigned int *restrMatrix, unsigned int restrCount, ifstream *file, bool isRightSide)
{
    string line;
    stringstream ss;
    for (int i = 0; i < restrCount; i++) {
        restrMatrix[i] = 0; // asegurar que no exista basura en el puntero
        int pow = 0;
        getline(*file, line);
        ss.clear(); // limpiar el stream de caracteres
        ss << line; // copiar la linea al stream
        int a;
        while (ss >> a) // https://comp.lang.cpp.moderated.narkive.com/vwstw4Un/std-stringstream-and-eof-strangeness
        { 
            pow = a-1;
            restrMatrix[i] += 1 << pow;
        }
        if (!isRightSide)
            restrMatrix[i] = ~restrMatrix[i]; // https://stackoverflow.com/questions/40169322/c-how-to-flip-the-binary-values-of-each-bit-in-int
    }
}

bool FileReader::read(unsigned int *restriccionesIzq, unsigned int *restriccionesDer, int *C, int *I, int *b, int *cantidadRestriccionesIzq, int *cantidadRestriccionesDer) 
{
    ifstream *input = new ifstream("test.txt"); // abrir el archivo
    if (input->is_open()) { // verificar que el archivo se abrio correctamente
        std::cout << "archivo abierto" << std::endl;

    } else {
        std::cout << "archivo no encontrado" << std::endl;
        return false;
    }

    string line; // linea de texto
    stringstream ss; // stream de caracteres

    // variables a leer del archivo

    // leer la primera linea
    getline(*input, line);
    ss << line; // copiar la linea al stream
    ss >> *C >> *I >> *b; // leer los datos del stream
    int N = *C + *I;
    cout <<"Conductores:"<< *C << " Items:" << *I << " Capacidad Botes:" << *b << endl;

    // leer la segunda linea
    getline(*input, line);
    *cantidadRestriccionesIzq = atoi(line.c_str()); // c_str convierte el string a un arreglo de caracteres
    
    restriccionesIzq = new unsigned int[*cantidadRestriccionesIzq]; 
    fillRestrMatrix(restriccionesIzq, *cantidadRestriccionesIzq, input, false);

    getline(*input, line);
    *cantidadRestriccionesDer=atoi(line.c_str()); // c_str convierte el string a un arreglo de caracteres
    restriccionesDer = new unsigned int[*cantidadRestriccionesDer]; 
    fillRestrMatrix(restriccionesDer, *cantidadRestriccionesDer, input, true);

    input->close();

    // veamos como quedan las matrices
    cout<<"Restricciones Izq:"<<endl;
    for(int i=0;i < *cantidadRestriccionesIzq;i++)
    {
        printBits(restriccionesIzq[i]);
    }

    cout<<"Restricciones Der:"<<endl;
    for(int i=0;i < *cantidadRestriccionesDer;i++)
    {
        printBits(restriccionesDer[i]);
    }
    cout << endl;
    return true;
}
