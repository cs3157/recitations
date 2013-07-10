# Recitation 3: Welcome to C #

## Bits Bytes and Binary ##

Let's just refresh our memory about memory:

  - A **bit** is a single digit in binary; on or off; 1 or 0
  - 8 bits form a single **byte**: 11111111 = 2^8 - 1 = 255
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
    - Consult the following table to see something interesting (note the
      wraparound effect):
      
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


## Data Types: Numbers ##

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
    (037777777777 == -1); //returns 1 (true)
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

## Expressions ##

    char *myString = "Here's a string!" //string literal
    int x = 10; //variable declaration and assignment
    int x; //variable declaration
    x = 30; //variable assignment: lvalue = rvalue

The order of the increment/decrement operators in C matters:

    int x = 1;
    int y = x++; // y==1
    y = ++x; // y==3

Valid bianry operators in order of increasing precedence:

  - + -
  - * / %

The positive and negative operators are more tightly binding than any of the
above operators (+/-).

Comparison operators:

  - < > <= >=

All of these comparison operators have the same precedence, and are more tightly
binding than the equality and inequality operators (==/!==).

The logical operators are `||` for or, `&&` for and, and `!` for not. The "or"
and "and" operators short-circuit.

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

Ternary operator:

```c
x = a ? b : c;
//or
if(x)
  b;
else
  c;
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
switch(v)
  case 1: // v == 1
    printf("v is 1");
    break;
  case 2:
    printf("v is 2");
    break;
  default:
    printf("v is neither 1 nor 2");
end
```

### Loops ###

```c
int i;
for(i = 0; 1 < 10; i++) {
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

## Variables ##

###Stack Variables ###

When you declare a variable in C, it is defined for the current scope and will
be released at the end of the scope. If you redeclare a variable inside a scope
within a scope (see below) you won't be able to change the outer variable.

```c
int x;
x = 0;
//do things with x
{
    int x;
    x = 1;
    //x is now 1 within here
}
//x is still 0 out here
```

The above are automatic variables or **stack variables**. Their scope is local
to a block (code enclosed by curly braces as shown above) - they are created when entering the block and destroyed upon exit.

### Static Variables ###

Many different meanings depending on where you declare:

```c
int global_static = 0;

static int file_static = 0;

int foo(int auto_1) {
    static int block_static = 0;
}
```
In general, global/static variables are created when the program runs and
persist until the program ends. This means they will not be re-declared or
re-initialized.

### Global Variables ###

Global variables are like a special case of static variables. They are
accessible from all files in the program, and if they are declared within the
current file already you don't need to use the `extern`. See below:

In one file:
```c
int global_static = 0;

int main() {
    int global_static;
    global_static++;
    magicPrint();
}
```

In another file:

```c
void magicPrint() {
    extern int global_static;
    printf("%d", global_static); //prints 1
}
```

## Address Space ##

Every process gets 512G of virtual memory space. The stack grows downward (see Jae's
notes for a diagram) starting from 512G while the program code, static
variables, and heap variables are all at the bottom (0). Basically, this means
when functions are called, space for them is built up on the stack and cleared
as they complete. Heap variables (you'll learn more about these later) will be
allocated on the heap and therefore, like static variables, will not be cleared
after each function call.
