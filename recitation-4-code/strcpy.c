#include <stdio.h>
#include <string.h>

int main()
{
    char *s = "cs3157 rocks";
    int len = strlen(s);
    char t[len+1]; // remember a c-style string contains the characters and a terminating '\0'

    char *p = s;
    char *p2 = t;

    while ((*p2++ = *p++) != 0)
        ;

    printf("s = %s\n", s);
    printf("t = %s\n", t);

    // what is p and p2 pointing to?
    // it is pointing to the '\0' in memory for the s string and the t string respectively

    return 0;
}
