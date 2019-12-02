#include "mylist.h"
#include <stdio.h>

double some_func(struct List *list1, struct List *list2)
{
    // do something complicated ...
    return *((double *) list1->head->data);
}

// It would be nice to have something like ...
//
//double some_func(/* list type that must have double node data */ list1
//               , /* other list type */ list2)
//{
//    // do something complicated ...
//    // no ugly casting stuff, 
//    // compiler should know list1->head->data is a double*
//    return *list1->head->data;
//}

int main()
{
    char arr1[] = "hello";
    char arr2[] = "world";
    // This list contains nodes with data pointing to char array (string)
    struct List list; 
    initList(&list);
    addFront(&list, arr2);
    addFront(&list, arr1);

    double x[] = {1., 2.};
    // This list contains nodes with data pointing to a double
    struct List list2;
    initList(&list2);
    addFront(&list2, x);
    addFront(&list2, x + 1);

    double value = some_func(&list, &list2);
    fprintf(stderr, "value: %f\n", value);

    return 0;
}
