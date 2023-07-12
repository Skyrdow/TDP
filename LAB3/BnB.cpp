#include "BnB.h"

BnB::BnB()
{
}

BnB::~BnB()
{
}

/// @brief Calcula el lower bound del simplex
/// @param simplex simplex a aplicar la operación
/// @return valor lower bound
float BnB::calcular_lb(Simplex *simplex)
{
    Simplex *simpl = simplex->clone();
    vector<float> numeros = simpl->getSolution();
    for (int i = 1; i < numeros.size(); i++)
    {
        // saltar si no pertenece a las variables enteras
        int skip = 1;
        for (auto indice : simpl->indx_enteros)
        {
            if (indice == i)
                skip = 0;
        }
        if (skip)
            continue;
        
        int truncado = static_cast<int>(numeros[i]);
        simpl->insertConstraint(truncado, i, 3);
    }
    vector<float> par = simpl->solve();
    delete simpl;
    if (par.size() == 0)
        return -1;
    return par[0];
}

/// @brief elige la variable más cercana a X.5f
/// @param simplex simplex a aplicar la operación
/// @return indice de la variable en el vector del simplex
int BnB::elegir_variable(Simplex *simplex)
{
    vector<float> numeros = simplex->getSolution();
    float val_min = 0.6f;
    int indice = -1;
    for (int i = 1; i < numeros.size(); i++)
    {
        // saltar si no pertenece a las variables enteras
        int skip = 1;
        for (auto indice : simplex->indx_enteros)
        {
            if (indice == i)
                skip = 0;
        }
        if (skip)
            continue;

        float val = abs((numeros[i] - static_cast<int>(numeros[i])) - 0.5f);
        if (val_min > val)
        {
            val_min = val;
            indice = i;
        }
    }
    return indice;
}

/// @brief Revisa si quedan números flotantes por transformar
/// @param simplex Simplex a revisar
/// @return booleano 0 o 1
int BnB::quedan_flotantes(Simplex *simplex) {
    vector<float> numeros = simplex->getSolution();
    for (int i = 1; i < numeros.size(); ++i) {
        // saltar si no pertenece a las variables enteras
        int skip = 1;
        for (auto indice : simplex->indx_enteros)
        {
            if (indice == i)
                skip = 0;
        }
        if (skip)
            continue;
            
        if (numeros[i] != static_cast<int>(numeros[i])) {
            return 1;
        }
    }
    return 0;
}

/// @brief Imprime por consola la solución de un simplex
/// @param simplex simplex a aplicar la operación
void BnB::print_solve(Simplex *simplex)
{
    vector<float> par1 = simplex->getSolution(); // retorna [Z,x1,...,xn] sino []
    simplex->printProblemMatrix();
    cout << "Solucion: " << endl;
    for(int i = 0; i < par1.size(); i++) {
        cout << par1[i] << " ";
    }
    cout << endl;
}

/// @brief Función principal, resuelve el problema. Imprime la solución
/// @param nombreArchivo nombre del archivo del problema
/// @return vector de variables que resuelve el problema
vector<float> BnB::solve(const char *nombreArchivo, int print)
{
    string line;
    ifstream file(nombreArchivo);
    if (!file.is_open()) {
        cout << "Could not open file " << endl;
        exit(2);
    }
    getline(file, line); // ignorar primera linea

    getline(file, line); // leer 2da linea
    vector<int> indx_enteros;
    istringstream iss(line);
    int num;
    while (iss >> num) {
        indx_enteros.push_back(num);
    }
    file.close();

    // cargar simplex
    Simplex *first_simplex = new Simplex(nombreArchivo);
    first_simplex->indx_enteros = indx_enteros;
    // la solución requiere que el simplex entre al ciclo resuelto
    vector<float> par1 = first_simplex->solve();
    
    Heap *heap = new Heap(2);
    Heap *heap_solucion = new Heap(2);
    heap->push(new Node(first_simplex, par1[0]));

    // ciclo principal
    while (heap->size != 0)
    {
        Node *node = heap->pop();
        Simplex *simplex = node->simplex;
        vector<float> par = simplex->getSolution();
        if (print)
            print_solve(simplex); // ver traza

        int lb_result = calcular_lb(simplex);
        if (node->lower < lb_result)
            node->lower = lb_result;
        // revisar si quedan numeros a truncar
        if (!quedan_flotantes(simplex))
        {
            if (node->upper - node->lower < 1e-6)
            {
                heap_solucion->push(new Node(simplex, node->lower));
            }
            continue;
        }

        int var_indice = elegir_variable(simplex);
        int var_entera = static_cast<int>(par[var_indice]);

        // restringir la variable elegida
        Simplex *left_simplex = simplex->clone();
        left_simplex->insertConstraint(var_entera, var_indice, 3);
        left_simplex->solve();
        // guardar si tiene solución
        if(left_simplex->getSolution().size() != 0)
            heap->push(new Node(left_simplex, node->lower));

        Simplex *right_simplex = simplex->clone();
        right_simplex->insertConstraint(var_entera + 1, var_indice, 3);
        right_simplex->solve();
        // guardar si tiene solución
        if(right_simplex->getSolution().size() != 0)
            heap->push(new Node(right_simplex, node->lower));
    }
    
    Simplex *solucion = heap_solucion->pop()->simplex;
    if (print)
    {
        cout << endl << "===================================" << endl;
        cout << endl << "Solución encontrada: " << endl;
        print_solve(solucion);
    }
    return solucion->getSolution(); // sin solución, vector vacio
}
