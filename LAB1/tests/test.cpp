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
    string resp;
    bool flagResp = false;

    cout << "Cuantas veces quieres que se resuelva el problema? ";
    cin >> numVeces;

    cout << endl << "Indique el nombre de archivo:  " ;
    cin >> nombreArchivo;


    cout << endl << "Usar prints? [Y/N]" ;
    cin >> resp;

    if ("Y" == resp || "y" == resp)
        flagResp = true;
    if ("N" == resp || "n" == resp)
        flagResp = false;

    cout << endl << "Resolviendo el problema " << nombreArchivo <<", "<< numVeces << " veces..." << endl;
    
    for (k=0; k<numVeces; k++) {
        RiverCrossing *r = new RiverCrossing(nombreArchivo.c_str());
        r->print = flagResp; // Desactivar prints
        t_ini = clock();
        r->solve();
        t_fin = clock();
        secs = secs + (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
        delete r;
    }
    cout << endl << "Tiempo promedio: " << secs/numVeces << " segundos" << endl;
    
    return 0;
}
