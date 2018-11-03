//
// Created by Alex on 10.09.2018.
//

#include "Tree.h"
#include <string>
#include <iostream>
#include "stack"

Tree::Tree() : top(new Node), nBrack(0)
{};

Tree::~Tree()
{
    for (Node* node : nodes_ptr)
    {
        delete node;
    }
}

void pre_pars(std::string &exp)
{
    for (int i = 0; i < exp.length()-1; ++i)
    {
        if (exp[i] != '*' && exp[i] != '|' && exp[i] != '.' && exp[i] != ')' && exp[i] != '(' && exp[i] != '-'
            &&  exp[i+1] != '*' && exp[i+1] != '|' && exp[i+1] != '.' && exp[i+1] != ')' && exp[i+1] != '(' && exp[i+1] != '-')
            exp.insert(exp.begin()+i+1, '-');
    }
}

bool Tree::reverce(std::string exp, Node* top)
{
    static int id = 0;
    for (int i = 0; i <= exp.length(); ++i)
    {
        if (exp[i] == '|')
        {
            Node* l_node = new Node(exp.substr(0, i));
            top->add_left(l_node);
            nodes_ptr.push_back(l_node);

            Node* r_node = new Node(exp.substr(i+1, exp.length()));
            top->add_right(r_node);
            nodes_ptr.push_back(r_node);

            reverce(l_node->get_value(), l_node);
            reverce(r_node->get_value(), r_node);
            return true;
        }
    }

    for (int i = 0; i <= exp.length(); ++i)
    {
        if (exp[i] == '.')
        {
            top->set_value(exp.substr(i-1,1));
            top->id = ++id;
            Node* l_node = new Node(exp.substr(i,1));
            l_node->id = ++id;
            top->add_left(l_node);
            nodes_ptr.push_back(l_node);

            Node* r_node = new Node(exp.substr(i+1, exp.length()));
            top->add_right(r_node);
            nodes_ptr.push_back(r_node);

            reverce(r_node->get_value(), r_node);
            return true;
        }
        else if (exp[i] == '-')
        {
            top->id = ++id;
            top->set_value(exp.substr(i-1,1));

            Node* r_node = new Node(exp.substr(i+1, exp.length()));
            top->add_right(r_node);
            nodes_ptr.push_back(r_node);

            reverce(r_node->get_value(), r_node);
            return true;
        }
        else if (exp[i] == '*')
        {
            top->id = ++id;
            top->set_value(exp.substr(i-1, 1));
            top->add_left(top);

            Node* r_node = new Node(exp.substr(i+1, exp.length()));
            top->add_right(r_node);
            nodes_ptr.push_back(r_node);

            reverce(r_node->get_value(), r_node);
            return true;
        }
    }

    top->id = ++id;
    return true;
}

void Tree::print_tree()
{
    std::stack<Node*> node_stack;
    node_stack.push(top);
    std::cout << "id" << "    " << "value" << "    " <<"r-node" << "    " << "l-node" << std::endl;
    while( !node_stack.empty() )
    {
        Node* new_node = node_stack.top();
        node_stack.pop();
        std::cout <<new_node->id << "       " << new_node->get_value();
        if (new_node->get_r_node() != nullptr)
        {
            node_stack.push(new_node->get_r_node());
            std::cout << "       " << new_node->get_r_node()->id;
        }
        if (new_node->get_l_node() != nullptr && new_node != new_node->get_l_node())
        {
            node_stack.push(new_node->get_l_node());
            std::cout << "       " << new_node->get_l_node()->id;
        }
        if (new_node == new_node->get_l_node())
        {
            std::cout << "       " << new_node->get_l_node()->id;
        }
        std::cout << std::endl;
    }
}

bool Tree::create_tree(std::string exp)
{
    pre_pars(exp);
    if (!reverce(exp, top))
    {
        std::cout << "Wrong data";
    };
    return true;
}