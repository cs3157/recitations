CC = gcc
CFLAGS = -Wall -g
LDFAGS = -g

pointerfun: 

pointerfun_clang: pointerfun.c
	clang $(CFLAGS) $(LDFLAGS) -o pointerfun_clang pointerfun.c

pointerfun-output: pointerfun
	./pointerfun > pointerfun-output

pointerfun_16: pointerfun.c
	clang $(CFLAGS) $(LDFLAGS) -m16 -mtune=i386  pointerfun.c -o pointerfun_16

pointerfun_32: pointerfun.c
	gcc $(CFLAGS) $(LDFLAGS) -m32 pointerfun.c -o pointerfun_32

.PHONY: clean all valgrind
clean:
	rm -f *.o pointerfun pointerfun_*

all: clean pointerfun pointerfun_clang pointerfun_16 pointerfun_32

valgrind: pointerfun
	valgrind --leak-check=yes ./pointerfun
