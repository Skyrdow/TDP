#include <iostream>
#include <bitset>

using namespace std;

void printBits(unsigned int n) {
    char* p = (char*)&n;
    for (int i = 3; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            cout << ((*(p + i) >> j) & 1);
        }
    }
    cout << endl;
}
void printBits1(unsigned int n) {

    cout << bitset<32>(n) << endl;
}
void printBits2(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        cout << ((n >> i) & 1);
    }
    cout << endl;
}

int main() {
    clock_t t_ini, t_fin;
    double secs=0;

    int k, numVeces;
    string nombreArchivo;

    cout << "Cuantas veces quieres que se resuelva el problema? ";
    cin >> numVeces;

    cout << endl << numVeces << " veces..." << endl;
    
    for (k=0; k<numVeces; k++) {
        t_ini = clock();
        for (int i = 0; i < 100; i++)
        {
            printBits(i);
        }
        
        t_fin = clock();
        secs = secs + (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
        // delete r;
    }
    double exp1 =secs/numVeces;
    cout << endl << "Tiempo promedio: " << secs/numVeces << " segundos" << endl;

    cout << endl << numVeces << " veces..." << endl;
    
    for (k=0; k<numVeces; k++) {
        t_ini = clock();
        for (int i = 0; i < 100; i++)
        {
            printBits2(i);
        }
        
        t_fin = clock();
        secs = secs + (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
        // delete r;
    }
    cout << endl << "Tiempo promedio: " << secs/numVeces << " segundos" << endl;
    cout << endl << "Tiempo promedio: " << exp1 << " segundos" << endl;
    
    return 0;
}