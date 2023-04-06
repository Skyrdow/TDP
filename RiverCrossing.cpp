#include <iostream>
#include <vector>
#include "RiverCrossing.h"
#include "FileReader.h"

using namespace std;

/// @brief Función para imprimir en binario un número entero sin signo
/// @param n número a imprimir
void RiverCrossing::printBits(unsigned int n) {
    char* p = (char*)&n;
    for (int i = 3; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            cout << ((*(p + i) >> j) & 1);
        }
    }
    cout << endl;
}

/// @brief Función que implementa el algoritmo de ordenamiento quicksort para un vector de objetos Operation.
/// @param arr arreglo/vector
/// @param left 
/// @param right 
void RiverCrossing::quicksort(std::vector<Operation *>arr, int left, int right) {
  int i = left, j = right;
  int pivot = arr[(left + right) / 2]->rightSideCount;

  while (i <= j) {
    while (arr[i]->rightSideCount < pivot)
    {
      i++;
    }

    while (arr[j]->rightSideCount > pivot) 
    {
      j--;
    }

    if (i <= j) 
    {
      swap(arr[i], arr[j]);
      i++;
      j--;
    }
  }

  if (left < j) { quicksort(arr, left, j); }

  if (i < right) { quicksort(arr, i, right); }
}

/// @brief Función envoltorio para quicksort
void RiverCrossing::sortOperations()
{
    quicksort(this->operationHeap, 0, this->operationHeap.size()-1);
}

/// @brief Constructor
RiverCrossing::RiverCrossing()
{
    this->openAVL = new AVL();
    this->closedAVL = new AVL();
}

/// @brief Destructor
RiverCrossing::~RiverCrossing()
{
    delete[](this->leftRestrictionMatrix);
    delete[](this->rightRestrictionMatrix);
    delete(this->openAVL);
    delete(this->closedAVL);
}

/// @brief Función que imprime en la salida estándar las matrices leftRestrictionMatrix y rightRestrictionMatrix
void RiverCrossing::printInfo()
{
    cout<<"Restricciones Izq:"<<endl;
    for(int i = 0; i < this->leftRestrictionCount; i++)
    {
        printBits(this->leftRestrictionMatrix[i]);
    }
    cout << endl;

    cout<<"Restricciones Der:"<<endl;
    for(int i = 0; i < this->rightRestrictionCount; i++)
    {
        printBits(this->rightRestrictionMatrix[i]);
    }
    cout << endl;
}

/// @brief Función que verifica si un estado checkState es el estado final del problema.
/// @param checkState Estado a revisar
/// @return true si la entrada es el estado final
bool RiverCrossing::isFinalState(State *checkState)
{
    if (checkState->rightSide == this->finalStateValue)
        return true;
    return false;
}

/// @brief Función que verifica si una operación realizada en un estado checkState es válida, es decir, si el conductor está presente y si el bote no excede su capacidad.
/// @param checkState Operación a revisar
/// @return true si la entrada es válida
bool RiverCrossing::isValidOperation(unsigned int checkState)
{
    // revisar conductor, debe haber al menos 1
    if ((this->driverCheck & checkState) == 0)
        return false;

    // revisar bote, contando los 1s del movimiento
    if (__builtin_popcount(checkState) > this->boatSize)
        return false;

    return true;
}

/// @brief Función que verifica si un estado checkState se le puede aplicar la operación move, respetando las restricciones del problema.
/// @param checkState Estado a revisar
/// @param move Operación a aplicar
/// @return true si se puede mover
bool RiverCrossing::canMove(State *checkState, unsigned int move)
{
    unsigned int leftSide = ~checkState->rightSide & this->finalStateValue; 
    unsigned int movedStateLeft;
    unsigned int movedStateRight;
    if (checkState->currentBoatSide == State::boatSide::right)
    {
        if ((checkState->rightSide & move) != move) { return false; }
        movedStateRight = checkState->rightSide & ~move;
        movedStateLeft = ~(checkState->rightSide & ~move) & this->finalStateValue;
    }
    if (checkState->currentBoatSide == State::boatSide::left)
    {
        if ((leftSide & move) != move) { return false; }
        movedStateLeft = leftSide & ~move;
        movedStateRight = ~(leftSide & ~move) & this->finalStateValue;
    }
    
    for (int i = 0; i < this->leftRestrictionCount; i++)
    {
        if (movedStateLeft == this->leftRestrictionMatrix[i]){
            return false;}
    }

    for (int i = 0; i < this->rightRestrictionCount; i++)
    {
        if (movedStateRight == this->rightRestrictionMatrix[i]){
            return false;}
    }
    return true;
}

/// @brief Función que recibe el nombre de un archivo de entrada y lee la información necesaria para resolver el problema
/// @param fileName Nombre del archivo
/// @return true si la lectura fue exitosa
bool RiverCrossing::getProblemInfo(const char *fileName)
{
    FileReader *fr = new FileReader();
    if (!fr->openFile(fileName))
    {
        delete fr;
        return false;
    }
    
    fr->readCountLine();

    this->driverCount = fr->getDriverCount();
    this->itemCount = fr->getItemCount();
    this->totalItemCount = driverCount + itemCount;
    this->boatSize = fr->getBoatSize();
    
    this->finalStateValue = (1 << this->totalItemCount) - 1;
    
    //! Lineas comentadas para evitar prints a consola y mejorar velocidad
    // cout << "Condición final: \n";
    // printBits(this->finalStateValue);
    // cout << endl;
    
    this->driverCheck = (1 << this->driverCount) - 1;

    this->leftRestrictionCount = fr->readRestrictionSize();
    this->leftRestrictionMatrix = new unsigned int[this->leftRestrictionCount];
    fr->fillRestrMatrix(this->leftRestrictionMatrix, this->leftRestrictionCount);

    rightRestrictionCount = fr->readRestrictionSize();
    this->rightRestrictionMatrix = new unsigned int[this->rightRestrictionCount];
    fr->fillRestrMatrix(this->rightRestrictionMatrix, this->rightRestrictionCount);
    
    genOperations();
    
    // printInfo();
    delete fr;
    return true;
}

/// @brief Generar las operaciones válidas
void RiverCrossing::genOperations()
{
    unsigned int operationTotal = (1 << this->totalItemCount);
    for (unsigned int i = 0; i < operationTotal; i++)
    {
        if (!isValidOperation(i))
            continue;
        Operation *op = new Operation();
        this->operationHeap.push_back(op);
        // contar los 1s que tiene la operación
        op->rightSideCount = __builtin_popcount(i);
        op->result = i;
    }
    sortOperations();
}

/// @brief Función principal que resuelve el problema
/// @param fileName Nombre del archivo que contiene la información del problema
void RiverCrossing::solve(const char *fileName)
{
    // leer el archivo
    if (!getProblemInfo(fileName))
        return;
    // Estado [0, 0, 0, ..., 0]
    State *currentState = new State(0, this->finalStateValue);
    // Lado inicial del bote derecho, ya que se invierte al inicio del loop
    State::boatSide side = State::boatSide::right;
    this->openAVL->insert(currentState);
    while (!this->openAVL->isEmpty()) 
    {
        if (side == State::boatSide::left)
            side = State::boatSide::right;
        else
            side = State::boatSide::left;

        State *s = this->openAVL->pop(side);

        if (isFinalState(s)) { return printFinalState(s); }

        closedAVL->insert(s);
        // recorrer el arreglo de ops desde el final
        for (int i = this->operationHeap.size()-1; 0 <= i; i--)
        {
            processState(s, this->operationHeap[i]->result);
        }
    }
    cout << "No hay solución" << endl;
}

/// @brief Imprime la solución al problema
/// @param final Estado final
void RiverCrossing::printFinalState(State *final)
{
    cout << "Solución encontrada:" << endl;
    final->print();
    return;
}

/// @brief Revisa si el estado se puede mover, y si ya existe en los AVL
/// @param state Estado a revisar
/// @param move Movimiento
void RiverCrossing::processState(State *state, unsigned int move)
{
    if (!canMove(state, move))
        return;

    State *s1 = state->boatMove(move);
    if (!closedAVL->search(s1) && !this->openAVL->search(s1))
    {
        this->openAVL->insert(s1);
    }
}