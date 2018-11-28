#include <iostream>
#include "Tree.h"

int main() {
    auto tree = new Tree();
    std::string exp = "abc(d|e)*";
    tree->create_tree(exp);
    tree->create_node_matrix();
    tree->make_dka();
	std::string str = "abcdededed";
	if (tree->is_consists(str))
		std::cout << std::endl << "Right!";
	else
		std::cout << std::endl << "Wrong :(";
	std::cin.get();
    return 0;
}