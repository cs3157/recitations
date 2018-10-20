CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -g

default: main leaky bad_access fgets

main: mymath.o

main.o: mymath.h

mymath.o: mymath.h

fgets: fgets.o

.PHONY: clean all valgrind
clean:
	rm -f *.o main a.out main leaky bad_access fgets

all: clean default 

valgrind: main
	valgrind --leak-check=full ./main
