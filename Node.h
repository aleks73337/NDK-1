//
// Created by Alex on 10.09.2018.
//

#ifndef TEST_NODE_H
#define TEST_NODE_H

#include <string>



class Node {
    std::string value;
    Node* l_node; // left node
    Node* r_node; // right node

public:
    int id;
    Node(std::string val);
    Node();
    void add_left(Node* node);
    void add_right(Node* node);
    std::string get_value();
    Node* get_l_node();
    Node* get_r_node();
    void set_value(std::string val);

};


#endif //TEST_NODE_H
