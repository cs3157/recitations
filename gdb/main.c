#include <stdlib.h>
#include <stdio.h>

int x;
int add(int a, int b);
int multiply(int a, int b);
int exponentiate(int a, int b);
void do_exponentiation();

int main(int argc, char **argv) {
    while (1) {
        printf("Exponentiate...\n");
        do_exponentiation();
    }
}

void do_exponentiation() {
    int y;
    printf("Number: ");
    scanf("%d", &x);
    printf("To the power of: ");
    scanf("%d", &y);

    int result = exponentiate(x, y);
    printf("Answer: %d^%d = %d\n", x, y, result);
}

int exponentiate(int x, int y) {
    int result = 1;
    while (y--) {
        result = multiply(result, x);
    }
    return result;
}

int multiply(int x, int y) {
    int result = 0;
    while (y--) {
        result = add(result, x);
    }
    return result;
}

int add(int x, int y) {
    return x + y;
}
