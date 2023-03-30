#include "RiverCrossing.h"
#include "FileReader.h"
#include <iostream>
#include <bitset>

using namespace std;

// https://www.geeksforgeeks.org/cpp-program-for-quicksort/
int partition(Operation** arr, int start, int end)
{  
      // assuming last element as pivotElement
    int index = 0, pivotElement = arr[end]->rightSideCount, pivotIndex;
    Operation **temp = new Operation*[end - start + 1]; // making an array whose size is equal to current partition range...
    for (int i = start; i <= end; i++) // pushing all the elements in temp which are smaller than pivotElement
    {
        if(arr[i]->rightSideCount < pivotElement)
        {
            temp[index]->rightSideCount = arr[i]->rightSideCount;
            index++;
        }
    }
 
    temp[index]->rightSideCount = pivotElement; // pushing pivotElement in temp
    index++;
 
    for (int i = start; i < end; i++) // pushing all the elements in temp which are greater than pivotElement
    {
        if(arr[i]->rightSideCount > pivotElement)
        {
            temp[index] = arr[i];
            index++;
        }
    }
  // all the elements now in temp array are order :
  // leftmost elements are lesser than pivotElement and rightmost elements are greater than pivotElement
               
    index = 0;
    for (int i = start; i <= end; i++) // copying all the elements to original array i.e arr
    {  
        if(arr[i]->rightSideCount == pivotElement)
        {
              // for getting pivot index in the original array.
              // we need the pivotIndex value in the original and not in the temp array
            pivotIndex = i;
        }
        arr[i]->rightSideCount = temp[index]->rightSideCount;
        index++;
    }
    return pivotIndex; // returning pivotIndex
}
 
void quickSort(Operation** arr, int start, int end)
{ 
    if(start < end)
    {  
        int partitionIndex = partition(arr, start, end); // for getting partition
        quickSort(arr, start, partitionIndex - 1); // sorting left side array
        quickSort(arr, partitionIndex + 1, end); // sorting right side array
    }
    return;
}

RiverCrossing::RiverCrossing()
{
    // this->openHeap = new Heap(2);
    // this->closedAVL = new AVL();
}

void RiverCrossing::printInfo()
{
    cout<<"Restricciones Izq:"<<endl;
    for(int i = 0; i < this->leftRestrictionCount; i++)
    {
        std::bitset<MAX_BITSIZE> A = this->leftRestrictionMatrix[i]; 
        cout << A << endl;
    }
    cout << endl;

    cout<<"Restricciones Der:"<<endl;
    for(int i = 0; i < this->rightRestrictionCount; i++)
    {
        std::bitset<MAX_BITSIZE> A = this->rightRestrictionMatrix[i];
        cout << A << endl;
    }
    cout << endl;
}

void RiverCrossing::calculateFinalState(int totalItemCount)
{
    unsigned int finalState = 0;
    for (int i = 0; i < totalItemCount; i++)
    {
        finalState += 1 << i;
    }
    this->finalStateValue = finalState;
    bitset<MAX_BITSIZE> bitFinalState(finalState);
    cout << "Condición final: \n" << bitFinalState << endl << endl;
}

bool RiverCrossing::isFinalState(State *checkState)
{
    if (checkState->rightSide == this->finalStateValue)
        return true;
    return false;
}

bool RiverCrossing::isValidState(unsigned int checkState)
{
    for (int i = 0; i < this->leftRestrictionCount; i++)
    {
        if (checkState == this->leftRestrictionMatrix[i])
            return false;
    }
    for (int i = 0; i < this->rightRestrictionCount; i++)
    {
        if (checkState == this->rightRestrictionMatrix[i])
            return false;
    }
    return true;
}

bool RiverCrossing::canMove(State *checkState, unsigned int move)
{

    if (checkState->currentBoatSide == State::boatSide::left)
        move = ~move;
    
    if ((checkState->rightSide & move) == move)
    {
        return true;
    }
    return false;

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
        calculateFinalState(driverCount + itemCount);

        this->leftRestrictionCount = fr->readRestrictionSize();
        this->leftRestrictionMatrix = new unsigned int[this->leftRestrictionCount];
        fr->fillLeftMatrix(this->leftRestrictionMatrix, this->leftRestrictionCount);

        rightRestrictionCount = fr->readRestrictionSize();
        this->rightRestrictionMatrix = new unsigned int[this->rightRestrictionCount];
        fr->fillRightMatrix(this->rightRestrictionMatrix, this->rightRestrictionCount);
        
        printInfo();
        delete fr;
        return true;
    }
    delete fr;
    return false;
}

void RiverCrossing::genOperations()
{
    int operationTotal = 1 << this->totalItemCount;
    this->operationHeap = new Operation*[operationTotal];
    for (unsigned int i = 0; i < operationTotal; i++)
    {
        Operation *op = new Operation(0);
        this->operationHeap[i] = op;
        if (!isValidState(i))
            continue;
        op->rightSideCount = bitset<MAX_BITSIZE>(i).count();
        op->result = i;
    }
    quickSort(operationHeap, 0 , operationTotal);
    
}

void RiverCrossing::solve(const char *fileName)
{
    // leer el archivo, pasando las direcciones donde se almacenan las variables relevantes para el problema
    if (!getProblemInfo(fileName))
        return;
    // Estado [0, 0, 0, ..., 0]
    State *currentState = new State(this->totalItemCount);
    this->openHeap->push(currentState);
    while (!this->openHeap->isEmpty()) 
    {
        // State *s = this->operationHeap->pop()->result;
        // if (isFinalState(s)) {
        //     cout << "Solucion encontrada" << endl;
        //     s->print();
        //     return;
        // }
        // closedAVL->push(s);
        
        // if (canMove(s, 2)) {
        //     State *s1 = s->boatMove(nullptr, 0);
        //     if (!closedAVL->search(this->openAVL->root, s1->rightSide) && !this->openAVL->search(this->openAVL->root, s1->rightSide))
        //         this->openAVL->push(s1);
        // }
    }
    cout << "No hay solucion" << endl;

}
