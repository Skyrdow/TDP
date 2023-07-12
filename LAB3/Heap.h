#include <iostream>
#include "Node.h"
using namespace std;

// Código entregado por el profesor en la tarea 1
// cambios:
// cambiar State por Nodo
// cambiar value por upper

class Heap {
    public:
    Node **data;
    int size; // current size
    int capacity; // max size
    Heap(int capacity);
    ~Heap();
    void swap(int i, int j);
    int left_idx(int i);
    int right_idx(int i);
    int parent_idx(int i);
    Node* pop();
    void push(Node *s);
    void heapify(int i);
};