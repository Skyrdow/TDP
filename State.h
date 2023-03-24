
class State
{
private:

public:
    enum class boatSide {left = 0, right = 1};
    boatSide currentBoatSide;
    int *rightSide; // se asigna memoria dinámicamente en el constructor
    int stateSize;
    State *previousState;

    State(int stateSize);
    State(int *right, int stateSize);
    State(int *right, int stateSize, boatSide newBoatSide);
    ~State();
    
    State *boatMove(int *movingArray, int arrLength);
    State *copy();

    void swapBoatSide();
};
