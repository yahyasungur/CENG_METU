#include <stdio.h>
#include <stdlib.h>
#include "linkedListDiff.h"
struct Node* createNode( int n){
    struct Node *newNode = malloc(sizeof(struct Node));
    if(newNode)
    {
	newNode->value = n;
        newNode->next = NULL;
    }
    return newNode;
}

int sizeofList(struct Node *head)
{
    int count;
    struct Node *curr;
    if(head==NULL)
        return 0;
    if(head->next==NULL)
        return 1;

    count=1;
    curr=head;
    while ( (curr = curr->next) != NULL )
        count++;

    return count;
}

void addNode(struct Node **head, int val){
    
    struct Node *newNode = createNode(val);
    struct Node *curr;

    if((*head)==NULL)
    {
        *head=newNode;
        (*head)->next=NULL;
    }
    
    else
    {
	curr = *head;
	while((curr->next)!=NULL)
	    curr=curr->next;
	curr->next=newNode;
    }   
}

void printList(struct Node *head)
{
    int listSize=sizeofList(head);
    
    int i;
    struct Node *curr;
    if(listSize==0)
    {
	printf("Nothing to print!\n");
	return;
    }
    
    curr=head;
    for(i=0;i<listSize;i++)
    {
        printf("%d ",curr->value);
	curr=curr->next;
    }
    printf("\n");
}


int main(){

    /* Do not change */
 
    struct Node *list1;
    struct Node *list2;
    struct Node *result;

    list1=list2=result=NULL;
    
    /*****************/

    addNode(&list1,10);
    addNode(&list1,43);
    addNode(&list1,20);
    addNode(&list1,30);
	
    addNode(&list2,20);
    addNode(&list2,40);
    
    /* Do not change */  

    result=getDifference(&list1,&list2);
    
    printList(list1);
    printList(list2);
    printList(result);

    /*****************/
    
    return 0;
}