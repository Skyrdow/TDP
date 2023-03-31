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
    unsigned int driverCheck;
    unsigned int finalStateValue;

    int leftRestrictionCount;
    int rightRestrictionCount;
    unsigned int *leftRestrictionMatrix;
    unsigned int *rightRestrictionMatrix;

    AVL *openAVL;
    AVL *closedAVL;

    Operation **operationHeap;
    unsigned int operationTotal;
    unsigned int operationSize;

    RiverCrossing();
    ~RiverCrossing();

    void solve(const char *fileName);
    bool isFinalState(State *checkState);
    bool isValidState(unsigned int checkState);
    bool canMove(State *checkState, unsigned int move);
    

    void sortOperations();
    void printInfo();
    bool getProblemInfo(const char *fileName);
    void genOperations();
};