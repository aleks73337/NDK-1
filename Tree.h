//
// Created by Alex on 10.09.2018.
//

#ifndef TEST_TREE_H
#define TEST_TREE_H

#include "Node.h"
#include <list>
#include <map>
#include <unordered_map>
#include <vector>

class Tree {

public:
    Tree();
    ~Tree();
    Node* top;
    bool create_tree(std::string exp);
    void print_tree();
    static std::list<Node*> nodes_ptr;
    void create_node_matrix();
    void make_dka();
	bool is_consists(std::string str, int pos = 0);

private:
    std::vector<int> move(char& symbol,int& start);
    std::vector<int> e_closure(std::vector<int>& starts);
    std::map<std::vector<int>,int> dka_nodes;
	std::multimap<int, std::pair<int, char>> accord; // from, to, token
    std::unordered_map<char, bool> values;
    char** nodes_matrix = nullptr;
    void add_vertex(Node* top, Node* parent);
    int  nBrack;
    bool reverce(std::string exp, Node* parent, Node* back_node);
    static int max_id;
};


#endif //TEST_TREE_H
