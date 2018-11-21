//
// Created by Alex on 20.11.2018.
//

#ifndef TEST_DK_TREE_H
#define TEST_DK_TREE_H

#include "Tree.h"
#include "Node.h"
#include <map>
#include <vector>

class DK_Tree : public Tree
{
public:

private:
    std::map<int, std::vector<Node*>> tree;
};


#endif //TEST_DK_TREE_H
