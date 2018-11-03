#include <iostream>
#include "Tree.h"
#include <regex>

int main() {
    Tree* tree = new Tree();
    std::string exp = "a|bc.dr*";
    tree->create_tree(exp);
    tree->print_tree();
    delete tree;
    return 0;
}