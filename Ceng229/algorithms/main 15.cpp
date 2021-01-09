#include<stdio.h>

int main  (){
	char text[256];
	FILE *filep = fopen("cdeneme.txt","a");
	
	if (filep == NULL){
		printf("basarisiz");
	}
	else{
	fgets(text,256,stdin);
	fputs(text,filep);
	printf("kralsin");
	fclose(filep);
	}
	getchar ();
	return 0;
}
