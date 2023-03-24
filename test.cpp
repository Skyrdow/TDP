#include "RiverCrossing.h"
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    string test = "test.txt";
    RiverCrossing *r = new RiverCrossing();
    r->readProblemFile(test.c_str());
    return 0;
}
