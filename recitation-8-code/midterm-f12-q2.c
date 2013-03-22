/*
 * program is compiled and run with two command line arguments as follows
 * $ gcc -g -Wall arg.c
 * $ ./a.out abc 123
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("usage: %s <arg1> <arg2>\n", argv[0]);
        return 1;
    }

    /*
     * *a = abc
     * *b = 123
     * c is an array of size two with two characters = 0
     */
    char *a = *++argv;  
    char *b = *++argv;
    char c[2] = { 0, 0 };
    char *p;
    char *q;

    /*
     * go through each character in "abc" stop when reaching string null terminator
     * test to see if current character is in the alphabet
     * if so increase the value present in p such that the result is capitalized. Storing it in c
     * else store the current character in character array of size two
     * finally print each character (converted or not). printing like a c-string
     * "ABC" is printed
     */
    for (p = a; *p; p++) {
        if ('a' <= *p && *p <= 'z')
            *c = *p + 'A' - 'a';
        else
            *c = *p;
        printf("%s", c);
    }

    /*
     * allocate heap memory size of (3 + 3 + 1) bytes
     * copy "abc" (original argv[1] hasn't changed) into p
     * q is a poitner to the address after "abc" (exactly pointing to the null terminator)
     * copy b (aka argv[2]) into p. in other words q = "123". in other words p = "abc123"
     * "abc123" is printed
     * p pointing to heap allocated memory is now set to NULL and therefore lost; leak
     */
    p = (char *)malloc(strlen(a) + strlen(b) + 1);
    strcpy(p, a);
    q = p + strlen(a);
    while ((*q++ = *b++) != 0)
        ;
    printf("%s\n", p);
    p = NULL; // TODO changing this line to free(p) makes this program leak free
    return 0;
}

/*
 * ==32573== Memcheck, a memory error detector
 * ==32573== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
 * ==32573== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
 * ==32573== Command: ./a.out abc 123
 * ==32573== 
 * ABCabc123
 * ==32573== 
 * ==32573== HEAP SUMMARY:
 * ==32573==     in use at exit: 7 bytes in 1 blocks
 * ==32573==   total heap usage: 1 allocs, 0 frees, 7 bytes allocated
 * ==32573== 
 * ==32573== 7 bytes in 1 blocks are definitely lost in loss record 1 of 1
 * ==32573==    at 0x4C2B6CD: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
 * ==32573==    by 0x4006F5: main (midterm-f12-q2.c:53)
 * ==32573== 
 * ==32573== LEAK SUMMARY:
 * ==32573==    definitely lost: 7 bytes in 1 blocks
 * ==32573==    indirectly lost: 0 bytes in 0 blocks
 * ==32573==      possibly lost: 0 bytes in 0 blocks
 * ==32573==    still reachable: 0 bytes in 0 blocks
 * ==32573==         suppressed: 0 bytes in 0 blocks
 * ==32573== 
 * ==32573== For counts of detected and suppressed errors, rerun with: -v
 * ==32573== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 2 from 2)
 */
