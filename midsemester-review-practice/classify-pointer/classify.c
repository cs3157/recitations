//Based on Jae's Fall 2014 Midterm 1

 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include "mylist.h"

char *str_dup(const char *str){
    char *copy = (char *)malloc(strlen(str) + 1);
    memset(copy, 0, strlen(str) + 1);
    strcpy(copy, str);
    return copy;
}

int word_count = 3;

int main(){
    char *words[word_count];
    words[0] = "midterm";
    words[1] = "programming";
    words[2] = "advanced";

    struct List list;
    struct List *listPt = &list;
    initList(listPt);

    int i;
    for (i = 0 ; i < word_count ; i++){
        addFront(listPt, str_dup(words[i]));
    }

    //classify pointers
    /* (1) */ classify_pointer( words );
    /* (2) */ classify_pointer( *words );
    /* (3) */ classify_pointer( listPt );
    /* (4) */ classify_pointer( listPt->head );
    /* (5) */ classify_pointer( (&listPt->head) );
    /* (6) */ classify_pointer( &(listPt->head->next) );
    /* (7) */ classify_pointer( listPt->head->data );
    /* (8) */ classify_pointer( &word_count );

    struct Node *node2 = listPt->head;
    while(node2){
        free(node2->data);
        node2 = node2->next;
    }
    removeAllNodes(listPt);

    return 0;
}
