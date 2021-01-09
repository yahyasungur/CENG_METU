#include <stdio.h>
#include <stdlib.h>
#include "linkedList_copy.h"

int main(){
    
    Node *list1 = NULL;
	Node *list2 = NULL;
	Node *list3 = NULL;
 	Node *palindromeList = NULL;
	Node *merged;

	insertEnd(&list1, 1);
	insertEnd(&list1, 2);
	insertEnd(&list1, 3);
	insertEnd(&list1, 4);
	insertEnd(&list1, 5);

	insertEnd(&list2, 2);
	insertEnd(&list2, 4);
	insertEnd(&list2, 6);
	
    insertEnd(&list3, 3);
	insertEnd(&list3, 7);
	insertEnd(&list3, 2);
	insertEnd(&list3, 4);
	insertEnd(&list3, 1);
	
	printf("List1: ");
	printList(list1);
	
	printf("List2: ");
	printList(list2);
	
	printf("List3: ");
	printList(list3);
    
    printf("#occurence of 4: %d\n", occurrences(list1, 4));

    list1 = removeNode(list1, 0);
    list1 = removeNode(list1, 2);
    printf("After removal: ");
    printList(list1); 
	
    merged = mergeLists(list1, list2);
    printf("Merged: ");
    printList(merged);

    printf("Reverse of merged: ");
    printList(reverse(merged));

    printf("Is palindrome: ");
    insertEnd(&palindromeList, 1);
	insertEnd(&palindromeList, 2);
	insertEnd(&palindromeList, 3);
	insertEnd(&palindromeList, 2);
	insertEnd(&palindromeList, 1);
    printList(palindromeList);
    if (isPalindrome(palindromeList)) printf("It is a palindrome.\n");
    else printf("It is not a palindrome.\n");

	printf("Sorted list 3: ");
	printList(insertionSort(list3));
    return 0;
}