CC=g++
CFLAGS=-c -ansi -Wall -pedantic-errors -O0

all: binarysearchtree bookcatalog

bookcatalog: main_bookcatalog.o book.o category.o bookcatalog.o
	$(CC) main_bookcatalog.o book.o category.o bookcatalog.o -o bookcatalog

binarysearchtree: main_binarysearchtree.o
	$(CC) main_binarysearchtree.o -o binarysearchtree

main_bookcatalog.o: main_bookcatalog.cpp
	$(CC) $(CFLAGS) main_bookcatalog.cpp -o main_bookcatalog.o

main_binarysearchtree.o: main_binarysearchtree.cpp
	$(CC) $(CFLAGS) main_binarysearchtree.cpp -o main_binarysearchtree.o

book.o: Book.cpp Book.h
	$(CC) $(CFLAGS) Book.cpp -o book.o

category.o: Category.cpp Category.h
	$(CC) $(CFLAGS) Category.cpp -o category.o

bookcatalog.o: BookCatalog.cpp BookCatalog.h BinarySearchTree.h Node.h Book.h Category.h
	$(CC) $(CFLAGS) BookCatalog.cpp -o bookcatalog.o

clean:
	rm *o
	rm binarysearchtree
	rm bookcatalog
