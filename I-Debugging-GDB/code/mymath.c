#include <stdlib.h>
#include <stdio.h>
#include "mymath.h"


int ppow(int *x, int *y) {
    int result = 1;
    while ((*y)--) {
        result = multiply(result, *x);
    }
    return result;
}

int multiply(int x, int y) {
    int result = 0;
    while (y--) {
        result = add(result, x);
    }
    return result;
}

int add(int x, int y) {
    return x + y;
}
