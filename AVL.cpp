#include "Node.h"
#include "AVL.h"
#include <iostream>

using namespace std;


Node* AVL::right_rotation(Node* p)
{
    Node* new_p = p->left_node_;
    p->left_node_ = new_p->right_node_;
    new_p->right_node_ = p;

    p->height_ = max(sub_tree_height(p->left_node_), sub_tree_height(p->right_node_));
    new_p->height_ = max(sub_tree_height(new_p->left_node_), sub_tree_height(new_p->right_node_));

    return new_p;
}

Node* AVL::left_rotation(Node* p)
{
    Node* new_p = p->right_node_;
    p->right_node_ = new_p->left_node_;
    new_p->left_node_ = p;

    p->height_ = max(sub_tree_height(p->left_node_), sub_tree_height(p->right_node_));
    new_p->height_ = max(sub_tree_height(new_p->left_node_), sub_tree_height(new_p->right_node_));

    return new_p;
}

Node* AVL::maximum_node_of_tree(Node* node)
{
    if(node->right_node_ == nullptr) return node;
    else return maximum_node_of_tree(node->right_node_);
}

unsigned int AVL::sub_tree_height(Node* node)
{
    return (node != nullptr)?node->height_ + 1:0;
}

Node* AVL::insert_(State *key, Node* node)
{
    if(node == nullptr)
    {
        return node = new Node(key);
    }

    if(key->rightSide < node->key_->rightSide) 
    {
        node->left_node_ = insert_(key, node->left_node_);
    }
    else if(key->rightSide > node->key_->rightSide) 
    {
        node->right_node_ = insert_(key, node->right_node_);
    }
    else if(node->key_->rightSide == key->rightSide) return node;

    int height_L = sub_tree_height(node->left_node_);
    int height_R = sub_tree_height(node->right_node_);

    node->height_ = max(height_L, height_R);
    
    int balance_factor = height_L - height_R;

    if(balance_factor > 1)//L
    {
        if(key->rightSide < node->left_node_->key_->rightSide)//L
        {
            return node = right_rotation(node);
        }
        else//R
        {
            node->left_node_ = left_rotation(node->left_node_);
            return node = right_rotation(node);
        }
    }
    else if(balance_factor < -1)//R
    {
        if(key->rightSide < node->right_node_->key_->rightSide)//L
        {
            node->right_node_ = right_rotation(node->right_node_);
            return node = left_rotation(node);
        }
        else//R
        {
            return node = left_rotation(node);
        }
    }

    return node;
}

Node* AVL::pop_(unsigned int key, Node* node)
{
    if(node == nullptr) return nullptr;

    if(key < node->key_->rightSide) 
    {
        node->left_node_ = pop_(key, node->left_node_);
    }
    else if(key > node->key_->rightSide) 
    {
        node->right_node_ = pop_(key, node->right_node_);
    }
    else //if(node->key_ == key) 
    {
        if(node->left_node_ == nullptr && node->right_node_ == nullptr)
        {
            delete node;
            return nullptr;
        }
        else if(node->left_node_ == nullptr && node->right_node_ != nullptr)
        {
            Node* sub_right_tree = node->right_node_;
            delete node;
            return sub_right_tree;
        }
        else if(node->left_node_ != nullptr && node->right_node_ == nullptr)
        {
            Node* sub_left_tree = node->left_node_;
            delete node;
            return sub_left_tree;
        }
        else            
        {
            Node* maxium_node_in_sub_left_tree = maximum_node_of_tree(node->left_node_);
            node->key_ = maxium_node_in_sub_left_tree->key_;
            node->left_node_ = pop_(maxium_node_in_sub_left_tree->key_->rightSide, node->left_node_);
        }
    }

    unsigned int height_L = sub_tree_height(node->left_node_);
    unsigned int height_R = sub_tree_height(node->right_node_);

    node->height_ = max(height_L, height_R);
    
    unsigned int balance_factor = height_L - height_R;

    if(balance_factor > 1)//L
    {
        if(sub_tree_height(node->left_node_->left_node_) > sub_tree_height(node->left_node_->right_node_))//L
        {
            return node = right_rotation(node);
        }
        else//R
        {
            node->left_node_ = left_rotation(node->left_node_);
            return node = right_rotation(node);
        }
    }
    else if(balance_factor < -1)//R
    {
        if(sub_tree_height(node->right_node_->left_node_) > sub_tree_height(node->right_node_->right_node_))//L
        {
            node->right_node_ = right_rotation(node->right_node_);
            return node = left_rotation(node);
        }
        else//R
        {
            return node = left_rotation(node);
        }
    }

    return node;
}

AVL::AVL()
{
    this->root_ = nullptr;
}

AVL::~AVL()
{

}

void AVL::insert(State *key)
{
    this->root_ = insert_(key, this->root_);
}

void AVL::deleteState(unsigned int key)
{
    this->root_ = pop_(key, this->root_);
}

State *AVL::pop()
{
    State *maxState = maximum_node_of_tree(this->root_)->key_;
    unsigned int max = maxState->rightSide;
    this->deleteState(max);
    return maxState;
}

bool AVL::search(Node *n, unsigned int value)
{
    if (n == nullptr)
        return false;
    unsigned int nodeVal = n->key_->rightSide;
    if (nodeVal == value)
        return true;
    if (nodeVal > value)
        return search(n->left_node_, value);
    if (nodeVal < value)
        return search(n->right_node_, value);
    return false;
}

bool AVL::searchValue(unsigned int value)
{
    return this->search(this->root_, value);
}

bool AVL::isEmpty()
{
    if (this->root_ == nullptr)
        return true;
    return false;
}