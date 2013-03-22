/*
 * Assuming that the databse provided in command line arguments has the following
 * mdb-lookup output
 *
 * lookup:
 *    1: {Obama} said {likable enough Hillary}
 *    2: {Romney} said {binders full of women}
 */


#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"

struct MdbRec {
    char name[16];
    char msg[24];
};

int main(int argc, char **argv)
{
    // added (not in exam) but inconsequential
    if (argc != 2) {
        fprintf(stderr, "%s\n", "usage: mdb-print <database_file>");
        exit(1); 
    }

    FILE *fp = fopen(argv[1], "rb");

    struct List list;
    initList(&list);

    struct Node *node = NULL;
    struct MdbRec *p;
    
    /* 
     * Tracing some of the program...
     * p points to a space in memory the size of MdbRec
     * a record is read from file and placed into that space in memory
     * that record is pointed to as data on a linked list node
     * that node is added to the front of the list (becuase node is NULL at first)
     * after addAfter node points to the first node just added
     * loop goes to the top
     * now we read another record from the file
     * BUT we read it into the SAME memory location as before essentially overwriting
     * the data from before
     * now p is equal to the "Romney" record.
     * and now we add a new node with the same memory as data!
     * We've just created two nodes with data pointing to the same place in memory
     * that memory has the "Romney" in it
     * loop goes to the top
     * there is no more data in the database left to read so while loop stops
     *
     * solutions to problem marked by TO-DO below
     */
    p = (struct MdbRec *)malloc(sizeof(struct MdbRec));
    while (fread(p, sizeof(struct MdbRec), 1, fp) == 1) {
        node = addAfter(&list, node, p);
        // TODO p = (struct MdbRec *)malloc(sizeof(struct MdbRec)); // alloc space for new data
    }
    // TODO free(p); // need to free the last unecessary malloc after file ran-out of data

    /*
     * What is printed is the two nodes each pointing to the space in memory
     * containing the "Romney" record
     */
    while ((p = (struct MdbRec *)popFront(&list)) != NULL) {
        printf("{%s} said {%s}\n", p->name, p->msg);
        // TODO free (p); // need to free each data item
    }

    /*
     * At this point we have "popFront"ed all the nodes off of the linked list
     * so those nodes that were malloc'd have been freed BUT we have not
     * freed the memory that we allocated for the data (40 bytes)
     */

    fclose(fp);
    return 0;
}

/*
 * ==13663== Memcheck, a memory error detector
 * ==13663== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
 * ==13663== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
 * ==13663== Command: ./midterm-f12-q3 my-mdb
 * ==13663== 
 * {Romney} said {binders full of women}
 * {Romney} said {binders full of women}
 * ==13663== 
 * ==13663== HEAP SUMMARY:
 * ==13663==     in use at exit: 40 bytes in 1 blocks
 * ==13663==   total heap usage: 4 allocs, 3 frees, 640 bytes allocated
 * ==13663== 
 * ==13663== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
 * ==13663==    at 0x4C2B6CD: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
 * ==13663==    by 0x4007C5: main (midterm-f12-q3.c:25)
 * ==13663== 
 * ==13663== LEAK SUMMARY:
 * ==13663==    definitely lost: 40 bytes in 1 blocks
 * ==13663==    indirectly lost: 0 bytes in 0 blocks
 * ==13663==      possibly lost: 0 bytes in 0 blocks
 * ==13663==    still reachable: 0 bytes in 0 blocks
 * ==13663==         suppressed: 0 bytes in 0 blocks
 * ==13663== 
 * ==13663== For counts of detected and suppressed errors, rerun with: -v
 * ==13663== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 2 from 2)
 */
