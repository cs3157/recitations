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

Jae's `myadd` `Makefile` in 10 Steps
------------------------------------

In this repository, you'll find a directory named `myadd-demo`, which contains
an interactive, step-by-step demo which shows you how to create a simple
Makefile from scratch. You may use the `./demo` to step through different
versions of the `Makefile`, and use it to run `make` during each step. You may
also inspect the `Makefile`s for each step under `myadd-demo/Makefiles`.

This guide will follow the demo and explain what's happening with the `Makefile`
at each step.


### Introduction

#### Source code

Before we get started, let's (re)familiarize ourselves with the files we're
compiling:

##### `myadd.h`

This is where the function prototype for the `add()` function is declared.
It tells the compiler that somewhere in the final program, we'll have an
implementation of the `add()` function, with the given type signature.
If you're familiar with Java, you can think of this as something like a Java
`interface` (though without the notion of a class).

##### `myadd.c`

This is where the `add()` function is actually implemented. Note that this
`#include`s `myadd.h` because we want to make sure that the compiler knows which
`add()` function we're implementing, and so that it can check that we're using
the right type signature.

##### `main.c`

This is where we call the `add()` function, and print its result. We `#include`
`myadd.h` because we're calling a function that we haven't implemented in this
`.c` file (also called a compilation unit).

#### Compilation

Recall that there are three actions we need to perform in order to build `main`:

    gcc -g -Wall -c myadd.c         # compiles myadd.c => myadd.o
    gcc -g -Wall -c main.c          # compiles main.c => main.o
    gcc -g main.o myadd.o -o main   # links main.o and myadd.o => main

We use the `-g` and `-Wall` flags to include debugger symbols and enable all
compiler warnings. The `-o` flag specifies that the resulting file shall be
named as the argument after it, `main`.


### Step 0

First, let's get the `Makefile` building just one thing. To do so, we write a
**rule** to build a **target**. The syntax of a Makefile is as follows:

    [target]: [dependencies...]
        [shell command]
        ...

This says that to build `target`, we must first satisfy the one or more
`dependencies` that come after the `:`. Then, once dependencies are satisfied,
we build the target with one or more shell commands.

_Note that before the shell command you must use a TAB character (and not just
4 or 8 spaces). Make sure your text editor is aware of this if you've configured
it to expand your tabs._

Let's write our rule to build `myadd.o`, from `myadd.c`:

    myadd.o: myadd.c myadd.h
        gcc -g -Wall -c myadd.c

Note that just because a file is a dependency doesn't mean that it actually
needs to be used in the build command. We don't need to tell `gcc` about
`myadd.h` because the `#include` preprocessor macro handles that for us. But
we still need to let Make know that it should rebuild `myadd.o` if updates are
made to either `myadd.c` or `myadd.h`, which is why we specify `myadd.h` as a
dependency.

With this as the only thing our `Makefile`, if we run `make`, we'll see that
`myadd.o` is built for us!


### Step 1

Now, let's also write the rule for building `main.o`. Since `main.c` also
`#include`s `myadd.h`, we should also specify that as a dependency:

    main.o: main.c myadd.h
        gcc -g -Wall -c main.c

Now, what happens when you type `make` will depend on _where_ you've written
this rule. If `make` is given no arguments, it will just build the first target
that is explicitly specified in the `Makefile`. In the demo, we've written the
`main.o` rule above the `myadd.o` rule, so if you type `make` now, you should
see only `main.o` building.

We can still build targets that aren't the default (top) target. If we wanted
to explicitly tell Make to build `myadd.o`, we can run `make myadd.o`.


### Step 2

Time to link! Let's put our linking rule at the very top, to make sure it's the
default target when we run `make`:

    main: main.o myadd.o
        gcc -g main.o myadd.o -o main

Note that we did not specify `myadd.h` as a dependency. That's because linking
doesn't need this header file at all. `main` will still be rebuilt if `myadd.h`
is updated, but because it implicitly inherits this dependency from its own
dependencies, `main.o` and `myadd.o`.

Now that we have a more complex `Makefile`, we can dig deeper into what it means
for a target to "depend" on others. Recall that every file in UNIX has a
"last modified" timestamp, which is updated any time the file is changed or
`touch`ed. A target is built only if it does not exist, or if one or more of its
dependencies have a later timestamp than it. The reason Make does this rather
than rebuilding the entire program from scratch is because for large software
projects, rebuilding from scratch every time can be very inefficient. Instead,
Make just rebuilds outdated targets as necessary.


### Step 3

It's sometimes useful to clean up your project directory and get rid of all
your build products. In this case, the `main` executable and any `.o` files.
If we built anything by hand, we may also have produced an executable named
`a.out`, which we'll want to get rid of too. We can do that with the following:

    rm -rf main *.o a.out

We want to sure `rm` just does what its told (and doesn't choke on, say, some
directory mischieviously named `main`), so we pass it the `-rf` flag.
But having to type this all the time can be pretty cumbersome.

It turns out that Make targets don't have to be files! We can create a shortcut
for ourselves with the following rule:

    clean:
        rm -f main *.o a.out
        
Now we can just clean up our project by running `make clean`. Isn't that neat?


### Step 4

Actually, there's a problem with the `Makefile` we left off with from step 3.
Consider the following sequence of commands:

    $ make
    gcc -g -Wall -c main.c
    gcc -g -Wall -c myadd.c
    gcc -g main.o myadd.o -o main
    $ touch clean
    $ make clean
    make: `clean' is up to date.

If you run `ls` now, you'll find that nothing has been cleaned. You'll also find
a file named `clean`, that was created by the `touch clean` command. Because
this file already exists, and its timestamp is not older than any of its
dependencies (since it has none), Make will not try to "build" the `clean`
target.

This kind of situation doesn't happen very often, but can be very frustrating
when it does. To get around it, we need to tell Make that this is a "phony"
target, using the special `.PHONY` directive, so that it ignores the timestamp
and runs the `clean` target every time:

    .PHONY: clean
    clean:
        rm -f main *.o a.out


### Interlude

At this point, you now have the basis complete `Makefile`. Every target in here
is explicit, which means for larger software projects, you'll be doing a _lot_
of typing, but it'll do for the rest of 3157. You can jump to this part of the
demo by running:
    
    ./demo explicit

In the following sections, we'll be explaining some of the fancier things you
can do with your Makefile by leveraging variables, implicit rules, and other
nifty features.


### Step 5

Make actually comes with a lot of the same features as shell scripting languages
like Bash and Python. One of these is the ability to assign variables.

Notice that every time compile, we use the same `-g -Wall` flags (in addition to
the `-c` flag). It doesn't seem like a big deal now, but if we were compiling
hundreds of compilation units and wanted to remove the `-Wall` flag from all of
them, that could get really annoying. (More annoying than those pesky warnings
you're trying to silence! But please leave in the `-Wall` flag for this class,
it's a good habit make.)

Instead, we add one more level ofindirection by assigning those flags to a
compiler flags variable instead:

    CFLAGS = -g -Wall

Now, in our rules, Make will substitute any instance of `$(CFLAGS)` it comes
across with `-g -Wall`. For example:

    gcc $(CFLAGS) -c main.c

We can do the same with the compiler command itself, `gcc`, as well as the `-g`
flag we're passing to the linking rule:

    CC = gcc
    LDFLAGS = -g

`CC` stands for "C Compiler," and `LDFLAGS` means "linking flags." Now we can
compile and link with the following:
    
    $(CC) $(CFLAGS) -c main.c
    $(CC) $(LDFLAGS) main.o myadd.o -o main

Now we can easily swap out the compiler and linking flags for our entire project
by modifying the build variables we've defined at the top of our `Makefile`.

It's not entirely obvious yet why we chose to substitute these particular parts
of our build commands, or why we're using such particular variable names. Why
this is important will become clear in step 8 when we use implicit rules.


### Step 6

In the rule to build `main`, the shell command takes an argument of `-o main`,
which tells `gcc` to name the output executable `main`. What if we just wanted
to name it whatever the name of our target is?

Make also provides special variables whose values are dependent on the rule in
which they appear. They can be invoked using a `$` followed by a special
character. You won't need to know any of these for the purposes of this course,
but they provide useful notation to understand how implicit rules work.

The special variable that is substituted with the name of the target is `$@`.
We can rewrite the linking rule as follows:

    main: main.o myadd.o
        $(CC) $(LDFLAGS) main.o myadd.o -o $@

Within the `main` rule, `$@` will expand to `main`. Now, if we change `main`,
the output executable name will change accordingly.

You can try this out by playing around with your Makefile, then running `make`.


### Step 7

We can use a couple more special variables to eliminate some of the filenames
we explicitly reference in the shell commands for each rule.

First, we can use `$^`, which will be substituted with every dependency of the
target. We can use this for the `main` target once again:

    $(CC) $(LDFLAGS) $^ -o $@

Make also provides a special variable which will expand to only the first
dependency of a target, `$<`. This is especially handy for the compilation
rules:

    $(CC) $(CFLAGS) -c $<

Notice that at this point, the build commands in our `Makefile` don't explicitly
mention anything about the target they're building or the dependencies they're
using. For example, there's no mention of `main.o`, `main.c`, or `myadd.h` in
`main.o`'s build commands. There's probably another opportunity to simplify our
`Makefile` even more just around the corner...


### Step 8

The guys who wrote Make also realized that there are some pretty common patterns
when it comes to compiling C software projects, so they built the ability to
recognize these patterns into Make. These are what we call "implicit rules."

The built-in implicit rules will use the file extensions of the targets and
dependencies to infer what build command pattern to invoke. It will then fill in
build command automatically, which will be looking for extra configuration
options like compiler flags from specially designated build variables.

Specifically, the built-in C implicit rules will look for build variables such
as `CC`, `CFLAGS`, and `LDFLAGS`... which we've already defined for ourselves!
So we can just go ahead and remove the build commands, and just write the
targets and dependencies on their own:

    main: main.o myadd.o
    main.o: main.c myadd.h
    myadd.o: myadd.c myadd.h

This will still build -- try running `make` to see for yourself. For larger
software projects, implicit rules like these can go a long way.


### Step 9

There's something else that the Make developers realized about the file naming
conventions we use for C software projects: the name of the build target is
often related to that of one of its dependencies. For example, `myadd.o` comes
from `myadd.c`, and `main` comes from `main.o`.

If you omit those dependencies, Make will look for them any way and use them
during the compilation process. Thus we end up with a set of incredibly terse
build rules:

    main: myadd.o
    main.o: myadd.h
    myadd.o: myadd.h

And this _still_ builds.

There's a lot more fancy stuff you can do with your `Makefile`, but they're
beyond the scope of this class, and certainly beyond the scope of our toy
`myadd` software project. You can check out GNU's [Make manual][man-make] online
to find out the full extent of what this utility can do.

[man-make]: https://www.gnu.org/software/make/manual/make.html


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
