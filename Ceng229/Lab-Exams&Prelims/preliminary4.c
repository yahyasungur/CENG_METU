#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct book{
  char name[50];
  char writer[20];
  char genre[20];
  int year;
  int status;
};

int Num_books = 0;
struct book *Library;

void add_book(struct book new_book);
int reserve_book(char *book_name);
void return_book(char *book_name);

void print_book(struct book b){
  char *sn;
  char *delim=" ";
  sn = strtok(b.writer, delim);
  sn = strtok(NULL, delim);

  printf("%d %d %.3s.%.3s. %.3s. %s\n", b.status, b.year, sn, b.writer, b.genre, b.name);

}

int main(){
  int i;
  struct book nineteen_eighty_four = {"Nineteen Eighty-Four", "George Orwel", "Dystopia", 1949, 1};
  struct book fahrenheit_451 = {"Fahrenheit 451", "George Orwel", "Dystopia", 1953, 1};
  struct book animal_farm = {"Animal Farm", "George Orwel", "Dystopia", 1945, 1};
  struct book jane_eyre = {"Jane Eyre", "Charlotte Bronte", "Romantic", 1847, 1};
  struct book pride_and_prejudice = {"Pride and Prejudice", "Jane Austen", "Romantic", 1813, 1};
  struct book harry_potter = {"Harry Potter and the Philosopher's Stone", "Joanne Rowling", "Fantastic Fiction", 1997, 1};
  struct book lotr = {"Lord of the Rings The Fellowship of the Ring", "John Tolkien", "Fantastic Fiction", 1954, 1};

  add_book(nineteen_eighty_four);
  printf("%d\n", reserve_book("Animal Farm")); /* should print -1 */
  add_book(fahrenheit_451);
  add_book(animal_farm);
  add_book(jane_eyre);
  add_book(pride_and_prejudice);
  add_book(harry_potter);
  add_book(lotr);
  printf("%d\n", reserve_book("Animal Farm")); /* should print 1 */
  for(i = 0; i < Num_books; print_book(Library[i++]));
  return 0;

}


void add_book(struct book new_book){
  /* YOUR IMPLEMENTATION */

}

int reserve_book(char *book_name){
  /* YOUR IMPLEMENTATION */

}

void return_book(char *book_name){
  /* YOUR IMPLEMENTATION */
	
}
