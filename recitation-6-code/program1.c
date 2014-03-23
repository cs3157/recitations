/* Rudimentary program used to illustrate FIFO usage */
#include <stdio.h>

int main()
{
    char buf[1000];
    fgets(buf, sizeof(buf), stdin);
    printf("Program 1 Output: Input is %s\n", buf);
    return 0;
}
