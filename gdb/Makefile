CC = gcc
CFLAGS = -Wall -g
LDFAGS = -g

default: automated interactive leaky

automated: mymath.o

automated.o: mymath.h

interactive: mymath.o

interactive.o: mymath.h

.PHONY: clean all valgrind
clean:
	rm -f *.o automated a.out main interactive leaky

all: clean default 

valgrind: automated
	valgrind --leak-check=yes ./automated
