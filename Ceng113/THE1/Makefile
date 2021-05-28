CC=g++
CFLAGS=-c -ansi -Wall -pedantic-errors -O0

all: linkedlist string

string: main_string.o string.o
	$(CC) main_string.o string.o -o string

linkedlist: main_linkedlist.o
	$(CC) main_linkedlist.o -o linkedlist

main_string.o: main_string.cpp
	$(CC) $(CFLAGS) main_string.cpp -o main_string.o

main_linkedlist.o: main_linkedlist.cpp
	$(CC) $(CFLAGS) main_linkedlist.cpp -o main_linkedlist.o

string.o: String.cpp String.h LinkedList.h Node.h
	$(CC) $(CFLAGS) String.cpp -o string.o

clean:
	rm *o
	rm linkedlist
	rm string
