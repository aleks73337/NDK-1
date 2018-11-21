//
// Created by Alex on 10.09.2018.
//

#include "Tree.h"
#include <string>
#include <iostream>
#include <vector>
#include "stack"

Tree::Tree() : top(new Node), nBrack(0)
{
};

Tree::~Tree()
{
    for (Node* node : nodes_ptr)
    {
        delete node;
    }
}

std::list<Node*> Tree::nodes_ptr;

void pre_pars(std::string &exp)
{
    for (int i = 0; i < exp.length()-1; ++i)
    {
        if (exp[i] != '*' && exp[i] != '|' && exp[i] != '.' && exp[i] != ')' && exp[i] != '(' && exp[i] != '-'
            &&  exp[i+1] != '*' && exp[i+1] != '|'  && exp[i+1] != ')' && exp[i+1] != '(' && exp[i+1] != '-')
            exp.insert(exp.begin()+i+1, '-');
        if (exp[i] == ')' && exp[i+1] != '*' && exp[i+1] != '*' && exp[i+1] != ')' && exp[i] != '|')
            exp.insert(exp.begin()+i+1, '-');
        if (exp[i+1] == '(' && exp[i] != '*' && exp[i] != '*' && exp[i] != ')' && exp[i] != '|' && exp[i] != '-')
            exp.insert(exp.begin()+i+1, '-');
    }
}

bool Tree::reverce(std::string exp, Node* top, Node* back_node = nullptr)
{
    static int id = 0;
    nBrack = 0;
    if (exp[0] == '(' && exp[exp.length()-1] == ')')
        exp = exp.substr(1, exp.length()-2);
    for (int i = 0; i <= exp.length(); ++i)
    {
        if (exp[i] == '(')
            nBrack++;
        else if (exp[i] == ')')
            nBrack--;
        if (exp[i] == '|' && nBrack == 0)
        {
            top->set_value("");
            top->id = ++id;
            Node* l_node = new Node(exp.substr(0, i));
            top->add_left(l_node);
            nodes_ptr.push_back(l_node);

            Node* r_node = new Node(exp.substr(i+1, exp.length()));
            top->add_right(r_node);
            nodes_ptr.push_back(r_node);

            reverce(l_node->get_value(), l_node, back_node);
            reverce(r_node->get_value(), r_node, back_node);
            return true;
        }
    }

    nBrack = 0;
    for (int i = 0; i <= exp.length(); ++i)
    {
        if (exp[i] == '(')
            nBrack++;
        else if (exp[i] == ')')
            nBrack--;
        if (nBrack == 0) {
            if (exp[i] == '.') {
                top->id = ++id;
                top->set_value(exp.substr(i, 1));

                Node *r_node = new Node(exp.substr(i + 1, exp.length()));
                top->add_right(r_node);
                nodes_ptr.push_back(r_node);

                reverce(r_node->get_value(), r_node, back_node);
                return true;
            } else if (exp[i] == '-') {
                top->id = ++id;
                top->set_value(exp.substr(i - 1, 1));

                Node *r_node = new Node(exp.substr(i + 1, exp.length()));
                top->add_right(r_node);
                nodes_ptr.push_back(r_node);

                reverce(r_node->get_value(), r_node, back_node);
                return true;
            } else if (exp[i] == '*') {
                top->id = ++id;
                top->set_value("");
                Node *l_node = new Node("");
                top->add_left(l_node);
                nodes_ptr.push_back(l_node);
                reverce(exp.substr(0, i), l_node, top);

                Node *r_node = new Node(exp.substr(i + 1, exp.length()));
                top->add_right(r_node);
                nodes_ptr.push_back(r_node);

                reverce(r_node->get_value(), r_node);
                return true;
            }
        }
    }

    if (exp.size() == 1)
    {
        top->id = ++id;
        top->set_value(exp);
    }
    if (back_node != nullptr)
        top->add_left(back_node);
    return true;
}

void Tree::print_tree()
{
    std::stack<Node*> node_stack;
    std::map<int, bool> out;
    int counter = 0;
    node_stack.push(top);
    std::cout << "id" << "    " << "value" << "    " <<"r-node" << "    " << "l-node" << std::endl;
    while( !node_stack.empty() && counter <= nodes_ptr.size())
    {
        Node* new_node = node_stack.top();
        node_stack.pop();
        while(true)
        {
            if (out.find(new_node->id) == out.end())
            {
                out.insert(std::pair<int, bool>(new_node->id, true));
                counter++;
                break;
            }
            else
            {
                new_node = node_stack.top();
                node_stack.pop();
            }
        }
        std::cout <<new_node->id << "       " << (new_node->get_value().empty() ? " ": new_node->get_value());
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

#include <map>
#include <vector>
std::map<int, std::vector<Node*>> dka_tree;

void make_dka(Node* top)
{
    static int id = 0;
    std::vector<Node*> vec;
    if (top->get_l_node()->get_value() == top->get_r_node()->get_value())
    {
        vec.push_back(top->get_l_node());
        vec.push_back(top->get_r_node());
        dka_tree.insert(std::pair<int,std::vector<Node*>>(id,vec));
    }

}