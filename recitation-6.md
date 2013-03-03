# Recitation 6 #
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
    [10] $ valgrind ./myprogram 2>&1 > ALLthethings
    [11] $ valgrind ./anotherprogram 2>&1 >> ALLthethings

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
`stdin` and `stdout` respectively.

### What's Buffering? ###

Buffering determines how often the contents of a stream are sent to their
destination. There's some low level stuff going on at this point, but just
understand that its not very efficient to send data one character at a time, so
buffering happens. Unbuffered streams are constantly flushed to its destination.
Line-buffered streams are only flushed to its destination after a newline
character is written. Block-buffered streams are flushed when they reach a
certain size. You can use `fflush(fp)` to manually flush the buffer for any file
pointer. 

## Unix ##

### The Stack ###

### Users and Permissions ###

### Processes ###

### Signals ###
