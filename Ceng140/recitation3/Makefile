# compiler
CC=gcc
# compiler flags
CFLAGS=-Wall -ansi -pedantic-errors
# link/load flags ex: "-lm" for math.h
LDFLAGS=
all : ex1_while ex2_while ex3_for ex4_do-while ex5_nested-loops ex6_nested-loops2 ex7_call-by-value ex8_scope ex9_scope first-loop switch-case break
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
ex7_call-by-value :
	$(CC) $(CFLAGS) $(LDFLAGS) ex7_call-by-value.c -o ex7_call-by-value
ex8_scope :
	$(CC) $(CFLAGS) $(LDFLAGS) ex8_scope.c -o ex8_scope
ex9_scope:
	$(CC) $(CFLAGS) $(LDFLAGS) ex9_scope.c -o ex9_scope
first-loop :
	$(CC) $(CFLAGS) $(LDFLAGS) first-loop.c -o first-loop
switch-case :
	$(CC) $(CFLAGS) $(LDFLAGS) switch-case.c -o switch-case
break :
	$(CC) $(CFLAGS) $(LDFLAGS) break.c -o break -lm
clean:
	rm -f ex1_while ex2_while ex3_for ex4_do-while ex5_nested-loops ex6_nested-loops2 ex7_call-by-value ex8_scope ex9_scope first-loop switch-case break
