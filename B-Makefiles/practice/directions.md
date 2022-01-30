# Recitation 2: Practice #

Try to do the following programs without a compiler, just pen and paper.

## Problem 1 ##

Read the sample makefile below:

p1/Makefile

```make
  CC = gcc
  CFLAGS = -Wall

  .PHONY: run
  run:
    ./main
```

Oh, well that's a rather sparse Makefile. I guess we'll have to fill it in.
Given the C files below, write this Makefile twice. (a) The first time with every
rule written out in its entirety, without relying on Make to fill in all the
stuff you've left out. (b) The second time, use all the defaults possible to make as
short a makefile as possible.

The requirements for the Makefile are as follows:

  1. Add a "clean" target that removes all compiled files.
  2. Add an "all" target that runs the clean target and then compiles
  3. Design your file such that typing `make` in the shell will result in all
     compiled files being removed, the entire project being compiled, and the
     compiled file being executed. **NOTE**: This requirement is incredibly bad
     practice, but will illustrate a point about Makefiles.
  4. The executable should be called "main" and should have debugging flags

p1/main.c

```c
#include <stdio.h>
#include "ops.h"

int main(int argc, char **argv) {
  int five = add(2, 3);
  int six = subtract(7, 1);
  int seven = divide(14, 2);
  int eight = multiply(2, 4);
  printf("Five: %d\nSix: %d\nSeven: %d\nEight: %d\n", five, six, seven, eight);
  return 0;
}
```

p1/ops.h

```c
int add(int x, int y);
int subtract(int x, int y);
int divide(int x, int y);
int multiply(int x, int y);
```

p1/ops.c

```c
#include "ops.h"
#include "opsprinter.h"

int add(int x, int y) {
  int ret = x + y;
  printOp(x, '+', y, ret);
  return ret;
}
int subtract(int x, int y) {
  int ret = x - y;
  printOp(x, '-', y, ret);
  return ret;
}
int divide(int x, int y) {
  int ret = x / y;
  printOp(x, '/', y, ret);
  return ret;
}
int multiply(int x, int y) {
  int ret = x * y;
  printOp(x, '*', y, ret);
  return ret;
}
```

p1/opsprinter.h

```c
#include <stdio.h>

void printOp(int x, char op, int y, int result);
```

p1/opsprinter.c

```c
#include "opsprinter.h"

void printOp(int x, char op, int y, int result) {
  printf("%d %c %d = %d\n", x, op, y, result);
}
```
