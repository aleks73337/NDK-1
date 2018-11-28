//
// Created by Alex on 10.09.2018.
//

#include "Tree.h"
#include <string>
#include <iostream>
#include <vector>
#include "stack"
#include "set"
#include "tuple"

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
int Tree::max_id = 0;

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
            top->set_value("E");
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
                top->set_value("E");
                Node *l_node = new Node("E");
                top->add_left(l_node);
                nodes_ptr.push_back(l_node);
                reverce(exp.substr(0, i), l_node, top);

				exp = exp.substr(i + 1, exp.length());
				if (exp.size() == 0)
					exp = "E";
                Node *r_node = new Node(exp);
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
    if (exp.empty())
    {
        top->id = ++id;
    }
    if (back_node != nullptr)
        top->add_left(back_node);
    if (top->id > max_id)
        max_id = top->id;
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
    Node* r_top = new Node("E");
    top->add_right(r_top);
    top->set_value("E");
    top->id = 0;
    if (!reverce(exp, r_top))
    {
        std::cout << "Wrong data";
    };
    return true;
}

void Tree::add_vertex(Node *top, Node* parent)
{
    static std::set<std::pair<int,int>> checked;
    if (checked.find(std::pair<int,int>(parent->id,top->id)) != checked.end())
        return;
    if (!top->get_value().empty())
    {
        nodes_matrix[parent->id][top->id] = top->get_value()[0];
        values.insert(std::pair<char, bool>(top->get_value()[0], true));
        checked.insert(std::pair<int,int>(parent->id,top->id));
    }
    else
    {
        nodes_matrix[parent->id][top->id] = ' ';
        checked.insert(std::pair<int,int>(parent->id,top->id));
    }
    Node* l_node = top->get_l_node();
    if (l_node != nullptr)
    {
        add_vertex(l_node, top);
    }
    Node* r_node = top->get_r_node();
    if (r_node != nullptr)
    {
        add_vertex(r_node, top);
    }
}

void Tree::create_node_matrix()
{
    nodes_matrix = new char* [max_id];
    for (int i = 0; i<=max_id; i++)
    {
        nodes_matrix[i] = new char [max_id];
        for (int j=0; j<=max_id; j++)
            nodes_matrix[i][j] = ' ';
    }

    add_vertex(top, top);
    std::cout << "  ";
    for (int i=0; i<=max_id; i++)
        std::cout << i << " ";
    std::cout << std::endl;
    for (int i = 0; i<= max_id; i++)
    {
        std::cout << i << " ";
        for (int j =0; j<=max_id; j++)
        {
            char val = nodes_matrix[i][j];
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int> Tree::move(char& symbol, int& start)
{
    std::vector<int> ways;
    for (int i=0; i <= max_id; i++)
    {
		if (nodes_matrix[start][i] == symbol && nodes_matrix[start][i] != 'E')
            ways.push_back(i);
    }
    return ways;
}

std::vector<int> Tree::e_closure(std::vector<int>& starts)
{
    std::vector<int> ways = starts;
	int size = ways.size();
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i <= max_id; i++)
        {
			if (nodes_matrix[ways[j]][i] == 'E')
			{
				ways.push_back(i);
				size = ways.size();
			}
        }
    }
    return ways;
}

void Tree::make_dka()
{
    int id = 0;
	std::vector<int> start = { 0 };
	dka_nodes.insert(std::pair< std::vector< int >, int >(start, id++));
	accord.insert(std::pair< int, std::pair < int, char > >(0, std::pair< int, char >(0,'E')));
	std::map<std::vector<int>, int>::iterator dka_end = dka_nodes.end();
	for (auto dka_it = dka_nodes.begin(); dka_it != dka_end; dka_it++)
	{
		for (auto node : dka_it->first)
		{
			for (auto pair : values) 
			{
				char letter_ = pair.first;
				std::vector<int> moves = move(letter_, node);
				std::vector<int> e_closures = e_closure(moves);
				if (dka_nodes.find(e_closures) == dka_nodes.end() && e_closures.size() != 0)
				{
					if (moves.size() != 0)
						accord.insert(std::pair<int, std::pair<int, char>>(dka_it->second, std::pair<int, char>(id, letter_)));
					else
						accord.insert(std::pair<int, std::pair<int, char>>(dka_it->second, std::pair<int, char>(id, 'E')));
					dka_nodes.insert(std::pair<std::vector<int>, int>(e_closures, id));
					id++;
				}
				else if (e_closures.size() != 0 && dka_nodes.find(e_closures) != dka_nodes.end())
				{
					int prev_id = dka_nodes.find(e_closures)->second;
					if (moves.size() != 0)
						accord.insert(std::pair<int, std::pair<int, char>>(dka_it->second, std::pair<int, char>(prev_id, letter_)));
					else
						accord.insert(std::pair<int, std::pair<int, char>>(dka_it->second, std::pair<int, char>(prev_id, 'E')));
				}
			}
		}
    }

	for (std::map<std::vector<int>, int>::iterator it = dka_nodes.begin(); it != dka_nodes.end(); it++)
	{
		std::cout << "id = " << it->second;
		for (int i = 0; i < it->first.size(); i++)
			 std::cout << "|| values = " << it->first[i];
		std::cout << std::endl;
	}

	for (std::multimap<int, std::pair<int, char>>::iterator it = accord.begin(); it != accord.end(); it++)
	{
		int from = it->first;
		int to = it->second.first;
		char token = it->second.second;

		std::cout << "From: " << from << " To: " << to << " Token: " << token << std::endl;
	}
}

bool Tree::is_consists(std::string str, int pos)
{
	if (str.size() == 0)
		return true;
	char token = str[0];
	str = str.substr(1, str.size() - 1);
	std::pair<std::multimap<int, std::pair<int, char>>::iterator, std::multimap<int, std::pair<int, char>>::iterator> range = accord.equal_range(pos);
	for (std::multimap<int, std::pair<int, char>>::iterator it = range.first; it != range.second; it++)
	{
		if (it->second.second == token)
		{
			if (is_consists(str, it->second.first))
				return true;
		}

	}
	return false;
}