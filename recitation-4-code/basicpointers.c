#include <stdio.h>

int main()
{
    int x = 5;
    
    // p is a pointer to an integer
    int *p;

    // p now holds the address of x
    p = &x;

    printf("Address of x is %p\n", &x);
    printf("The address is also being held by p: %p\n", p);
    
    /*
     * When we dereference a pointer, we know how to interpret
     * the data at that address location because of the pointer type.
     * This is an int* so we will interpret the data at address p
     * as an integer
     */

    printf("The value at address p = %d\n", *p);
    return 0;
}
