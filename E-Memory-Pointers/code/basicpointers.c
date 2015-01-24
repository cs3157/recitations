#include <stdio.h>

int main()
{
    int x = 5;
    printf("int x = 5;\n");
    printf("Address of x is: &x == %p.\n", &x);
    printf("\tx contains: x == %d.\n\n", x);
   

    // p is a pointer to an integer
    int *p;

    // p now holds the address of x
    p = &x;
    printf("int *p = &x;\n");
    printf("Address of p is:\t&p == %p\n", &p);

    printf("\tp contains:\t p == %p\n\n", p);
    
    /*
     * When we dereference a pointer, we know how to interpret
     * the data at that address location because of the pointer type.
     * This is an int* so we will interpret the data at address p
     * as an integer
     */

    printf("By dereferencing p, we get: *p == %d\n\n", *p);
    return 0;
}
