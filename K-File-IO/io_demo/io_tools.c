#include <stdio.h>
#include "io_tools.h"

void print_test_name(const char *test_name)
{
    for (int i = 0; i < 20; ++i) {
        printf("-");
    }
    printf("%s", test_name);
    for (int i = 0; i < 20; ++i) {
        printf("-");
    }
    printf("\n"); 
}
