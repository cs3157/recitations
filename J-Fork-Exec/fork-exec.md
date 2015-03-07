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

### Processes ###

One-to-one programs-processes is not a thing! A program is a packaged set of
instructions, whereas a process is an instance of a program. A program can have
many processes associated with it. For example, we can run multiple instances of
an executable independently, thereby initiating multiple processes that run that 
program. We can create more processes associated with the executable by splitting
a process with the `fork` system call, as we'll soon see.

Each process has a unique, non-negative numeric identifier known as the **process ID**.

#### Creating New Processes with fork/exec ####

We can create new processes using the `fork` system call. The caller of fork is known as 
the parent process and the process getting created is known as the child process.

`fork()` will split your process into two new processes, each one executing
forward from the point of the fork. `fork()` is called once in the parent, but returns 
twice: once in the parent and once in the child. The return value of `fork()` 
depends on if it's executing within the child process or parent process. `fork()` 
will return the process id of the child if it's executing within the parent, and 
it will return 0 of it's executing within the child process. This means you can 
identify which process you are in simply by checking the return of `fork()`. Note
that the process ID of the child process is **NOT** equal to 0. Also note that
the order of execution of the child and parent processeses relative to each other
is unpredictable.

One of the most common uses of forking--which is what you'll be using forking for
in lab 5--is to run other programs via an existing process. That is, you'll have
a running process that will fork itself and, while the parent continues executing
the original program instructions, the child will transform into another process.
How do we transform the child?

You can use the `exec()` family of functions to *turn your current process* into
an instance of another program. The new program is specified in the arguments to
the `exec()` call. Once the call to `exec()` has been made, the process running
`exec()` will cease to execute the code of its original program and begin executing
the code of the new program. Your process has no memory (ha-ha) of the previously 
running program, i.e., its program code, data, heap, and stack are replaced with 
those of the new program. If the program reaches its end, the process will exit 
and will never return to the code of your old program. This means that any code 
following a call to `exec()` will only be executed if the call to `exec()` fails. 

For lab 5, you'll be dealing with the `execl()` function. It takes as arguments
the path to the program you want to execute (make sure you use a relative path!)
and the command line arguments you want to pass to the program. Be sure to study 
`execl()`'s man page carefully.

Fork and executing is how the entire operating system works. The kernel starts
an `init` process and everything is fork/exec'ed from there.

#### Communicating Between Processes ###
Check out [recitation L](https://github.com/cs3157/recitations/blob/master/L-IPC-TCP-IP/ipc-tcpip.md) about interprocess communication (IPC).

#### Dealing with Terminated Processes ####

So what happens when the child process terminates before the parent process?
The parent is responsible for ensuring that the child process is "reaped", so
to speak. In other words, the system resources associated with the child 
process need to be released. Otherwise, the child will become a "zombie" process.
Ah, CS humor. 

We can release these resources using the `wait()` family of functions. In lab 5,
you'll be using `waitpid()`, which can wait for a process with a specific ID,
as well as other categories of processes. Check out its man page for more info.

Okay, so we know what to do when a child terminates before its parent, but how
about when a parent process terminates before the child? In that case, the child 
becomes an "orphaned" process. If you're interested in orphan and zombie processes, 
you can check out the optional part 2 of lab 5. 

For a fun fork/exec example, check out the `jsh` program in the 
[recitation-J-code directory](https://github.com/cs3157/recitations/tree/master/J-Fork-Exec/code).

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
