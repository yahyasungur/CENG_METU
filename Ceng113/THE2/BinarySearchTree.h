#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


#include <iostream>
#include <stack>
#include <queue>

#include "Node.h"

template<class T>
class BinarySearchTree {
public: // DO NOT CHANGE THIS PART.
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T> &obj);

    ~BinarySearchTree();

    Node<T> *getRoot() const;

    void insert(const T &element);
    void remove(const T &element);
    Node<T> *find(const T &element);
    Node<T> *findWithoutOrderingProperty(const T &element);

    std::vector<Node<T> *> getListOfAllNodes();

    void depthFirstTraversal() const;
    void breadthFirstTraversal() const;

    template <class U>
    friend std::ostream &operator<<(std::ostream &os, const BinarySearchTree<U> &tree);
    template <class U>
    friend std::ostream &streamOutputOperatorHelper(std::ostream &os, Node<T> *node);

    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void remove2(const T &element){
        remove_helper(element,root);
    }

    void rm_all(Node<T> *root){
        if( root != NULL){
            rm_all(root->left);
            rm_all(root->right);
            remove2(root->element);
        }
    }

    void insert_helper(const T & x, Node<T> *& t){
        if(t == NULL){
            t = new Node<T>;
            t->element = x;
        }
        else if (x < t->element){
            insert_helper(x,t->left);
        }
        else if (x > t->element){
            insert_helper(x,t->right);
        }
    }

    Node<T> * find_min(Node<T> *t) const {
        if(t == NULL){
            return NULL;
        }
        if (t->left == NULL){
            return t;
        }
        return find_min(t->left);
    }

    void remove_helper(const T & x, Node<T> *& t) const {
        if(t == NULL){
            return;
        }
        if (x < t->element){
            remove_helper(x,t->left);
        }
        else if (x > t->element){
            remove_helper(x,t->right);
        }
        else if (t->left != NULL && t->right !=NULL){
            t->element = find_min(t->right)->element;
            remove_helper(t->element,t->right);
        }
        else{
            Node<T> * temp = t;
            t = ( t->left != NULL ) ? t->left : t->right;
            delete temp;
        }
    }

    void remove_helper2(const T & x, Node<T> *& t) const {
        if(t == NULL){
            return;
        }
        else if (x == t->element){
            if (t->left != NULL && t->right !=NULL){
                t->element = find_min(t->right)->element;
                remove_helper2(t->element,t->right);
            }
            else{
                Node<T> * temp = t;
                t = ( t->left != NULL ) ? t->left : t->right;
                delete temp;
            }
        }
        else{
            Node<T> * temp = preorder_traversal_find(x,t->left);

            if (temp == NULL){
                remove_helper2(x,t->right);
            }
            else{
                remove_helper2(x,t->left);
        }
        }

    }

    Node<T>* find_helper(const T & x, Node<T> *t )const{
        if( t == NULL ){
            return NULL;
        }
        else if( x < t->element ){
            return find_helper( x, t->left );
        }
        else if( t->element < x ){
            return find_helper( x, t->right );
        }
        else{
            return t;
        }
    }

    Node<T>* preorder_traversal_find(const T & x, Node<T> *t )const{
        if( t == NULL )
            return NULL;

        if(t->element == x){
            return t;
        }

        Node<T>* temp = preorder_traversal_find(x,t->left);

        if(temp == NULL){
            return preorder_traversal_find(x,t->right);  
        }
        else{
            return temp;
        }
    }

    void inorder_traversal(std::vector<Node<T>*> & k,Node<T> *&t){
        if(t == NULL){
            return;
        }
        inorder_traversal(k,t->left);
        k.push_back(t);
        inorder_traversal(k,t->right);
    }

private: // DO NOT CHANGE THIS PART.
    Node<T> *root;
};

template<class T>
BinarySearchTree<T>::BinarySearchTree() {
    root = NULL;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &obj) {
    root = NULL;
    if (this != &obj){
        if (obj.root == NULL){
            root = NULL;
        }
        
        std::queue<Node<T>*> q;
        q.push(obj.root);

        while (q.empty() == false){
            Node<T>* node = q.front();
            this->insert(node->element);
            q.pop();

            if(node->left){
                q.push(node->left);
            }
            if (node->right){
                q.push(node->right);
            }
        }
    }
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
    rm_all(root);
}

template<class T>
Node<T> *BinarySearchTree<T>::getRoot() const {
    return root;
}

template<class T>
void BinarySearchTree<T>::insert(const T &element) {
    insert_helper(element,root);
}

template<class T>
void BinarySearchTree<T>::remove(const T &element) {
    remove_helper2(element,root);
}

template<class T>
Node<T> *BinarySearchTree<T>::find(const T &element) {
    return find_helper(element,root);
}

template<class T>
Node<T> *BinarySearchTree<T>::findWithoutOrderingProperty(const T &element) {
    return preorder_traversal_find(element,root);
}

template<class T>
std::vector<Node<T> *> BinarySearchTree<T>::getListOfAllNodes() {
    std::vector<Node<T> *> k;
    inorder_traversal(k,root);
    return k;
}

template<class T>
void BinarySearchTree<T>::depthFirstTraversal() const {
    if (root == NULL) {
        std::cout << "BinarySearchTree()";
        return;
    }
    std::cout << "BinarySearchTree(\n";
    std::stack<Node<T>*> stck;
    stck.push(root);

    while (stck.empty() == false){
        if (stck.top() != root){
            std::cout << ", \n";
        }
        Node<T>* node = stck.top();
        std::cout << "Node(" << node->element << ")";
        stck.pop();

        if (node->right){
            stck.push(node->right);
        }
        if (node->left){
            stck.push(node->left);
        }
    }
    std::cout << "\n)" <<std::endl;

}

template<class T>
void BinarySearchTree<T>::breadthFirstTraversal() const {
    if (root == NULL) {
        std::cout << "BinarySearchTree()";
        return;
    }
    std::cout << "BinarySearchTree(\n";
    std::queue<Node<T>*> q;
    q.push(root);

    while (q.empty() == false){
        if (q.front() != root){
            std::cout << ", \n";
        }
        Node<T>* node = q.front();
        std::cout << "Node(" << node->element << ")";
        q.pop();

        if (node->left){
            q.push(node->left);
        }
        if (node->right){
            q.push(node->right);
        }
    }
    std::cout << "\n)\n";
}

template<class T>
std::ostream &operator<<(std::ostream &os, const BinarySearchTree<T> &tree) {

    // check if the tree is empty?
    if (tree.root == NULL) {
        os << "BinarySearchTree()";
        return os;
    }

    // recursively output the tree.
    os << "BinarySearchTree(" << "\n";
    streamOutputOperatorHelper(os, tree.root);
    os << "\n" << ")";

    return os;
}

template<class T>
std::ostream &streamOutputOperatorHelper(std::ostream &os, Node<T> *node) {

    // check if the node is NULL?
    if (node == NULL)
        return os;

    // outputing inorder.

    // first, output left subtree and comma (if needed).
    streamOutputOperatorHelper(os, node->left);
    if (node->left) {
        os << ", " << "\n";
    }

    // then, output the node.
    os << *node;

    // finally, output comma (if needed) and the right subtree.
    if (node->right) {
        os << ", " << "\n";
    }
    streamOutputOperatorHelper(os, node->right);

    return os;
}

template<class T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(const BinarySearchTree<T> &rhs) {
    if (this != &rhs){
        rm_all(root);

        if (rhs.root == NULL){
            root = NULL;
            return *this;
        }

        std::queue<Node<T>*> q;
        q.push(rhs.root);

        while (q.empty() == false){
            Node<T>* node = q.front();
            this->insert(node->element);
            q.pop();

            if(node->left){
                q.push(node->left);
            }
            if (node->right){
                q.push(node->right);
            }
        }
    }
    return *this;
}


#endif //BINARYSEARCHTREE_H
