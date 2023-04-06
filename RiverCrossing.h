#pragma once
#include "State.h"
#include "Operation.h"
#include "AVL.h"
#include <vector>
class RiverCrossing
{
private:
    void quicksort(std::vector<Operation *>arr, int start, int end);
    void printBits(unsigned int n);

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

    std::vector<Operation *> operationHeap;
    unsigned int operationIndex;

    bool isFinalState(State *checkState);
    bool isValidOperation(unsigned int checkState);
    bool canMove(State *checkState, unsigned int move);

    void printFinalState(State *final);
    void processState(State *state, unsigned int move);

    void sortOperations();
    void printInfo();
    bool getProblemInfo(const char *fileName);
    void genOperations();
public:
    RiverCrossing();
    ~RiverCrossing();

    void solve(const char *fileName);
};