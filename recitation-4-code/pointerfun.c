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

    static double staticvar = 0.0;
    printf("The memory address of global variable globalvar is %p\n", &globalvar);
    printf("The memory address of static variable staticvar is %p\n", &staticvar);
    printf("\n");

    int a = 4;
    int b = 3;
    printf("The memory address of local variable a is %p\n", &a);
    printf("The memory address of local variable b is %p\n\b", &b);

    int *ptr_to_a;
    ptr_to_a = &a;
    printf("ptr_to_a has the address %p, and the content %p. *ptr_to_a = %d \n\n",
            &ptr_to_a, ptr_to_a, *ptr_to_a);

    int **ptr_to_ptr_to_a;
    ptr_to_ptr_to_a = &ptr_to_a;
    printf("ptr_to_ptr_to_a has the address %p, and the content %p.  "
        "*ptr_to_ptr_to_a = %p. **ptr_to_ptr_to_a = %d \n\n",
        &ptr_to_ptr_to_a, ptr_to_ptr_to_a, *ptr_to_ptr_to_a, **ptr_to_ptr_to_a);


    printf("Mallocing *c to sizeof(int)*5; *d to sizeof(int)\n");
    int *c = malloc(sizeof(int)*5);
    int *d = malloc(sizeof(int));

    *c = 9;
    printf("The memory address on the heap int *c points to is %p\n", c);
    printf("The memory address on the heap int *d points to is %p\n", d);
    printf("\tBut note that c itself is in the address %p.", &c);
    printf("\t%p ->  %p, which contains %d \n", &c, c, *c);


    printf("Look at all the different ways we can use pointers to a block of malloc'd memory\n");
    *(c+1) = 10;
    c[2] = 11;
    3[c] = 12;
    *(c+4) = 0;
    printf("Now looping through c+0...c+4:\n");
    int i;
    for (i = 0; i < 5; i++) {
        printf("    *(c+%d) == %2d", i, *(c+i));
        printf("    c[%d] == %2d", i, c[i]);
        printf("    %d[c] == %2d \n", i, i[c]);
    }
    printf("\n");

    printf("one last thing, carr is an int array of size 5. Let's do what we did with c again with carr...\n");
    int carr[5];
    carr[0] = 9;
    *(carr+1) = 10;
    carr[2] = 11;
    3[carr] = 12;
    *(carr+4) = 0;
    printf("Now looping through carr+0...carr+4:\n");
    for (i = 0; i < 5; i++) {
        printf("    *(carr+%d) == %2d", i, *(carr+i));
        printf("    carr[%d] == %2d", i, carr[i]);
        printf("    %d[carr] == %2d \n", i, i[carr]);
    }
    printf("\n");



    printf("null pointers are just pointers whose value is 0 (or in hex 0x0)\n");
    int *e;
    e = NULL;
    printf("e = NULL. Its value is %p\n", e);
    e = 0;
    printf("e = 0. Its value is still %p\n", e);
    e = '\0';
    printf("e = '\\0'. Its value is still %p\n", e);

    printf("null characters are the number 0. 0 == '\\0'\n");
    char f;
    f = '0';
    printf("f = '0'. Its value as a char is %c, but as a number is %d\n", f, f);
    f = 0;
    printf("f = 0. Its value as a char is %c, but as a number is %d\n", f, f);
    f = 'a';
    printf("f = 'a'. Its value as a char is %c, but as a number is %d\n", f, f);
    printf("\n");


    printf("Now let's play with functions!\n");
    printf("The memory address of the function add is %p\n", &add);
    printf("The memory address of the function multiply is %p\n", &multiply);
    printf("\n");


    printf("We'll try to add, by asking the operate function to use the add function...\n");
    printf("We'll add a + b and store into d \n");
    operate(&a, &b, d, &add);
    printf("The contents of malloc'd space %p, d, is %d\n", d, *d);
    printf("\n");

    printf("Ok, now let's try to multiply, by asking the operate function to use the multiply function...\n");
    printf("We'll multiply a * b and store into globalvar, but use *ptr_to_ptr_to_a, rather than &a\n");
    operate(*ptr_to_ptr_to_a, &b, &globalvar, &multiply);
    printf("The contents of global variable %p, globalvar, is %d\n", &globalvar, globalvar);

    /* allways free! */
    free(c);
    free(d);
    printf("\n\n");

    char *sl = "This is a string literal!";
    printf("\"%s\" is acessed via char *sl at %p\n", sl, sl);

    char *lastChar = sl+strlen(sl)-1;
    printf("The last character of ^ is '%c', stored at %p\n", *lastChar, lastChar);

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
