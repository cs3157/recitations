/*
 * mdb.h
 */

#ifndef _MDB_H_
#define _MDB_H_

#include <stdio.h>
#include "mylist.h"

struct MdbRec {
    char name[16];
    char  msg[24];
};

int loadmdb(FILE *fp, struct List *dest);
void freemdb(struct List *list);

#endif /* _MDB_H_ */
