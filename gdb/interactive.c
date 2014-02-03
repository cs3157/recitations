#include <stdlib.h>
#include <stdio.h>
#include "mymath.h"

int main(int argc, char **argv) {
    while (1) {
        int x;
        int y;
        printf("Number: ");
        scanf("%d", &x);
        printf("To the power of: ");
        scanf("%d", &y);

        int result = exponentiate(x, y);
        printf("Answer: %d^%d = %d\n", x, y, result);
    }
}


