#ifndef linkedlist_h
#define linkedlist_h

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};
typedef struct Node Node;

struct NodeMeta
{
    int data;
    int index;
};
typedef struct NodeMeta NodeMeta;

/*
Prints linked list
*/
void printList(Node *head);

/*
Prints meta-data array
*/
void printMetaArray(NodeMeta *list, int size);

/*
Insert new data node into linked list at the given index
*/
void insertKth(Node **list, int data, int index);

/*
Creates a new meta-data array using given integer list
[ind_1, data_1, ind_2, data_2, ..., ind_n, data_n]

size: Size of the given integer array = n*2
*/
NodeMeta *createNodeMetaArray(int size, int *metaData);

/*
Insert each item in metaDataArray to given linked list.
*/
void insertMetaToLinkedList(Node **head, NodeMeta *metaArray, int metaSize);

/*
Remove duplicates from given linked list.
*/
void removeDuplicates(Node **head);

#endif