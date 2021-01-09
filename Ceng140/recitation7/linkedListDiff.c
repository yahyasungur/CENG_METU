#include <stdlib.h>
#include "linkedListDiff.h"
#include <stdio.h>

struct Node *getDifference(struct Node **list1, struct Node **list2){
    struct Node *diff_list = NULL;
    struct Node *curr1,*curr2;
    int check = 0;

    curr1 = (*list1);
    while(curr1 != NULL){
        curr2 = (*list2);
        check = 1;
        while (curr2 != NULL){
            if (curr2->value == curr1->value){
                check = 0;
                break;
            }
            curr2 = curr2->next;
        }
        if (check){
            addNode(&diff_list,curr1->value);
        }
        
        curr1 = curr1->next;
    }
    return diff_list;
}