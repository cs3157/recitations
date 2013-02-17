#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *a[] = {"one", "two"};
    
    printf("\n\nThe pointer to the beginning of the array of pointers: %p\n\n", a);

    printf("The first value in the pointer array is a pointer: %p\n\n", *a);
    
    printf("The second value in the pointer array is a pointer: %p\n\n", *(a+1));
    
    printf("This is the pointer to the beginning of the ptr array again: %p\n\n", a+0);
    
    printf("This is a pointer two the second item in the array of ptrs: %p\n\n", a+1);
    
    printf("This is the first address of the what the first pointer in the pointer array points to: %p\n\n", &a[0][0]);
    
    printf("This is the second: %p\n\n\n", &a[0][1]);
}

