#include "BnB.h"
#include <ctime>

//! para imprimir linealmente reemplaza printAST por print_linear

/// @brief Programa principal que controla el menú
int main() {
    
    clock_t t_ini, t_fin;
    double secs=0;

	// Definiciones
	string nombreArchivo;
	int opcion;
	BnB *bnb = new BnB();
	char caracter;
	int numero;
	int cantidad;
	int sol;

	// Ciclo do while para el menú
    do {
        // Mostrar el menú
        cout << endl << "-----------------------------" << endl;
        cout << "Menú:\n";
        cout << "1. Cargar archivo\n";
        cout << "2. Resolver sin prints (mayor velocidad)\n";
        cout << "3. Salir\n";
        cout << "-----------------------------" << endl;

        // Leer la opción seleccionada
        cout << "Seleccione una opción: ";
        cin >> opcion;
		cin.ignore(); // Agregado para solucionar bug de entrada por consola
        // Realizar acciones según la opción seleccionada
        switch (opcion) {
            case 1:
				cout << "Ingrese el nombre del archivo: ";
				if (getline(cin, nombreArchivo));
				cout << "Cargando archivo: \n";
                t_ini = clock();
				bnb->solve(nombreArchivo.c_str(), 1);
                t_fin = clock();
                secs = secs + (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
                break;
            case 2:
				cout << "Ingrese el nombre del archivo: ";
				if (getline(cin, nombreArchivo));
				cout << "Cargando archivo: \n";
                for (int i = 0; i < 100; i++)
                {
                    t_ini = clock();
				    bnb->solve(nombreArchivo.c_str(), 0);
                    t_fin = clock();
                }
                secs = secs + (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
                
                cout << endl << "Tiempo promedio en 100 ejecuciones: " << secs/100 << " segundos" << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, seleccione una opción válida.\n";
                break;
        }

    } while (opcion != 2);

	delete(bnb);
    return 0;
}