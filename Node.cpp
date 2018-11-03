//
// Created by Alex on 10.09.2018.
//

#include "Node.h"

Node::Node(std::string val) : value(val),
                                            l_node(nullptr),
                                            r_node(nullptr)
{};

Node::Node() : value(),
               l_node(nullptr),
               r_node(nullptr)
{};

void Node::add_left(Node *node)
{
    l_node = node;
}

void Node::add_right(Node *node)
{
    r_node = node;
}

Node* Node::get_l_node()
{
    return l_node;
}

Node* Node::get_r_node()
{
    return r_node;
}

std::string Node::get_value()
{
    return value;
}

void Node::set_value(std::string val)
{
    value = val;
}