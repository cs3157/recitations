#include <stdlib.h>
#include <stdio.h>
#include "mymath.h"

int main(int argc, char **argv) {
    int a = 2;
    int b = 4;
    
    int *x = &a;
    int *y = &b;

    int xtoy = exponentiate_p(x, y);

    printf("%d^%d = %d\n", *x, *y, xtoy);

    return 0;
}


