#include <stdio.h>
#include <stdlib.h>

int add(const int*, const int*);
int multiply(const int*, const int*);
int operate(const int*, const int*, int(*functionPtr)(const int *, const int *));


int main(int argc, char **argv) {
    int a = 4;
    int b = 3;
    printf("The memory address of local variable a is %p\n", &a);
    printf("The memory address of local variable b is %p\n", &b);
    printf("\n");

    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int));
    printf("The memory address of heap variable c is %p\n", &c);
    printf("The memory address of heap variable d is %p\n", &d);
    printf("\n");

    printf("The memory address of the function add is %p\n", &add);
    printf("The memory address of the function multiply is %p\n", &multiply);
    printf("\n");

    *c = operate(&a, &b, &add);
    printf("\n");

    *d = operate(&a, &b, &multiply);

    free(c);
    free(d);
    return 0;
}

int operate(const int *a, const int *b, int (*operationPtr)(const int *, const int*)) {
    printf("Operating with operator at memory address %p\n", operationPtr);
    return (*operationPtr)(a, b);
}

int add(const int *a, const int *b) {
    printf("Adding the contents of %p and %p. (%d+%d)\n", a, b, *a, *b);
    return *a + *b;
}

int multiply(const int *a, const int *b) {
    printf("Multiplying the contents of %p and %p. (%d*%d)\n", a, b, *a, *b);
    return *a * *b;
}
