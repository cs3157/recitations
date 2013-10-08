CC = gcc
CFLAGS = -Wall -g
LDFAGS = -g

pointerfun: 

pointerfun_clang: pointerfun.c
	clang $(CFLAGS) $(LDFLAGS) -o pointerfun_clang pointerfun.c

pointerfun.o: 

output: pointerfun
	./pointerfun > output


.PHONY: clean all valgrind
clean:
	rm -f *.o pointerfun

all: clean pointerfun pointerfun_clang

valgrind: pointerfun
	valgrind --leak-check=yes ./pointerfun
