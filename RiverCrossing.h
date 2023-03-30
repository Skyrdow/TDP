#pragma once
#include "State.h"
#include "Operation.h"
#include "Heap.h"
#include "AVL.h"
class RiverCrossing
{
private:
    /* data */
public:
    int driverCount;
    int itemCount;
    int totalItemCount;
    int boatSize;
    unsigned int finalStateValue;

    int leftRestrictionCount;
    int rightRestrictionCount;
    unsigned int *leftRestrictionMatrix;
    unsigned int *rightRestrictionMatrix;

    Heap *openHeap;
    AVL *closedAVL;

    Operation **operationHeap;

    RiverCrossing();
    ~RiverCrossing();

    void solve(const char *fileName);
    bool isFinalState(State *checkState);
    bool isValidState(unsigned int checkState);
    bool canMove(State *checkState, unsigned int move);
    
    void calculateFinalState(int totalItemCount);
    void printInfo();
    bool getProblemInfo(const char *fileName);
    void genOperations();
};