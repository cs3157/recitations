Final Exam Review
=================

Our final review session typically goes through one of the sample exams. 
We're also providing this outline of some important topics in case
it helps organize your studying (but it's not meant to be exhaustive).

If you find a topic you're not familiar with, click the link to the full review
session notes. Make sure you understand the topic thoroughly before moving on.
Remember, the exams are written to test how deep your knowledge goes!

Topics from Midterm 1
---------------------

### Bits, Bytes, and Binary

_Main article: [Bits, Bytes, and Binary](D-Bits-Binary-C-Basics/bits-and-binary.md)_

*   Definition of bit, byte, MSB, LSB
*   Hexadecimal, octal
*   Two's complement


### C Basics

_Main article: [C Basics](D-Bits-Binary-C-Basics/c-basics.md)_

*   Data types and their sizes
    -   Integer: `char`, `short` `int`, `long, `long long`
    -   Floating point: `float`, `double`
    -   `sizeof` operator
*   ASCII table
    -   Know the relationships (don't memorize)
*   C strings (`char` arrays)
*   Syntax
    -   Bitwise operators `&`, `|`, `^` `~` `<<` `>>`
    -   Literal notations: `'`, `"`, `0x`, and `0`
    -   Order of operations


### Git

_Main article: [Git](C-Git/git.md)_

*   Usage of basic commands: `clone`, `status`, `add`, and `commit`
*   Tracking state


### Makefiles

_Main article: [Makefiles](B-Makefiles/makefiles.md)_

*   Understand each line of Jae's sample Makefile
*   Declaring targets & dependencies
    -   Implicit rules
    -   Phony targets
*   Build process: preprocessing, compiling, and linking


### Function Pointers

_Main article: [Function Pointers](F-Function-Pointers/function-pointers.md)_

*   Syntax examples: [goshdarnfunctionpointers.com](http://goshdarnfunctionpointers.com)
*   Usage, e.g. in `traverseList()` and `qsort()`


### Memory

_Main article: [Memory and Pointers](E-Memory-Pointers/memory-pointers.md)_

*   Common Valgrind errors & how to fix them
    -   [Valgrind manual, Section 4.2: Explanation of error messages from Memcheck](http://valgrind.org/docs/manual/mc-manual.html#mc-manual.errormsgs).
*   Process memory layout (relative position of stack, heap, static, code)
*   Pointers
    -   Regular pointer vs double pointer
    -   Why is `void *` different / special?


Topics from Midterm 2
---------------------

### File I/O

_Main article: [File I/O](K-File-IO/file-io.md)_

*   Usage of library functions related to `FILE *`
    -   Examples: `fopen()`, `fdopen()`, `fgets()`, `fwrite()`
*   Files you get automatically: `stdin`, `stdout`, `stderr`
    -   Buffering differences
*   File permissions
    -   What does `644` mean? Same as `rw-r--r--`?


### Fork & Exec

_Main article: [Fork / Exec](J-Fork-Exec/fork-exec.md),
[IPC and TCP/IP](IPC-TCP-IP/ipc-tcpip.md)_

*   Process vs program
*   Usage of `fork()` and `execl()`
    -   Idiomatic fork-then-exec pattern
*   Zombies and `waitpid()`
*   Pipes and shell redirection
    -   Difference between `|`, `>`, and `>>`
    -   Named pipe
    -   Netcat version of `mdb-lookup-server`

### Sockets

_Main article: [IPC and TCP/IP](IPC-TCP-IP/ipc-tcpip.md)_

*   Sockets API
    -   Understand (but don't memorize) Jae's TCP sample code
    -   `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`,
        `recv()`, etc.
*   Five-layer networking model (OSI model)


### HTTP

*   Basic structure of requests and responses
*   Important [status codes](https://httpstatuses.com/): 200, 400, 404, 501
*   HTTP 1.0 vs HTTP 1.1


Topics introduced after the midterms
------------------------------------

### Software Architecture

_Main article: See lecture notes_

*   Client-server architecture
*   Web app architecture: presentation, application, data


### C++ Basics

_Main article: [Introducing C++](M-cpp/cpp.md)_

*   Classes and structs
    -   Object lifecycle (Basic 4)
*   References
*   Heap allocation: `new` and `delete`
*   Function overloading
*   "Real" strings: `MyString` and `std::string`


### Templates & Containers

_Main article: [C++ Templates & Containers](N-Templates-Containers/templates-containers.md)_

*   Template syntax for classes and functions
*   Compiling templates
    -   Why do we need to put all template code into the `.h` file?
*   Standard library containers: `vector` and `list`
*   Iterators


### Smart Pointers

_Main article: [Smart Pointers](O-Smart-Pointer/smart-pointers.md)_

*   Reference counting
*   Behaviors & usage
    -   How does `SmartPtr` use the Basic 4 to update the reference count?
    -   What parts are on the stack vs the heap?


* * *

Thanks for reading our notes. Good luck on the final! You're gonna do great. 🌻
