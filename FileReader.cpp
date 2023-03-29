#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include "FileReader.h"

using namespace std;

// Autor: Lucas Mesías
// Código original: Pablo Román  "testLoad.cpp"

FileReader::FileReader(){}

// Es necesario borrar el objeto (delete obj;) para cerrar el archivo
FileReader::~FileReader()
{
    this->inputFile->close();
}
/// @brief Abre el archivo
/// @param fileName nombre del archivo
/// @return true si se abre correctamente, en caso contrario, false
bool FileReader::openFile(const char *fileName)
{
    this->inputFile = new ifstream(fileName); // abrir el archivo
    if (this->inputFile->is_open()) 
    {
        std::cout << "archivo abierto" << std::endl;
        return true;

    }
    std::cout << "archivo no encontrado" << std::endl;
    return false;
    
}
/// @brief Lee la linea que contiene la cantidad de elementos
void FileReader::readCountLine()
{
    // leer la primera linea
    getline(*this->inputFile, this->countLine);
    stringstream ss;
    // copiar la linea al stream
    ss << this->countLine; 
    // leer los datos del stream
    ss >> this->driverCount >> this->itemCount >> this->boatSize; 
    cout << "Conductores:" << driverCount
         << " Items:" << itemCount 
         << " Capacidad Botes:" << boatSize
         << endl;
}

/// @brief Getter de la cantidad de conductores
int FileReader::getDriverCount() { return this->driverCount; }
/// @brief Getter de la cantidad de items
int FileReader::getItemCount() { return this->itemCount; }
/// @brief Getter del tamaño del bote
int FileReader::getBoatSize() { return this->boatSize; }

/// @brief Lee la cantidad máxima de restricciónes para la matriz
/// @return el valor leído
int FileReader::readRestrictionSize()
{
    // leer la segunda linea
    string line;
    getline(*this->inputFile, line);
    // c_str convierte el string a un arreglo de caracteres
    return atoi(line.c_str()); 
}

/// @brief Rellena la matriz izquierda de restricciones
/// @param restrMatrix matriz con memoria ya asignada, esta se modifica
/// @param restrCount cantidad de restricciones
void FileReader::fillLeftMatrix(unsigned int *restrMatrix, int restrCount)
{
    string line;
    stringstream ss;
    for (int i = 0; i < restrCount; i++) 
    {
        restrMatrix[i] = 0; // asegurar que no exista basura en el puntero
        int pow = 0;
        getline(*this->inputFile, line);
        ss.clear(); // limpiar el stream de caracteres
        ss << line; // copiar la linea al stream
        int a;
        while (ss >> a) // https://comp.lang.cpp.moderated.narkive.com/vwstw4Un/std-stringstream-and-eof-strangeness
        { 
            pow = a-1;
            restrMatrix[i] += 1 << pow;
        }
        // https://stackoverflow.com/questions/40169322/c-how-to-flip-the-binary-values-of-each-bit-in-int
        restrMatrix[i] = ~restrMatrix[i];
    }
}

/// @brief Rellena la matriz izquierda de restricciones
/// @param restrMatrix matriz con memoria ya asignada, esta se modifica
/// @param restrCount cantidad de restricciones
void FileReader::fillRightMatrix(unsigned int *restrMatrix, int restrCount)
{
    string line;
    stringstream ss;
    for (int i = 0; i < restrCount; i++) 
    {
        restrMatrix[i] = 0; // asegurar que no exista basura en el puntero
        int pow = 0;
        getline(*this->inputFile, line);
        ss.clear(); // limpiar el stream de caracteres
        ss << line; // copiar la linea al stream
        int a;
        while (ss >> a) // https://comp.lang.cpp.moderated.narkive.com/vwstw4Un/std-stringstream-and-eof-strangeness
        { 
            pow = a-1;
            restrMatrix[i] += 1 << pow;
        }
    }
}