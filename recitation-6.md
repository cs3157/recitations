# Recitation 6 #

## *nix Systems ##

### The Stack ###

  1. Hardware
  2. OS Kernel
  3. System Calls
  4. Library Functions
  5. Applications

Software is built in many layers that depend on each preceding layer.
Understanding what level each piece of functionality exists at is imperitave to
strong programming.

### Users and Permissions ###

Unix systems have three different ways to allocate permissions: owner (a user),
group, and everyone else.

  - **Owner** The owner is always a user and the owner can own both files and
    directories.
  - **Group** A file or directory is assigned to a group, usually but not always
    the user group that the owner belongs to.
  - **Others** Those who are not in the assigned group, nor an owner, belong to
    the others.

The owner can always assign owner permissions to another user.

There are three UNIX file permissions. Read, write, and execute. Always think of
them in this order. Read is the ability to access or look at the contents of
the file. Write is the ability to modify the contents of the file. Execute is 
the ability to execute a file.

When set for directories, read allows for listing the files in the directory;
write allows for creating, deleting, and renaming files; and execute allows for
accessing files and metainfo if their name is known, but not listing the files
in the directory.

Permissions are conventionally represented as combinations of 3 binary digits.
Each digit represents one of read write and execute. So for example, 100
would represent the ability to only read and is a value of 4. 110 is the
ability to write and read and is a value of 6. 111 would grant read, write,
and execute and is a value of 7. Conventionally, you could combine these in the
order owner-group-other in a string like "644" which would mean the owner can
write/read, and the group and others and only read. `chmod ### path` can
be used to set permissions for a path. Note that you can view permissions 
(among other things) of files in your current directory by entering `ls -al`.
The `-a` option includes files that begin with a dot and the `-l` option displays 
each file in long format, which is what shows you the file permissions
and all that good stuff. See the `ls` man page for more information. 

### Some Notes About Lab 4 ###
If you plan on doing the pair option and would like to 
[procure a private GitHub repo](https://github.com/edu), please request one ASAP,
because it takes a few days to process. Additionally, if you're new to GitHub/BitBucket,
you may find the [Git Documentation](http://git-scm.com/book), the 
[GitHub Help page](https://help.github.com/), and the 
[BitBucket Documentation](https://confluence.atlassian.com/display/BITBUCKET/Bitbucket+Documentation+Home)
handy.

Whether you choose to do the pair option or the solo option, you may wish to 
review each of the I/O functions we've learned in lecture note 9. Be sure that 
you understand the differences between them and note that there are certain situations
when some are more appropriate than others, and vice versa (ex., `fgets()` vs. `fread()`).

### Processes ###

one-to-one programs-processes is not a thing! A program is a packaged set of
instructions, where as a process is an instance of a program. A program can have
many processes associated with it. 

`fork()` will split your process into two new processes, each one executing
forward from the point of the fork. `fork()` will return a pid of 0 if it is
executing within the child process, or the pid of the child process if it is
executing within the parent process. This means you can identify which process
you are in simply by checking the return of `fork()`. 

`exec(char *command)` will *turn your process into* an instance of command. This
means it will cease executing your code and execute as the program you have
decided to execute. If the program reaches its end, the process will exit and
will never return to your code. It will only execute code following an `exec`
call if `exec` fails.

Fork and executing is how the entire operating system works. The kernel starts
an `init` process and everything is fork/exec'ed from there.

### Signals ###

Signals are an OS's way of communicating with a process outside of the I/O
streams. They can be sent at any time and a process has three options upon
receiving them:

  1. Let the default action take place
  2. Explicitly ignore the signal (not necessarily possible)
  3. Catch the signal and do something special (not necessarily possible)

There are tons of signals and each one has a number associated with it. Ctrl-C
for example is a signal, SIGINT for signal interrupt. You can use the `signal()`
function to set your program up to handle these signals. `signal()` takes two
arguments: the signal you want to handle, and a function pointer to a function
of what to do if that signal is received. Not all signals can always be caught
with this method, so it is convention to wrap the call to signal as follows:

```c
if(signal(SIGINT, &myHandler) == SIG_ERR) {
  perror("call to signal() failed");
  exit(1);
}
```

In this way, if the call to signal is not accepted by the operating system you
will be aware and can respond appropriately. In this case we simply exit the
program with an error code but this might not be the best behavior. Note that to
use these constants and functions you must `#include <signal.h>`. Also be aware
that you can only catch the first reception of the signal. The call to signal
will set the action to be taken to "myHandler" but afterwards it will be reset
to the default action for that signal. Page 255 in the K&R has a little bit more
information on this.
