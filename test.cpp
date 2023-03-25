#include "RiverCrossing.h"
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    RiverCrossing *r = new RiverCrossing();
    r->solve("test.txt");
    return 0;
}
