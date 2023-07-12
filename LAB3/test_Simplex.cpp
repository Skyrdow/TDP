#include "Simplex.h"

int main() {

    Simplex *simplex1 = new Simplex("sistema.txt");

    vector<float> par1 = simplex1->solve(); // retorna [Z,x1,...,xn] sino []
    simplex1->printProblemMatrix();
    cout << "Solucion: " << endl;
    for(int i = 0; i < par1.size(); i++) {
        cout << par1[i] << " ";
    }
    cout << endl;

    Simplex *simplex2 = simplex1->clone(); // Aqui falla porque se necesita un clone
    cout << "simplex2->insertConstraint(2, 1, 3)" << endl;
    simplex2->insertConstraint(2, 1, 3);
    vector<float> par2 = simplex2->solve(); // retorna [Z,x1,...,xn] sino []
    simplex1->printProblemMatrix();
    cout << "Solucion: " << endl;
    for(int i = 0; i < par1.size(); i++) {
        cout << par1[i] << " ";
    }
    cout << endl;

    simplex2->printProblemMatrix();
    cout << "Solucion: " << endl;
    for(int i = 0; i < par2.size(); i++) {
        cout << par2[i] << " ";
    }
    cout << endl;

}
