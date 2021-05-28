#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getDummyHead() const;
    Node<T> *getDummyTail() const;
    Node<T> *getActualHead() const;
    Node<T> *getActualTail() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheBeginning(const T &data);
    void insertAtTheEnd(const T &data);
    void insertBeforeGivenNode(const T &data, Node<T> *node);

    void deleteNode(Node<T> *node);
    void deleteNode(const T &data);
    void deleteAllNodes();

    void swapNodes(Node<T> *node1, Node<T> *node2);

    void traverse() const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *dummyHead;
    Node<T> *dummyTail;
};

template<class T>
LinkedList<T>::LinkedList() {
    dummyHead = new Node<T>;
    dummyTail = new Node<T>;
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
    /* TODO */
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    Node<T> *temp = obj.getActualHead();
    dummyHead = new Node<T>;
    dummyTail = new Node<T>;
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
    while (temp != obj.dummyTail){
        this->insertAtTheEnd(temp->data);
        temp = temp->next;
    }
    /* TODO */
}

template<class T>
LinkedList<T>::~LinkedList() {
    this->deleteAllNodes();
    delete this->dummyTail;
    delete this->dummyHead;
    /* TODO */
}

template<class T>
int LinkedList<T>::getSize() const {
    Node<T> * temp = this->dummyHead->next;
    int num = 0;
    while (temp != dummyTail){
        num++;
        temp = temp->next;
    }
    return num;
    /* TODO */
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    return this->dummyHead->next == this->dummyTail && dummyTail->prev == dummyHead;
    /* TODO */
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    Node<T> * temp = this->dummyHead->next;
    while (temp != dummyTail){
        if (temp == node && temp->next == node->next && temp->prev == node->prev){
            return true;
        }
        temp = temp->next;
    }
    return false;
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getDummyHead() const {
    return dummyHead;
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getDummyTail() const {
    return dummyTail;
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getActualHead() const {
    if (this->isEmpty()){
        return NULL;
    }
    return dummyHead->next;
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getActualTail() const {
    if (this->isEmpty()){
        return NULL;
    }
    return dummyTail->prev;
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    Node<T> *temp = dummyHead->next;
    while (temp != dummyTail){
        if (temp->data == data){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    Node<T> * temp = dummyHead;
    if (this->getSize() <= index || index < 0){
        return NULL;
    }
    for (int i = 0; i < index; i++){
        temp = temp->next;
    }
    return temp->next;
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtTheBeginning(const T &data) {
    Node<T> * newNode = new Node<T>(data);
    newNode->next = dummyHead->next;
    newNode->prev = dummyHead;
    newNode->prev->next = newNode;
    newNode->next->prev = newNode;
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    Node<T> * newNode = new Node<T>(data);
    newNode->prev = dummyTail->prev;
    newNode->next = dummyTail->prev->next;
    newNode->prev->next = newNode;
    newNode->next->prev = newNode;
    /* TODO */
}

template<class T>
void LinkedList<T>::insertBeforeGivenNode(const T &data, Node<T> *node) {
    if (this->contains(node) || node == this->dummyTail){
        Node<T> * newNode = new Node<T>(data);
        newNode->next = node;
        newNode->prev = node->prev;
        newNode->prev->next = newNode;
        newNode->next->prev = newNode;
    }
}

template<class T>
void LinkedList<T>::deleteNode(Node<T> *node) {
    Node<T> *temp = node;
    if (this->contains(node)){
        node->next->prev = node->prev;
        node->prev->next = node->next;
        delete temp;
    }
    /* TODO */
}

template<class T>
void LinkedList<T>::deleteNode(const T &data) {
    Node<T> *node = this->getNode(data),*temp = node;
    if (node != NULL){
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete temp;
    }
    /* TODO */
}

template<class T>
void LinkedList<T>::deleteAllNodes() {
    if (this->isEmpty()){
        return;
    }
    
    Node<T> *tempintempi = NULL,*temp = dummyHead->next;
    while (temp != dummyTail){
        tempintempi = temp->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        temp = tempintempi;
    }
    /* TODO */
}

template<class T>
void LinkedList<T>::swapNodes(Node<T> *node1, Node<T> *node2) {
    Node<T> *temp_next = NULL,*temp_prev = NULL;
    if (this->contains(node1) && this->contains(node2)){
        if (node1->next == node2 || node2->next == node1){
            node1->prev->next = node2;
            temp_prev = node1->prev;
            node1->prev = node2;
            node1->next->prev = temp_prev;
            node1->next = node2->next;
            node2->next->prev = node1;
            node2->next = node2->next->prev;
        }
        
        else{  
            node1->prev->next = node2;
            temp_prev = node1->prev;
            node1->prev = node2->prev;
            node1->next->prev = node2;
            temp_next = node1->next;
            node1->next = node2->next;
            node2->prev->next = node1;
            node2->next->prev = node1;
            node2->prev = temp_prev;
            node2->next = temp_next;
        }
        
        

    }
}

template<class T>
void LinkedList<T>::traverse() const {
    /* ALREADY IMPLEMENTED. DO NOT CHANGE. */

    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getActualHead();

    while (node && node->next) {
        std::cout << *node << std::endl;
        node = node->next;
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    if (this != &rhs){
        this->deleteAllNodes();
        const Node<T> *temp = rhs.getActualHead();

        while (temp != rhs.dummyTail){
            this->insertAtTheEnd(temp->data);
            temp = temp->next;
        }
        
    }
    return *this;
    /* TODO */
}

#endif //LINKEDLIST_H
