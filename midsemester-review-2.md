# Mid-Semester Review 2 #
This is a quick summary of topics leading up to the second midterm.
It is by no means fully comprehensive; use the rest of the lecture notes and
recitation notes to help if you're unclear on anything.

## Files ##

_Main article: [File I/O](K-File-IO/file-io.md)_

### 3 channels ###
Remember that all C programs are automatically given 3 channels for input and
output: `stdin` (0), `stdout` (1), and `stderr` (2). Make sure you understand
their purposes and how to interact with them using function such as `fprintf()`.

#### Redirecting I/O #####
It is possible to redirect the source of `stdin` or the destination of `stderr` and
`stdout`. Make sure you understand how to use `>`, `<`, and `>>`.

Remember `|`? We'll talk about that in the Pipes section below.

### File I/O ###
`FILE *`'s (file descriptors) are your best friends; they're just fancy pointers
for files. As noted above, all C programs start with `FILE *`s `stdin`,
`stdout`, and `stderr`.

You open a file with `fopen()`, which takes two strings: the name of the file
you want to open and the mode in which you want to open it. Modes include
`r`, `w`, `a`, `r+`, `w+`, `a+`, and all of the previous with a `b` tacked on
the end. Do you remember the differences? (Hint: check out the `man` page.)

You read from and write to the file with functions `fgets()`/`fputs()`,
`fprintf()`/`fscanf()`, and `fread()`/`fwrite()`. Hopefully you're familiar
with these functions by now; if not, reviewing the `man` pages is a great idea.

Don't forget that you need to close the file when you're done by using
`fclose()`. Before closing, you can use `feof()` or `ferror()` to see if
anything weird happened while you were interacting with the file.

### Buffering ###
Buffering determines how often the contents of a stream are sent to their
destination. Unbuffered streams are constantly flushed to its destination.
Line-buffered streams are only flushed to its destination after a newline
character is written. Block-buffered streams are flushed when they reach a
certain size. You can use `fflush(fp)` to manually flush the buffer for any file
pointer.

* `stderr` is unbuffered - remember why? (hint: debugging!)
* `stdout` is line-buffered when it's connected to the terminal
* everything else is block-buffered

## Fork/Exec ##

_Main article: [Fork / Exec](J-Fork-Exec/fork-exec.md)_

### Quick UNIX overview ###
Before we can talk about `fork()` and `exec()`, here's a quick review of the
UNIX system.

#### Users and Permissions ####
Unix systems have three different ways to allocate permissions: owner (a user),
group, and everyone else.

* __Owner__ The owner is always a user and the owner can own both files and directories.
* __Group__ A file or directory is assigned to a group, usually but not always the user group that the owner belongs to.
* __Others__ Those who are not in the assigned group, nor an owner, belong to the others.

There are also three UNIX file permissions: read, write, and execute. Make sure
you're comfortable with the binary and octal representations of these
permissions. For example: 100 is the ability to only read, and has a value of 4.
111 is read, write, and execute, and has value 7. These numbers can be combined
for owner, group, and others as well, like `chmod 644`. (Exercise: who has what
permissions on a file after `chmod 644`?)

#### Processes ####
A program is a packaged set of instructions, whereas a process is an instance
of a program. A program can have many processes associated with it. For
example, we can run multiple instances of an executable independently, thereby
initiating multiple processes that run that program. We can create more
processes associated with the executable by splitting a process with the fork
system call, as we'll soon see.

Confused? Here's an analogy: Let's say you have a recipe for an amazing soup.
While you only have one recipe, you can have multiple pots cooking at once.
A program is like that recipe; you can have multiple processes (pots) running at
once.

Each process has a unique, non-negative numeric identifier known as the
__process ID__ (`pid`).

### `fork()` ###
We can create new processes using the `fork()` system call. The process that
calls `fork()` is the __parent process__; this creates a second process called
the __child process__, essentially splitting your original process into two
processes.

After `fork()`, the parent and child process both execute all code after the
`fork()` statement. `fork()` is called once in the parent, but returns twice:
once in the parent and once in the child. The return value of `fork()`
depends on if it's executing within the child process or parent process.

* If `fork()` is returning in the __parent process__, it returns the __child's `pid`__
* If `fork()` is returning in the __child process__, it returns __0__

This means you can identify which process you are in simply by checking the
return value of `fork()`.

Note that the process ID of the child process is NOT equal to 0. Also note
that the order of execution of the child and parent processes relative
to each other is unpredictable.

### `exec()` ###
Now that you've used `fork()`, you have two exact copies of the same process.
That's great, but it can be limiting. The `exec()` family of functions lets you
turn your current process into an instance of _another_ program. Cool!

You create the new program with `exec()` by specifying arguments, which include
things like the new program name and any command line arguments. (Check out the
`man` page for more info.) Once the call to `exec()` has been made, the
process running `exec()` stops executing the code of its original program and
begins executing the code of the new program. Your process has no memory
(ha-ha) of the previously running program: its program code, data, heap, and
stack are replaced with those of the new program. If the new program ends, the
process exits and never returns to the code of your old program. This means
that any code following a call to `exec()` will only be executed if the call to
`exec()` fails.

### Dealing with Terminated Processes ###
When a child process terminates before the parent process, the parent is
responsible for ensuring the child process is __reaped__. In other words, the
system resources associated with the child process need to be released,
otherwise the child will become a __zombie__.

But what if a parent process terminates before the child? Then the child
becomes an __orphan__; it is usually then "adopted" by `init` (`pid`=1).
(`init` is the first process started by an operating system; everything else
is `fork`/`exec`'d from there.)

## Pipes ##

_Main article: [IPC and TCP/IP](IPC-TCP-IP/ipc-tcpip.md)_

__Pipes__ allow one-way data flow and can connect processes having a common
ancestor. We can use a pipe to connect the `stdout` of one process to the
`stdin` of another. For example, we can "pipe" the output of `program1` to
`program2` like this:

```
./program1 | ./program2
```

Note that pipes and file redirects are _not_ directly interchangeable. `>` is
used to direct `stdout` into a file; `|` is used to direct `stdout` into
_another process's_ `stdin`. Look at the difference between the following
examples:

```
cat hello.txt > goodbye.txt     // puts contents of hello.txt into a file called goodbye.txt
cat hello.txt > less            // puts contents of hello.txt into a __file__ called less
cat hello.txt | less            // puts contents of hello.txt as stdin to the program less
```

You can, however, combine `|` and redirects (`>`, `<`, `>>`). Give it a try!
And check out the next section.

## FIFO, aka Named Pipe ##
A __FIFO (First In First Out)__ or __named pipe__ provides a slightly more
flexible form of communication than a regular pipe. Since we can refer to FIFOs
by name, we can get a bit more creative with how we use them.

Recall the pipeline from Lab 5:

```
mkfifo mypipe
cat mypipe | nc -l <port #> | /home/jae/.../mdb-lookup-cs3157 > mypipe
```

`mypipe` serves as a link between `nc` and `mdb-lookup-cs3157`. This
accomplishes a circular pipeline:
* `cat` pulls contents out of `mypipe`
* The first `|` sends contents from `cat mypipe` to `nc`
* The second `|` sends the output of `nc` as input to `mdb-lookup-cs3157`
* `>` sends output of `mdb-lookup-cs3157` into `mypipe`
* Now there's something in `mypipe` for `cat` to pull out, and we start all over again

Note that we redirect (`>`) into `mypipe`, not `|` into it. `mypipe` itself is
not a program or process, it's more like a file that we can read from and write to.

## Sockets ##

_Main article: [IPC and TCP/IP](IPC-TCP-IP/ipc-tcpip.md)_

Pipes and FIFOs are fine for local, one-way data flow, but often we want to
communicate between processes that may not even be on the same machine.
__Sockets__ are a way to do just that. A socket is a type of file used for
network communication between processes. Sockets are generalizations of pipes:
with sockets, we can achieve both intramachine communication, as with our
above examples, and intermachine communication. Additionally, sockets allow for
__two-way__ interprocess communication, unlike pipes. To talk about sockets,
let's take a quick detour to TCP/IP.

### TCP/IP ###
TCP/IP is the protocol that makes the world go 'round. The internet is powered by
IP (Internet Protocol), and almost all the traffic is TCP (Transmission Control
Protocol). IP sends bundles of bytes called packets toward IP addresses. Instead
of having to memorize IP addresses, we can use DNS to translate between IP
addresses and hostnames.

There are five protocol layers of TCP/IP networking:
1. Physical
2. Link
3. IP
4. Transport
5. Application
The sockets API connects Transport and Application layers. We're mostly
concerned with the Application layer.

### Back to sockets ###
In order to send data via a socket connection, we need a few means of
identification to figure out where the data needs to go: an IP address and a
port number. The IP address is a unique identifier that is assigned to a
computer or device on a TCP/IP network. A port number works together with an
IP address to identify the application or process on the host to which data must
be transmitted. If it helps, you can consider
[Beej](http://beej.us/guide/bgnet/output/html/multipage/index.html)'s analogy:
an IP address is like a hotel address and a port number is like a room number in
that hotel. Port numbers range from 0 to 65535, but we can only use ports 1024
and above.

We won't go over the socket API in depth here, but make sure you understand
all the steps to create a server socket and a client socket. Definitely use the
[Donahoo slides](http://cs.baylor.edu/~donahoo/practical/CSockets/PracticalSocketC.pdf)
to help you out.

## Netcat ##
`nc` is the Swiss army knife of the networking world. You can set up a
server-client connection with the following commands:

Set up a server listening on `<port>`:
```
nc -l <port>
```

Connect a client to the server above:
```
nc <hostname or IP address of server> <server port>
```

Vanilla `nc` has two jobs: get connected and share information. The server waits
until a client connects to it. After that happens, some neat `stdin`/`stdout`
redirecting happens. The server sends all of its `stdin` to the client, and prints
everything it receives from the client to `stdout`. The same happens with the
client: its `stdin` is sent to the server, and it prints what it receives from the
server to `stdout`. So, effectively, the `stdin` of the client is sent to the
`stdout` of the server, and the `stdin` of the server is sent to the `stdout`
of the client. You can think of it as a super simple instant messenger!

`nc` can obviously do more complex things when used in conjunction with pipes,
named pipes, redirects, etc. Take another look at the pipeline from Lab 5 and
make sure you fully understand it.

## HTTP ##
Make sure you understand HTTP in depth (to the extent that you
needed it for Lab 6). You can read more about HTTP/1.0
[here](http://www.jmarshall.com/easy/http/).

To request information from a server, you can formulate a GET request as follows:
```
GET /path/file.html HTTP/1.0
[zero or more headers ...]
[a blank line, must be '\r\n']
```
The response from the web server looks something like this:
```
HTTP/1.0 200 OK
Date: Fri, 31 Dec 1999 23:59:59 GMT
Content-Type: text/html
Content-Length: 1354

<html>
<body>
<h1>Happy New Millennium!</h1>
(more file contents)
.
.
.
</body>
</html>
```

## C++ Basics ##

_Main article: [Introducing C++](M-cpp/cpp.md)_

### What's different? ###
* Classes/structs: default constructor
* References
* Stack allocation and heap allocation (`new`/`delete`)
* The Basic 4
* Function overloading
* "Real" strings (`MyString`)

### References ###
In C, when you call a function, you pass arguments by value: a brand new copy
of the argument is made for the function to use. That's why we needed pointers.
Remember the following example?
```
void swap(int x, int y) {
	int tmp = x;
	x = y;
	y = tmp;
	return;
}
```
This doesn't actually work, because `swap()` gets its own copies of the
parameters. `swap()` never even touches the "original" `x` and `y` that it
is called with. Instead, you needed to do something like this:
```
void swap(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
	return;
}
```
C++ has something new: a construct known as a __reference__. You can think of
a reference as a dereferenced pointer to something. Here's a quick example:
```
int x = 5;
int& y = x; //y is a reference to x

x = 6; //y is now 6
y = 7; //x is now 7
```
`y` and `x` are essentially the same thing. You could write `swap()` in C++
like this:
```
void swap(int& x, int& y) {
	int tmp = x;
	x = y;
	y = tmp;
}
```
Cool, right?

### Stack and Heap Allocation ###
Allocating space on the stack for a struct in C++ looks exactly the same as it
does in C, e.g.
```
struct Pt myPt; // you can omit the "struct" in C++
```
Even though they look the same, though, they actually don't operate the same
way. In C++, classes and structs have special functions called __constructors__
that initialize all data members and base classes when the class/struct is
allocated.

Heap allocation is also different in C++. You can still use `malloc()` and
`free()`, but `malloc()` doesn't allow you to call the constructor. Instead,
you can use the `new` keyword, like this:
```
Pt *myPt = new Pt; //allocates sizeof(Pt) space on heap, calls constructor
Pt *someArray = new Pt[10]; //heap-allocated array of Pts
```
Just like every `malloc()` must have a `free()`, every `new` must have a
`delete`:
```
delete myPt;
delete [] someArray;
```

Don't mix up `malloc()`/`free()` and `new`/`delete`.

### The Basic 4 ###
1. Constructor
    - Called when an object is allocated on stack/heap
2. Destructor
    - Called when an object goes out of scope/`delete` is used
3. Copy Constructor
    - Called when object needs to be copied (e.g. passed as argument)
4. Operator=()
    - Called when an object is assigned to a variable

Make sure you understand why all of the above are necessary when you're writing
a class or struct.
