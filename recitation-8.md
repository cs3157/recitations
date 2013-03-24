# Recitation 8 - Midterm Review #

## Signed and Unsigned Integers ##

From Recitation 3:

### Bits Bytes and Binary ###

Let's just refresh our memory about memory:

  - A **bit** is a single digit in binary; on or off; 1 or 0
  - 8 bits form a single **byte**: 11111111 = 2^7 - 1 = 255
  - **Hexadecimal** is another notation to count even higher in fewer places
    - Two hexadecimal places express 1 byte
    - FF in Hexadecimal is 255
  - **Two's complement**
    - Most modern computers use this notation for signed integers
    - **Most significant bit**: Usually the leftmost, but generally the bit with the
      highest value: If 1000 = 8, then 1 is the most significant bit. If we were
      using a different notation such as 1010 = 5, then the rightmost 0 is the
      most significant bit. 
    - If the most significant bit is 1, then in two's complement, you're looking
      at a negative number
    - To convert: 1010 (read as ten if unsigned), first note that it is
      negative. Then find its magnitude by flipping all the bits (0101, 5) and
      then adding 1 (0110) meaning the value is -6.
    - Consult the following table to see something interesting: (note the
      wraparound effect
      
Binary | usigned decimal | two's complement decimal
------ | --------------- | ----------------------- 
000    | 0               | 0
001    | 1               | 1
010    | 2               | 2
011    | 3               | 3
100    | 4               | -4
101    | 5               | -3
110    | 6               | -2
111    | 7               | -1


### Data Types: Numbers ###

Integer Types:

  - char
  - int

Modifiers (and sugar):

  - short
  - long

Memory size for each type depends on system, and only restrictions are that

    char <= short <= int <= long <= long long

Clic machines follow

  - char = 1 byte
  - short = 2 bytes
  - int = 4 bytes
  - long = 8 (these last two vary from system to system a lot)
  - long long = 8 

Test it out for yourself:

```c
#include <stdio.h>
 
 int main(int argc, char** argv) {
   printf("char: %d\n
     short: %d\n
     int: %d\n
     long: %d\n
     longlong: %d\n",
     sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(long long));
   return 0;
}
```

Here are some declarations to help you understand what really happens when we're
talking characters and integers. Definitely take a look at [The
Ascii Table](http://www.asciitable.com) and understand the relationships in the
order of the first 128 ascii characters. The C language is built on a subset of
7-bit ascii (0-127) so its important to know what the table is like, not to
memorize it. Also note that in C, single quotes means a character.

Declaration     | x (dec) | y (dec)
--------------- | ------- | -------
int x;          | NULL    | -
int x, y;       | NULL    | NULL
int x = 0, y;   | 0       | NULL
char x = 'x';   | 120     | -
char x = '\n';  | 10      | -
char x = '\13'; | 11      | -
char x = '0';   | 48      | -
char x = '\0';  | 0       | -
char x = 0;     | 0       | -
long x = 0L;    | 0       | -

Preceding a constant with 0x denotes hexadecimal notation:

    (0xFFFFFFFF == -1); //returns 1 (which is true, but C doesn't have true)
    (0177777 == -1); //returns 1 (true)
    sizeof(1234L); //returns 8
    sizeof(1234); //returns 4
    0xFFFFU; //returns 65535
    0177777U; //returns 65535

Float and double are the two floating point types (decimal) and can be expressed
with a decimal point or as scientific notation:

    float miles = 1.8;
    double big = 1e10;

The only implementation constraint is that

    float <= double <= long double

so they could all be one size, or be three distinct sizes.

In C there is no such thing as a string, just an array and pointers.
Essentially, a bunch of single characters located consecutively in memory will
make up a string, but more on this later.

## Bitwise Operators ##

Also from Recitation 3:

Bit-wise operators are tricky and can be used for a variety of purposes:

  - `&` can be used to "mask" or turn off all bits except certain ones. For
    example:
        
        n = n & 0177; // n and 00000001111111

  - `|` can be used to set on all bits:

        n = n | 0177; // n or 00001111111

  - Note:

        int x = 1;
        int y = 2;
        x & y; // 0
        x && y; // 1

  - `^` Sets 1 in each bit where its operators differ and 0 where they are the
    same.
  - `<<` and `>>` shift their left operator by the number of digits specified by
    the right operator. Left shifting always fills vacated bits by zero. Right
    shifting varies from machine to machine and whether or not we're talking
    unsigned or signed.

        int x = 2;
        x = x << 2; // x == 8
        x = x >> 1; // x == 4

  - `~` just does the one's complement, ie. flipping all the bits.

