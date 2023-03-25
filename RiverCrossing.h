#include "State.h"
class RiverCrossing
{
private:
    /* data */
public:
    int driverCount;
    int itemCount;
    int boatCount;
    int leftRestrictionCount;
    int rightRestrictionCount;
    unsigned int *leftRestrictionMatrix;
    unsigned int *rightRestrictionMatrix;

    RiverCrossing();
    ~RiverCrossing();

    State *solve(const char *fileName);
    bool isValidState(State *state);
};