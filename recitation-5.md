# Recitation 5 #
The main topics for these notes will be those useful for lab 3, material from
lecture note 9, and useful information for the practice midterm.

## Function Pointers (K&R 5.11) ##
It is often the case in programming that you'll want your program to change its
behavior for the person using your program but have no idea how they may want to
do this. For example, when writing a sort function, you could just specify a
parameter that let's them choose between sorting ascending and descending.
However, what if they wanted to sort characters by their unicode value instead of
lexicographically? For this, the user has to supply their own functionality.
That's where you need function pointers. Some higher level (read
lambda-programming languages) support this is in a more intuitive way, but C
does a pretty good job itself.

### Accepting functions as a parameter to your function ###

Function pointers allow you to accept as a parameter to your function, another
function. Let's start out with accepting functions as a parameter:

```c
void notifier(int (*fn)()) {
  printf("Starting\n");
  fn();
  printf("Finished\n");
}
```

Let's examine this more closely. We have a function called notifier whose only
parameter is another function. How do we do this? we specify what kind of
function it accepts. The basic layout for a function pointer type is `returntype
(*functionName)(parameter1type, parameter2type, ...)`. Why? Well the returntype
denotes the type of the function. The name of the function being preceded with
an asterisk tells us its a pointer. The function is surrounded by parentheses so
that the compiler doesn't think we've got a variable `returntype *functionName`.
The parenthesis following the declaration are necessary as well, even if the
function we want to accept doesn't have any arguments. The parameter's only need
their types declared so that the compiler can check these. Since you won't have
access to the code you don't need to worry about what to call them.

### Passing a function as a parameter ###

```c
int wasteTime() {
  int i = 0;
  while(i < 1000000)
    i++;
  return i;
}

int main(int argc, char **argv) {
  wasteTime();
  notifier(wasteTime);
  return 0;
}
```

Notice how we have a function `wasteTime`. And when we follow it with
parentheses it gets called. When we don't, it is automatically a function
pointer. Why is this?

Well everything in the program is stored in memory, even the functions, which
means even they have an address. So `wasteTime` has an address in memory. When
you follow `wasteTime` with parentheses (`wasteTime()`), C goes to the address
and executes the function. If you think of `wasteTime` as storing a pointer to a
function, then you can think of `wasteTime()` as dereferencing the pointer.
Therefore, when we call `notifier` and pass it `wasteTime` without parentheses, it
passes the address to `wasteTime` to the `notifier` function.

### Calling functions from pointers ###
We could further use the functions above as follows:

```c
int main(int argc, char **argv) {
  int (*f1)();
  char *(*f2)(char *, const char *);
  char arr[5] = "bann"

  f1 = wasteTime;
  f2 = strcpy;

  notifier(f1);
  f2(arr, "hihi");
  printf("%s\n", arr);
}
```

As you can see from the above code, you can declare variables of "function
pointer" type and assign function pointers to their values. Then you can call
those functions simply by adding parentheses to the end of the variable name.
Make sure to check out Jae's notes (lecture 7) for more complicated examples of
this. Notice that we did the same thing when calling `fn()` in our `notifier`
function.


### Functions vs Pointers to Functions ###
Functions aren't quite like regular variables, so function pointers aren't quite
like regular pointers either. Think about this small program:

```c
void myFunc(int x) {
  x++; //this function is irrelevant...
}

int functionAcceptor(void (*f)(int), void (*g)(int)) {
  return f == g;
}

int main() {
  char *s = functionAcceptor(myFunc, &myFunc) ? "They're the same thing" :
    "They're totally different.";
  printf("%s", s);
}
```

What will this program print?

```
They're the same thing
```

Why? Because referencing a pointer to a function just gets you the same
pointer back. It has no effect. Too bad. Boring.


## Makefiles ##

Makefiles aren't as hard as they look so long as you understand the three steps
to compilation. [(Source
here)](http://stackoverflow.com/questions/6264249/how-does-the-compilation-linking-process-work)

1. Pre-processing: This is when special isntructions like `#include` are
processed.
2. Compilation: This is when your c code is processed into an object file in
binary form. At this point, undefined symbols are okay so long as they're
declared. That's why you `#include` header files - to declare functions and
variables that you don't define in that particular file. `gcc` lets you stop the
entire process at this point using the `-c` flag. Object files generated in this
step can be linked together to form an executable or put in a special archive
called a static library. Most error checking takes place at this stage.
3. Linking: The linker takes object files with binary symbols and produces
either a shared (AKA dynamic) library, or an executable. At this point it
replaces all the references to undefined symbols with the proper memory address.
Most often at this stage the only errors left come from double-defined symbols
or undefined symbols.

Now let's take a look at the Makefile's default rules and variables:

Compilation (includes pre-processing):
```make
n.o:
  $(CC) -c $(CPPFLAGS) $(CFLAGS) n.c
```
Linking:
```make
n:
  $(CC) $(LDFLAGS) n.o $(LOADLIBES) $(LDLIBS)
```

Let's take a look at some of the variable definitions we've used in the past:

```make
CC  = gcc
INCLUDES =
CFLAGS   = -g -Wall $(INCLUDES)
LDFLAGS = -g
LDLIBS =
```

And here are some entries from running `man gcc`:

```
gcc [-c|-S|-E] [-std=standard]
           [-g] [-pg] [-Olevel]
           [-Wwarn...] [-pedantic]
           [-Idir...] [-Ldir...]
           [-Dmacro[=defn]...] [-Umacro]
           [-foption...] [-mmachine-option...]
           [-o outfile] [@file] infile...
-g  
           Produce debugging information in the operating system's native format (stabs, COFF, XCOFF, or DWARF 2).
           GDB can work with this debugging information.

           On most systems that use stabs format, -g enables use of extra debugging information that only GDB can
           use; this extra information makes debugging work better in GDB but will probably make other debuggers
           crash or refuse to read the program.

-Wall
           Turns on all optional warnings which are desirable for normal code.  At present this is -Wcomment,
           -Wtrigraphs, -Wmultichar and a warning about integer promotion causing a change of sign in "#if"
           expressions.  Note that many of the preprocessor's warnings are on by default and have no options to
           control them.

-I dir
           Add the directory dir to the list of directories to be searched for header files.  Directories named by -I
           are searched before the standard system include directories.  If the directory dir is a standard system
           include directory, the option is ignored to ensure that the default search order for system directories
           and the special treatment of system headers are not defeated .  If dir begins with "=", then the "=" will
           be replaced by the sysroot prefix; see --sysroot and -isysroot.

-Ldir
           Add directory dir to the list of directories to be searched for -l.

-llibrary
-l library
           Search the library named library when linking.
```

Given what we know about compilation, where might we want to use these flags and
for what purposes? The order we use these flags and the variables we insert them
in is **very** important.

## Important Things to Review ##

- Arrays, pointers, and the structure of argv. Understanding how these data
  types and structures work will be crucial to your understanding of C as this
  class progresses. Try practice problem 1 for an understanding of this.
- Order of operations. This stuff will make the exam much easier if you're not
  trying to figure out whether the increment or the dereference happens first
  when there are no parentheses.
- Structs and Unions. You've already had to use structs on numerous occassions.
  Though unions weren't on any labs, but are definitely in the lecture notes and
  therefore fair game.
- Stack and Heap allocation. Make sure you know how to use malloc and free. Try
  to determine if there are memory leaks in some sample code. 
- libmylist.a. Make sure you understand how the linked list is supposed to
  function
- Makefiles and git. These questions are always fair game as well. You've been
  using makefiles and git long enough that you should know what tracked,
  untracked, staged, and modified mean in the context of git. You should also
  know about what rules are implicit to make, and how to write a makefile with pen
  and paper.

Try to work on pen and paper as much as possible leading up to the midterm.
Compile-and-check methods aren't going to get you far when you're sitting down
to take the test, so don't use them to practice. Try to really understand what
you're writing so that you can be confident it works on your own without the
compiler checking it for you.

## File I/O ##
### 3 channels ###
A C program is automatically given 3 channels for input and output. They can all
be redirected, but the basic three streams are:

- (0) stdin (Standard input)
  This stream is for incoming characters which normally come from the keyboard
  but can also be from other sources.
- (1) stdout (Standard output)
  This stream is for outgoing characters, and normally goes to the terminal
  screen but does not necessarily have to. (see below) This stream is buffered
  which means it is not sent to the terminal until a new line character is sent.
  This means if you use `printf("hello")` you likely will not see it until the
  end of your program is reached.
- (2) stderr (Standard error)
  This stream is for error messages and is not buffered, meaning any characters
  written to it will immediately be flushed to their destination. This
  destination is normally the terminal screen but can be other locations as
  well.

If you wish to interact with these buffers you will need to `#include <stdio.h>`
which is a library that defines standard operations such as `printf()` `scanf()`
and others which you may or may not have already used.

### Redirecting I/O ###

While most input and output to/from programs will go to the shell, it is
possible to redirect the source of stdin or the destination of stderr and
stdout. The `<` and `>` characters are used to denote redirection at the 
console. `2>` will redirect stderr whereas `>` will redirect stdout. `2>&1`
will redirect stderr to the same location as stdout. `>>` will append the output
to a file instead of overwriting the file. You can use other programs or files
on either side of most of these operators.

     [1] $ cat myfile.c 
     [2] $ cat < myfile.c 
     [3] $ cat myfile.c > cat
     [4] $ cat myfile.c > myfilecopy.c
     [5] $ cat myfile.c >> myfilecopy.c
     [6] $ valgrind ./myprogram 2> myerrors
     [7] $ valgrind ./myprogram > myoutput
     [8] $ valgrind ./anotherprogram 2>> myerrors
     [9] $ valgrind ./anotherprogram >> myoutput
    [10] $ valgrind ./myprogram > ALLthethings 2>&1
    [11] $ valgrind ./anotherprogram >> ALLthethings 2>&1

Each of the above expressions build on each other. If you can tell what the
effect of each expression above is, then you're set. If not, try them out and
see what happens.

### Formatting ###

printf and scanf both use format strings to specify what how to format their
output. They also both accept variable arguments. All arguments to scanf
**must** be pointers whereas arguments to printf should be values (in the case
of numbers) or `char *` in the case of strings. Pages 153-154 in the K&R explain
how to format your format strings for `printf()` and 157-158 explain formatting
for `scanf()`. Make sure you can identify the following two format strings:

```c
printf("%-15.10s", "hello, world");
sscanf("25 Dec 1988", "%d %s %d", &day, month, &year);
```

### Functions with Variable Arguments ###

`printf()` and `scanf()` family of functions accept a variable number of
arguments. You can do this too! Once you've enumerated all the required
arguments, you can specify that you would like to also accept variable arguments
with `...`:

    int myFWithVarArgs(int a, int b, ...);

The declaration means that the number and types of all arguments after the
integer b can vary. If you want to be able to actually access these arguments
you'll need to `#include <stdarg.h>` whose implementation is system dependent,
but interface is the same. To access the values, you will have to do the
following:

  1. Declare a variable of type `va_list` that will point to each argument.
```c
va_list my_arg;
```
  2. Call `va_start()` with the last named argument, and your variable that will
     point to each argument.
```c
va_start(my_arg, b);
```
  3. Call `va_arg()` with the variable that will point to the argument as well
     as the type of the argument (you'll need some way to figure out the type of
     this argument from your other arguments). Assign the return value to a
     variable. Repeat this step for each argument you want to read.
```c
int myvarInt = va_arg(my_arg, int);
```
  4. Clean up by calling `va_end()` with the variable list of args variable.
```c
va_end(my_arg);
```

### File I/O ###

Think of file I/O as writing/reading from stdin or stdout and your life will be
much simpler. It all starts with File descriptors which you use to reference a 
file. In order to work with files, you'll need to `#include <stdio.h>`. 
```c
FILE *fp; //Declare a file pointer
fp = fopen("README.txt", "r");
```
File descriptors are just fancy pointers for files. By default, all C programs
are given three to start with: `stdin`, `stdout`, and `stderr` so note that any
functions you can use file descriptors with you can use on the I/O streams we've
already mentioned. A file descriptor is a pointer to a special struct that
stores important information about where you currently are in a file, whether
you can read/write to it, and what the file is. You don't need to know how it
works, just accept that it does and you'll need to pass the File descriptor to
functions that work with files.

`fopen()` is how you'll open files. It takes two arguments, both strings. The
first is a string representing the path to the file you want to open, and the
second is the mode with which you will open it. The mode tells whether or not
you are going to be reading, writing, or appending to the file and also how you
want to read the file in. Make sure you know the difference between "r", "w",
"a", "r+", "w+", "a+", and all of the above with a "b" on the end. If `fopen()`
fails it will return a NULL pointer. This can happen because a file doesn't
exist (in the case of r's and a's) or because you don't have permissions to
access the file.

`fclose()` will close the file when you're done. In general you will use
`fgets()` and `fputs()` to read from and write to files. You can also use the
variants of printf and scanf, `fprintf()` and `fscanf()` to write to and read
from files. `getc()` and `putc()` are the lower level versions of these
functions, and have macros for `getchar()` and `putchar()` which interact with
`stdin` and `stdout` respectively. The functions `fread()` and `fwrite()` work
in blocks instead of characters. These can be far more efficient than `fgets()`
and `fputs()`

### What's Buffering? ###

Buffering determines how often the contents of a stream are sent to their
destination. There's some low level stuff going on at this point, but just
understand that its not very efficient to send data one character at a time, so
buffering happens. Unbuffered streams are constantly flushed to its destination.
Line-buffered streams are only flushed to its destination after a newline
character is written. Block-buffered streams are flushed when they reach a
certain size. You can use `fflush(fp)` to manually flush the buffer for any file
pointer. 

- stderr is unbuffered (why?)
- stdout is line-buffered when it's connected to terminal
- everything else is block-buffered

### Some Notes About Lab 4 ###
If you plan on doing the pair option and would like to 
[procure a private GitHub repo](https://github.com/edu), please request one ASAP,
because it takes a few days to process. Additionally, if you're new to GitHub/BitBucket,
you may find the [Git Documentation](http://git-scm.com/book), the 
[GitHub Help page](https://help.github.com/), and the 
[BitBucket Documentation](https://confluence.atlassian.com/display/BITBUCKET/Bitbucket+Documentation+Home)
handy.

Whether you choose to do the pair option or the solo option, you may wish to 
review each of the I/O functions we've learned in lecture note 9. Be sure that 
you understand the differences between them and note that there are certain situations
when some are more appropriate than others, and vice versa (ex., `fgets()` vs. `fread()`).
