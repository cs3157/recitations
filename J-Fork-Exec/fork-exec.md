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
[recitation-6-code directory](https://github.com/cs3157/recitations/tree/master/recitation-6-code).

#### Interprocess Communication: pipes, FIFOs, and sockets ####

Sometimes, we want two or more processes to be able to communicate with each 
other. The most commonly used means of interprocess communication are pipes. 
**Pipes** allow one-way data flow and can connect processes having a common 
ancestor. We can use a pipe to connect the stdout of one process to the stdin of 
another. For example, we can "pipe" the output of `program1` to `program2` like this:

```bash
./program1 | ./program2
```

What if we wanted a more flexible means of interprocess communication? Let's say
we want to transmit the output of `program1` to two programs: `program2` and 
`program3`. We can accomplish this using a **named pipe** or a **FIFO (First In
First Out)**. A FIFO is a type of file used for interprocess communication.
Since we can refer to FIFOs by name, we can get a bit more creative with how we use them. 
This example from *Advanced Programming in the Unix Environment* by W. Richard Stevens 
and Steven A. Rago illustrates how we can achieve our above goal:
```bash
mkfifo myfifo
./program3 < myfifo &
./program1 < input.txt | tee myfifo | ./program2
```

Note that we need to run ```./program3 < myfifo``` in the background because 
opening a FIFO for reading normally blocks until another process opens the FIFO 
for writing and vice versa. `input.txt` is passed as input to `program1`, and 
`program1`'s output is piped to the `tee` command. The `tee` command transmits
its stdin both to stdout and to the file(s) specified in the argument, in this
case, `myfifo`. Since we pass `myfifo` as an input to `program3`, `program3` 
is able to receive `program1`'s output. The stdout of `tee` is piped to `program2`, 
allowing `program2` to receive `program1`'s output as well. Nifty!

If you'd like to run this example, programs 1, 2, 3, and `input.txt` can be found
in the [recitation-6-code directory](https://github.com/cs3157/recitations/tree/master/recitation-6-code).

Pipes and FIFOs are fine for local, one-way data flow, but oftentimes we want
our interprocess communication to be even more flexible. A **socket** is a type 
of file used for network communication between processes. Sockets are 
generalizations of pipes: with sockets, we can achieve both intramachine communication, as
with our above examples, and intermachine communication. Additionally, sockets
allow for two-way interprocess communication, unlike pipes. We'll be discussing 
sockets in conjunction with the TCP/IP protocol: the standard for communication 
via the Internet. 

There are five protocol layers of TCP/IP:

1. Physical
2. Link
3. IP
4. Transport
5. Application

The sockets API sits between the Transport and Application layers. In this class,
we're mostly concerned with the Application layer.

In order to send data via a socket connection, we need a few means of
identification to figure out where the data needs to go: an IP address and a port 
number. The IP address is a unique identifier that is assigned to a computer or 
device on a TCP/IP network. In Internet Protocol Version 4, the IP address is a 
32-bit integer, for example: "192.0.0.1". A port number works together with an IP 
address to identify the application or process on the host to which data must be 
transmitted. If it helps, you can consider 
[Beej's](http://beej.us/guide/bgnet/output/html/multipage/index.html) analogy: 
an IP address is like a hotel address and a port number is like a room number in 
that hotel. Port numbers range from 0 to 65535, but we can only use ports 1024 
and above. 

We'll go more in depth about the sockets API later on, but our journey into 
network programming will begin with the `netcat` tool, which deals with all the 
socket connection stuff under the hood. To quote the man page description, "The 
nc (or netcat) utility is used for just about anything under the sun involving 
TCP or UDP.  It can open TCP connections, send UDP packets, listen on arbitrary 
TCP and UDP ports, do port scanning, and deal with both IPv4 and IPv6." One of 
the many uses for netcat is building a basic client/server model. The server will 
listen on a particular port number, passively waiting. The client will connect to 
the host on which the server is running, using that host's IP address, on the 
port on which the server is listening.

We can achieve this using the following shell commands:

Server:

```nc -l <port>```

Client:

```nc <hostname or IP address> <port>```

Note that `<port>` and `<hostname or IP address>` need to be replaced with the appropriate values. 

In this example, `netcat` takes whatever it receives from stdin and sends it
out to whomever is connected to it. It also reads whatever it gets from whomever
is connected to it and outputs it to stdout. So, effectively, the stdin of the 
client is sent to the stdout of the server, and the stdin of the server is sent
to the stdout of the client. 

Now that we've learned about `netcat` and FIFOs, we have all the tools we need to turn `mdb-lookup-cs3157` 
into a network server. Yippee!

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
