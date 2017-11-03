
## *nix Systems ##

### The Stack ###

  1. Hardware: physical components - processor, disk, keyboard, etc...
  2. OS Kernel: core of an operating system that loads first, controls resources, performs fundamental tasks
  3. System Calls: a call/request for a kernel operation, e.g. `open()`, `signal()`, `fork()` and `exec()` 
  4. Library Functions: inbuilt functions that come with programming language performing specific functions, e.g. `printf()`, `malloc()`
  5. Applications: end-user programs like emacs, gcc, and executables you build in class. 

### Users and Permissions ###

Unix systems have three different ways to allocate permissions: owner (a user),
group, and everyone else. The owner can always assign owner permissions to another user. (root users !!)

There are three UNIX file permissions. Read, write, and execute. Always think of
them in this order. Permissions are conventionally represented as combinations of 3 binary digits.
Each digit represents one of read write and execute. So for example, 110 is the
ability to write and read and is a value of 6. (100-> read-> value of 4. 111 -> read, write, execute -> value of 7). Conventionally, you could combine these in the order owner-group-other in a string like "644" which would mean the owner can
write/read, and the group and others can only read. `chmod ### path` can
be used to set permissions for a path. Note that you can view permissions 
(among other things) of files in your current directory by entering `ls -al`.

### Processes ###

A program is a packaged set of instructions, whereas a process is an instance of a program. A program can have
many processes associated with it. For example, we can run multiple instances of
an executable independently, thereby initiating multiple processes that run that 
program. We can create more processes associated with the executable by splitting
a process with the `fork` system call, as we'll soon see.

Each process has a unique, non-negative numeric identifier known as the **process ID**. You can use `getpid()` to get the process ID of the current process.

#### Creating New Processes with fork/exec ####

We can create new processes using the `fork` system call from an existing process. `fork()` creates a new process by duplicating the current process, and each process executes from the point of the `fork()` call. (duplicates tasks, stack, etc... specify) The caller of fork is known as 
the parent process and the process getting created is known as the child process. `fork()` returns 0 in the child process, and the process ID of the new (child) process in the parent process. One of the most common uses of forking--which is what you'll be using forking for
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
following a call to `exec()` will only be executed if the call to `exec()` fails. For lab 5, you'll be dealing with the `execl()` function. 

Fork and executing is how the entire operating system works. The kernel starts
an `init` process and everything is fork/exec'ed from there.

(Cut more of this part ?)

#### Communicating Between Processes ###
Check out [recitation L](https://github.com/cs3157/recitations/blob/master/L-IPC-TCP-IP/ipc-tcpip.md) about interprocess communication (IPC).

(keep?)

#### Dealing with Terminated Processes ####

So what happens when the child process terminates before the parent process?
The parent is responsible for ensuring that the child process is "reaped", so
to speak. In other words, the system resources associated with the child 
process need to be released. Otherwise, the child will become a "zombie" process.
Ah, CS humor. We can release these resources using the `wait()` family of functions. In lab 5,
you'll be using `waitpid()`, which can wait for a process with a specific ID,
as well as other categories of processes. Check out its man page for more info. If a parent terminates before its child, the child 
becomes an "orphaned" process. If you're interested in orphan and zombie processes, 
you can check out the optional part 2 of lab 5. 

For a fun fork/exec example, check out the `jsh` program in the 
[recitation-J-code directory](https://github.com/cs3157/recitations/tree/master/J-Fork-Exec/code). 

(Needs editing)
(moved Signals to bottom)
(need better transition to shell.c)

## Jae's shell.c Program ##

Let's go through shell.c and see these system calls in action. (shell.c is found in -- put in recitations?)

### Variables ### 
```c
    char  buf[100];
    pid_t pid;
    int   status;
```
Aside from the buffer, we declare a variable `pid` of type `pid_t`. `pid_t` is a signed integer data type that represents proccess IDs. We also declare an integer variable, `status`, to store process status information. We'll see how later, during the `waitpid()` function call. 

### System Calls ### 

```c
  pid = fork();
```

`fork()` will duplicate your current (parent) process, creating a new (child) process. Each will execute from the point of the fork. `fork()` is called once in the parent, but returns 
twice: once in the parent and once in the child. The return value of `fork()` 
depends on if it's executing within the child process or parent process. `fork()` 
will return the process id of the child if it's executing within the parent, and 
it will return 0 of it's executing within the child process. `fork()` returns (??/) if there is an error. This means you can 
identify which process you are in simply by checking the return of `fork()`. Note
that the process ID of the child process is **NOT** equal to 0. Also note that
the order of execution of the child and parent processeses relative to each other
is unpredictable. 


```c
else if (pid == 0) {  
            // child process
            execl(buf, buf, (char *)0);
            die("execl failed");
        }
```

The above block of code is only executed in the child process (where `pid == 0`). `execl()` completely replaces the child process image with the new one - an instance of the program passed through `buf`. The first argument of `exec()` family of functions is the path of the file to be executed. The second argument, by convention, is the filename of the file to be executed (hence `buf` being passed in twice). Subsequent arguments are arguments to pass into the file to be executed. The list of parameters must **always** be ended by `NULL` pointer cast to `char *` to show the end of the argument list. The above block calls `execl()` with just the file to be run and no arguments. Once `execl()` is called and succeeds, the process is turned into an instance of the program pointed to by `buf` - nothing beyond the `execl()` call in the original program is executed. 

```c
else {
            // parent process
            if (waitpid(pid, &status, 0) != pid)
                die("waitpid failed");
        }
``` 

The above block of code is only executed in the parent process (where `p > 0`). `waitpid()` is used to wait or check for state changes in child processes. `waitpid()` takes in three arguments. The first is a number of type `pid_t`. This can be a specific process ID of a child process, or an integer representing other categories of process. In the case above, it passes in the process ID of its child to `waitpid()`. In lab 5, you'll see a case where `waitpid()` is called with -1. (explain? refer to man?) The second argument is a pointer to `status`, telling `waitpid()` to save state information in that variable. State information could be signals set in the process, exits and terminations or errors. (Point to info on signals ???) If `NULL` is passed instead of a pointer to variable, then state information is not saved. `status` can be used with a variety of functions to inspect/get information about child process. (man page) The third arguments is an option parameter. `0` tells `waitpid()` to wait put off returning until child process has changed state or terminated. In lab5, we'll see the `WNOHANG` option that tells `waitpid()` to **not** wait for child processes to terminate and return immediately if children are still running. In the above block, `waitpid()` returns the process ID of the child it waited for. For different return values with different options, check out man page (improve sentence, refer to man page only once).

```c
printf("AP> ");
```

The `printf()` statement above is executed only by the parent process, once the child process has terminated. Remember, the child process never gets to this point because it was replaced by a different instance, and the parent has to wait for the child before it continues through the loop. After printing, the while loop will star over, going through everything again until parent process is terminated. 


### Signals ###

(keep?) 

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
