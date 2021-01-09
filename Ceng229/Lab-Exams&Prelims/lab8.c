#include<stdio.h>
#include<stdlib.h>

#define SIZE 2000
#define WORDSIZE 20

char text[SIZE];
const char* helper;

void fillText();
void printText();
void countCharacters(int* charCountP);
void countWords(int* wordCountP);
int searchWord(char* searchedWordP, int* startP, int* endP);
void removeSpaces();
void runLab3();
char* word;

int main()
{
	word = (char*)malloc(WORDSIZE * sizeof(char));
	fillText();
	runLab3();	/* Uncomment this line when you complete your functions */
	//printText();
	return 0;
}

void runLab3()
{
	int wordCount = 0, characterCount = 0, startIndex, endIndex;
	scanf("%s", word);
	printText();
	countCharacters(&characterCount);
	countWords(&wordCount);
	printf("%d\n", characterCount);
	printf("%d\n", wordCount);
	if (searchWord(word, &startIndex, &endIndex))
		printf("%s %d %d\n", word, startIndex, endIndex);
	else
		printf("No result\n");
	removeSpaces();
	printText();
}

void countCharacters(int* charCountP)
{
	int i,count =0;
	for ( i = 0; i < SIZE,text[i] != '\n'; i++)
	{
		if (text[i] != ' ') count++;
	}
	*charCountP = count;
}

void countWords(int* wordCountP)
{
	int i, count=0, check=1;
	for ( i = 0; i < SIZE; i++)
	{
		if (text[i] == '\n') break;
		if (check == 1 && text[i] != ' ') {
			count++;
			check = 0;
		}
		if (text[i] == ' ') check = 1;
	}
	*wordCountP = count;
}

int searchWord(char* searchedWordP, int* startP, int* endP)
{
	int i, j,k=0;
	for (i = 0; searchedWordP[i] != 0; i++);

	for ( j = 0; j < SIZE; j++)
	{
		if (text[i] == '\n') break;
		if (k >= i) k = 0;
		if (text[j] == *(searchedWordP+k) && text[j-1-k] == ' ' )
		{
			k++;
			if ((text[j+1] == ' ' || text[j+1] == '.'|| text[j+1] == '\n' || text[j+1] == '\0' || text[j+1] == '?' || text[j+1] == '-' || text[j+1] == ',' || text[j+1] == '!') && searchedWordP[k] == 0) {
				*startP = j - i + 2;
				*endP = j+1;
				return 1;
			}
		}
	}
	return 0;
}

void removeSpaces()
{
	int i, j;
	for ( i = 0; i < SIZE-1; i++)
	{
		if (text[i] == ' ' && text[i + 1] == ' ') {
			for (j = i; j < SIZE-1 ; j++)
			{
				text[j] = text[j + 1];
			}
			i--;
		}
	}
}

void fillText()
{
	int i;
	helper = (char*)malloc(SIZE * sizeof(char));

	helper = "My         message is that we'll be watching you. This is all wrong. I shouldn't be up here. I should be back in school on the other side of the ocean. Yet you all come to us young people for hope. How dare you! You have stolen my dreams           and my childhood with your empty words. And yet I'm one of the lucky ones. People are suffering. People are dying. Entire ecosystems are         collapsing. \n";

	for (i = 0; ; i++)
	{
		text[i] = helper[i];
		if (helper[i] == '\n')
			break;
	}
}

void printText()
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		printf("%c", text[i]);
		if (text[i] == '\n')
			break;
	}
}