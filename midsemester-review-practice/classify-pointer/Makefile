
CC = gcc
CFLAGS = -g -Wall $(INCLUDES)

classify: classify.o mylist.o

classify.o: classify.c mylist.h

mylist.o: mylist.c mylist.h

clean:
	rm -f *.o classify a.out

val: classify
	valgrind --leak-check=yes ./classify