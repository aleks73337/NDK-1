#include <iostream>
#include "Tree.h"
#include <regex>

int main() {
    auto tree = new Tree();
    std::string exp = "ajsnd(d|s)*c|a(nsdf|sd)*";
    tree->create_tree(exp);
    tree->print_tree();
    delete tree;
    return 0;
}