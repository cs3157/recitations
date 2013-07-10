# Recitation 4 #

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
  - spacing of asterisk doesn't matter, but \*p is generally preferable as it makes declarations clearer.  `int* p1, p2;` would lead you to assume that both p1 and p2 are being declared as type int* (a pointer to an integer), but in reality the compiler interprets this statement as if it was written `int *p1; int p2;` - declaring p1 as a pointer to int and p2 as a normal int.  Writing the declaration as `int *p1, p2` will avoid confusion in such cases.
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
the pointer. In this case we're dealing with an int so it will likely move it
ahead 4 bytes to the next int. Unlike a pointer, though, an array is a constant
variable.

### Strings in C ###

Strings in C are just a special case of arrays. C strings are arrays of
characters with a null terminating character at the end.

```c
char c[] = "abc";
char c[] = {'a', 'b', 'c', '\0'};
char *s = "my string"; // modifiable pointer
```

There's a slight difference between these two definitions. c is an array which
means you can't move where it points to, its always going to point to a. s on
the other hand can be incremented and decremented and moved around however you
like.

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
