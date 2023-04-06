#include "../RiverCrossing.h"
#include <string>
#include <iostream>
#include <ctime>

using namespace std;



int main() {
    clock_t t_ini, t_fin;
    double secs=0;

    int k, numVeces;
    string nombreArchivo;

    cout << "Cuantas veces quieres que se resuelva el problema? ";
    cin >> numVeces;

    cout << endl << "Indique el nombre de archivo:  " ;
    cin >> nombreArchivo;

    cout << endl << "Resolviendo el problema " << nombreArchivo <<", "<< numVeces << " veces..." << endl;
    
    for (k=0; k<numVeces; k++) {
        t_ini = clock();
        RiverCrossing *r = new RiverCrossing();
        r->solve(nombreArchivo.c_str());
        delete r;
        t_fin = clock();
        secs = secs + (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
        // delete r;
    }
    cout << endl << "Tiempo promedio: " << secs/numVeces << " segundos" << endl;
    
    return 0;
}