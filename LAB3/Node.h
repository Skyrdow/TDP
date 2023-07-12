#include "Simplex.h"
class Node
{
private:
    /* data */
public:
    Node(Simplex *simplex, float lower);
    ~Node();
    Simplex *simplex;
    float lower;
    float upper;
};
