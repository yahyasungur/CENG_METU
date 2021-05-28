#include <iostream>

#include "LinkedList.h"

int main() {
    std::cout << "-> Creating a linked list with default constructor." << std::endl;

    LinkedList<int> llist;

    std::cout << "-> Printing the list." << std::endl;

    llist.traverse();

    std::cout << "-> Making some insertions to the list." << std::endl;

    llist.insertAtTheEnd(1);
    llist.insertAtTheEnd(2);
    llist.insertAtTheEnd(3);
    llist.insertAtTheEnd(4);
    llist.insertAtTheEnd(5);

    std::cout << "-> Printing the list." << std::endl;

    llist.traverse();

    llist.deleteAllNodes();


    llist.swapNodes(llist.getNodeAtIndex(0),llist.getNodeAtIndex(1));
    llist.traverse();

    std::cout << "-> swapping-2" << std::endl;

    llist.swapNodes(llist.getNodeAtIndex(1),llist.getNodeAtIndex(2));
    llist.traverse();

    std::cout << "-> swapping-2" << std::endl;

    llist.swapNodes(llist.getNodeAtIndex(2),llist.getNodeAtIndex(3));
    llist.traverse();

    std::cout << "-> swapping-2" << std::endl;

    llist.swapNodes(llist.getNodeAtIndex(3),llist.getNodeAtIndex(4));
    llist.traverse();


    return 0;
}