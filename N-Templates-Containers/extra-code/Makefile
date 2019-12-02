CC = g++
CXX = g++
CFLAGS = -g -Wall 
CXXFLAGS = -std=c++11 -g -Wall
LDFLAGS = -g

.PHONY: default

default: test_vector test_mylist test_list test_myadd

test_vector:

test_vector.o: vector.h

test_list:

test_myadd:

test_mylist: test_mylist.o mylist.o
	gcc $(LDFLAGS) test_mylist.o mylist.o -o test_mylist

test_mylist.o: test_mylist.c mylist.h
	gcc -c $(CFLAGS) test_mylist.c -o test_mylist.o 

mylist.o: mylist.c mylist.h
	gcc -c $(CFLAGS) -o mylist.o mylist.c

.PHONY: clean

clean:
	rm -f *.o test_vector test_list test_mylist test_myadd
