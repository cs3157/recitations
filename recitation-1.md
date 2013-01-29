# First Recitation #

## Logging in ##
 

Logging in is fairly simple if you're in the clic lab. Just use your UNI and 
password on any of the machines when prompted. You may have to back out once 
to be able to enter your UNI.

Remember that your password isn't necessarily the same as your UNI password, 
its the one you used when creating your clic account.

If you're on a mac:

- Open up Terminal
- type `ssh your_uni@clic-lab.cs.columbia.edu` You will be prompted for your 
clic password. Enter it.
- NOTE: if you want to enable X11 forwarding (this will allow you to share 
graphical programs as well as the shell with the remote machine) append the X 
(must be capital) flag to your ssh command. 
`ssh your_uni@clic-lab.cs.columbia.edu -X`
- You will now be in a remote shell session on a random machine in the clic 
cluster.

If you're on Windows

- Download and install either [Putty](http://cuit.columbia.edu/putty-software) 
or [MobaXterm](http://mobaxterm.mobatek.net/)
- Each program has a fairly simple to use GUI for connecting, so the relevant 
information is just:
  - Username: your_uni
  - Password: your click password
  - Remote server: clic-lab.cs.columbia.edu
- Click connect and you'll be in a remote shell session on a random machine in 
the clic cluster.

Also note, if you ever need to connect to a specific machine in the clic 
cluster (this will be necessary if you want multiple sessions on the same 
machine) just use `ssh you_uni@machine.clic.cs.columbia.edu`

## Basic UNIX ##
 

### Paths ###
 
A good palce to start with UNIX is the filesystem structure. Our clic machines 
run Ubuntu linux. Unlike Windows machines, UNIX uses forward slashes to denote 
the break between directories and files. An example file path in UNIX might be 
`/usr/bin/dict`. The path `/` by itself denotes *the highest level directory*. 
If you start any path with a forward slash, it will assumed to be a path 
relative to the root directory `/`. Alternatively, your current directory is 
represented by the notation `./`. In most cases you can leave this off. You 
can find out your current directory using the command `pwd`. If you're current
directory is `/usr/bin` and you wish to reference the directory `/usr` in a
path, you can do so using *either* `/usr` (this is known as an absolute path),
or you can use `../` (this is a relative path. `../` denotes the directory above
the current directory. You could reference the root directory `/` from the
directory `/usr/bin` using the relative path `../../`.

### Basic Navigation ###

When you log into clic, your current (working) directory will be
`/home/your_uni`. Check this by typing:

    pwd

This is what's known as your home directory. You can do pretty
much whatever you want to the files in this directory. You own the place. Let's
make a new directory here for your work in this class. Use the `mkdir` command
to make a new directory:

    mkdir cs3157 //if you're in COMS W3157
    mkdir cs3136 //if you're in COMS 3136
    mkdir cs3157/learning

Now let's move into your working directory. Use the change directory command,
`cd`. All three commands below will do the same thing (which ones are the
relative paths?)

    cd cs3157/learning
    cd ./cs3157/learning
    cd /home/your_uni/cs3157/learning

Let's create a new text file using the `touch` command. This will create
a new empty file if one does not exist, or update the last modified date if a
file exists.

    touch testing.txt
    touch .hidden.txt

Let's see if it worked. The `ls` command lists all files in the current
directory. Some commands in UNIX take flags. These are special arguments
preceded by a dash. Usually it will make the most sense to attach the `-l` and
the `-a` flags to our ls calls. `-l` will include the permissions of each file
(more on this later) and `-a` will include files that are hidden (in UNIX, these
are files that start with a .)

    ls
    ls -l
    ls -la //we can combine flags for ls

Notice the differences in output each time the command is run. Now let's delete
our hidden file using the remove command, `rm`.

    rm .hidden.txt
    ls -la

Alright, now lets get rid of the directory we created here. `rm` accepts flags 
too and won't let you delete directories unless you specify to run it 
recursively (repeatedlygo into each subdirectory and delete all files. It will
also ask for confirmation that you want to delete files unless you tell it to 
force the delete. For force delete, use `-f` and for recursive use `-r`:

    cd ../
    rm learning -rf
    ls -la

One last thing as a side note: if you ever don't know how to use a command in
UNIX (or even a function in the standard C library) you can use the `man`
command. It will bring up the manual pages for the command you ask it for. Try
to learn more about the ls command:

    man ls

Use `q` to quit out of a man page.

### Useful Tricks ###
 
#### Tab Complete ####
 
When in bash, try to make use of *tab-complete* as often as possible. This just
means pressing tab after typing the first few letters of a command. For example
typing `tou` followed by the tab key will complete to `touch`. Tab complete also
works for directory and file names.

#### Previous command ####
 
You can go through your history by pressing the up and down arrows in terminal.
This will navigate between previously used commands so that you can easily use
the same commands over and over.

#### back i search ####
 
For long complicated commands that you only use every so often you can use the
reverse search to locate them in your history. Pressing `ctrl` `r` in terminal
will bring up a backward search through your history. Start typing until you
find the command you're looking for.


## Text Editors ##
 

There are two main text editors that you can use from inside terminal: emacs and
vim. Which you use will ultimately be your decision (you could even write
everything in pico if you really wanted, but this would be difficult).

### Vim ###
 
Vim is a difficult to use text editor and very confusing at first. It's goal is
to be incredibly efficient by preventing unnecessary movement of your hands
around the keyboard. It operates in different modes, the most important of 
which will be *edit mode* and *insert mode*.

Open vim, editing a new file "vimtest".

    vim vimtest

When you open vim, it will be in Normal mode. Typing will cause a variety of
different operations to happen. For now switch to Insert Mode by pressing `i`.
You should see `-- INSERT --` appear at the bottom of the screen. At this point
anything you type will appear as text in the text file. This is fine for basic
editing. Now let's switch back to Normal mode. Press the `esc` key to switch
back.

Most vim commands execute as soon as you type them. Here are some basic commands
that will execute immediately:

  - `h` `j` `k` and `l` are how you move while in Normal mode. They are,
    respectively, left, down, up, right. Notice that this will save you time in
    moving to the arrows keys.
  - `dd` will delete the current line
  - `D` will delete from the current location to the end of the line
  - `yy` will copy the current line
  - `p` will paste whatever is the buffer (kind of like a clipboard)
  - `0` jumps to the beginning of the line
  - `$` jumps to the end of the current line
  - `u` undoes the last change

Some vim commands will not be executed until you press enter. These begin with a
colon.

  - `:w [optional filename]` This will save the current file if no file name is
    passed or write the current file to specified location.
  - `:e filename` will open the filename specified
  - `:q` will quite vim and take you back to terminal
  - `:[line numer]` will jump to that line

That should be enough for basic vim navigation. If you want to learn to be a
real vim ninja, get used to switching between modes first. Then try to expand
your Normal mode vocabulary one command at a time. In vim, most commands work
with some sort of combination between prepositions and actions. For example,
`gg=G` would indent the entire file, as `gg` takes you to the beginning of the
file, `=` auto-indents a line, and `G` jumps to the end of the file. 

You can also use vimtutor to really learn the ins and outs. In terminal, just
type

    vimtutor

Alternatively, check out [Open Vim's Tutorial](http://www.openvim.com/tutorial.html)
for another interactive vim lesson.

After learning vim, you might want to configure it. This is done by editting the .vimrc file in your home directory. Let's check out our current settings.

    vim ~/.vimrc

There should be default settings there already, but you can look to make changes here in the future.

### Emacs ###
 
Emacs is an easier to pick up text editor but has less efficient keyboard
shortcuts compared to vim.

Let's start by editing a new file in emacs

    emacs emacstest

As soon as emacs starts running, you will be able to type into it. There is no special insert mode like in vim. You can backspace at any time without having to switch between modes. 

Emacs has much of the functionality that vim has and we present the basics below:
  
  - 'Ctrl-f' will move your cursor forward, 'Ctrl-b' will move it back, 'Ctrl-p' will move it up, 'Ctrl-n' will move it down
  - 'Ctrl-k' will delete the current line
  - 'Ctrl-s' will search for a word forward, 'Ctrl-r' will search for a word backward
  - 'Ctrl-a' goes to beginning of line, 'Ctrl-e' goes to end
  - 'Ctrl-spacebar' to select text to manipulate
  - 'Esc-w' to copy text, 'Ctrl-w' to cut text, Ctrl-y' will paste your most recently copied/deleted text

Unfortunately, emacs makes some commonly used shortcuts a real pain to use:

  - 'Esc-x' then type in 'goto-line' and then the line number to go to a specific line (I usually map this to 'Ctrl-l' so it's actually useful)
  

To exit and save we will use Ctrl-X + Ctrl-C. If you just want to save then use Ctrl-X + Ctrl-S.

Just like vim, emacs also has a configuration file that you can edit. This is .emacs file within your home directory. Let's check out our emacs settings.

    emacs ~/.emacs

There should be default settings there already, but feel free to add more for shortcuts.

*Note that backspaces can be a little funky when ssh-ing into CLIC and your backspace button might actually be sending "Ctrl + H" instead! To fix this you will have to add the following lines to your .emacs file.

    ;; make sure backspace deletes backwards
    (normal-erase-is-backspace-mode 1)
    ;; make sure your backspace is mapped correctly
    (global-set-key "\C-h" 'backward-delete-char)

## Compiling and linking a C Program ##

There are many steps to compiling a program in C. They occur in the following
order:

  1. *Pre-processing*: This is when the compiler processes lines that start with
     a hash-mark (#).
  2. *Compiling*: This converts a source code file (foo.c) into an object file
     (foo.o) which contains a system dependent compiled representation of the
     program as described in the source file. This code may contain symbols
     (like variables and function names) that are not defined in the individual
     source files.
  3. *Linking*: This step links code in various object files together, linking
     up the pieces that are required in all the .o files. This will produce an
     executable file. 

Let's take a look at this process in an actual program: myadd. We'll create
three text files in the same working directory.

myadd.h

```c
#ifndef _MYADD_H_
#define _MYADD_H_
int add(int x, int y);
#endif
```

myadd.c

```c
#include "myadd.h"
int add(int x, int y)
{
    return x + y;
}
```
main.c

```c
#include "myadd.h"
int main(int argc, char **argv) 
{
    add(2, 4);
}
```
We'll be using gcc to compile our programs. `gcc` as a terminal command accepts
a few parameters that we'll be making use of often.

  - `-g` This flag will include debugging flags when you compile. If you're going
    to be shipping your program, you won't want to include this flag, but for
    the purposes of this class, you'll probably always want these flags. They'll
    enable debugging tools to give you more useful information like the line
    number and file of the code that crashed.
  - `-Wall` This will turn on all warnings. Essentially, if there's a problem in
    your code that isn't a compiler error, it will be reported as a warning.
    These can be small problems now that cause big crashes later, so its best to
    turn this on when compiling.
  - `-c [files]` This will compile a list of .c files into .o files without
    going through the linking stage. You'll need this in the future for
    Makefiles.
  - `-o [file]` specifies what gcc's output should be. If none is specified this
    will default to either foo.o or a.out. foo.o will be the case if you're only
    compiling without linking. If you're creating an executable file, a.out is
    the default executable filename.

Now let's try to compile myadd. First we'll build object files for both myadd.c
and main.c. Notice the compiler directive `#include`. This tells the compiler to
just copy paste the specified file into the current file at that location. The
reason we include this line in main.c and myadd.c is so that if we reference a
function in either of these files before it is defined, the compiler can know
its header. 

As an example, in main.c we have `add(2, 4);`. The compiler wants to make sure
that this is a valid function call but knows nothing of the function "add", what
type it will return, or what its explicit parameters are. Including myadd.h will
tell the compiler that "add" returns type int, and accepts two integer
parameters.

Let's compile these two files:

    gcc -c myadd.c myadd.h
    gcc -c main.c myadd.h
    ls

You should see that you now have a myadd.o and main.o in your directory. There 
was one other set of directives that we've used now. The `#ifndef` `#define` 
and `#endif` directives. The first and the last define a block of code that 
should only be executed if a pre-processor variable is *not* defined. This will
prevent multiple header files from conflicting. If myadd.h is included more 
than once, the first time the pre-processor will define \__MYADD_H_ and each 
time thereafter will skip over the entire file. Now let's link these two files.

    gcc myadd.o main.o -o main
    ls

You should now have an executable file in your directory `main`. Calling
`./main` will run your program. In this scenario, you *must* use `./` to note to
the shell that you want to execute the program main in the current directory.
Otherwise it will go looking in all the places it searches for commands like
`ls` and `touch` to find `main`.

For more on compiling, linking, and debugging, see 
[this article](http://cslibrary.stanford.edu/107/UnixProgrammingTools.pdf)
