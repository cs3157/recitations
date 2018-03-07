#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int *p = malloc(10 * sizeof(int));
    if (p == NULL) {
        perror("couldn't malloc array");
        exit(1);
    }

    for (int i = 0; i <= 10; i++) {
        printf("%d\n", i);
        p[i] = i;
    }

    printf("%d\n", p[10]);

    return 0;
}
