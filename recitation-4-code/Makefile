CC = gcc
CFLAGS = -Wall -g
LDFAGS = -g

default: pointerfun converter

converter:

pointerfun: 

pointerfun_clang: pointerfun.c
	clang $(CFLAGS) $(LDFLAGS) -o pointerfun_clang pointerfun.c

pointerfun-output: pointerfun
	./pointerfun > pointerfun-output


.PHONY: clean all valgrind
clean:
	rm -f *.o pointerfun pointerfun_* converter

all: clean default pointerfun_clang

valgrind: pointerfun
	valgrind --leak-check=yes ./pointerfun
