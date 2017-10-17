# Mid-Semester Review 1 #

This document is an outline of what's covered in our mid-semester review
session. If you'd like more detail, use the link in each section to see the full
review session notes for that topic.


## Bits, Bytes, and Binary ##

_Main article: [Bits, Bytes, and Binary](D-Bits-Binary-C-Basics/bits-and-binary.md)_

Let's refresh our memory about memory:

- **Bit** (b)
  - A single digit in binary
  - Two possible values: 1 or 0
- **Byte** (B)
  - 8 bits make a byte
  - Can take on 2^8 = 256 different values (from 0 to 255, inclusive)
- **Hexadecimal**
  - A base-16 numerical notation that can represent up to 15 in a single digit
  - Uses base-10 + first 5 letters of alphabet:
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, b, c, d, e, f }
  - 2 hexadecimal digits make a byte
- **Least significant bit** (LSB)
  - Right-most binary digit
- **Most significant bit** (MSB)
  - Left-most binary digit
  - Indicates positive or negative for signed integers

### Two's Complement ###

-   MSB indicates whether number is positive (0) or negative (1)
-   If negative, invert all bits and add 1 to find out what number is
    represented

The table shows the same bit pattern interpreted as unsigned and signed
integers, assuming that integers are 3 bits long:

Binary | unsigned decimal | two's complement decimal
------ | ---------------- | ------------------------
000    | 0                | 0
001    | 1                | 1
010    | 2                | 2
011    | 3                | 3
100    | 4                | -4
101    | 5                | -3
110    | 6                | -2
111    | 7                | -1


## C Basics ##

_Main article: [C Basics](D-Bits-Binary-C-Basics/c-basics.md)_

### Data Types: Numbers ###

Memory size for each type depends on system, and only restrictions are that

    char <= short <= int <= long <= long long

CLAC machines follow:

Type        | Size
----------- | -------
`char`      | 1 byte
`short`     | 2 bytes
`int`       | 4 bytes
`long`      | 8 bytes
`long long` | 8 bytes

Use the `sizeof` operator to find the size of a data type in bytes:

```c
// sizeof on a data type
printf("ints are %d bytes", sizeof(int));

// Works on variable names too
char *p;
printf("pointers are %d bytes", sizeof(p));
```


### ASCII ###

-   The "character" or `char` data type is simply a very small integer
-   C uses a system called ASCII encoding to assign a number to each character
    -   For example, `'a'` is 97
-   See [ASCII table](http://man7.org/linux/man-pages/man7/ascii.7.html) for the
    complete list
    -   Focus on understanding relationships between values rather than trying
        to memorize the whole thing
    -   For example, capital letters have smaller numerical values than
        lowercase ones

Here are some integer declarations and the corresponding values of the
variables:

Declaration       | x (dec)   | y (dec)
----------------- | -------   | -------
`int x;`          | undefined | -
`int x, y;`       | undefined | undefined
`int x = 0, y;`   | 0         | undefined
`char x = 'x';`   | 120       | -
`char x = '\n';`  | 10        | -
`char x = '\13';` | 11        | -
`char x = '0';`   | 48        | -
`char x = '\0';`  | 0         | -
`char x = 0;`     | 0         | -


### Different notations for integer literals ###

-   Single quote `'` means character (double quotes `"` are for strings)
-   `0x` at the beginning means hexadecimal notation
-   `0` at the beginning means octal notation

So, the following literals all have the same value:

    '@'   // character literal
    0x40  // hexadecimal
    0100  // octal
    64    // decimal

Some more hex and octal examples:

    (0xFFFFFFFF == -1)    // equal to 1 (which is true, but C doesn't have true)
    (037777777777 == -1)  // 1 (true)
    0xFFFFU               // 65535
    0177777U              //  65535


### Floating point types ###

The only implementation constraint is that

    float <= double <= long double

Floating point types can be expressed with a decimal point or scientific
notation:

```c
float miles = 1.8;
double avogadro = 6.02e23; // 6.02 x 10^23
```


### Strings ###

-   No string object in C
-   C "strings" are an array of characters
-   Have a null byte (`'\0'` or `0`) at the end

```c
char *s = "cs3157";
// similar to the array { 'c', 's', '3', '1', '5', '7', '\0' }
```


### Bitwise Operators ###

- `&` can be used to "mask" or turn off all bits except certain ones. For
  example:

  ```c
  n = n & 0177; // n bitwise-and 00000001111111
  ```

- `|` can be used to ensure that bits are set:

  ```c
  n = n | 0177; // n bitwise-or 00000001111111
  ```

- It's easy to confuse bitwise and `&` with logical and `&&`:

  ```c
  printf("%d\n", 1 & 2);  // 0
  printf("%d\n", 1 && 2); // 1
  ```

- `^` is a bitwise exclusive or. The resulting bit is 1 if the inputs were
  different, and 0 if they were the same.

- `~` flips all the bits.

- `<<` and `>>` shift their left operand by the number of digits specified by
  the right operand. Left shifting fills vacated bits by zero. Right shifting
  typically fills with whatever the MSB was.

  ```c
  int x = 2;
  int y = x << 2; // y == 8
  int z = x >> 1; // z == 1
  ```


### Order of Operations ###

Make sure you're familiar with [operator precedence in C](http://en.cppreference.com/w/c/language/operator_precedence).

Based on the precedence rules, what does `*p++` do?


## Test yourself: C Basics ##

On midterm 1, a common type of question provides a C program, then asks you to
evaluate some expressions based on what was declared or run in that program.

The instructions will typically say:

-   For integer expressions, write the actual number value in decimal notation.
    -   Remember — `char` is a type of integer!
    -   Boolean expressions, such as `x == 1`, are also integer expressions.
        This means you should never write "true" or "false."
-   For non-integer expressions, write the type name, in the format that you use
    to declare a variable of that type.
-   Write "INVALID" if a given expression is not a valid C expression.

On the front of the exam, you might find useful information like:

> Language: C<br>
> Compiler: gcc<br>
> Platform: Ubuntu Linux 16.04, 64-bit version<br>
> Primitive type sizes: `sizeof(int)` is 4 and `sizeof(int *)` is 8

Now you know tons about the other types!

Consider the following program:

```c
struct Node {
  void *data;
  struct Node *next;
};

int main(int argc, char **argv)
{
  int a = 3;
  int b[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  struct Node arr[5] = { &a, arr + 1, b, arr + 2, "hello", arr + 3 };
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


## Git ##

_Main article: [Git](C-Git/git.md)_

Some key Git commands to understand the basic usage of:

    git clone
    git status
    git add
    git commit

Use `git help <command>` to see the manual page for a command.

Make sure you know what levels of tracking exist:

  - untracked
  - tracked, unmodified
  - tracked, modified, but unstaged
  - tracked, modified, staged
  - tracked, committed


## Makefiles ##

_Main article: [Makefiles](B-Makefiles/makefiles.md)_

Let's review Jae's sample Makefile piece by piece:

> ```make
> CC  = gcc
> CXX = g++
> ```

Make has a pre-configured rules for how to compile C programs. We just need to
set Makefile variables for the C compiler (`CXX`) and C++ compiler (`CXX`).

> ```make
> INCLUDES =
>
> CFLAGS   = -g -Wall $(INCLUDES)
> CXXFLAGS = -g -Wall $(INCLUDES)
> ```

Here we define our own variable, `INCLUDES`, which use to specify directories
to search for header files during compilation. For example, the value
`-I/home/jae/cs3157` would tell the compiler to look in `/home/jae/cs3157` for
header files.

Also set the flags we want each compilation to run with. What do these flags
mean? We also reference our `INCLUDES` to add those flags as well.

> ```make
> LDFLAGS = -g
> ```

Flags to pass during the linking step.

> ```make
> LDLIBS =
> ```

`LDLIBS` will automatically be appended to the linker commands. These are flags
like `-lm` for linking the math library. It's analogous to our `INCLUDES` from
the compilation step.

Now we define the dependencies of our files. The first target we specify is
run if we simply type `make`:

> ```make
> main: main.o myadd.o
> ```

This rule means that make should produce an executable `main` by linking
`main.o` and `myadd.o`. When either `.o` file is modified, it will regenerate
`main` the next time we run `make`.

If we don't provide a command to run, make follows this implied linking rule:

    $(CC) $(LDFLAGS) <all-dependent-.o-files> $(LDLIBS)

It also assumes that `main` depends on `main.o`, so we could have omitted
`main.o` like this:

```make
main: myadd.o
```

(Take a moment to understand how all of that works. Makefile dependencies are an
important topic!)

> ```make
> main.o: main.c myadd.h
> ```

Again, we don't specify a command here because make assumes the implicit rule:

    $(CC) -c $(CFLAGS) <the-.c-file>

Just as before, the dependency of `main.o` on `main.c` is implicit. So we could
have omitted `main.c`.

Why does main.o depend on main.h?

> ```make
> myadd.o: myadd.c myadd.h
> ```

Same as previous.

> ```make
> .PHONY: clean
> clean:
>         rm -f *.o a.out core main
> ```

Since the `clean` target is "phony," make won't look for a file named `clean` to
decide whether it should run the commands in the target. So `make clean` will
always run, even if there is a file named `clean` in the directory.

The first phony target removes the compiler-generated files so that only the
source code is left.

> ```make
> .PHONY: all
> all: clean main
> ```

Make runs its dependencies left-to-right. So the `all` target will first run
`clean`, then generate `main`. Run `make all` when you want to completely
recompile the program from scratch, without using any previously compiled files.


## Function Pointers ##

_Main article: [Function Pointers](F-Function-Pointers/function-pointers.md)_

-   Problem: want to write an algorithm then let users customize its
    functionality
    -   Example: a sorting algorithm may let users specify whether characters
        should be compared lexicographically, or by Unicode value
-   Solution: The caller passes a pointer to a function that implements the
    desired feature

Example of accepting a function as an parameter to your function:

```c
void notifier(int (*fn)()) {
  printf("Starting\n");
  fn();
  printf("Finished\n");
}
```

-   Basic layout for a function pointer type is
    `returnType (*functionName)(parameterType1, parameterType2, ...)`
    -   More examples: [goshdarnfunctionpointers.com](http://goshdarnfunctionpointers.com)
-   This denotes the return and parameter types of functions you can accept
-   Parentheses are necessary even if there are no arguments
-   What does the function do?

Passing a function as a parameter:

```c
int wasteTime() {
  int i;
  for (i = 0; i < 1000000; i++) { }
  printf("Finished counting to %d\n", i);
  return i;
}

int main(int argc, char **argv) {
  wasteTime(); // Calling the function directly
  notifier(wasteTime); // Passing a pointer to the function

  return 0;
}
```

-   Notice the difference between calling a function directly and passing it as
    a function pointer
-   Everything in the program is stored in memory — this means the `wasteTime`
    function's code also has an address
-   Calling a function causes the program to start executing code at that
    address
-   Getting a pointer to the function instead gets the value of that address
    -   Value can be stored in a variable or passed as a parameter

Storing a function pointer in a variable (this example is equivalent to the one above):

```c
int main(int argc, char **argv) {
  int (*f1)();
  f1 = wasteTime;

  f1(); // Calling the function through the function pointer
  notifier(f1); // Passing a pointer to the function

  return 0;
}
```

-   Call function pointers by adding parentheses to the end of the variable name
-   Check out Jae's notes (lecture 7) for more complicated examples


## Memory Errors ##

_Main article: [Memory and Pointers](E-Memory-Pointers/memory-pointers.md)_

Here are some common Valgrind errors:

### Illegal read / write errors ###

```c
int a[10];
a[10] = 42; // wrote past the end of the array
```

### Illegal frees ###

```c
char *p = malloc(16);
free(p);
free(p); // p was already freed, so you can't free it again
```

### Use of uninitialized values ###

```c
char *p = malloc(16);
char c = p[0]; // nothing was written to p[0] before reading from it

int n;
printf("%d\n", n); // nothing was written to n before passing it as an argument
```

You can find a full list of errors and more detailed explanations in the
[Valgrind manual, Section 4.2: Explanation of error messages from Memcheck](http://valgrind.org/docs/manual/mc-manual.html#mc-manual.errormsgs).


## Other exam tips! ##

Just some things it might pay to know well:

-   What `MdbRec` structs look like and how to use them
-   How to use the functions from lab3 and what they return
-   What the pipeline for lab5 looked like and how it worked
-   **Please follow directions!** The exam will be graded in the same way your
    labs are graded if not less lenient. Read all the directions. Take your time
    to understand them. If it says "write the line number and the code that
    should be on that line," do just that!

Thanks for reading these notes. Good luck on the exam!
