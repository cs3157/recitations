# Recitation 2 #

## Makefiles ##

Make is a UNIX utility that follows a blueprint you create for compiling
programs. Calling `make` will automatically search your current directory for a
file called "Makefile" and use it to call various compiler commands according to
the rules outlined therein. 

### Jae's myadd Makefile ###

Take Jae's Makefile piece by piece. It can be found in this git repository as
`sample-makefile`

```make
CC  = gcc
CXX = g++
```

Make has a some pre-configured rules for how to compile programs. For example it
knows how to specify files as arguments to a compiler. However, you should tell
it what compiler to use for C files and C++ files. Here, we set the
special make variables CC and CXX to gcc, the C-compiler, and g++, the c++
compiler.

```make
INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)
```

Here we define our own variable, INCLUDES, which we can use for directories that
we wish to include at the compilation step. An example value for INCLUDES could
be `-I/home/jae/cs3157` which would tell the compiler to look in
/home/jae/cs3157 during the compilation step for missing header files and other
sorts of relevant files.

After defining INCLUDES, we define the flags that we want each compiler to be
run with. In this case we include the `-g` flag for debugging and `-Wall` flag
to display all warnings. Lastly, we reference our variable INCLUDES to add those
flags as well.

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
compile order and dependencies. The very first "target" or rule in your makefile
gets built when you type `make` in this case the first target is:

```make
main: main.o myadd.o
```

Note that we did not specify the linking rule, because make follows an implied
linking rule:

    $(CC) $(LDFLAGS) <all-dependent-.o-files> $(LDLIBS)

Also note that make assumes that main depends on main.o, so we could omit it:

    main: myadd.o 

Basically what this rule says is make should produce an executable called "main"
by linking myadd.o and main.o. This declares main.o and myadd.o as dependencies
of main, meaning that if any of the dependencies (or their dependencies) change 
between the last time this target was run, it should re-run the outdated targets
as well as this one.

The next target we declare is main.o:

```make
main.o: main.c myadd.h
```

This says that main.o depends on main.c (assumed) as well as myadd.h. See last
week's recitation notes to understand why main.o depends on myadd.h. We could
omit main.c as follows:

  main.o: myadd.h

Either way, we do not specify a rule here because make assumes the implicit
rule:

    $(CC) -c $(CFLAGS) <the-.c-file>

Lastly, we specify the target for myadd.o:

```make
myadd.o: myadd.c myadd.h
```

# Always provide the "clean" target that removes intermediate files.
# What you remove depend on your choice of coding tools
# (different editors generate different backup files for example).
#
# And the "clean" target is not a file name, so we tell make that
# it’s a "phony" target.

We'll include two phony targets. We tell make that they're "phony" so that it
doesn't attempt to use implicit rules or try to compile them. The first target
we make is "clean" which should remove all intermediate files. *Always include a
clean* so that `make clean` can be used to remove intermediate files like object
files, compiled code, etc. This should return your directory to just its source
code that can generate all the other files. *Be careful:* Using `rm -r` will not
prompt you to remove files. This is customary for `make clean` but it also means
if you make a mistake in designing your rule it could remove files that you
didn't want to. There is no "trash" in UNIX - they'll be gone forever.

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

## Git ##

For this part of the recitation, we will follow Jae's "git-tutorial" which can
be found on CourseWorks. Here's a quick run through of the operations reviewed
in the tutorial, along with some bonus operations:

Configuration:

    git config --global user.name "Your Full Name" 
    git config --global user.email your_uni@columbia.edu
    git config --global --add color.ui true

Working with repositories

    git init
    git status
    git add
    git commit
    git commit -m

Checking up on your changes

    git status
    git diff
    git diff --cached
    git log
    git log --state --summary
    git log -p

Removing and renaming

    git rm
    git mv

Undoing

    git checkout -- [filename]
    git reset HEAD [filename]

Tools

    git grep [pattern]
    git help
    man git
    man gittutorial

Patches

    git format-patch --stdout origin > mywork.mbox
    git am path/to/mywork.mbox

Remotes

    git remote add
    git pull
    git fetch && git merge

*Important*: statuses of files

1. Untracked
2. Tracked, unmodified
3. Tracked, modified, unstaged
4. Tracked, modified, staged

Lastly, all of these recitation notes are tracked using git. You should try and
learn a little bit about github for yourself. Create an account there, try
forking this repository, adding some changes, and submitting a pull-request to
add some useful info. If there's time at the end of recitation we can talk about 
using git and github.

## How NOT to get a Zero ##

Jae makes it pretty easy to not get a zero when submitting your lab. His
instructions are pretty clear, but let's just make sure we've got it all
straight. Here's the process you should follow when you're working on your lab:

1. **Clone Jae's repository** by using the following command:

    git clone /home/jae/cs3157-pub/labN labN

2. **Work on the lab and make FIVE commits** using

    git commit

  or

    git commit -m "A message about your commit"

3. **Make sure you have**:
    1. `README.txt` spelled and capitalized exactly like that. It MUST contain
your name, UNI, the lab number, and a description of your solution to the
assignment.
    2. tested your code. Run `make all` to ensure you're compiling the latest
version of your code and test it. If your code does not compile you will receive
a zero for that portion of the assignment, without exception.
    3. only commited what is necessary. Run `make clean` followed by `git
status` to ensure that the only code that you've committed is source, not object
file or executable. git status should show nothing changed after running make
clean if all has been done properly.

4. **Submit your lab** using the following command:

    /home/w3157/submit/submit-lab labN

This will create a patch for your code, clone Jae's code into a folder
`./labN-CURRENT_TIME`, apply your patch to that directory, copy your patch to
the submission directory that TAs can access, and lastly print "SUCCESS!"

5. **Test your submission** by going into the `./labN-CURRENT_TIME` directory,
running `make` and checking that your program runs. Also make sure that if the
lab instructions specified how to name your compiled files, they are properly
named. If anything is wrong, fix it in your initial repository, commit the
changes, and go back to step 4 :smiley:
