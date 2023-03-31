#include "../RiverCrossing.h"
#include <string>
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char const *argv[])
{
	auto start = chrono::steady_clock::now();

    RiverCrossing *r = new RiverCrossing();
    r->solve("test.txt");
    //  Insert the code that will be timed

    auto end = chrono::steady_clock::now();

    // Store the time difference between start and end
    auto diff = end - start;
    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
}
