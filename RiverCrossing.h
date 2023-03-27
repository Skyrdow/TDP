#include "State.h"
#include "Heap.h"
class RiverCrossing
{
private:
    /* data */
public:
    int driverCount;
    int itemCount;
    int boatSize;
    unsigned int finalStateValue;

    int leftRestrictionCount;
    int rightRestrictionCount;
    unsigned int *leftRestrictionMatrix;
    unsigned int *rightRestrictionMatrix;

    Heap *open;
    Heap *closed;

    RiverCrossing();
    ~RiverCrossing();

    void solve(const char *fileName);
    bool isFinalState(State *checkState);
    bool isValidState(State *checkState);
    bool canMove(State *checkState, int move);
    
    void calculateFinalState(int totalItemCount);
    void printInfo();
    bool getProblemInfo(const char *fileName);
};