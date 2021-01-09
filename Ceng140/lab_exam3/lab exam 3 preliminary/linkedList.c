#include "linkedList_copy.h"

void printList(Node *head){

    Node *temp = head;
    
    while (1){
        printf("%d",temp->data);
        
        if (temp->next != NULL){
            printf("->");
            temp = temp->next;
        }
        else{
            printf("\n");
            break;
        }    
    }
}

void insertEnd(Node** list, int data){

    Node *temp;

    if (*list == NULL){
        (*list) = (Node*)malloc(sizeof(Node));
        (*list)->data = data;
        (*list)->next = NULL;
    }
    else{
        temp = (*list);
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = (Node*)malloc(sizeof(Node));
        temp->next->data = data;
        temp->next->next = NULL;
    }
}

int occurrences(Node *head, int value){
    int number = 0;
    Node *temp = head;
    
    while (temp != NULL){
        if (temp->data == value){
            number ++;
        }
        temp = temp->next;
    }
    return number;
}

Node* removeNode(Node *head, int index){
    int i;
    Node *temp = NULL,*oldtemp = NULL;
    temp = head;

    if (index == 0){
        head = head->next;
    }
    else{
        for (i = 0; i < index; i++){
        oldtemp = temp;
        temp = temp->next;
        }
        oldtemp->next = temp->next;
    }
    free(temp);
    temp = NULL;
    
    return head;
}

Node* mergeLists(Node *list1, Node *list2){
    Node *temp1 =NULL,*temp2 = NULL,*newlist = NULL;
    temp1 = list1;
    temp2 = list2;

    while (1){
        if (temp1 == NULL && temp2 == NULL){
            break;
        }
        else if (temp1 == NULL){
            insertEnd(&newlist,temp2->data);
            temp2 = temp2->next;
        }
        else if (temp2 == NULL){
            insertEnd(&newlist,temp1->data);
            temp1 = temp1->next;
        }
        else if (temp1->data <= temp2->data){
            insertEnd(&newlist,temp1->data);
            temp1 = temp1->next;
        }
        else{
            insertEnd(&newlist,temp2->data);
            temp2 = temp2->next;
        }
    }
    return newlist;
}

Node* reverse(Node *head){
    Node *prev = NULL,*curr =NULL;
    if (head == NULL){
        return head;
    }
    prev = head;
    head = head->next;
    curr = head;
    prev->next = NULL;

    while (head != NULL){
        head = head->next;
        curr->next = prev;
        prev = curr;
        curr = head;
    }
    head = prev;
    return head;
}

int isPalindrome(Node *head){
    Node *curr1 = head;
    int data,j,i,size = 0;
    while (curr1 != NULL){
        size ++;
        curr1 = curr1->next;
    }

    for (i = 0; i < size/2; i++){
        curr1 = head;
        for (j = 0; j < size - i; j++){
            data = curr1->data;
            curr1 = curr1->next;
        }
        curr1 = head;
        for (j = 0; j < i; j++){
            curr1 = curr1->next;
        }
        if (curr1->data != data){
            return 0;
        }
    }
    return 1;
}

Node* insertionSort(Node *head){
    Node *sorted=NULL,*curr=head;
    int min,index=0,i;

    while (head != NULL){
        min = 999999;
        curr = head;
        for (i = 0; curr != NULL; i++){
            if (min > curr->data){
                min = curr->data;
                index = i;
            }
            curr = curr->next;
        }
        insertEnd(&sorted,min);
        head = removeNode(head,index);
    }
    return sorted;
}

