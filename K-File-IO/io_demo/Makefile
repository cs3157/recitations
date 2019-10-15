CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -g

io_demo: io_demo.o io_tools.o

io_demo.o: io_tools.h

io_tools.o: io_tools.h

.PHONY: clean

clean: 
	rm -f io_demo myiofile *.o
