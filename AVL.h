#include "State.h"
struct node {
    struct node *left;
    State *data;
    int height;
    struct node *right;

};

class AVL
{
private:
    
public:
    node * root;
    AVL();
    ~AVL();
    int calheight(node *p);
    int bf(node *n);
    node *llrotation(node *n);
    node *rrrotation(node *n);
    node *rlrotation(node *n);
    node *lrrotation(node *n);
    node *insert(node *r, State *data);
    void levelorder_newline();
    void levelorder_newline(node *v);
    node *deleteNode(node *p, int data);
    node *inpre(node *p);
    node *insuc(node *p);
    bool search(node *n, int value);
};