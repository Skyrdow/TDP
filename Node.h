#pragma once
#include "State.h"
class Node
{
private:
    /* data */
public:
    Node *left;
    State *data;
    int height;
    Node *right;
    Node();
    ~Node();
};