CC = gcc
CFLAGS = -Wall -g
LDFAGS = -g

main: 

main.o:

.PHONY: clean all valgrind
clean:
	rm -f *.o main a.out

all: clean main 

valgrind: main
	valgrind --leak-check=yes ./main
