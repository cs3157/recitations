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

