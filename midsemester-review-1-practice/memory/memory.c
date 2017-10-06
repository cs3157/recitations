#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylist.h"
#include "mdb.h"

struct MdbRec r;

int main(int argc, char **argv) { 

    struct List list;
    initList(&list);

    //create nodes
    struct MdbRec *n1 = (struct MdbRec *) malloc(sizeof(struct MdbRec));
    memcpy(n1->name, "ap", sizeof("ap"));
    memcpy(n1->msg, "cs3157", sizeof("cs3157"));

    struct MdbRec *n2 = (struct MdbRec *) malloc(sizeof(struct MdbRec));
    memcpy(n2->name, "jae", sizeof("jae"));
    memcpy(n2->msg, "woolee", sizeof("woolee"));

    struct MdbRec *n3 = &r;
    memcpy(n3->name, "12345678", sizeof("12345678"));
    memcpy(n3->msg, "90", sizeof("90"));

    //add to list
    addFront(&list, n1);
    addFront(&list, n2);
    addFront(&list, n3);

    struct Node *head = list.head;
    struct MdbRec* data;
    while(head){
        data = (struct MdbRec *) head->data;
        printf("name: {%s} \n", data->name);
        head = head->next;
    }

    removeAllNodes(&list);
    free(data);

    return 0;
}
