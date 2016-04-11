CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -g

fileio: fileio.o

.PHONY: all
all: clean fileio

.PHONY: clean
clean:
	rm -f *.o test test_fwrite test_fputs fileio

