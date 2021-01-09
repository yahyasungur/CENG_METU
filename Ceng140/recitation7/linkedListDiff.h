#ifndef LINKEDLISTDIFF_H
#define LINKEDLISTDIFF_H

struct Node {
    int value;
    struct Node *next;
};

struct Node* createNode( int n);

void addNode(struct Node **head, int val);

void printList(struct Node *head);

struct Node *getDifference(struct Node **list1, struct Node **list2);

#endif
