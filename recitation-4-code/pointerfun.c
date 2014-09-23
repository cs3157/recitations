/**
 * Chris Mulligan, clm2186
 * COMSW3157 Advanced Programming
 * pointerfun.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add(const int *a, const int *b);
int multiply(const int *a, const int *b);
void operate(const int *a, const int *b, int *dest, int (*operationPtr)(const int *, const int*));

int globalvar = 0;

int main(int argc, char **argv) {
    printf("We'll be running a series of experiments, and printing the results\n"
            "to try to better understand pointers and memory in C. Ready?\n\n");


    printf("\nBefore we start, let's talk about NULL pointers.\n");
    printf("null POINTERS are just pointers whose value is 0 (or in hex 0x0)\n");
    int *e;
    e = NULL;
    printf("int *e = NULL. Its value is %%p == %p\n", e);
    e = 0;
    printf("     e = 0.    Its value is still %p\n", e);


    printf("\n\nWe begin with stack (local) variables.\n");
    int a = 4;
    int b = 3;
    printf("The memory address of local variable int a is %p\n", &a);
    printf("The memory address of local variable int b is %p\n\n", &b);

    int *ptr_to_a;
    ptr_to_a = &a;
    printf("ptr_to_a has the address &ptr_to_a == %p. ptr_to_a has value ptr_to_a == %p. Dereferenced, *ptr_to_a == %d \n", &ptr_to_a, ptr_to_a, *ptr_to_a);
    printf("\t%p -> %p -> %d\n\n", &ptr_to_a, ptr_to_a, *ptr_to_a);

    int **ptr_to_ptr_to_a;
    ptr_to_ptr_to_a = &ptr_to_a;
    printf("ptr_to_ptr_to_a has the address %p, and the content %p.  "
        "*ptr_to_ptr_to_a = %p. **ptr_to_ptr_to_a = %d \n",
        &ptr_to_ptr_to_a, ptr_to_ptr_to_a, *ptr_to_ptr_to_a, **ptr_to_ptr_to_a);
    printf("\t%p -> %p -> %p -> %d\n\n",
        &ptr_to_ptr_to_a, ptr_to_ptr_to_a, *ptr_to_ptr_to_a, **ptr_to_ptr_to_a);

    printf("\n\nNow let's look at the heap!\n");

    printf("Mallocing int *c to point to sizeof(int). int *d to point to sizeof(int)*5.\n");
    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int)*5);

    *d = 9;
    printf("The memory address on the heap int *c points to is %p\n", c);
    printf("The memory address on the heap int *d points to is %p\n", d);
    printf("\tBut note that d itself is on the stack at %p.\n", &d);
    printf("\t%p ->  %p, which contains %d \n", &d, d, *d);


    printf("\n\nLook at all the different ways we can use pointers to a block of malloc'd memory aka an array\n");
    *(d+1) = 10;
    d[2] = 11;
    3[d] = 12;
    *(d+4) = 13;
    printf("Now looping through d+0...d+4:\n");
    int i;
    int *copy = d;
    for (i = 0; i < 5; i++) {
        printf("    *(d+%d) == %2d", i, *(d+i));
        printf("    d[%d] == %2d", i, d[i]);
        printf("    %d[d] == %2d", i, i[d]);
        printf("    *copy++ == %2d \n", *copy++);
    }
    printf("\n");


    static double staticvar = 0.0;
    printf("The memory address of global variable globalvar is %p\n", &globalvar);
    printf("The memory address of static variable staticvar is %p\n", &staticvar);
    printf("\n\n");
    
    char *sl = "This is a string literal!";
    printf("\"%s\" is acessed via char *sl at %p\n", sl, sl);

    char *lastChar = sl+strlen(sl)-1;
    printf("\tThe last character of ^ is '%c', stored at %p\n", *lastChar, lastChar);

    printf("\n\nNow let's play with functions!\n");
    printf("The memory address of the function add is %p\n", &add);
    printf("The memory address of the function multiply is %p\n", &multiply);
    printf("\n");

    printf("We'll try to add, by asking the operate function to use the add function...\n");
    printf("We'll add a + b and store into d \n");
    operate(&a, &b, d, &add);
    printf("The contents of malloc'd space %p, d, is %d\n", d, *d);
    printf("\n");



    printf("\n\n-----SUMMARY-----\n");
    printf("early stack var argc: %p\n", &argc);
    printf("late stack var sl:    %p\n", &sl);
    printf("heap variable c:      %p\n", c);
    printf("globalvar is at:      %p\n", &globalvar);
    printf("string literal:       %p\n", sl);
    printf("code (main):          %p\n", &main);
    printf("code (printf):        %p\n", &printf);


    /* allways free! */
    free(c);
    free(d);
    printf("\n\n");

    return 0;
}



/* add two ints, returning the sum */
int add(const int *a, const int *b) {
    printf("    (inside add) Adding the contents of %p and %p. (%d+%d)\n", a, b, *a, *b);
    return *a + *b;
}

/* Multiple two ints, returning the product */
int multiply(const int *a, const int *b) {
    printf("    (inside multiply) Multiplying the contents of %p and %p. (%d*%d)\n", a, b, *a, *b);
    return *a * *b;
}

/* Call a function on two pointers, store the result to another location  */
void operate(const int *a, const int *b, int *dest, int (*operationPtr)(const int *, const int*)) {
    printf("  (inside operate) Storing into %p results of operation at memory address %p\n", dest, operationPtr);
    *dest = (*operationPtr)(a, b);
}
