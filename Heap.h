#pragma once
#include <iostream>
#include "State.h"
using namespace std;

class Heap {
    public:
    State **data;
    int size; // current size
    int capacity; // max size
    Heap(int capacity);
    ~Heap();
    void swap(int i, int j);
    int left_idx(int i);
    int right_idx(int i);
    int parent_idx(int i);
    State* pop();
    void push(State *s);
    void heapify(int i);
    bool isEmpty();
    bool search(int value);
};