//
// Created by Alex on 10.09.2018.
//

#ifndef TEST_TREE_H
#define TEST_TREE_H

#include "Node.h"
#include <list>
#include <map>

class Tree {

public:
    Tree();
    ~Tree();
    Node* top;
    std::list<Node*> nodes_ptr;
    bool create_tree(std::string exp);
    void print_tree();
private:
    int  nBrack;
    bool reverce(std::string exp, Node* parent);
};


#endif //TEST_TREE_H
