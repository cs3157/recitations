
CC = gcc
CFLAGS = -g -Wall $(INCLUDES)

memory: memory.o mylist.o

mylist.o: mylist.c mylist.h

memory.o: memory.c mdb.h

clean:
	rm -f *.o memory a.out

val: memory
	valgrind --leak-check=yes ./memory