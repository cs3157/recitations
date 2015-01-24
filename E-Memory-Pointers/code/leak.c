#include <stdio.h>
#include <stdlib.h>

int main()
{
    // this is defining and declaring an integer stack variable
    // memory space has been pushed onto the stackframe to hold this value
    int x = 5;

    // we can point to that place in memory defining a pointer like this
    // when the main function RETURNS the stack variable x will be "popped"
    // int* is also a stack variable and will be popped
    int *p = &x;

    // It is possible to create memory in a location that is not
    // on the stack and is persistent. This place is the "heap.""
    // we can remember where it is with a pointer

    // here we have created space on the heap the size of the number
    // of bytes it takes to hold an integer
    // on the CUNIX machines this is 4 bytes
    // So, what we have done here is very similar to what we have
    // done above. We have allocated space to hold a single integer
    // it is good practice to cast the return value of malloc
    // what is being returned naturally is (void *)
    // this is syntatic suger
    int *p2 = (int *)malloc(sizeof(int));

    // it is a good idea to check that malloc worked
    // required for all labs
    if (p2 == NULL) {
        perror("malloc failed");
        exit(1);
    }

    // we can now use this space of 4 bytes to write a number!
    *p2 = 17;
    printf("Here is the number we're storing on the heap: %d\n", *p2);

    // if we were to end this program now like this
    // 
    // return 0;
    //
    // the memory on the heap would persist after the program died
    // this is not good. this is a leak
    //
    // ==15433== Memcheck, a memory error detector
    // ==15433== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
    // ==15433== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
    // ==15433== Command: ./a.out
    // ==15433== 
    // Here is the number we're storing on the heap: 17
    // ==15433== 
    // ==15433== HEAP SUMMARY:
    // ==15433==     in use at exit: 4 bytes in 1 blocks
    // ==15433==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
    // ==15433== 
    // ==15433== LEAK SUMMARY:
    // ==15433==    definitely lost: 4 bytes in 1 blocks
    // ==15433==    indirectly lost: 0 bytes in 0 blocks
    // ==15433==      possibly lost: 0 bytes in 0 blocks
    // ==15433==    still reachable: 0 bytes in 0 blocks
    // ==15433==         suppressed: 0 bytes in 0 blocks
    // ==15433== Rerun with --leak-check=full to see details of leaked memory
    // ==15433== 
    // ==15433== For counts of detected and suppressed errors, rerun with: -v
    // ==15433== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2) 
    
    // but we won't do that
    // instead we will be good citizens and free the memory

    free(p2); 

    // now that we have properly freed memory
    // we'll get the most satisfying message from valgrind
    //
    // ==15627== Memcheck, a memory error detector
    // ==15627== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
    // ==15627== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
    // ==15627== Command: ./a.out
    // ==15627== 
    // Here is the number we're storing on the heap: 17
    // ==15627== 
    // ==15627== HEAP SUMMARY:
    // ==15627==     in use at exit: 0 bytes in 0 blocks
    // ==15627==   total heap usage: 1 allocs, 1 frees, 4 bytes allocated
    // ==15627== 
    // ==15627== All heap blocks were freed -- no leaks are possible
    // ==15627== 
    // ==15627== For counts of detected and suppressed errors, rerun with: -v
    // ==15627== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)

    return 0;
}
