#include "Heap.h"

// Código entregado por el profesor en la tarea 1
// cambios:
// cambiar State por Nodo
// cambiar value por upper
// cambiar el heap de minimo a maximo

Heap::Heap(int capacity) {
    this->capacity = capacity;
    data = new Node*[capacity];
    size = 0;
}

Heap::~Heap() {
    delete[] data;
}

void Heap::swap(int i, int j) {
    Node *temp = data[i];
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

Node* Heap::pop() {
    if (size == 0) {
        return nullptr;
    }
    Node *s = data[0];
    data[0] = data[size-1];
    size--;
    heapify(0);
    return s;
}

void Heap::push(Node *s) {
    if (size == capacity) {
        Node **temp= new Node*[capacity*2];
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
        if (data[i]->upper > data[p]->upper) {
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
    int largest = i;
    if (l < size && data[l]->upper > data[i]->upper) {
        largest = l;
    }
    if (r < size && data[r]->upper > data[largest]->upper) {
        largest = r;
    }
    if (largest != i) {
        swap(i, largest);
        heapify(largest);
    }
}