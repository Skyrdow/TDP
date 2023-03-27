#include "RiverCrossing.h"
#include <string>
#include <bitset>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    RiverCrossing *r = new RiverCrossing();
    r->solve("test.txt");
    return 0;
}
