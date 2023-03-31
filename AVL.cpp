#include <iostream>
#include "AVL.h"
#include <queue>
#include <unordered_map>
using namespace std;

AVL::AVL()
{
    this->root = NULL;
}

AVL::~AVL()
{
}

int AVL::calheight(Node *p)
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

int AVL::bf(Node *n)
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

Node *AVL::llrotation(Node *n)
{
    Node *p;
    Node *tp;
    p = n;
    tp = p->left;

    p->left = tp->right;
    tp->right = p;

    return tp;
}

Node *AVL::rrrotation(Node *n)
{
    Node *p;
    Node *tp;
    p = n;
    tp = p->right;

    p->right = tp->left;
    tp->left = p;

    return tp;
}

Node *AVL::rlrotation(Node *n)
{
    Node *p;
    Node *tp;
    Node *tp2;
    p = n;
    tp = p->right;
    tp2 = p->right->left;

    p->right = tp2->left;
    tp->left = tp2->right;
    tp2->left = p;
    tp2->right = tp;

    return tp2;
}

Node *AVL::lrrotation(Node *n)
{
    Node *p;
    Node *tp;
    Node *tp2;
    p = n;
    tp = p->left;
    tp2 = p->left->right;

    p->left = tp2->right;
    tp->right = tp2->left;
    tp2->right = p;
    tp2->left = tp;

    return tp2;
}

Node *AVL::insert(Node *r, State *data)
{

    if (r == NULL)
    {
        Node *n;
        n = new Node;
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

void AVL::levelorder_newline()
{
    if (this->root == NULL)
    {
        cout << "\n"
             << "Empty tree"
             << "\n";
        return;
    }
    levelorder_newline(this->root);
}

void AVL::levelorder_newline(Node *v)
{
    queue<Node *> q;
    Node *cur;
    q.push(v);
    q.push(NULL);

    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        if (cur == NULL && q.size() != 0)
        {
            cout << "\n";

            q.push(NULL);
            continue;
        }
        if (cur != NULL)
        {
            cur->data->print();

            if (cur->left != NULL)
            {
                q.push(cur->left);
            }
            if (cur->right != NULL)
            {
                q.push(cur->right);
            }
        }
    }
}

Node *AVL::deleteNode(Node *p, int data)
{

    if (p->left == NULL && p->right == NULL)
    {
        if (p == this->root)
            this->root = NULL;
        // delete p;
        return NULL;
    }

    Node *t;
    Node *q;
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

/// @brief retorna el elemento max
Node *AVL::inpre(Node *p)
{
    while (p->right != NULL)
        p = p->right;
    return p;
}

/// @brief retorna el elemento min
Node *AVL::insuc(Node *p)
{
    while (p->left != NULL)
        p = p->left;

    return p;
}

bool AVL::searchValue(unsigned int value)
{
    return this->search(this->root, value);
}
bool AVL::search(Node *n, unsigned int value)
{
    if (n == NULL)
        return false;
    unsigned int nodeVal = n->data->rightSide;
    if (nodeVal == value)
        return true;
    if (nodeVal > value)
        return search(n->left, value);
    if (nodeVal < value)
        return search(n->right, value);
    return false;
}

bool AVL::isEmpty()
{
    if (this->root == NULL)
        return true;
    return false;
}

void AVL::push(State *insert)
{
    this->root = this->insert(this->root, insert);
}

void AVL::deleteState(unsigned int value)
{
    this->root = this->deleteNode(this->root, value);
}

State *AVL::pop()
{
    State *ret = this->inpre(this->root)->data;
    deleteState(ret->rightSide);
    return ret;
}