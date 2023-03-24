
class RiverCrossing
{
private:
    /* data */
public:
    int driverCount;
    int itemCount;
    int leftRestrictionCount;
    int **leftRestrictionMatrix;
    int **rightRestrictionMatrix;

    RiverCrossing();
    ~RiverCrossing();

    bool readProblemFile(const char *fileName);
    State *RiverCrossing::solve(const char *fileName);
};