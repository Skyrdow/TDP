#pragma once
#include "Node.h"

class AVL
{
private:
    
public:
    Node * root;
    AVL();
    ~AVL();
    int calheight(Node *p);
    int bf(Node *n);
    Node *llrotation(Node *n);
    Node *rrrotation(Node *n);
    Node *rlrotation(Node *n);
    Node *lrrotation(Node *n);
    Node *insert(Node *r, State *data);
    void levelorder_newline();
    void levelorder_newline(Node *v);
    Node *deleteNode(Node *p, int data);
    Node *inpre(Node *p);
    Node *insuc(Node *p);

    void push(State *insert);
    void deleteState(unsigned int value);
    bool search(Node *n, unsigned int value);
    bool isEmpty();
};