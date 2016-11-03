## File I/O ##
### 3 channels ###
By convention, every C program is given 3 channels for input/output operations,
often called I/O. I/O refers to anything that involves data coming into the 
program from outside (such as getting user input with `scanf`) and writing data 
to the outside (such as printing data to the console with `printf`). 

The 3 basic channels (often called "streams") as well as their corresponding
integer representations are:
- **(0) stdin (standard input)**
  This stream is for incoming data, which often comes from the keyboard but can 
  also be from other sources.
- **(1) stdout (standard output)**
  This stream is for outgoing data, and normally goes to the terminal
  screen but does not necessarily have to. (see below) This stream is buffered
  which means it is not sent to the terminal until a new line character is sent.
  This means if you use `printf("hello")` you likely will not see it until the
  end of your program is reached.
- **(2) stderr (standard error)**
  This stream is for error messages and is not buffered, meaning any characters
  written to it will immediately be flushed to their destination. This
  destination is often the terminal screen, but can be other locations as
  well.

If you wish to interact with these buffers you will need to `#include <stdio.h>`.
This library defines standard functions such as `printf()` `scanf()` and others 
which you may or may not have already used.

### Redirecting I/O ###

Lots of input and output to/from programs is visible in the shell (your terminal 
screen). That being said, it's possible to redirect the source of stdin or the 
destination of stderr and stdout. 

There are several kinds of redirection possible from the console:
- `>` redirects the standard output of the left argument to the right argument.
  For example `echo "hello world" > hi.txt` will write the words 'hello world'
  to a file called `hi.txt`.
- `2>` is similar, except that it takes the standard error and redirects it,
  rather than the standard output.
- `<` does 'input redirection', meaning that the contents of the file on the 
  right of the operator serves as the standard input of the left argument. For 
  example, after running the example above, `cat < hi.txt` will print "hello
  world" to the console.
 - `2>&1` will redirect stderr to the same location as stdout. 
 - `>>` will append the output to a file instead of overwriting the file. 

Here are some examples to try out from your UNIX console:
```
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
```

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


## size_t ##

`size_t` shows up all over the place in memory operations. `malloc` expects its
parameters to be of this form, and certain file operation functions will return
the number of bytes read in this formed. What you need to know about `size_t` is
that it's an unsigned integer type. This means it works like an integer but
**cannot represent negative values**. So, while the following is okay:

```c
size_t x = 5;
size_t y = 3;
int z = x + y;
```

The following is not (and wouldn't be a good idea even if the value was
positive):

```c
size_t x = 5;
size_t y = 3;
int z = y - x;
```

Other than that you can treat `size_t` as any other integer type.


## File I/O ##

When writing your C programs, you will often be interacting with files in
various forms.  The standard library provides a simplified interface for
interacting with those files through the `stdio` header and the *FILE pointer*.

### FILE * ###

`FILE` is a typedef'ed structure in `stdio.h`. Whenever you use it, you'll use a
`FILE *` though because you'll always be getting a value back from/passing it to
common file operating functions. Why a pointer? Because these functions will
modify the internal values of the `FILE` value. So while you could copy them
because it's a struct and C would be fine with passing it by value, things like
your place in the file would not be maintained.  A `FILE *` is given as an
*opaque type*, meaning you should never be accessing it's internals directly.

### File Descriptors ###
Among other things, a FILE wraps a file descriptor, an integer used by the
operating system to keep track of open files.  As you'll see below, a FILE
provides a nicer interface than a file descriptor for interacting with files.
You can use function like `fopen` and `fclose` instead of the more low-level
`open` and `close`.

### fopen and fclose ###
`fopen()` is how you'll open files. It takes two arguments, both strings. The
first is a string representing the path to the file you want to open, and the
second is the mode with which you will open it. The mode tells whether or not
you are going to be reading, writing, or appending to the file and also how you
want to read the file in. Make sure you know the difference between "r", "w",
"a", "r+", "w+", "a+", and all of the above with a "b" on the end. If `fopen()`
fails it will return a NULL pointer. This can happen because a file doesn't
exist (in the case of r's and a's) or because you don't have permissions to
access the file. `fclose()` will close the file when you're done.

```c
FILE *fopen(char *name, char *mode);
int fclose(FILE *fp);
```

The above structure should look a tiny bit familiar. Knowing what we know about
`FILE *`s you might see the likeness here to:

```c
void *malloc(size_t size);
int free(void *p);
```

That's because fopen and fclose create a new `FILE` structure on the heap so
that the status of the open file can be maintained. This means that **if you
don't `fclose` your `FILE *`s, you'll have memory leaks**. Be careful about
this.

### fgets and fputs ###

**THESE FUNCTIONS ARE FOR LINE INPUT AND LINE OUTPUT**

What's that you ask? It means they're really good at reading in strings, but bad
for everything else. Only use these functions if lines are a logical way to
delimit chunks of the file you're reading.

```c
char *fgets(char *line, int maxline, FILE *fp);
int fputs(char *line, FILE *fp);
```

`fgets` reads the next *line* from the input file in `fp` into the memory
location pointed to by `line`. If all is successful, it reads at most
`maxline-1` characters out of the file, and returns `line` as well. If something
goes wrong (on end of file, or error) it returns `NULL`. It will keep the
newline character it reads if it gets to one before it reaches `maxline-1`
characters. It also ALWAYS appends the null character to the end of the string.

`fputs` returns EOF if there's an error and 0 otherwise. This will not append a
newline to the file, nor does your string need to contain a newline character.

**Watch out!** `gets` and `puts` work very similarly for `stdin` and `stdout`
but `gets` will not give you the newline character.  But you shouldn't have to
worry about that because you should NEVER use `gets`.  It does not perform any
bounds checking on the input, so you're just asking for memory errors.

### fread and fwrite ###

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

Each of these functions accept pointers of type `void`. So if you want each item
to be read into the right size memory space, you'll need to tell it the `size`
of each item, and the number of items `nmemb` to read/write from/to the
`stream`. `fwrite` promises not to modify the data that `ptr` references as
well. The return the number of bytes read/written. If it's anything less than
what you expected, you should check what happened using `ferror` or `feof`.

### fseek ###

```c
int fseek(FILE *stream, long offset, int origin);
```

This handy dandy function lets you hop through a file without doing anything
other than changing the position in the `FILE` structure. You can use any
`stream` of your choosing, but pay attention to whether or not it's a binary
stream. If it's a binary stream, `offset` can be any number of bytes/characters from
`origin` which should be set to either `SEEK_SET` (a constant representing the
beginning of the file), `SEEK_CUR` (a constant representing the current
position), or `SEEK_END` (the end of the file).

If you're reading a text stream, `offset` must either be zero or the current
position as returned by a call to `ftell` (see below). In this case, always set
origin to `SEEK_SET`.

```c
FILE *text = fopen("myfile", "r");
FILE *binary = fopen("myfile", "rb");

fseek(text, ftell(text), SEEK_SET);
fseek(binary, -100, SEEK_END);
```

### feof and ferror ###

```c
int feof(FILE *stream);
int ferror(FILE *stream);
```

So you didn't get what you were expecting from one of the above functions. What
do you do? You call `feof` or `ferror`. These two functions let you know what
happened. `feof` returns true if the end of the `stream` has been reached, and
`ferror` returns true if there was an error reading the `stream`.

### fprintf and fscanf ###

These functions work just like their counterparts `printf` and `scanf`,
respectively, except you specify which FILE to write to, rather than defaulting
to `stdout` and `stdin`, respectively.

### What's Buffering? ###

Buffering determines how often the contents of a stream are sent to their
destination. There's some low level stuff going on at this point, but just
understand that its not very efficient to send data one character at a time, so
buffering happens. Unbuffered streams are constantly flushed to their destination.
Line-buffered streams are only flushed to its destination after a newline
character is written. Block-buffered streams are flushed when they reach a
certain size. You can use `fflush(fp)` to manually flush the buffer for any file
pointer.

- stderr is unbuffered (why?)
- stdout is line-buffered when it's connected to terminal
- everything else is block-buffered
