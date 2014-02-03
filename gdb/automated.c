#include <stdlib.h>
#include <stdio.h>
#include "mymath.h"

int main(int argc, char **argv) {
    int x = 3;
    int y = 4;
    int xtoy = exponentiate(3, 4);
    printf("%d^%d = %d\n", x, y, xtoy);

    return 0;
}


