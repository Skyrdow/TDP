#include "RiverCrossing.h"
#include "FileReader.h"
#include <iostream>
#include <bitset>

using namespace std;

// https://www.geeksforgeeks.org/cpp-program-for-quicksort/

unsigned int partition(Operation *arr[], unsigned int start, unsigned int end)
{

	Operation *pivot = arr[start];

	unsigned int count = 0;
	for (unsigned int i = start + 1; i <= end; i++) {
		if (arr[i]->rightSideCount <= pivot->rightSideCount)
			count++;
	}

	// Giving pivot element its correct position
	unsigned int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);

	// Sorting left and right parts of the pivot element
	unsigned int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (arr[i]->rightSideCount <= pivot->rightSideCount) {
			i++;
		}

		while (arr[j]->rightSideCount > pivot->rightSideCount) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
		}
	}

	return pivotIndex;
}

void quickSort(Operation *arr[], unsigned int start, unsigned int end)
{

	// base case
	if (start >= end)
		return;

	// partitioning the array
	unsigned int p = partition(arr, start, end);

	// Sorting the left part
	quickSort(arr, start, p - 1);

	// Sorting the right part
	quickSort(arr, p + 1, end);
}

void RiverCrossing::sortOperations()
{
    quickSort(this->operationHeap, 0, this->operationTotal-1);
}

RiverCrossing::RiverCrossing()
{
    this->openAVL = new AVL();
    this->closedAVL = new AVL();
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

bool RiverCrossing::isFinalState(State *checkState)
{
    if (checkState->rightSide == this->finalStateValue)
        return true;
    return false;
}

bool RiverCrossing::isValidState(unsigned int checkState)
{
    if (checkState == 15)
        cout << "asdasd";
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
    // revisar conductor, debe haber al menos 1
    if ((this->driverCheck & move) == 0);
        return false;

    if (checkState->currentBoatSide == State::boatSide::right)
    {
        move = ~move;
        if ((checkState->rightSide & move) == move)
            return true;
    }
    else if ((~(checkState->rightSide) & move) == move)
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
        
        this->finalStateValue = (1 << this->totalItemCount) - 1;
        
        // bitset<MAX_BITSIZE> bitFinalState(this->finalStateValue);
        // cout << "Condición final: \n" << bitFinalState << endl << endl;
        
        this->driverCheck = (1 << this->driverCount) - 1;

        this->leftRestrictionCount = fr->readRestrictionSize();
        this->leftRestrictionMatrix = new unsigned int[this->leftRestrictionCount];
        fr->fillLeftMatrix(this->leftRestrictionMatrix, this->leftRestrictionCount);

        rightRestrictionCount = fr->readRestrictionSize();
        this->rightRestrictionMatrix = new unsigned int[this->rightRestrictionCount];
        fr->fillRightMatrix(this->rightRestrictionMatrix, this->rightRestrictionCount);
        
        genOperations();
        
        printInfo();
        delete fr;
        return true;
    }
    delete fr;
    return false;
}

void RiverCrossing::genOperations()
{
    this->operationTotal = (1 << this->totalItemCount);
    this->operationSize = 0;
    this->operationHeap = new Operation*[operationTotal];
    for (unsigned int i = 0; i < operationTotal; i++)
    {
        Operation *op = new Operation();
        this->operationHeap[i] = op;
        if (!isValidState(i))
            continue;
        this->operationSize++;
        op->rightSideCount = bitset<MAX_BITSIZE>(i).count();
        op->result = i;
    }
    sortOperations();
}

void RiverCrossing::solve(const char *fileName)
{
    // leer el archivo, pasando las direcciones donde se almacenan las variables relevantes para el problema
    if (!getProblemInfo(fileName))
        return;
    // Estado [0, 0, 0, ..., 0]
    State *currentState = new State(this->totalItemCount);
    for (int i = 0; i < this->operationTotal; i++)
    {
        cout << this->operationHeap[i]->result << " ";
    }
    cout << endl;
    this->openAVL->push(currentState);
    while (!this->openAVL->isEmpty()) 
    {
        State *s = this->openAVL->pop();
        if (isFinalState(s)) {
            cout << "Solucion encontrada" << endl;
            s->print();
            return;
        }
        closedAVL->push(s);
        int bottomBound = this->operationTotal-this->operationSize;
        for (unsigned int i = this->operationTotal-1; bottomBound < i; i--)
        {
            // cout << "i:"  << i << endl;
            // cout << this->operationHeap[i]->result << " ";
            // cout << s->rightSide << " ";
            // cout << endl;
            if (canMove(s, this->operationHeap[i]->result))
            {
                // cout << bitset<32>(s->rightSide) << "|";
                // cout << bitset<32>(this->operationHeap[i]->result) << endl;
                State *s1 = s->boatMove(this->operationHeap[i]->result);
                // cout << bitset<32>(s1->rightSide) << "|";
                if (!closedAVL->searchValue(s1->rightSide) && !this->openAVL->searchValue(s1->rightSide))
                {
                    this->openAVL->push(s1);
                }
            }
        }
    }
    cout << "No hay solucion" << endl;

}
