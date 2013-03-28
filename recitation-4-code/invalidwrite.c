#include <stdio.h>
#include <stdlib.h>

int main()
{
    // here again we are allocating 4 bytes for an integer
    int *p = (int *)malloc(sizeof(int));

    // checking that malloc worked
    if (p == NULL) {
        perror("malloc failed");
        exit(1);
    }

    // in c it is possible to go into areas we don't belong.
    // malloc difined the 4 byte area in which we can play
    // but we can use the pointer p to read or write in places before or after that space allocated
    // it's possible we'll hit a nerve and the program will crash
    // it's possible nothing will happen of any consequence
    // or it's possible we're silently ruining memory that someone else is using
    //
    // Valgrind can help to find if we've read or written out of bounds

    // here we're storing a copy of the pointer
    int *p2 = p;

    // here we are using pointer arithmetic to point to the next location in memory
    // our address location + 4 bytes
    // so now p2 will be pointing past where we have officially allocated memory
    // Note that in C, pointer arithmetic always moves in the size of the data type, so
    // adding 1 to a pointer of type int will move it 4 bytes forward in memory (in a 32-bit system)
    p2 += 1;

    // so if we assign a value into this memory location we're not allowed bad things could happen!
    *p2 = 17;

    // Or nothing may happen but this is still bad.  Valgrind can catch this. And It will be marked off
    // In your lab
    // 
    // Valgrind error looks like this:
    //
    // ==16419== Memcheck, a memory error detector
    // ==16419== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
    // ==16419== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
    // ==16419== Command: ./a.out
    // ==16419== 
    // ==16419== Invalid write of size 4
    // ==16419==    at 0x400616: main (in /home/cd2665/cs3157/TA/valgrindtests/a.out)
    // ==16419==  Address 0x51f1050 is 12 bytes after a block of size 4 alloc'd
    // ==16419==    at 0x4C2B6CD: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    // ==16419==    by 0x4005E5: main (in /home/cd2665/cs3157/TA/valgrindtests/a.out)
    // ==16419== 
    // ==16419== 
    // ==16419== HEAP SUMMARY:
    // ==16419==     in use at exit: 0 bytes in 0 blocks
    // ==16419==   total heap usage: 1 allocs, 1 frees, 4 bytes allocated
    // ==16419== 
    // ==16419== All heap blocks were freed -- no leaks are possible
    // ==16419== 
    // ==16419== For counts of detected and suppressed errors, rerun with: -v
    // ==16419== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 2 from 2)
    
    free(p);


    return 0;
}
