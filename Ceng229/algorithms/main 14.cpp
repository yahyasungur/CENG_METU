#include<stdio.h>

struct student {
	char lastname[25];
	char surname[25];
	
	int age;
	int studentnumber;
};

int main(){
	
	struct student Yahya = {"YAHYA","SUNGUR",19,2375723}; 
	
	printf(" %s  %s \n Age: %d Student Number: %d",Yahya.lastname,Yahya.studentnumber,Yahya.age,Yahya.studentnumber);
	printf("Ali");
	
	
	
	
	
	getchar();
	return 0;
}
