#include <stdio.h>
#include "ops.h"

int main() {
  int five = add(2, 3);
  int six = subtract(7, 1);
  int seven = divide(14, 2);
  int eight = multiply(2, 4);
  printf("Five: %d\nSix: %d\nSeven: %d\nEight: %d\n", five, six, seven, eight);
  return 0;
}

