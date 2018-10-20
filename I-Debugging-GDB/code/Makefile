CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -g

default: main leaky bad_access fgets seg_fault

main: mymath.o

main.o: mymath.h

mymath.o: mymath.h

fgets: fgets.o

seg_fault: seg_fault.o

.PHONY: clean all valgrind
clean:
	rm -f *.o main a.out main leaky bad_access fgets seg_fault

all: clean default 

valgrind: main
	valgrind --leak-check=full ./main
