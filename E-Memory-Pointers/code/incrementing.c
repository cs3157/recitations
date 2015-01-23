#include <stdio.h>

int main()
{
    int i = 4;
    int j;
    int k;

    j = i++; // j is set to i, which is 4, then i is incremented
    k = i;   // k is 5

    j = ++i; // i is incremented, then j is set to i, which is 6

    return 0;
}
