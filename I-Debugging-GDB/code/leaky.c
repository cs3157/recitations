#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int *ptr2i = (int *)malloc(sizeof(int));
    if (ptr2i == NULL) {  
        perror("malloc returned NULL"); /* Jae often defines a die() to do this */
        exit(1);
    }
    *ptr2i = 4;

    printf("The value pointed to by ptr2i is %d\n", *ptr2i);

    return 0;
}
