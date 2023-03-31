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
    // revisar conductor
    
    cout << bitset<32>(checkState->rightSide) << "|";
    if (checkState->currentBoatSide == State::boatSide::right)
    {
    cout << bitset<32>(move) << endl;
    cout << (checkState->rightSide & move) << endl;
        move = ~move;
        if ((checkState->rightSide & move) == move)
            return true;
    }
    else if ((~(checkState->rightSide) & move) == move)
    {
    cout << (~checkState->rightSide & move) << endl;
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
    genOperations();
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
        cout << this->operationHeap[i]->result << " ";
        cout << s->rightSide << " ";
        cout << (s->rightSide & this->operationHeap[i]->result) << " ";
    cout << endl;
            if (canMove(s, this->operationHeap[i]->result))
            {
                State *s1 = s->boatMove(this->operationHeap[i]->result);
                if (!closedAVL->searchValue(s1->rightSide) && !this->openAVL->searchValue(s1->rightSide))
                    this->openAVL->push(s1);
            }
        }
    }
    cout << "No hay solucion" << endl;

}
