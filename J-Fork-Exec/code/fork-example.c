#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    pid_t p;

    p = fork();

    if (p > 0) {
        for (i = 0; i < 10; i++) {
            printf("Listen to me\n");
            sleep(1);
        }
        printf("I give up...\n");
        return 0;
    }
    else if (p == 0) {
        for (i = 0; i < 10; i++) {
            printf("No way\n");
            sleep(1);
        }
        printf("Whatever.\n");
        return 1;
    }
    else {
        perror("fork failed");
        return -1;
    }
}
