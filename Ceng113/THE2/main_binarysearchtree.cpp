#include <iostream>

#include "BinarySearchTree.h"

int main() {
    std::cout << "-> Creating a binary search tree node." << std::endl;

    Node<int> node(10, NULL, NULL);

    std::cout << "-> Printing the node." << std::endl;

    std::cout << node << std::endl;

    std::cout << "-> Creating a binary search tree with default constructor." << std::endl;

    BinarySearchTree<int> tree;

    std::cout << "-> Making some insertions to the tree." << std::endl;

    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    std::cout << "-> Printing the tree." << std::endl;

    std::cout << tree << std::endl;
    std::cout << "----------------------------" << std::endl;
    BinarySearchTree<int> tree2(tree);
    std::cout << "-> Printing the tree2." << std::endl;
    std::cout << tree2 << std::endl;
    return 0;
}
