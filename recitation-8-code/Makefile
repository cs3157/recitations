CC  = gcc
CXX = g++

INCLUDES = 
CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g -L.
LDLIBS = -lmylist

PROG1 = midterm-f12-q1
PROG2 = midterm-f12-q2
PROG3 = midterm-f12-q3

.PHONY: default
default: $(PROG1) $(PROG2) $(PROG3)

.PHONY: clean
clean:
	rm -f *.o *~ a.out core $(PROG1) $(PROG2) $(PROG3)

.PHONY: all
all: clean default

