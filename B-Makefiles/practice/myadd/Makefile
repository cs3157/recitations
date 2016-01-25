# This is Jae's makefile with the comments removed. 
# Toggling which lines are commented demonstrates how the implicit and explicit rules in makefiles are equivalent.

CC  = gcc
CXX = g++

INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g

LDLIBS =

main: main.o myadd.o
#main: myadd.o

main.o: main.c myadd.h
#main.o: myadd.h

myadd.o: myadd.c myadd.h
#myadd.o: myadd.h

.PHONY: clean
clean:
	rm -f  *.o a.out core main myadd executable

.PHONY: all
all: clean main
