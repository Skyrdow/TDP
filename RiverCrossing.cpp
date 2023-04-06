#include <iostream>
#include <bitset>
#include <vector>
#include "RiverCrossing.h"
#include "FileReader.h"

using namespace std;

void RiverCrossing::printBits(unsigned int n) {
    char* p = (char*)&n;
    for (int i = 3; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            cout << ((*(p + i) >> j) & 1);
        }
    }
    cout << endl;
}

void RiverCrossing::quicksort(std::vector<Operation *>arr, int left, int right) {
  int i = left, j = right;
  int pivot = arr[(left + right) / 2]->rightSideCount;

  while (i <= j) {
    while (arr[i]->rightSideCount < pivot) {
      i++;
    }

    while (arr[j]->rightSideCount > pivot) {
      j--;
    }

    if (i <= j) {
      swap(arr[i], arr[j]);
      i++;
      j--;
    }
  }

  if (left < j) {
    quicksort(arr, left, j);
  }

  if (i < right) {
    quicksort(arr, i, right);
  }
}

void RiverCrossing::sortOperations()
{
    quicksort(this->operationHeap, 0, this->operationHeap.size()-1);
}

RiverCrossing::RiverCrossing()
{
    this->openAVL = new AVL();
    this->closedAVL = new AVL();
}

// RiverCrossing::~RiverCrossing()
// {
//     delete[](this->operationHeap);
//     delete[](this->leftRestrictionMatrix);
//     delete[](this->rightRestrictionMatrix);
//     delete(this->openAVL);
//     delete(this->closedAVL);
// }

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

bool RiverCrossing::isFinalState(State *checkState)
{
    if (checkState->rightSide == this->finalStateValue)
        return true;
    return false;
}

bool RiverCrossing::isValidOperation(unsigned int checkState)
{
    // revisar conductor, debe haber al menos 1
    if ((this->driverCheck & checkState) == 0)
        return false;

    // revisar bote
    if (__builtin_popcount(checkState) > this->boatSize)
        return false;

    return true;
}

bool RiverCrossing::canMove(State *checkState, unsigned int move)
{
    unsigned int leftSide = ~checkState->rightSide & this->finalStateValue; 
    unsigned int movedStateLeft;
    unsigned int movedStateRight;
    if (checkState->currentBoatSide == State::boatSide::right)
    {
        if ((checkState->rightSide & move) != move){
            // cout << "No están los elementos der" << endl;
            // cout << bitset<MAX_BITSIZE>(checkState->rightSide) << "|"<< bitset<MAX_BITSIZE>(move) << endl;
            return false;}
        movedStateRight = checkState->rightSide & ~move;
        movedStateLeft = ~(checkState->rightSide & ~move) & this->finalStateValue;
    }
    if (checkState->currentBoatSide == State::boatSide::left)
    {
        if ((leftSide & move) != move){
            // cout << "No están los elementos izq" << endl;
            return false;}
        movedStateLeft = leftSide & ~move;
        movedStateRight = ~(leftSide & ~move) & this->finalStateValue;
    }
    
    for (int i = 0; i < this->leftRestrictionCount; i++)
    {
        if (movedStateLeft == this->leftRestrictionMatrix[i]){
            // cout << "Restricción" << endl;
            return false;}
    }

    for (int i = 0; i < this->rightRestrictionCount; i++)
    {
        if (movedStateRight == this->rightRestrictionMatrix[i]){
            // cout << "Restricción" << endl;
            return false;}
    }
    return true;
}

bool RiverCrossing::getProblemInfo(const char *fileName)
{
    FileReader *fr = new FileReader();
    if (fr->openFile(fileName))
    {
        fr->readCountLine();

        this->driverCount = fr->getDriverCount();
        this->itemCount = fr->getItemCount();
        this->totalItemCount = driverCount + itemCount;
        this->boatSize = fr->getBoatSize();
        
        this->finalStateValue = (1 << this->totalItemCount) - 1;
        
        cout << "Condición final: \n";
        printBits(this->finalStateValue);
        cout << endl;
        
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
    delete fr;
    return false;
}

void RiverCrossing::genOperations()
{
    unsigned int operationTotal = (1 << this->totalItemCount);
    for (unsigned int i = 0; i < operationTotal; i++)
    {
        if (!isValidOperation(i))
            continue;
        Operation *op = new Operation();
        this->operationHeap.push_back(op);
        // contar los 1s que tiene el número
        op->rightSideCount = __builtin_popcount(i);
        op->result = i;
    }
    sortOperations();
}

void RiverCrossing::solve(const char *fileName)
{
    // int iterations = 0;
    // leer el archivo, pasando las direcciones donde se almacenan las variables relevantes para el problema
    if (!getProblemInfo(fileName))
        return;
    // Estado [0, 0, 0, ..., 0]
    State *currentState = new State(0, this->finalStateValue);
    // for (int i = 0; i < operationIndex; i++)
    // {
    //     cout << operationHeap[i]->result << " ";
    // }
    // cout << endl;
    
    State::boatSide side = State::boatSide::right;
    this->openAVL->insert(currentState);
    while (!this->openAVL->isEmpty()) 
    {
        if (side == State::boatSide::left)
            side = State::boatSide::right;
        else
            side = State::boatSide::left;

        State *s = this->openAVL->pop(side);
        // cout << "Open->" << bitset<32>(s->rightSide).to_string() << endl;
        // cout << "Side->" << (int)s->currentBoatSide << endl;
        if (isFinalState(s)) 
        {
            cout << "Solución encontrada:" << endl;
            s->print();
            return;
        }
        closedAVL->insert(s);
        // recorrer el arreglo de ops desde el final
        for (int i = this->operationHeap.size()-1; 0 <= i; i--)
        {
            // cout << "probando operacion:"  << bitset<32>(this->operationHeap[i]->result) << endl;
            if (canMove(s, this->operationHeap[i]->result))
            {
                State *s1 = s->boatMove(this->operationHeap[i]->result);
                // cout << "operacion realizada-----: " << bitset<32>(s1->rightSide) << endl;
                if (!closedAVL->search(s1) && !this->openAVL->search(s1))
                {
                    this->openAVL->insert(s1);
                }
                // else
                    // cout << "ya está en los aVL"<< endl;
            }
        }
        // cout << endl;
        // iterations++;
    }
    cout << "No hay solución" << endl;
    // delete this->operationHeap._Destroy;
}
