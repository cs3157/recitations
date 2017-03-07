## Bits, Bytes and Binary ##

Let's just refresh our memory about memory:

  - A **bit** is a single digit in binary; on or off; 1 or 0
  - 8 bits form a single **byte**: 11111111 = 2^8 - 1 = 255
  - **Hexadecimal** is another notation to count even higher in fewer places
    - Two hexadecimal places express 1 byte
    - FF in Hexadecimal is 255
  - **Two's complement**
    - Most modern computers use this notation for signed integers
    - **Most significant bit**: Usually the leftmost, but generally the bit 
    with the highest value: If 1000 = 8, then 1 is the most significant bit. 
    If we were using a different notation such as 1010 = 5, then the rightmost 
    0 is the most significant bit. 
    - If the most significant bit is 1, then in two's complement, you're 
    looking at a negative number
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

Be aware of some important boundaries as well:

  - 0x00000000 = 0
  - 0x7FFFFFFF = 2147483647
  - 0x80000000 = -2147483648
  - 0xFFFFFFFF = -1

### Bitwise Operators ###

While we're on the subject of binary representation, let's take a moment to 
examine C's bitwise operators. They're a bit tricky, but perform extremely fast 
low level operations and learning them well now will help you with more 
complex concepts later on.

#### Bitwise AND ###

The bitwise AND operator, `&`, takes two integers as operands and returns a 
new integer with a bit pattern consisting of ones only in the positions that 
both operands contain bits set to 1.

```
int x = 5;  // 0101 in binary
int y = 12; // 1100 in binary
x & y;      // 0100 (4)
```

Note: `x & y == 4`, but `x && y == 1`. Can you explain why?

This provides a handy way of checking the bit value at a given position in a 
number:

```
int mask = 8; // 1000 in binary, for checking the 4th bit
x & mask;     // 0, since 5 doesn't contain a 1 in the 4th bit
y & mask;     // 1000 == 8 > 0, since 12 contains a 1 in the 4th bit
```

#### Bitwise OR ####

The bitwise OR, `|`, behaves like the bitwise AND but the returned integer's 
bit pattern consists of ones where either operand has a 1.

```
int x = 5;  // 0101 in binary
int y = 12; // 1100 in binary
x | y;      // 1101 (13)
```

#### Bitwise XOR and Complement ####

The bitwise XOR, `^`, sets 1 in each bit where its operands differ and 0 
where they are the same. The bitwise complement, `~`, performs the one's 
complement on its operatand by flipping each bit.

#### Bit Shifting ####

The bitwise shift operators, `<<` and `>>`, shift their left operand by the 
number of digits specified by the right operand. Left shifting always fills 
vacated bits by zero.

Right shifting depends on whether we're dealing with signed or unsigned numbers.
Unsigned numbers and positive signed numbers fill vacated bits with zero.
Right-shifting negative signed numbers can produce varying results depending
on the machine and compiler.

```
int x = 2;  // 000010 in binary
x << 2;     // 001000 (8)
8 >> 1;     // 000100 (4)
```

## Data Types: Numbers ##

Integer Types:

  - char
  - int

Modifiers (and sugar):

  - short
  - long

Memory size for each type depends on system, and only restrictions are that

    char <= short <= int <= long <= long long

CLAC machines follow

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

Here are some declarations to help you understand what really happens when we're talking characters and integers. Definitely take a look at 
[The Ascii Table](http://www.asciitable.com) and understand the relationships 
in theorder of the first 128 ascii characters. The C language is built on a 
subset of 7-bit ascii (0-127) so its important to know what the table is like, 
not to memorize it. Also note that in C, single quotes means a character.

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
    (037777777777 == -1); //returns 1 (true)
    sizeof(1234L); //returns 8
    sizeof(1234); //returns 4
    0xFFFFU; //returns 65535
    0177777U; //returns 65535

Also not that converting a signed value to an unsigned value or vice verse
preserves the bit pattern:

```c
  char c = -1; //0xFF
  unsigned char uc = c; //0xFF
  int i = uc; //i == 255
```

Float and double are the two floating point types (decimal) and can be 
expressedwith a decimal point or as scientific notation:

    float miles = 1.8;
    double big = 1e10;

The only implementation constraint is that

    float <= double <= long double

so they could all be one size, or be three distinct sizes.

In C there is no such thing as a string, just an array and pointers.
Essentially, a bunch of single characters located consecutively in memory will
make up a string, but more on this later.


## Expressions ##

    char *myString = "Here's a string!" //string literal
    int x = 10; //variable declaration and assignment
    int x; //variable declaration
    x = 30; //variable assignment: lvalue = rvalue

The order of the increment/decrement operators in C matters:

    int x = 1;
    int y = x++; // y==1
    y = ++x; // y==3

Valid binary operators in order of increasing precedence:

  - + -
  - * / %

The positive and negative operators are more tightly binding than any of the
above operators (+/-).

Comparison operators:

  - < > <= >=

All of these comparison operators have the same precedence, and are more tightly
binding than the equality and inequality operators (==/!=).

The logical operators are `||` for or, `&&` for and, and `!` for not. The "or"
and "and" operators short-circuit.

[Bitwise operators](recitation-2.md#bitwise-operators) are tricky and can be 
used for a variety of purposes. See the examples in the recitation 2 notes for 
a refresher.

Ternary operator:

```c
x = a ? b : c;
```

is the same thing as this:

```c
if(a)
  x = b;
else
  x = c;
```

Note that any integer is also a boolean!! 0 is false, any other number is true!


## Statements ##

### If-Else Statements ###

```c
if(condition)
  if(condition2) {
    printf("conditions met");
    return 0;
  }
  else
    printf("no conditions met");
```

### Switch Statements ###

```c
switch(v) {
  case 1: // v == 1
    printf("v is 1");
    break;
  case 2:
    printf("v is 2");
    break;
  default:
    printf("v is neither 1 nor 2");
}
```

### Loops ###

```c
int i;
for(i = 0; i < 10; i++) {
    // do things here
}
while(i) { //condition checked at the beginning
    //other things
    i--;
}

do {
    //more things
} while(i < 5); //condition is checked at the end
```

Using `break;` inside a loop will break out of the innermost loop. Using
`continue;` will stop executing the current iteration of the loop and skip to
the next iteration. `for(;;)` is an idiom for an infinite loop. `goto label`
will jump to a line beginning with `label: `. Be careful with gotos.

## Appendix: Truth Tables for Bitwise Operations ##
### AND
If both bits are 1, the result will be 1. Otherwise, the result is 0.

`A` | `B` | `A & B`
:--:|:---:|:------:
0   | 0   | **0**
0   | 1   | **0**
1   | 0   | **0**
1   | 1   | **1**

### OR
If either bit is 1, the result will be 1. Otherwise, the result is 0.

`A` | `B` | <code>A &#124; B</code>
:--:|:---:|:--------------------------:
0   | 0   | **0**
0   | 1   | **1**
1   | 0   | **1**
1   | 1   | **1**

### XOR
If both bits differ, the result is 1. If both bits are the same, the result is 0.

`A` | `B` | `A ^ B`
:--:|:---:|:------:
0   | 0   | **0**
0   | 1   | **1**
1   | 0   | **1**
1   | 1   | **0**

### NOT
The result is the opposite of the bit's current value.

`A` | `~A`
:--:|:-----:
0   | **1**
1   | **0**
