Makefiles
=========

Make is a UNIX utility that helps you compile programs by following a blueprint
you specify.

Calling `make` will first automatically search your current directory for a
file called `Makefile`. Then, Make will use it to call various shell commands,
according to the rules outlined therein. This allows you to chain together
complex sequences of commands you would use to compile a program.

In other words, you can execute all the preprocessing, compiling, and linking
commands just by typing `make`. It's also a handy way to automate cumbersome
tasks, like cleaning up build products.

## Jae's myadd Makefile ##

Take Jae's Makefile piece by piece. It can be found in this git repository as
`sample-makefile`.

### Makefile Variables ###
Make relies on your variable names being the same as the ones laid out in Jae's
example Makefile. For example, you must call the `CC` and `LDLIBS` variables 
by those exact names in order for the implicit rules laid out below to work.
Here, we'll lay out what each variable does.

```make
CC  = gcc
CXX = g++
```

Make has some pre-configured rules for how to compile programs. For example,
it knows how to specify files as arguments to a compiler. However, you should 
tell it what compiler to use for C files and C++ files. Here, we set the
special make variables CC and CXX to gcc, the C-compiler, and g++, the c++
compiler.

```make
INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)
```

Here we define our own variable, INCLUDES, which we can use for directories 
that we wish to include at the compilation step. An example value for INCLUDES 
could be `-I../myHeaders` which would tell the compiler to look in the myHeaders 
directory, located one directory above the current directory, during the 
compilation step for missing header files and other sorts of relevant files. For 
this class, please do NOT use absolute paths in your Makefiles; we do not have 
the permissions to access your /home/your_uni directory (you'll learn about 
permissions later on).

After defining INCLUDES, we define the flags that we want each compiler to be
run with. In this case we include the `-g` flag for debugging and `-Wall` flag
to display all warnings. Lastly, we reference our variable INCLUDES to add 
those flags as well.

```make
LDFLAGS = -g
```

LDFLAGS are the flags that are appended to the compiler when the compiler is
being used for linking. In this case, we just want the debugging info to be 
included.

```make
LDLIBS =
```

LDLIBS will automatically be appended to the commands invoked to link. 
These are flags like `-lm` and function similarly to our INCLUDES variable 
but are added at a different step. `m` denotes the math library.

### Targets ###
That's about it for our variable declarations. The next step is to define
compile order and dependencies. On a high level, you are laying out what files
each target is dependent on. The following syntax is used to denote that
target to dependent files relationship:

```make
[targetname]: [dependency1] [dependency2]
```

The very first "target" or rule in your makefile gets built when you type `make`. 
In the case of Jae's example Makefile, the first target is:

```make
main: main.o myadd.o
```

### Implicit Rules ###

Note that we did not specify the linking rule even though we were making an
executable out of some `.o` files. This is because make follows an implied
linking rule:

    $(CC) $(LDFLAGS) <all-dependent-.o-files> $(LDLIBS)

Also note that make assumes that main depends on main.o, so we could omit it:

```make
main: myadd.o 
```

Basically what this rule says is make should produce an executable called 
"main" by linking myadd.o and main.o. This declares main.o and myadd.o as 
dependencies of main, meaning that if any of the dependencies (or their 
dependencies) change between the last time this target was run, it should 
re-run the outdated targets as well as this one.

The next target we declare is main.o:

```make
main.o: main.c myadd.h
```

This says that main.o depends on main.c (assumed) as well as myadd.h. See last
week's recitation notes to understand why main.o depends on myadd.h. We could
omit main.c as follows:

```make
main.o: myadd.h
```

Either way, we do not specify a rule here because make assumes the implicit
rule:

    $(CC) -c $(CFLAGS) <the-.c-file>

Lastly, we specify the target for myadd.o:

```make
myadd.o: myadd.c myadd.h
```

### Other (Phony) Targets ###

We'll include two phony targets. We tell make that they're "phony" so that it
doesn't attempt to use implicit rules or try to compile them. 

The first target we make is "clean" which should remove all intermediate files. 
*Always include a clean* so that `make clean` can be used to remove 
intermediate files like object files, compiled code, etc. This should return 
your directory to just its source code that can generate all the other files. 
*Be careful:* Using `rm -f` will not prompt you to make sure you want to remove 
files. This is customary for `make clean` but it also means if you make a 
mistake in designing your rule it could remove files that you didn't want to. 
Note that there's no "trash" or "recycle bin" in UNIX: the files will be gone 
forever!

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
