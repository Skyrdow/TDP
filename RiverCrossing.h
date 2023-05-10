#pragma once
#include "State.h"
#include "Operation.h"
#include "AVL.h"
#include <vector>
class RiverCrossing
{
private:
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

    std::vector<Operation *> operationVector;
    std::vector<Operation *> operationHeap;
    unsigned int operationIndex;

    void print32Bits(unsigned int n);

    bool isFinalState(State *checkState);
    bool isValidOperation(unsigned int checkState);
    bool canMove(State *checkState, unsigned int move);

    void printFinalState(State *final);
    void processState(State *state, unsigned int move);

    void printInfo();
    bool getProblemInfo(const char *fileName);
    
    void quicksort(std::vector<Operation *>arr, int start, int end);
    void sortOperations();
    void generateCombinations(std::vector<Operation *>& result, unsigned int current, int start, int end, int r);
    void genOperations();
public:
    RiverCrossing(const char *fileName);
    ~RiverCrossing();
    
    // si es true se usan prints
    bool print;

    void solve();
};