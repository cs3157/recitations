#include <stdlib.h>
#include <stdio.h>

int add(int a, int b);
int multiply(int a, int b);
int exponentiate(int a, int b);

int exponentiate(int x, int y) {
    int result = 1;
    while (y--) {
        result = multiply(result, x);
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
