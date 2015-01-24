CC = gcc
CFLAGS = -Wall -g
LDFAGS = -g

jsh: 

jsh.o:

.PHONY: clean all valgrind
clean:
	rm -f *.o jsh 

all: clean jsh 

valgrind: jsh
	valgrind --leak-check=yes ./jsh
