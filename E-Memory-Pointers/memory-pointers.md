## Variables ##

### Stack Variables ###

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
    global_static++;
    magicPrint();
	return 0;
}
```

In another file:

```c
void magicPrint() {
    extern int global_static;
    printf("%d\n", global_static); //prints 1
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
  return 0;
}
```

Note not only the difference in the function, but how the parameters are passed.
**Passing a pointer is fundamentally a different type than passing a value.**

For more pointer examples, see `recitation-4-code/basicpointers.c`

---- 

## Arrays (jk they're the same thing) ##

C has arrays, but they're basically just pointers. An array has a type, just
like a pointer, and represents multiple instances of enough space for that type
in contiguous memory.

```c
int a[10];
```

This would allocate space on the stack for 10 integers in contiguous memory
locations. i.e., `a[0]` is located immediately before `a[1]`, and the entire `a`
array is on the stack. Arrays generally operate like you're used to in Java or
other languages:

```c
int a[10];
a[0] = 0;
int i = 3;
a[i] = -1;
```

However note that arrays in C have no bound checking, so you can access something
past the end of the array. It may even work, at least most of the time, but
it's illegal. Valgrind testing can catch some of this, and compiler warnings might
catch others, but it's up to the programmer to be careful.

```c
int a[10]
a[10000]; //the compiler lets you do this, but it's illegal
```
Declaring multidimensial arrays is also possible, but fairly rare.

    int matrix[50][50];


## Pointer Arithmetic ##

If you have a pointer, you can do basic arithmetic with it to address
adjacent elements. All arithmetic is with respect to the element being addressed,
so if you have an int pointer `p`, `p+1` points to the next int, which is 4 bytes later.
So usually you should think in terms of elements, not in terms of bytes.

```c
int *p = q; //p is a pointer to int; It's pointing to the same place as q, exactly where doesn't matter now
p+1; //this is a pointer-to-int that's point to an integer that immediately follows p
*(p+1); //this is an integer, the dereferenced value pointed to by the previous line
*p++; //this returns the current derefenced value (ie the integer), and advanced the pointer to the next element
     //the above is VERY common when looping over arrays in C
```

Because arrays are just contiguous blocks of memory, you can access them using
both pointer arithmetic and array notation:

```c
int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int *p = a; // p points to the first element of `a`, 0
int *p = &a[0]; //p still points to 0

*(p+5) == a[5]; // 5 == 5

p+5 == a+5; // p+5 is a pointer to the 5th element of the array, so is a+5
p++; // ok: `p` is just a pointer like any other, p now points to the next element in the array
a++; // illegal (will throw an error): `a` is an array name, a constant variable
size_t x = sizeof(a); // x == 40
size_t y = sizeof(p); // y == 8
/* NOTE: sizeof is an operator, not a function!
    sizeof is evaluated at COMPILE TIME, so the
    size must be known based on only the source,
    not any runtime parameters.
    It can tell the difference between a pointer and
    an array INSIDE the scope in which it was declared.
    */
```

In almost all cases using the variable name of an array with no brackets, ie `a` above,
is treated as pointer-to pointing to the first element of the array, not an array-of.
The majors exceptions are `sizeof` inside the scope in which the array was declared,
and when used as the left hand side of an assignment. When passed into functions,
dereferenced with `*`, used in arithematic it behaves like a pointer-to-type that
points to the first element of the array.

Unlike a pointer, though, an array is a constant variable. You cannot change its
assignment after it has been created, it must point to the same chunk of memory.
```c
int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int *p = a; // p points to the first element of `a`, 0

p++; // ok: `p` is just a pointer like any other, p now points to the next element in the array
a++; // illegal (will throw an error): `a` is an array name, a constant variable
```

Note that as discussed above, `sizeof` is an operator, not a function. 
sizeof is evaluated at *compile time*. This means that the value of the
operator cannot be anything that depends on user input.


### Strings in C ###

Strings in C are just a special case of arrays: C strings are arrays of
characters with a null terminating character at the end.

```c
char c[] = "abc";
char c[] = {'a', 'b', 'c', '\0'};
char *s = "my string"; // modifiable pointer
"my string"[0] == 'm' //true!
```

There's a slight difference between these two definitions. `c` is an array which
means you can't move where it points to: it's always going to point to the character 
`a`. `s`, on the other hand, can be incremented and decremented and moved around 
however you like. `"my string"`, however, can't be modified; it's a string literal! 

Some useful string functions (need to `#include string.h`):
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
For a closer look at the strcpy function, see [`E-Memory-Pointers/code/strcpy.c`](https://github.com/cs3157/recitations/blob/master/E-Memory-Pointers/code/strcpy.c).

So how about an array of strings? Well that would be an array of arrays.

```c
char *a[] = {"hello", "world" };
char **p = a;
char a[][10] = {"hello", "world" }; //what's the difference here?
```

You can find more examples of this in [`E-Memory-Pointers/code/ptrtoptrs.c`](https://github.com/cs3157/recitations/blob/master/E-Memory-Pointers/code/ptrtoptrs.c).


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

### Valgrind+Makefile=Good ###

Remembering to run valgrind, and retyping the command, is annoying. A clever way
to more easily run valgrind repeatedly as part of your normal edit/compile/test
loop is to add valgrind to your makefile. Remember how you can include phony
targets in your Makefile? We can use that to have it run Valgrind for us.

For example, using Jae's Makefile template from lecture note 1, you can add a
stanza at the end:

    .PHONY: valgrind
    valgrind: main
        valgrind --leak-check=yes ./main
      

Then instead of running `make` followed by `./main` you can just run
`make valgrind` and it will compile your code and run it under valgrind.


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

### Uninitialized values ###

Valgrind will also inform you when the visible behavior of the program is affected by usage of uninitialized values. For example, let's say you want to increment a variable, but forget to initialize it:
```c
int *d = (int *)malloc(sizeof(int));
++*d;
printf("%d\n", *d);
```
Valgrind will inform you that the visible behavior of your program depends on an uninitialized, hence unpredictable, values. Always be sure to initialize your variables before using them! 

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
