# Recitation 4 #

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
to a block (code enclosed by curly braces as shown above) - they are created 
when entering the block and destroyed upon exit.

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

## Pointers ##

Pointers are what will get you a job. Understanding pointers is crucial and
using them naturally will make you stand out as a programmer. Let's start with
the basics.

**Pointer:** A variable that stores a memory address. That's it.

Pointers can have types as well so you know what kind of address you're dealing
with. They're pretty nifty. An asterisk denotes pointer types.

Here's an example:
```c
int x = 5;
int *p; // integer pointer
int* p2; // also integer pointer
p = &x; // operator
*p == 5;
```

Note:
  - spacing of asterisk doesn't matter, but \*p is generally preferable as it 
makes declarations clearer.  `int* p1, p2;` would lead you to assume that both 
p1 and p2 are being declared as type int* (a pointer to an integer), but in 
reality the compiler interprets this statement as if it was written 
`int *p1; int p2;` - declaring p1 as a pointer to int and p2 as a normal int.  
Writing the declaration as `int *p1, p2` will avoid confusion in such cases.
  - * is also an operator that will dereference a pointer (get you its value)
  - & is an operator that will reference a value (get you its address)

### Why use pointers? ###

C is a call-by-value language which means if you want a function to modify a
value that you have, you'll have to tell the function where to find the memory,
not just the value, otherwise C will just make a copy:

```c
void increment(int x) {
  x++;
}
void actually_increment(int *x) {
  (*x)++
}
int main() {
  int x = 1;
  increment(x); // x is still 1
  actually_increment(&x); // x is now 2
}
```

Note not only the difference in the function, but how the parameters are passed.
**Passing a pointer is fundamentally a different type than passing a value**

For more pointer examples, see `recitation-4-code/basicpointers.c`

## Arrays (jk they're the same thing) ##

C has arrays, but they're basically just pointers. An array has a type, just
like a pointer, and represents multiple instances of enough space for that type
in contiguous memory.

```c
int a[10];
```

This would allocate space for 10 integers in contiguous memory locations.
Declaring multidimensial arrays is also possible.

    int matrix[50][50];

Because arrays are just contiguous blocks of memory, you can access them using
pointer arithmetic, or natural array notation:

```c
int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int *p = &a[0]; //p points to 0
*(p+5) == a[5]; //5 == 5
magic_function(a); (passes a pointer to the first element of a)
p+5 == a+5;
p++; //legal
a++; //illegal!
```

In most cases, just calling an array by its variable name without the square
brackets will be interpreted as a pointer to the first element of the array. 
Incrementing a pointer will always move it ahead not one byte, but the size of
the type to which it's pointing. In this case we're dealing with an int so it will likely move it
ahead 4 bytes to the next int. Unlike a pointer, though, an array is a constant
variable.

### Strings in C ###

Strings in C are just a special case of arrays. C strings are arrays of
characters with a null terminating character at the end.

```c
char c[] = "abc";
char c[] = {'a', 'b', 'c', '\0'};
char *s = "my string"; // modifiable pointer
"my string"[0] == 'm' //true!
```

There's a slight difference between these two definitions. c is an array which
means you can't move where it points to, its always going to point to a. s on
the other hand can be incremented and decremented and moved around however you
like. "my string", however, can't be modified; it's a string literal! 

Some useful string functions (need to #include string.h):
```c
char d[20];
char c[] = "abc";
strcpy(d, "123");
strcat(d, c);

printf("%s\n", d); //prints 123abc
printf("%lu\n", strlen(d)); //prints 6

//to only copy/cat the first n chars:
strncpy(d, "456", 2); 
strncat(d, "def", 2);

printf("%s\n", d); //what does this print?
```
For a closer look at the strcpy function, see `recitation-4-code/strcpy.c`

So how about an array of strings? Well that would be an array of arrays.

```c
char *a[] = {"hello", "world" };
char **p = a;
char a[][10] = {"hello", "world" }; //what's the difference here?
```

You can find more examples of this in `recitation-4-code/ptrtoptrs.c`

## Heap allocations ##

Sometimes you need memory to persist across function calls (recall
pseudo-pass-by-reference using pointers). Recall also that variables declared
within a scope will be cleared once the scope's stack frame collapses. In other
words, if you're trying to pass back a pointer to a variable that was declared
within the function as a return value, it won't be there when you try to access
it. To alleviate this you can allocate space on the heap using malloc.

(From Jae's notes)
```c
int *p = (int *) malloc(100 * sizeof(int));
// malloc returns NULL if it cannot allocate the requested memory
if (p == NULL) {
  perror("malloc failed");
  exit(1); 
}
// initialize all elements to 0
for (int i = 0; i < 100; i++)
  p[i] = 0;
// another way to do the same thing
memset(p, 0, 100 * sizeof(int));
//free() deallocates the memory block previously returned by malloc.
free(p);
```

## Memory Errors ##

You'll be testing your code with valgrind for this class to make sure you don't
have any memory errors in your code. This can include forgetting to free
allocated memory, accessing memory that doesn't exist, etc. To run valgrind call:

    valgrind --leak-check=yes ./your_executable

Recall from other classes that if valgrind doesn't return, it means your program
isn't returning (this is a case of the halting problem). If your valgrind isn't
giving you line numbers (and is giving you hex codes) then you're not compiling
with the debugging flag `-g`.

The following are excerpts from `recitation-4-code/invalidwrite.c` and
`recitation-4-code/leak.c`.

### Invalid Write ###

This is pretty easy to do but hard to catch in your code. Like many memory
errors its usually caused by an off-by-one error. Imagine this:

```c
int *p = (int *)malloc(sizeof(int));
// checking that malloc worked
if (p == NULL) {
  perror("malloc failed");
  exit(1);
}
```

You'll have a pointer, `p`, to one integer worth of space. Now imagine we move
our pointer ahead one integer

```c
p++;
```

`p` will now point past the space it was allocated. We know nothing about this
space. It could be accessible, it could be protected. It could be someone else's
variable that we're about to change. *This is terrible*. But let's mess around
with it.

```c
*p = 5;
```

What happens? You've got an invalid write. What about

```c
int x = *p
```

Now you've got an invalid read. Valgrind will tell you about these and where
they're happening. So long as you know what you're looking for you should be
able to find it.

### Memory leaks ###

Calling malloc without free-ing the memory you've allocated is awful. If you
don't free space that's malloced when you're finished, it will persist even
after your program exits. To correct for this, when you're finished, just call
`free()` on the pointer to the memory that was malloced.

```c
free(--p);
```

Now aside from those invalid read/writes, our program will run through valgrind
pretty happily. The trick to memory leaks isn't just in free-ing that integer
though. Imagine you've malloced space for an array of arrays, each of which was
also malloc'ed. You'll have to go back through, freeing each individual array,
and then when you're finished with that, free the higher order array.

## Lab 2 ##

Tips:

  - Test all your code with valgrind. Just do it.
  - Watch out for fence post errors when it comes to invalid read/writes. You're
    probably just one outside of your bounds
  - Watch out for being just inside your bounds on freeing. If you have a leak,
    its probably because you forgot to free one last element.
  - Don't forget that in C, strings are characters arrays followed by a *null
    character*. Without the null character, C has no idea where you string ends!
  - ALWAYS check the return value of malloc to make sure you were actually given
    allocated memory.
  - Name your executables properly. For part1, `isort` and for part2, `twecho`.
