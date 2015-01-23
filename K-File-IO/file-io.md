# Recitation 7 #

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

## File operations ##

All of the following are defined in `stdio.h` and therefore you must 
`#include <stdio.h>` to use them.

### FILE * ###

`FILE` is a typedef'ed structure in `stdio.h`. Whenever you use it, you'll use a
`FILE *` though because you'll always be getting a value back from/passing it to
common file operating functions. Why a pointer? Because these functions will
modify the internal values of the `FILE` value. So while you could copy them
because it's a struct and C would be fine with passing it by value, things like
your place in the file would not be maintained.

### fopen and fclose ###

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

What's that you ask? It means they're really good at reading in lines, but bad
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
but `gets` will not give you the newline character.

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
