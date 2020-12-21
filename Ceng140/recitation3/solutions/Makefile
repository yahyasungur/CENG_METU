# compiler
CC=gcc
# compiler flags
CFLAGS=-Wall -ansi -pedantic-errors
# link/load flags ex: "-lm" for math.h
LDFLAGS=
all : ex1_while ex2_while ex3_for ex4_do-while ex5_nested-loops ex6_nested-loops2 
ex1_while :
	$(CC) $(CFLAGS) $(LDFLAGS) ex1_while.c -o ex1_while
ex2_while :
	$(CC) $(CFLAGS) $(LDFLAGS) ex2_while.c -o ex2_while
ex4_do-while :
	$(CC) $(CFLAGS) $(LDFLAGS) ex4_do-while.c -o ex4_do-while
ex5_nested-loops :
	$(CC) $(CFLAGS) $(LDFLAGS) ex5_nested-loops.c -o ex5_nested-loops
ex6_nested-loops2 :
	$(CC) $(CFLAGS) $(LDFLAGS) ex6_nested-loops2.c -o ex6_nested-loops2 -lm
clean:
	rm -f ex1_while ex2_while ex3_for ex4_do-while ex5_nested-loops ex6_nested-loops2
