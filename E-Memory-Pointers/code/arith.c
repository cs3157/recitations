#include <stdio.h>
int main(int argc, char **argv) {
    char *ta = "elsy";
    printf("%ld\n", (ta + 4) - ta);
    printf("%ld\n", (int *) (ta + 4) - (int *) (ta));
    
    char *tas[] = {"hansy", "aunosy", "nelsy", "chansy"};
    printf("%ld\n", (tas + 4) - tas);
    printf("%ld\n", (int *) (tas + 4) - (int *) (tas));
}
