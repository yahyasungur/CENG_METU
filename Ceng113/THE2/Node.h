#ifndef NODE_H
#define NODE_H


// DO NOT CHANGE THIS FILE.

#include <ostream>

template<class T>
class Node {
public:
    T element;
    Node<T> *left;
    Node<T> *right;

    Node();
    Node(T element);
    Node(T element, Node<T> *left, Node<T> *right);

    friend std::ostream &operator<<(std::ostream &os, const Node &node) {

        os << "Node(" << node.element << ")";
        return os;
    }
};

template<class T>
Node<T>::Node() {
    this->left = NULL;
    this->right = NULL;
}

template<class T>
Node<T>::Node(T element) {
    this->element = element;
    this->left = NULL;
    this->right = NULL;
}

template<class T>
Node<T>::Node(T element, Node<T> *left, Node<T> *right) {
    this->element = element;
    this->left = left;
    this->right = right;
}


#endif //NODE_H
