# Unix, Text Editors, and Compiling #

## Logging in ##

- If you're on a Mac, open up the Terminal app.
- If you're on Windows, install [MobaXterm](http://mobaxterm.mobatek.net/).
- Type `ssh your_uni@clac.cs.columbia.edu`. You will be prompted for your CLAC
password.
- If you want to share graphical programs as well as the shell with the remote
machine, enable X11 Forwarding: `ssh -Y your_uni@clac.cs.columbia.edu`

### Changing your password ###

Earlier this week, we generated a password and emailed it to you. You may want
to change your password by entering the command:

    passwd

Enter your current password and hit return. Then, enter your new password. For
security reasons, your keystrokes are not displayed when typing passwords.

### What about CLIC? ###

You might've heard about CLIC, the CS department's computing service. We used to
require CLIC accounts for this course, but we are now running our own computing
infrastructure called CLAC. It stands for "**C** **L**anguage is **A**wesome and
**C**ool."


## Basic UNIX ##

### Paths ###

A good place to start with UNIX is the filesystem structure. Our CLAC machines
run Ubuntu Linux. Unlike Windows machines, UNIX uses forward slashes to separate
each part of the file path.

An example file path in UNIX might be `/usr/bin/dict`. The path `/` by itself
denotes *the highest level directory*. If you start any path with a forward
slash, it will assumed to be a path relative to the root directory `/`.

Alternatively, your current directory is represented by `./`. In most cases you
can leave this off. You can find out your current directory using the command
`pwd`.

If your current directory is `/students/alice` and you wish to reference the
directory `/students` in a path, you can do so in two ways:

- `/students` — an **absolute path** (begins with `/`)
- `../` — a **relative path** (does not begin with `/`)

`../` denotes the directory above the current directory. You could reference the
root directory `/` from the directory `/students/alice` using the relative path
`../../`.

### Basic Navigation ###

When you log into CLAC, your current (working) directory will be
`/students/your_uni`. Check this by typing:

    pwd

This is your home directory. All of your files on CLAC are stored in this
directory, and you can do pretty much whatever you want to them. You own the
place.

Let's view all the files in the current directory:

    ls

Let's make some new directories here for your work in this class. Use the
`mkdir` command to make a new directory:

    mkdir cs3157
    mkdir cs3157/learning

Now let's move into your working directory. Use the change directory command,
`cd`. All three commands below will do the same thing. (Which paths are
relative, and which ones are absolute?)

    cd cs3157/learning
    cd ./cs3157/learning
    cd /students/your_uni/cs3157/learning

Let's create a new text file using the `touch` command. This will create
a new empty file if one does not exist, or update the last modified date if the
file exists.

    touch testing.txt
    touch .hidden.txt

Did both commands work? Try the `ls` command again.

Some commands in UNIX take flags. These are special arguments preceded by a
dash. The two flags we use the most with `ls` are:

- `-l` shows more information about each file, such as the size, owner, and
permissions.
- `-a` includes files that are hidden. In UNIX, these are files whose names
start with a period, such as `.hidden.txt`.

Try these commands. Notice how the output changes for each one.

    ls
    ls -l
    ls -a

We can also combine flags for `ls`:

    ls -la

Now let's delete our hidden file using the remove command, `rm`.

    rm .hidden.txt
    ls -la

Alright, now let's get rid of the directory we created here. Just as with
`.hidden.txt`, we'll use the `rm` command.

However, `rm` doesn't let you delete directories unless you specify to run it
recursively (`-r`) (repeatedly go into each subdirectory and delete all files). It will
also ask for confirmation that you want to delete files unless you tell it to
force the delete (`-f`).

    cd ../
    rm -rf learning
    ls -la

One last thing as a side note: if you ever don't know how to use a command in
UNIX (or even a function in the standard C library) you can use the `man`
command. It will bring up the manual pages for the command you ask it for. Try
to learn more about the ls command:

    man ls

Use `q` to quit out of a man page.

### Useful Tricks ###

#### Tab completion ####

Tab completion is a feature that auto-completes your commands when you press the
tab key. For example, typing `tou` followed by the tab key will complete to
`touch`. Tab completion also works for directory and file names.

#### Previous command ####

You can go through your history by pressing the up and down arrows in terminal.
This will navigate between previously used commands so that you can easily use
the same commands over and over.

#### Reverse intelligent search (reverse-i-search) ####

You can also search through your command history. Press Ctrl-R to bring up the
search prompt. Start typing until you find the command you're looking for.

This feature is especially useful for long, complicated commands that you rarely
use. Instead of memorizing them, you can simply search your history.


## Text Editors ##

There are two main text editors that you can use from inside terminal: `emacs`
and `vim`. Although we are teaching the course with `vim`, which editor you use
is ultimately your decision. (You could even write everything in `nano` if you
really wanted, but it might get annoying.)

### Vim ###

Vim is a difficult to use text editor and can be confusing at first. Its goal is
to be incredibly efficient by preventing unnecessary movement of your hands
around the keyboard. It operates in different modes, the most important of
which will be **normal (command) mode** and **insert mode.**

Launch Vim and tell it the filename you want to edit:

    vim myfile

When you open vim, it will be in Normal mode. Typing will cause a variety of
different operations to happen. For now switch to Insert Mode by pressing `i`.
You should see `-- INSERT --` appear at the bottom of the screen. At this point
anything you type will appear as text in the text file. This is fine for basic
editing.

Now let's switch back to Normal mode. Press the `esc` key to switch back.

Most vim commands execute as soon as you type them. Here are some basic commands
that will execute immediately:

  - `h` (left), `j` (down), `k` (up), and `l` (right) are how you move while in
    Normal mode. You may also use the arrow keys.
  - `dd` deletes the current line
  - `D` deletes from the current location to the end of the line
  - `yy` copies the current line
  - `p` pastes whatever has been previously copied or deleted
  - `0` jumps to the beginning of the line
  - `$` jumps to the end of the current line
  - `w` jumps to the beginning of the next word (`W` uses a broader definition of word)
  - `b` jumps to the end of the previous word (likewise `B`)
  - `u` undoes the last change
  - `Ctrl-R` redoes the last change

Some vim commands will not be executed until you press enter. These begin with a
colon.

  - `:w [optional filename]` — save the current file if no file name is passed,
    or write the current file to specified location.
  - `:x` or `:wq` — save and quit
  - `:e filename` — open the filename specified
  - `:q` — quit vim and return to the shell
  - `:[line number]` — jump to that line

In vim, most commands work with some sort of combination between prepositions
and actions. For example, `gg=G` would indent the entire file, as `gg` takes you
to the beginning of the file, `=` auto-indents a line, and `G` jumps to the end
of the file.

To practice the above commands and learn some more, try running the built-in
tutorial:

    vimtutor

Alternatively, check out [Open Vim's Tutorial](http://www.openvim.com/tutorial.html)
for another interactive vim lesson. Or play a little NES Zelda type game while
learning vim, with [Vim Adventures](http://vim-adventures.com/).

After learning vim, you might want to configure it. This is done by editing the
.vimrc file in your home directory. Let's check out our current settings.

    vim ~/.vimrc

There should be default settings there already, but you can look to make changes
here in the future. Jae and the TAs will send out their configurations later,
but a good starting point is to enable line numbers and syntax highlighting by
adding this to your .vimrc:

    set number
    syntax on


### Emacs ###

*May be skipped for time*

Emacs is an easier to pick up text editor, and many of its commands are identical
to those of the shell.

Let's start by editing a new file in emacs:

    emacs myfile

As soon as emacs starts running, you will be able to type into it. There is no
special insert mode like in vim. You can backspace at any time without having to
switch between modes.

Emacs has the same functionality as vim, and we present the basics below:

  - 'Ctrl-f' will move your cursor forward, 'Ctrl-b' will move it back, 'Ctrl-p'
    will move it up, 'Ctrl-n' will move it down; the arrow keys work as well
  - 'Ctrl-s' will search for a word forward, 'Ctrl-r' will search for a word backward
  - 'Ctrl-a' goes to beginning of line, 'Ctrl-e' goes to end
  - 'Ctrl-k' will delete the portion of the current line after the cursor
  - 'Ctrl-spacebar' to select text to manipulate
  - 'Esc-w' to copy text, 'Ctrl-w' to cut text, Ctrl-y' will paste your most
    recently copied/deleted text
  - 'Esc-g g' then enter a line number to jump to a particular line in the buffer

To exit and save we will use Ctrl-X + Ctrl-C. If you just want to save then use
Ctrl-X + Ctrl-S.

Just like vim, emacs also has a configuration file that you can edit. This is
.emacs file within your home directory. Let's check out our emacs settings.

    emacs ~/.emacs

There should be default settings there already, but feel free to add more for
shortcuts.

*Note that backspaces can be a little funky when ssh-ing into CLAC and your
*backspace button might actually be sending "Ctrl + H" instead! To fix this you
*will have to add the following lines to your .emacs file.

    ;; make sure backspace deletes backwards
    (normal-erase-is-backspace-mode 1)
    ;; make sure your backspace is mapped correctly
    (global-set-key "\C-h" 'backward-delete-char)

And if you want mouse support, you'll have to add the following:

    (require 'mouse) ; mouse support
    (xterm-mouse-mode t) ; Turn on mouse mode
    (defun track-mouse (e)) ; Track the mouse
    (setq mouse-sel-mode t) ; Mouse selection
    (delete-selection-mode 1) ; For deleting the current selection
    (global-set-key [mouse-4] (lambda () (interactive) (scroll-down 1))) ; For scrolling up
    (global-set-key [mouse-5] (lambda () (interactive) (scroll-up 1))) ; For scrolling down


## Compiling and Linking a C Program ##

Just like Java code, C code can't be run directly on the CPU. It's converted to
an executable in these three steps:

  1. **Preprocessing:** This is when lines that start with a hashmark (`#`) are
     processed. For example, a line like `#include "somefile.h"` would be
     replaced with the contents of `somefile.h`. All other lines are passed
     onto the next step without modification.

  2. **Compiling:** This converts the C source code into a lower level language
     that's specific to the operating system and type of CPU in the computer. It
     reads C source code files (such as `foo.c`) and saves its output to object
     files (`foo.o`).

  3. **Linking:** The previous step may have produced several .o files that each
     contain part of our program's code. Linking puts all of that code together
     into a single file that we can execute.

Let's take a look at this process in an actual program. We'll create a
simple program that computes 1 + 2 by calling a function in another file.

`main.c`

```c
#include <stdio.h>
#include "myadd.h"

int main(int argc, char **argv) {
  printf("The sum is: %d \n", add(1, 2));
  return 0;
}
```

`myadd.h`

```c
#ifndef __MYADD_H__
#define __MYADD_H__
int add(int a, int b);
#endif
```

### Preprocessor directives

Notice the preprocessor directive `#include`. This instructs the preprocessor to
copy and paste the specified file into the current file at that location.
We use this line in `main.c` so that function declarations in the included
files are visible.

For example, in `main.c` we have the function call `add(1, 2)`. The compiler
wants to ensure that this is a valid function call, but doesn't know anything
about `add()`, what type it will return, or what its explicit parameters are.
After including `myadd.h`, the compiler knows that `add()` returns type `int`
and accepts two `int` parameters.

You might have recognized a slight difference in syntax between the first two
lines. Within `#include`s, files with names enclosed in `""` are assumed to be
user-defined; files with names enclosed in `<>`,  are assumed to be system-defined.
`stdio.h` is a common system-defined header file that declares input and output
functions, like `printf()`.

There is one other set of directives that we've used now: `#ifndef`, `#define`, and
`#endif`. `#ifndef` and `#endif` define a block of code that should only be included
if a preprocessor variable is *not* defined. This will prevent any conflicts caused
by headers being included multiple times. The first time it encounters `#include
"myadd.h"`, the preprocessor will define the macro `__MYADD_H__`, so if the file
is included again, the `#ifndef` condition will be false.

### How to Compile and Link

Now, let's compile `main.c` with the following command:

    gcc -g -Wall -c main.c

What do these flags mean?

  - `-g` — include extra information so that, if the program crashes, we can
    know which line and function caused the crash
  - `-Wall` — turns on several compile-time warnings. Warnings are likely
    problems with your code, but they aren't severe enough to stop the program from
    running. The sources of warnings can cause bigger problems
    later, so it's best to turn this on when compiling and fix all warnings.
  - `-c` — only preprocess and compile the files (do not link them yet)

After running the command above, you should have a `main.o` in your directory.



Hold on—we haven't written the `add()` function yet! However, `gcc` let us compile
`main.c` without warning. `gcc` knows that the function call in `main()` is valid
from its declaration in the included header `myadd.h`. That's all the compiler needs;
it doesn't care how `add()` works, just that it exists and is being validly used.

It's only during linking—when the code for `add()` is actually needed—that we will
get an error. Link with the following commmand:

    gcc -g main.o -o main

  - `-o filename` — tells `gcc` what to name the output file

Let's define `add()` in `myadd.c`.

`myadd.c`

```c
#include "myadd.h"
int add(int x, int y)
{
    return x + y;
}
```

It's a good idea to `#include "myadd.h"` in `myadd.c` even though we aren't
required to. Doing this allows the compiler to make sure the functions we write
in the `.c` file match the prototypes from the `.h` file. This feature will become
more useful as our programs get more complicated.

Compile `myadd.c`,

    gcc -g -Wall -c myadd.c
    ls

and, finally, link our two object files into the executable `main`.

    gcc -g myadd.o main.o -o main
    ls


You should now have an executable file in your directory `main`. Running
`./main` will run your program.

In this case, you must use `./` to indicate that you want to execute the program
main in the current directory. Otherwise, it will try to look for a system
program named "main," which doesn't exist on our system.

Building C programs by hand is extremely tedious. In the next review session,
we'll learn how to automate compilation and linking with Makefiles.

For more on compiling, linking, and debugging, see
[this article](http://cslibrary.stanford.edu/107/UnixProgrammingTools.pdf).
