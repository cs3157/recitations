#include <stdio.h>
#include <string.h>

struct MdbRec {
    char name[16];
    char msg[24];
};

int main(int argc, char **argv)
{
    int a[10] = { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109 };
    int *p = a + 2;

    struct MdbRec m[1];
    strcpy(m[0].name, "dude");
    strcpy(m[0].msg, "0");

    int x = 0xffffffff;
    int y = 0xffffffff;
    unsigned char *c = (unsigned char *)&x;
    
    /* answer to question is an integer or for non-integer expressions
     * answer is a type
     * below I'm printing out an example interpretation of that type
     */
    printf("Question 1.1:  %20d\n", p[2]); // 104
    
    // sizeof returns size_t so I'm casting it here to avoid compiler warning
    printf("Question 1.2:  %20d\n", (int)sizeof(p)); // 8
    
    printf("Question 1.3:  %20p\n", m->msg+1); // char *

    /* "0" is a static c-string
     * if you dereference [0] you will get "0"
     * if you dereference [1] you will get the null terminator of that c-string ZERO
     * recall 0 and '\0' are the same
     * both statements are true so return 1
     */
    int q1_4 = "0"[1] == 0 && "0"[1] == '\0';
    printf("Question 1.4:  %20d\n", q1_4); // 1

    // actual value is the executable name
    // type is char *
    printf("Question 1.5:  %20s\n", *argv++); // char *

    /* m->msg is the pointer to the array of 24 characters
     * m->msg memory begins immediately after the array of 16 characters "name"
     * m is the beginning of the MdbRec structure.
     * Subtracting the difference of these two pointers will yield 16
     */
    printf("Question 1.6:  %20ld\n", (m->msg - (char *)m)); // 16
    
    // m[0] is the dereferenced MdbRec structure
    // &m[0] is the address of that MdbRec
    printf("Question 1.7:  %20p\n", &m[0]); // struct MdbRec *

    /* m[0] is the MdbStructure
     * m[0].msg is the character array in MdbStruct of size 16 bytes
     * sizeof(any-character-array) will return the number number of bytes in the argument
     * example sizeof(a) will return 40 bytes (10 items * 4 bytes each)
     */
    printf("Question 1.8:  %20d\n", (int)sizeof(m[0].msg)); // 24

    printf("Question 1.9:  %20p\n", &p); // int **

    /* x = 0xffffffff which is -1 in twos complement
     * y = 0xffffffff which is -1 in twos complement
     * a 4 byte integer is 32 bits
     * each symbol 'f' occupies 4 bits
     * 'f' is the hexadecimal symbol for 15 decimal = 1111 in decimal
     * in other words x and y is full of 1s
     * if the most significant bit (the left one) is 1 (which it is here)
     * two find the value of a negative number in twos complement
     * the trick is to flip the bits and add one
     * example: 1101 = -3 because we flip the bits 0010 and add one 0011
     */
    printf("Question 1.10: %20d\n", x + y); // -2

    /*
     * let's unpack c[2]...
     * we start off at the address of x which on this machine
     * is the least significant bit. (this is irrelevant in this situation as
     * all of the bits in x are 1)
     * we then move 2 bytes in the "left" direction. and we dereference ONE byte
     * at that location. We dereference one byte because we are looking at this
     * integer memory location and interpreting it as an unsigned char
     *
     * Visualation: Here is x in memory 11111111 11111111 11111111 11111111
     *                                           ********                      
     * The above stars are the locations pointed to by c[2]
     * 
     * Because the byte is interpreted as an unsigned char
     * we know that these 8 bytes will not be interpreted as negative
     * and all 8 bits will be used to calculate the number
     * 2^8-1 = 255
     *
     */
    printf("Question 1.11: %20d\n", c[2]); // 255

    // &c is an address of a pointer
    printf("Question 1.12: %20p\n", &c); // unsighed char **

    /*
     * ~ is the negation operator
     * ~x will flip all the bits of x to zeros
     * & is the AND bit operator
     * ~x & y is essentially: all 0 bits AND all 1 bits == 0
     */
    printf("Question 1.13: %20d\n", ~x&y); // 0

    /*
     * sizeof(a) = number of bytes in array a = 40
     * sizeof(a[0]) = number of bytes in integer a[0] = 4
     * 40 / 4 = 10
     * casting to int because sizeof returns type size_t
     */
    printf("Question 1.14: %20d\n", (int)sizeof(a) / (int)sizeof(a[0])); // 10

    /*
     * a[5] is 105
     * &a[5] is the address of that 105
     * *&a[5] is that 105 again
     * &*&a[5] is that address of that 105 again
     * *&*&a[5] is that 105 again!
     */
    printf("Question 1.15: %20d\n", *&*&a[5]);

    return 0;
}
