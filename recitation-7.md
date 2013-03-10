# Recitation 7 #

Not too much progress was made in class last week being that there was only one
lecture, but we'll go over and solidify some of the necessary skills for working
with files - these seem to be giving everyone a bit of trouble.

## size_t ##

`size_t` shows up all over the place in memory operations. `malloc` expects its
parameters to be of this form, and certain file operation functions will return
the number of bytes read in this formed. What you need to know about `size_t` is
that its an unsigned integer type. This means it works like an integer but
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

Other than that you can treat size_t as any other integer type.

## File operations ##

All of the following are defined in stdio.h and therefore
to use them you must `#include <stdio.h>` to use them.

### FILE * ###

### fopen and fclose ###

### fgets and fputs ###

### fread and fwrite ###

### fseek ###

## Clarifications ##

### Function pointers ###
