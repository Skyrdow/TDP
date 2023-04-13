#include "Operation.h"

Operation::Operation(unsigned int num)
{
    this->rightSideCount = __builtin_popcount(num);
    this->result = num;
}

Operation::~Operation()
{
}
