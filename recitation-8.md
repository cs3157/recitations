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

## Declarations ##

It seems in order to prepare for the midterm, it might be a good idea to go over
some existing programs and declarations.

  - For integer expressions, write the actual number value in decimal notation.
    (Remember char is integer!)
  - For non-integer expressions, write the type name, in the format that you use
    to declare a variable of that type.
  - Write "invalid" if a given expression is not a valid C expression

Note:

  - Boolean expressions are integer expressions in C. Do not write true or
    false.
  - You can assume that the program is run with no command line argument

On the front of the exam, you'll find useful information (sometimes) like:

  - Language: C
  - Compiler: gcc
  - Platform: Ubuntu Linux 12.04, 64-bit version
  - Primitive type sizes: sizeof(int) is 4 and sizeof(int *) is 8

Now you know tons about the other types!

```c
struct Node {
  void *data;
  struct Node *next;
};

int main(int argc, char **argv)
{
  int a = 3;
  int b[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  struct Node arr[5] = {&a, arr+1, b, arr+2, "hello", arr+3};
```

Some tricky (maybe not) questions now:

  - `b[2]`
  - `sizeof(b)`
  - `sizeof(b[2])`
  - `sizeof(&b[0])`
  - `"hello"`
  - `arr[1].data[4]`
  - `arr[0].data[4]`
  - `sizeof(arr[3].next)`

## Git and Makefiles ##

Some key git commands to understand the basic usage of:

  - git clone
  - git status
  - git add
  - git commit

Make sure you know what levels of git tracking exist:

  - untracked
  - tracked, unmodified
  - tracked, modified, but unstaged
  - tracked, modified, staged
  - tracked, committed (??? What's wrong here?)

Also know how dependencies work in Make. Jae's sample makefile is really great
to use to understand this. I've included the relevant sections from recitation 2
below:

Take Jae's Makefile piece by piece. It can be found in this git repository as
`sample-makefile`

```make
CC  = gcc
CXX = g++
```

Make has a some pre-configured rules for how to compile programs. For example it
knows how to specify files as arguments to a compiler. However, you should tell
it what compiler to use for C files and C++ files. Here, we set the
special make variables CC and CXX to gcc, the C-compiler, and g++, the c++
compiler.

```make
INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)
```

Here we define our own variable, INCLUDES, which we can use for directories that
we wish to include at the compilation step. An example value for INCLUDES could
be `-I/home/jae/cs3157` which would tell the compiler to look in
/home/jae/cs3157 during the compilation step for missing header files and other
sorts of relevant files.

After defining INCLUDES, we define the flags that we want each compiler to be
run with. In this case we include the `-g` flag for debugging and `-Wall` flag
to display all warnings. Lastly, we reference our variable INCLUDES to add those
flags as well.

```make
LDFLAGS = -g
```

LDFLAGS are the flags that are appended to the compiler when using it for
linking. In this case we just want the debugging info to be included.

```make
LDLIBS =
```

LDLIBS will automatically be appended to the linker commands. These are flags
like `-lm` and function similarly to our INCLUDES variable but are added at a
different step. `m` denotes the math library.

That's about it for our variable declarations. The next step is to define
compile order and dependencies. The very first "target" or rule in your makefile
gets built when you type `make` in this case the first target is:

```make
main: main.o myadd.o
```

Note that we did not specify the linking rule, because make follows an implied
linking rule:

    $(CC) $(LDFLAGS) <all-dependent-.o-files> $(LDLIBS)

Also note that make assumes that main depends on main.o, so we could omit it:

    main: myadd.o 

Basically what this rule says is make should produce an executable called "main"
by linking myadd.o and main.o. This declares main.o and myadd.o as dependencies
of main, meaning that if any of the dependencies (or their dependencies) change 
between the last time this target was run, it should re-run the outdated targets
as well as this one.

The next target we declare is main.o:

```make
main.o: main.c myadd.h
```

This says that main.o depends on main.c (assumed) as well as myadd.h. See last
week's recitation notes to understand why main.o depends on myadd.h. We could
omit main.c as follows:

  main.o: myadd.h

Either way, we do not specify a rule here because make assumes the implicit
rule:

    $(CC) -c $(CFLAGS) <the-.c-file>

Lastly, we specify the target for myadd.o:

```make
myadd.o: myadd.c myadd.h
```

We'll include two phony targets. We tell make that they're "phony" so that it
doesn't attempt to use implicit rules or try to compile them. The first target
we make is "clean" which should remove all intermediate files. *Always include a
clean* so that `make clean` can be used to remove intermediate files like object
files, compiled code, etc. This should return your directory to just its source
code that can generate all the other files. *Be careful:* Using `rm -r` will not
prompt you to remove files. This is customary for `make clean` but it also means
if you make a mistake in designing your rule it could remove files that you
didn't want to. There is no "trash" in UNIX - they'll be gone forever.

Lastly, we define a phony "all" target that just depends on the main and clean
targets. This will always remove all intermediate files and compiled files,
forcing make to recompile everything when main is called.

```make
.PHONY: clean
clean:
        rm -f *.o a.out core main

.PHONY: all
all: clean main
```

