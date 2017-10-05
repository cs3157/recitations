#include <stdio.h>

int main(int argc, char **argv) { 

    //(1)
    //numbers that start with 0x are in hexadecimal
    printf("(1): %d \n", 0xFFFFFFFF);

    
    //(2)
    int x = 0xFFFFFFFF;
    int y = 0xFFFFFFFE;
    int z = 0xF739C090;

    int ans = x >> 31 & ~(y | z);
    printf("(2): %d \n", ans);

    //(3)
    int val1 = -1;
    printf("(3): ");
    int i;
    for (i = sizeof(int) * 8 - 1; i >= 0; i--) {
        printf("%d", (val1 >> i) & 1);
        if (i % 4 == 0)
            printf(" ");
    }
    printf("\n");

    int val2 = (~val1) + 1;
    printf("(4): ");
    int j;
    for (j = sizeof(int) * 8 - 1; j >= 0; j--) {
        printf("%d", (val2 >> j) & 1);
        if (j % 4 == 0)
            printf(" ");
    }
    printf("\n");
}
