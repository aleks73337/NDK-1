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
    bool create_tree(std::string exp);
    void print_tree();
    static std::list<Node*> nodes_ptr;
private:
    int  nBrack;
    bool reverce(std::string exp, Node* parent, Node* back_node);
};


#endif //TEST_TREE_H
