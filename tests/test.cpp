// #include "../RiverCrossing.h"
#include "../State.h"
#include "../Operation.h"
#include <string>
#include <bitset>
#include <iostream>

using namespace std;

int partition(Operation *arr[], int start, int end)
{

	Operation *pivot = arr[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i]->rightSideCount <= pivot->rightSideCount)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);

	// Sorting left and right parts of the pivot element
	int i = start, j = end;

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

void quickSort(Operation *arr[], int start, int end)
{

	// base case
	if (start >= end)
		return;

	// partitioning the array
	int p = partition(arr, start, end);

	// Sorting the left part
	quickSort(arr, start, p - 1);

	// Sorting the right part
	quickSort(arr, p + 1, end);
}

int main(int argc, char const *argv[])
{
    // RiverCrossing *r = new RiverCrossing();
    // r->solve("test.txt");

    int driver = 3;
    int item = 2;
    int totalItemCount = 3;
    int total = item+driver;

    int operationTotal = (1 << total) - 1;
    Operation **operationHeap = new Operation*[operationTotal];
    for (unsigned int i = 0; i < operationTotal; i++)
    {
        Operation *op = new Operation(0);
        op->result = i;
        op->rightSideCount = bitset<MAX_BITSIZE>(i).count();
        operationHeap[i] = op;
    }

    quickSort(operationHeap, 0 , operationTotal-1);
    
}
