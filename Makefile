CC = gcc
CFLAGS = -Wall -g
LDFAGS = -g

pointerfun: 

pointerfun.o: 

output: pointerfun
	./pointerfun > output


.PHONY: clean all valgrind
clean:
	rm -f *.o pointerfun

all: clean pointerfun

valgrind: pointerfun
	valgrind --leak-check=yes ./pointerfun
