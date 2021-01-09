#ifndef linkedList_h
#define linkedList_h

#include "stdio.h"
#include "stdlib.h"

struct Node {
    int data;
    struct Node *next;
};
typedef struct Node Node;

void printList(Node*);
void insertEnd(Node** list, int data);
int occurrences(Node *head, int value);
Node* removeNode(Node *head, int index);
Node* mergeLists(Node *list1, Node *list2);
Node* reverse(Node *head);
int isPalindrome(Node *head);
Node* insertionSort(Node *head);

#endif