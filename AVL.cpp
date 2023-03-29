#include <iostream>
#include "AVL.h"
using namespace std;

AVL::AVL()
{
    this->root = NULL;
}
int AVL::calheight(node *p)
{

    if (p->left && p->right)
    {
        if (p->left->height < p->right->height)
            return p->right->height + 1;
        else
            return p->left->height + 1;
    }
    else if (p->left && p->right == NULL)
    {
        return p->left->height + 1;
    }
    else if (p->left == NULL && p->right)
    {
        return p->right->height + 1;
    }
    return 0;
}

int AVL::bf(node *n)
{
    if (n->left && n->right)
    {
        return n->left->height - n->right->height;
    }
    else if (n->left && n->right == NULL)
    {
        return n->left->height;
    }
    else if (n->left == NULL && n->right)
    {
        return -n->right->height;
    }
    return 0;
}

node *AVL::llrotation(node *n)
{
    node *p;
    node *tp;
    p = n;
    tp = p->left;

    p->left = tp->right;
    tp->right = p;

    return tp;
}

node *AVL::rrrotation(node *n)
{
    node *p;
    node *tp;
    p = n;
    tp = p->right;

    p->right = tp->left;
    tp->left = p;

    return tp;
}

node *AVL::rlrotation(node *n)
{
    node *p;
    node *tp;
    node *tp2;
    p = n;
    tp = p->right;
    tp2 = p->right->left;

    p->right = tp2->left;
    tp->left = tp2->right;
    tp2->left = p;
    tp2->right = tp;

    return tp2;
}

node *AVL::lrrotation(node *n)
{
    node *p;
    node *tp;
    node *tp2;
    p = n;
    tp = p->left;
    tp2 = p->left->right;

    p->left = tp2->right;
    tp->right = tp2->left;
    tp2->right = p;
    tp2->left = tp;

    return tp2;
}

node *AVL::insert(node *r, State *data)
{

    if (r == NULL)
    {
        node *n;
        n = new node;
        n->data = data;
        r = n;
        r->left = r->right = NULL;
        r->height = 1;
        return r;
    }
    else
    {
        if (data->rightSide < r->data->rightSide)
            r->left = insert(r->left, data);
        else
            r->right = insert(r->right, data);
    }

    r->height = calheight(r);

    if (bf(r) == 2 && bf(r->left) == 1)
    {
        r = llrotation(r);
    }
    else if (bf(r) == -2 && bf(r->right) == -1)
    {
        r = rrrotation(r);
    }
    else if (bf(r) == -2 && bf(r->right) == 1)
    {
        r = rlrotation(r);
    }
    else if (bf(r) == 2 && bf(r->left) == -1)
    {
        r = lrrotation(r);
    }

    return r;
}

node *AVL::deleteNode(node *p, int data)
{

    if (p->left == NULL && p->right == NULL)
    {
        if (p == this->root)
            this->root = NULL;
        delete p;
        return NULL;
    }

    node *t;
    node *q;
    if (p->data->rightSide < data)
    {
        p->right = deleteNode(p->right, data);
    }
    else if (p->data->rightSide > data)
    {
        p->left = deleteNode(p->left, data);
    }
    else
    {
        if (p->left != NULL)
        {
            q = inpre(p->left);
            p->data = q->data;
            p->left = deleteNode(p->left, q->data->rightSide);
        }
        else
        {
            q = insuc(p->right);
            p->data = q->data;
            p->right = deleteNode(p->right, q->data->rightSide);
        }
    }

    if (bf(p) == 2 && bf(p->left) == 1)
    {
        p = llrotation(p);
    }
    else if (bf(p) == 2 && bf(p->left) == -1)
    {
        p = lrrotation(p);
    }
    else if (bf(p) == 2 && bf(p->left) == 0)
    {
        p = llrotation(p);
    }
    else if (bf(p) == -2 && bf(p->right) == -1)
    {
        p = rrrotation(p);
    }
    else if (bf(p) == -2 && bf(p->right) == 1)
    {
        p = rlrotation(p);
    }
    else if (bf(p) == -2 && bf(p->right) == 0)
    {
        p = llrotation(p);
    }

    return p;
}

node *AVL::inpre(node *p)
{
    while (p->right != NULL)
        p = p->right;
    return p;
}

node *AVL::insuc(node *p)
{
    while (p->left != NULL)
        p = p->left;

    return p;
}

bool AVL::search(node *n, int value)
{
    if (n == NULL)
        return false;
    int nodeVal = n->data->rightSide;
    if (nodeVal == value)
        return true;
    if (nodeVal > value)
        return search(n->left, value);
    if (nodeVal < value)
        return search(n->right, value);
    return false;
}

AVL::~AVL()
{
}

int main()
{

    AVL b;
    int c, x;


    do
    {

        State *a;
        cout << "\n1.Display levelorder on newline";
        cout << "\n2.Insert";
        cout << "\n3.Delete\n";
        cout << "\n0.Exit\n";
        cout << "\nChoice: ";

        cin >> c;

        switch (c)
        {
        case 1:
            b.levelorder_newline();
            // to print the tree in level order
            break;

        case 2:
            cout << "\nEnter no. ";
            cin >> x;
            a = new State(x, 10);
            b.root = b.insert(b.root, a);
            break;
        case 3:
            cout << "\nWhat to delete? ";
            cin >> x;
            b.root = b.deleteNode(b.root, x);
            break;
        case 4:
            cout << "\nWhat to search? ";
            cin >> x;
            cout << (b.search(b.root, x) ? "true" : "false");
            break;

        case 0:
            break;
        }

    } while (c != 0);
}