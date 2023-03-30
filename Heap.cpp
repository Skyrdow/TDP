#include "Heap.h"

Heap::Heap(int capacity) {
    this->capacity = capacity;
    data = new State*[capacity];
    size = 0;
}

Heap::~Heap() {
    delete[] data;
}

void Heap::swap(int i, int j) {
    State *temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

int Heap::left_idx(int i) {
    return 2*i + 1;
}

int Heap::right_idx(int i) {
    return 2*i + 2;
}

int Heap::parent_idx(int i) {
    return (i-1)/2;
}

State* Heap::pop() {
    if (size == 0) {
        return nullptr;
    }
    State *s = data[0];
    data[0] = data[size-1];
    size--;
    heapify(0);
    return s;
}

void Heap::push(State *s) {
    if (size == capacity) {
        State **temp= new State*[capacity*2];
        for(int i=0; i<size; i++){
            temp[i] = data[i]; 
        }
        delete[] data;
        data = temp;
        capacity = capacity*2;
    }
    data[size] = s;
    size++;
    int i = size-1;
    while (i > 0) {
        int p = parent_idx(i);
        if (data[i]->rightSide > data[p]->rightSide) {
            swap(i, p);
            i = p;
        } else {
            break;
        }
    }
}

void Heap::heapify(int i) {
    int l = left_idx(i);
    int r = right_idx(i);
    int biggest = i;
    if (l < size && data[l]->rightSide > data[i]->rightSide) {
        biggest = l;
    }
    if (r < size && data[r]->rightSide > data[biggest]->rightSide) {
        biggest = r;
    }
    if (biggest != i) {
        swap(i, biggest);
        heapify(biggest);
    }
}

bool Heap::isEmpty()
{
    if (this->size == 0)
        return true;
    return false;
}

bool Heap::search(int value)
{
    for (int i = 0; i < this->size; i++)
    {
        if (value == data[i]->rightSide)
            return true;
    }
    return false;
}