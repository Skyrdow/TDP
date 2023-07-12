#include "Simplex.h"
#include "Heap.h"

class BnB
{
private:
    int quedan_flotantes(Simplex *simplex);
    int elegir_variable(Simplex *simplex);
    float calcular_lb(Simplex *simplex);
public:
    vector<float> solve(const char *nombreArchivo, int print);
    vector<int> indices_no_enteros(vector<float>& numeros);
    void print_solve(Simplex *simplex);
    BnB();
    ~BnB();
};
