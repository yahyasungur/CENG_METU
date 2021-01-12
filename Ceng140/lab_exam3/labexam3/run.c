#include <stdio.h>
#include <stdlib.h>
#include "linkedlist_copy.h"

int main(){
    /* You can test your functions in run.c */
    
    
    Node *list1 = NULL;
 	NodeMeta *metaArray;
	int meta[10] = {1, 1, 3, 40, 5, 60, 7, 80, 9, 100};

	insertKth(&list1, 1, 0);
	insertKth(&list1, 2, 1);
	insertKth(&list1, 2, 2);
	insertKth(&list1, 2, 3);
	insertKth(&list1, 3, 4);
	insertKth(&list1, 4, 5);
	insertKth(&list1, 5, 6);

	printList(list1);
    metaArray = createNodeMetaArray(10, meta);
	printMetaArray(metaArray, 5);

	insertMetaToLinkedList(&list1, metaArray, 5);
	printList(list1);

	removeDuplicates(&list1);
	printList(list1);
	
	return 0;
}