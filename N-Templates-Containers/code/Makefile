CC  = g++
CXX = clang++ -O0

INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -fPIC -g -Wall $(INCLUDES)

LDFLAGS = -g
LDLIBS  =

executables = main
objects = main.o

.PHONY: default
default: $(executables)

$(executables): main.o

$(objects):

.PHONY: clean
clean:
	rm -f *~ a.out core $(objects) $(executables)

.PHONY: all
all: clean default
