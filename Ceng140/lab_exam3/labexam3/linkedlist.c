#include "linkedlist_copy.h"

/*
Prints linked list
*/
void printList(Node *head){
    Node *temp = head;
    
    if (temp == NULL){
        return;
    }
    
    while (1){
        printf("%d",temp->data);
        
        if (temp->next != NULL){
            printf(" -> ");
            temp = temp->next;
        }
        else{
            printf("\n");
            break;
        }    
    }
}

/*
Prints meta-data array
*/
void printMetaArray(NodeMeta *list, int size){
    int i;
    for ( i = 0; i < size; i++){
        printf("Data: %d, Ind: %d\n",list[i].data,list[i].index);
    }
}

/*
Insert new data node into linked list at the given index
*/
void insertKth(Node **list, int data, int index){
    Node *temp = NULL,*oldtemp = NULL,*new = NULL,*tempsize = (*list);
    int i,size=0;
    
    while (tempsize != NULL){
        size++;
        tempsize = tempsize->next;
    }
    
    if (*list == NULL){
        (*list) = (Node*)malloc(sizeof(Node));
        (*list)->data = data;
        (*list)->next = NULL;
    }
    else if (index == 0){
        temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        temp->next = (*list);
        (*list) = temp;
    }
    else if (index >= size){
        temp = (*list);
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = (Node*)malloc(sizeof(Node));
        temp->next->data = data;
        temp->next->next = NULL;
    }
    else{
        temp = (*list);
        for ( i = 0; i < index; i++){
            oldtemp = temp;
            temp = temp->next;
        }
        new = (Node*)malloc(sizeof(Node));
        new->data = data;
        oldtemp->next = new;
        new->next = temp;
    }
}

/*
Creates a new meta-data array using given integer list
[ind_1, data_1, ind_2, data_2, ..., ind_n, data_n]

size: Size of the given integer array = n*2
*/
NodeMeta *createNodeMetaArray(int size, int *metaData){
    int i,j=0;
    NodeMeta *array = (NodeMeta*)malloc(sizeof(NodeMeta)*(size/2));
    
    for ( i = 0; i < size; i++){
        if (i%2 == 0){
            array[j].index = metaData[i];
        }
        else{
            array[j].data = metaData[i];
            j++;
        }
    }
    return array;
}

/*
Insert each item in meta-data array to given linked list.
*/
void insertMetaToLinkedList(Node **head, NodeMeta *metaArray, int metaSize){
    int i;
    for ( i = 0; i < metaSize; i++){
        insertKth(head,metaArray[i].data,metaArray[i].index);
    }
}

/*
Remove duplicates from given linked list.
*/
void removeDuplicates(Node **head){
    Node *oldtemp = NULL,*temp = NULL;
    oldtemp = (*head);
    temp = oldtemp->next;

    while (temp != NULL){
        
        if (oldtemp->data == temp->data){
            oldtemp->next = temp->next;
            free(temp);
            temp = NULL;
            oldtemp = (*head);
            temp = oldtemp->next;
        }
        else{
            temp = temp->next;
            oldtemp = oldtemp->next;
        }
    }
}