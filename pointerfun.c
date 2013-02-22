#include <stdio.h>
#include <stdlib.h>

int add(const int *, const int *);
int multiply(const int *, const int *);
void operate(const int *, const int *, int *, int(*functionPtr)(const int *, const int *));


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

    operate(&a, &b, c, &add);
    printf("The contents of malloc'd space %p, \"c\", is %d\n", c, *c);
    printf("\n");

    operate(&a, &b, d, &multiply);
    printf("The contents of malloc'd space %p, \"d\", is %d\n", d, *d);
    printf("\n");


    free(c);
    free(d);
    return 0;
}

void operate(const int *a, const int *b, int *dest, int (*operationPtr)(const int *, const int*)) {
    printf("Storing into %p results of operation at memory address %p\n", dest, operationPtr);
    *dest = (*operationPtr)(a, b);
}

int add(const int *a, const int *b) {
    printf("Adding the contents of %p and %p. (%d+%d)\n", a, b, *a, *b);
    return *a + *b;
}

int multiply(const int *a, const int *b) {
    printf("Multiplying the contents of %p and %p. (%d*%d)\n", a, b, *a, *b);
    return *a * *b;
}
