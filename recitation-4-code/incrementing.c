#include <stdio.h>

int main()
{
    int i = 4;
    int j;
    int k;

    j = i++; // j is 4
             // i is incremented
    k = i;   // k is 5

    
    j = ++i; // i is incremented to 5, j = 5


    return 0;
}
