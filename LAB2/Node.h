#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>

class Node {

#define NUMBER 0
#define OPERATOR 1
#define VARIABLE 2
#define INVALID 3

public:
    Node();
    ~Node();
    int type;
    int getType();
    virtual void print() = 0;
    Node *parent;
    bool visited;
};

#endif
