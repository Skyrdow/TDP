#include "AST.h"

//! para imprimir linealmente reemplaza printAST por print_linear

/// @brief Programa principal que controla el menú
int main() {
	// Definiciones
	string nombreCarpeta = "txts/";
	string nombreArchivo;
	int opcion;
	loadFile *lf = new loadFile();
	Node *root = nullptr;
	AST *ast = new AST();

	vector<char> vectorChar;
	vector<int> vectorInt;

	char caracter;
	int numero;
	int cantidad;

	// Ciclo do while para el menú
    do {
        // Mostrar el menú
        cout << endl << "-----------------------------" << endl;
        cout << "Menú:\n";
        cout << "1. Cargar archivo desde la carpeta txts\n";
        cout << "2. Evaluar\n";
        cout << "3. Evaluar con reemplazo de variables\n";
        cout << "4. Derivar\n";
        cout << "5. Salir\n";
        cout << "6. Simplicación de árbol de suma | sum_tree()\n";
        cout << "7. Evaluación simple | eval()\n";
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
				nombreArchivo = nombreCarpeta + nombreArchivo;
				root = lf->readfile(nombreArchivo.c_str());
				cout << "Archivo cargado: \n";
				ast->printAST(root);
                break;
            case 2:
				if (root == nullptr)
				{
					cout << "Ingrese primero una ecuación\n";
					break;
				}
                cout << "Evaluando: \n";
				root = ast->evaluate(root);
				ast->printAST(root);
                break;
            case 3:
				if (root == nullptr)
				{
					cout << "Ingrese primero una ecuación\n";
					break;
				}
                cout << "Cantidad de variables a reemplazar: ";
				cin >> cantidad;
				vectorChar.clear();
				vectorInt.clear();
				for (int i = 0; i < cantidad; i++)
				{
					cout << "Ingrese una variable: ";
					cin >> caracter;
					vectorChar.push_back(caracter);

					cout << "Ingrese un entero: ";
					cin >> numero;
					vectorInt.push_back(numero);
				}
                cout << "Evaluando: \n";
				root = ast->evaluate(root, vectorChar, vectorInt);
				ast->printAST(root);
                break;
            case 4:
				if (root == nullptr)
				{
					cout << "Ingrese primero una ecuación\n";
					break;
				}
                cout << "Ingrese la variable para derivar: ";
				cin >> caracter;
				root = ast->derive(root, caracter);
				ast->printAST(root);
                break;
            case 5:
				if (root == nullptr)
				{
					cout << "Ingrese primero una ecuación\n";
					break;
				}
                cout << "Saliendo del programa...\n";
				break;
			//! Opciones agregadas por falta de tiempo (informe)
			case 6:
                cout << "Evaluando: \n";
				root = ast->sum_tree(root);
				ast->printAST(root);
			break;
			case 7:
                cout << "Evaluando: \n";
				root = ast->eval(root);
				ast->printAST(root);
			break;
            default:
                cout << "Opción inválida. Por favor, seleccione una opción válida.\n";
                break;
        }

    } while (opcion != 5);

    return 0;
}