# TDP
#include <iostream>
#include <vector>

using namespace std;

// Función para generar todas las combinaciones de tamaño 'size'
// de un vector 'arr' empezando en la posición 'start'
vector<vector<int>> generate_combinations(vector<int>& arr, int size, int start) {
    vector<vector<int>> result;
    if (size == 0) {
        result.push_back({});
        return result;
    }
    for (int i = start; i <= arr.size() - size; i++) {
        for (auto&& comb : generate_combinations(arr, size - 1, i + 1)) {
            comb.insert(comb.begin(), arr[i]);
            result.push_back(comb);
        }
    }
    return result;
}

int main() {
    int N = 10; // Número máximo en el arreglo
    int D = 3; // Cantidad de conductores
    int I = 5; // Cantidad de items
    int B = 7; // Tamaño del bote
    
    // Crear el arreglo de números
    vector<int> nums(N + 1);
    for (int i = 0; i <= N; i++) {
        nums[i] = i;
    }
    
    // Generar todas las combinaciones de conductores e items
    vector<vector<int>> drivers_items_combinations;
    for (int num_drivers = 1; num_drivers <= D; num_drivers++) {
        for (int num_items = 0; num_items <= I; num_items++) {
            if (num_drivers + num_items <= B) {
                auto drivers_combinations = generate_combinations(nums, num_drivers, 0);
                auto items_combinations = generate_combinations(nums, num_items, 0);
                for (auto&& drivers : drivers_combinations) {
                    for (auto&& items : items_combinations) {
                        if (!items.empty() || !drivers.empty()) {
                            drivers.insert(drivers.end(), items.begin(), items.end());
                            drivers_items_combinations.push_back(drivers);
                        }
                    }
                }
            }
        }
    }
    
    // Imprimir las combinaciones generadas
    for (auto&& comb : drivers_items_combinations) {
        for (auto&& elem : comb) {
            cout << elem << " ";
        }
        cout << endl;
    }
    
    return 0;
}
