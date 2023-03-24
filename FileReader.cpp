#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Código original: Pablo Román

bool read() {

    ifstream *input = new ifstream("sistema.txt"); // abrir el archivo
    if (input->is_open()) { // verificar que el archivo se abrio correctamente
        std::cout << "archivo abierto" << std::endl;

    } else {
        std::cout << "archivo no encontrado" << std::endl;
        return false;
    }

    string line; // linea de texto
    stringstream ss; // stream de caracteres

    // variables a leer del archivo
    int C,I,b,N; // cantidad de conductores, cantidad de item, capacidad del bote, cantidad total de item mas conductores
    int cantidadRestriccionesIzq, cantidadRestriccionesDer; // cantidad de restricciones de cada lado
    int **restriccionesIzq, **restriccionesDer; // matriz de restricciones de cada lado


    // leer la primera linea
    getline(*input, line);
    ss << line; // copiar la linea al stream
    ss >> C >> I >> b; // leer los datos del stream
    N = C + I;
    cout <<"C:"<< C << " I:" << I << " b:" << b << endl;

    // leer la segunda linea
    getline(*input, line);
    cantidadRestriccionesIzq=atoi(line.c_str()) ; // c_str convierte el string a un arreglo de caracteres
    cout<<"cantidadRestriccionesIzq:"<<cantidadRestriccionesIzq<<endl;
    
    restriccionesIzq = allocateMatrix(cantidadRestriccionesIzq, N);
    fillRestrMatrix(restriccionesIzq, cantidadRestriccionesIzq, input);

    restriccionesDer = allocateMatrix(cantidadRestriccionesDer, N);
    fillRestrMatrix(restriccionesDer, cantidadRestriccionesDer, input);

    input->close();

    // veamos como quedan las matrices
    cout<<"restriccionesIzq:"<<endl;
    for(int i=0;i<cantidadRestriccionesIzq;i++){
        for(int j=0;j<N;j++){
            cout<<restriccionesIzq[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"restriccionesDer:"<<endl;
    for(int i=0;i<cantidadRestriccionesDer;i++){
        for(int j=0;j<N;j++){
            cout<<restriccionesDer[i][j]<<" ";
        }
        cout<<endl;
    }
}

int **allocateMatrix(int restrCount, int totalItemCount)
{
    int **matrixPointer = new int*[restrCount]; // crear la matriz de restricciones
    for (int i = 0; i < restrCount; i++) {
        matrixPointer[i] = new int[totalItemCount];
        for (int j = 0; j < totalItemCount; j++) {
            matrixPointer[i][j] = 0;
        }
    }
    return matrixPointer;
}

void fillRestrMatrix(int **restrMatrix, int restrCount, ifstream *file)
{
    string line;
    stringstream ss;
    for (int i = 0; i < restrCount; i++) {
        getline(*file, line);
        ss.clear(); // limpiar el stream de caracteres
        ss << line; // copiar la linea al stream
        while (!ss.eof()) { // mientras no termine esta linea
            int a;
            ss >> a;
            restrMatrix[i][a-1] = 1; // recuerden que los elementos de los archivos empiezan en 1, pero los indices en 0
            cout << a << " ";
        }
        cout << endl;
    }
}