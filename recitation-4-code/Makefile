CC = gcc
CFLAGS = -Wall -g
LDFAGS = -g

pointerfun: 

pointerfun_clang: pointerfun.c
	clang $(CFLAGS) $(LDFLAGS) -o pointerfun_clang pointerfun.c

pointerfun-output: pointerfun
	./pointerfun > pointerfun-output


.PHONY: clean all valgrind
clean:
	rm -f *.o pointerfun pointerfun_clang

all: clean pointerfun pointerfun_clang

valgrind: pointerfun
	valgrind --leak-check=yes ./pointerfun
