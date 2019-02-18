#include <stdio.h>
int main(int argc, char **argv) {
    int nums[] = {1, 2, 3, 4};
    printf("%ld\n", (nums + 4) - nums);
    printf("%ld\n", (char *) (nums + 4) - (char *) (nums));
}
