# Recitation 2 #

## Makefiles ##

Make is a UNIX utility that follows a blueprint you create for compiling
programs. Calling `make` will automatically search your current directory for a
file called "Makefile" and use it to call various compiler commands according 
to the rules outlined therein. 

### Jae's myadd Makefile ###

Take Jae's Makefile piece by piece. It can be found in this git repository as
`sample-makefile`

```make
CC  = gcc
CXX = g++
```

Make has a some pre-configured rules for how to compile programs. For example 
itknows how to specify files as arguments to a compiler. However, you should 
tell it what compiler to use for C files and C++ files. Here, we set the
special make variables CC and CXX to gcc, the C-compiler, and g++, the c++
compiler.

```make
INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)
```

Here we define our own variable, INCLUDES, which we can use for directories 
thatwe wish to include at the compilation step. An example value for INCLUDES 
couldbe `-I/home/jae/cs3157` which would tell the compiler to look in
/home/jae/cs3157 during the compilation step for missing header files and other
sorts of relevant files.

After defining INCLUDES, we define the flags that we want each compiler to be
run with. In this case we include the `-g` flag for debugging and `-Wall` flag
to display all warnings. Lastly, we reference our variable INCLUDES to add 
those flags as well.

```make
LDFLAGS = -g
```

LDFLAGS are the flags that are appended to the compiler when using it for
linking. In this case we just want the debugging info to be included.

```make
LDLIBS =
```

LDLIBS will automatically be appended to the linker commands. These are flags
like `-lm` and function similarly to our INCLUDES variable but are added at a
different step. `m` denotes the math library.

That's about it for our variable declarations. The next step is to define
compile order and dependencies. The very first "target" or rule in your 
makefile gets built when you type `make` in this case the first target is:

```make
main: main.o myadd.o
```

Note that we did not specify the linking rule, because make follows an implied
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

We'll include two phony targets. We tell make that they're "phony" so that it
doesn't attempt to use implicit rules or try to compile them. The first target
we make is "clean" which should remove all intermediate files. 
*Always include a clean* so that `make clean` can be used to remove 
intermediate files like object files, compiled code, etc. This should return 
your directory to just its source code that can generate all the other files. 
*Be careful:* Using `rm -f` will not prompt you to remove files. This is 
customary for `make clean` but it also means if you make a mistake in 
designing your rule it could remove files that youdidn't want to. There is no 
"trash" in UNIX - they'll be gone forever.

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


## Bits, Bytes and Binary ##

Let's just refresh our memory about memory:

  - A **bit** is a single digit in binary; on or off; 1 or 0
  - 8 bits form a single **byte**: 11111111 = 2^8 - 1 = 255
  - **Hexadecimal** is another notation to count even higher in fewer places
    - Two hexadecimal places express 1 byte
    - FF in Hexadecimal is 255
  - **Two's complement**
    - Most modern computers use this notation for signed integers
    - **Most significant bit**: Usually the leftmost, but generally the bit 
    with the highest value: If 1000 = 8, then 1 is the most significant bit. 
    If we were using a different notation such as 1010 = 5, then the rightmost 
    0 is the most significant bit. 
    - If the most significant bit is 1, then in two's complement, you're 
    looking at a negative number
    - To convert: 1010 (read as ten if unsigned), first note that it is
      negative. Then find its magnitude by flipping all the bits (0101, 5) and
      then adding 1 (0110) meaning the value is -6.
    - Consult the following table to see something interesting: (note the
      wraparound effect
      
Binary | usigned decimal | two's complement decimal
------ | --------------- | ----------------------- 
000    | 0               | 0
001    | 1               | 1
010    | 2               | 2
011    | 3               | 3
100    | 4               | -4
101    | 5               | -3
110    | 6               | -2
111    | 7               | -1

Be aware of some important boundaries as well:

  - 0x00000000 = 0
  - 0x7FFFFFFF = 2147483647
  - 0x80000000 = -2147483648
  - 0xFFFFFFFF = -1

### Bitwise Operators ###

While we're on the subject of binary representation, let's take a moment to 
examine C's bitwise operators. Although they're a bit tricky, each one 
performs relatively simple logical checks on its operands:

#### Bitwise AND ###

The bitwise AND operator, `&`, takes two integers as operands and returns a 
new integer with a bit pattern consisting of ones only in the positions that 
both operands contain bits set to 1.

```
int x = 5;  // 0101 in binary
int y = 12; // 1100 in binary
x & y;      // 0100 (4)
```

Note: `x & y == 4`, but `x && y == 1`. Can you explain why?

This provides a handy way of checking the bit value at a given position in a 
number:

```
int mask = 8; // 1000 in binary, for checking the 4th bit
x & mask;     // 0, since 5 doesn't contain a 1 in the 4th bit
y & mask;     // 1000 == 8 > 0, since 12 contains a 1 in the 4th bit
```

#### Bitwise OR ####

The bitwise OR, `|`, behaves like the bitwise AND but the returned integer's 
bit pattern consists of ones where either operand has a 1.

```
int x = 5;  // 0101 in binary
int y = 12; // 1100 in binary
x | y;      // 1101 (13)
```

#### Bitwise XOR and Complement ####

The bitwise XOR, `^`, sets 1 in each bit where its operands differ and 0 
where they are the same. The bitwise complement, `~`, performs the one's 
complement on its operatand by flipping each bit.

#### Bit Shifting ####

The bitwise shift operators, `<<` and `>>`, shift their left operand by the 
number of digits specified by the right operand. Left shifting always fills 
vacated bits by zero. Right shifting varies from machine to machine and whether 
or not we're talking unsigned or signed.

```
int x = 2;  // 000010 in binary
x << 2;     // 001000 (8)
8 >> 1;     // 000100 (4)
```

## Git ##

For this part of the recitation, we will follow Jae's "git-tutorial" which can
be found on the mailing list and CourseWorks. Here's a quick run through of the
operations reviewed in the tutorial, along with some bonus operations:

Configuration:

    git config --global user.name "Your Full Name"
    git config --global user.email your_uni@columbia.edu
    git config --global --add color.ui true

And set your editor globally (here vim, if you prefer emacs use that). Note that
using the graphical version, `gvim`, is trickier, so we recommend you stick
to the command line version.

    echo "EDITOR=vim" >> ~/.bashrc

Getting Started

    git init
    git clone remote

Working with repositories

    git status
    git add file1 file2
    git add -p    #individually pick for each set of changes whether to stage it
    git commit
    git commit -m "some message"

Checking up on your changes

    git status
    git diff
    git diff file1
    git diff --cached
    git log
    git log --stat --summary
    git log -p

Removing and renaming

    git rm file1
    git mv oldfilename newfilename

Undoing

    git checkout -- [filename]
    git reset HEAD [filename]

Going back in time

    git checkout <commit hash>

Tools

    git grep [pattern]
    git help
    git help commit
    man git
    man gittutorial

Patches are rarely necessary, but this is how the submit script works

    git format-patch --stdout origin > mywork.mbox
    git am path/to/mywork.mbox

Remotes

    git remote add
    git pull
    git fetch && git merge
    git push

*Important*: statuses of files

1. Untracked
2. Tracked, unmodified
3. Tracked, modified, unstaged
4. Tracked, modified, staged


### gitignore ###
Git wants to track everything, but you don't want it to track everything. In
particular you want to ignore all your object `.o` files, and your compiled
executables. You can tell git to ignore certain files by using a gitignore file.
It's a list of file names (including wildcards) for git to ignore when running
commands like status.

In your repository create a file named `.gitignore`, where each line is a
pattern of filenames git should ignore.

    a.out
    *.o
    *.a
    main
    *.mbox
    /labN-2013*

You can add the `.gitignore` file itself to the `.gitignore`, or you can add it
to the repository. You may also create a global ignore file so you don't have to
copy it to each repository. More details about that are in Github's help on
[ignoring files](https://help.github.com/articles/ignoring-files).


### Bonus ###

All of these recitation notes are tracked using git and hosted on github. If we
have time we'll come back to this during recitation, but here's some github 101.

1. Create an account by going to [github.com](http://github.com) and signing up.
Then, [configure git for use with remote
servers](https://help.github.com/articles/set-up-git).

2. Add your SSH keys to github. They have [a handy
tutorital](https://help.github.com/articles/generating-ssh-keys) to help out.
All you should need to do is Step 4 - adding ssh keys.

3. Try [forking](https://help.github.com/articles/fork-a-repo) [this
repository](https://github.com/jrbalsano/cs3157-recitations). Pull your fork to
your local machine.

    **Digression**: One of the reasons git is so great for working
in distributed teams is a feature called branching. Branches are subsections of git
commits that don't affect other branches. For example "master" is the branch
that you'll do all your work on for this class. Let's say though you want to
add more unix commands to recitation-1.md. You could create a branch called
`improve_recitation1_unix` like so:

        git checkout -b improve_recitation1_unix

    This would create a new branch, and switch to it. On this branch you would make
and commit your changes. When finished, you could switch back to the master
branch and merge your changes from the feature branch as follows:

        git checkout master
        git merge improve_recitation1_unix

    The reason branching is so useful is that it allows for multiple people to work
on their own issues, and then merge their changes in only *after* they are
certain their changes will not cause problems to the master branch. In this way,
the master branch always represents a completely functioning project, while the
branches may have broken code.

    Anyway, all this was a bit of a digression to discuss branching, but now that
you have a fork of my respository, you can make changes on the master branch.
When you're done, use `git push origin master` to push your changes back up to
your fork, and then go to github.com to pull-request your changes. If I like
what you've done, I'll definitely accept your pull request.

And that's about it for github. Forking and branching are crucial to working on
teams, both private and open-source. Github and git are great tools for managing
all sorts of things, even notes, so make sure you're familiar with them.
Proficiency in git and github is a desirable trait to have when job-hunting.

Other useful tutorials:

- [Be Social](https://help.github.com/articles/be-social)
- [Create a Repository](https://help.github.com/articles/create-a-repo)

