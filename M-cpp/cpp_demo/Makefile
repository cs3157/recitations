CC = g++
CXX = g++
CXXFLAGS = -std=c++11 -g -Wall $(INCLUDES)
LDFLAGS = -g

.PHONY: default

default: cpp_demo

cpp_demo: matrix.o 

cpp_demo.o: matrix.hpp 

matrix.o: matrix.hpp

.PHONY: clean

clean:
	rm -f cpp_demo *.o

.PHONY: all

all: clean default 
