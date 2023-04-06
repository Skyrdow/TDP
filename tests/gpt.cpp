#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

void generate_combinations(int N, int D, int B, vector<int>& drivers, vector<int>& items, vector<unsigned int>& combinations, unsigned int current, int index) {
    if (index == D) {
        // Se han generado todas las combinaciones de los conductores
        combinations.push_back(current);
        return;
    }
    // Generar todas las combinaciones de items para el conductor actual
    for (int i = 0; i < (1 << B); i++) {
        unsigned int new_combination = current;
        for (int j = 0; j < B; j++) {
            if ((i & (1 << j)) && (index*B+j < N)) {
                new_combination |= (1 << (index*B+j));
            }
        }
        generate_combinations(N, D, B, drivers, items, combinations, new_combination, index+1);
    }
}

int main() {
    int N = 5; // Número total de objetos
    int D = 3; // Número de conductores
    int B = 2; // Tamaño del bote
    vector<int> drivers = {1, 2, 3}; // Conductores
    vector<int> items = {4, 5, 6, 7, 8}; // Items
    vector<unsigned int> combinations;
    generate_combinations(N, D, B, drivers, items, combinations, 0, 0);
    // Imprimir todas las combinaciones generadas
    for (int i = 0; i < combinations.size(); i++) {
        cout << "Combinacion " << i+1 << ": " << bitset<32>(combinations[i]) << endl;
    }
    return 0;
}
