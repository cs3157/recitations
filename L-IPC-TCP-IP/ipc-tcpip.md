## Interprocess Communication: pipes, FIFOs, and sockets ##
_How do processes running on the same system talk to each other? What about
processes on different systems?_

### Pipes ###
Sometimes, we want two or more processes to be able to communicate with each 
other. The most commonly used means of interprocess communication are pipes.
**Pipes** allow one-way data flow and can connect processes having a common 
ancestor. We can use a pipe to connect the stdout of one process to the stdin
of another. For example, we can "pipe" the output of `program1` to `program2`
like this:

```bash
./program1 | ./program2
```

Notice that data flows left to right. The idea is that this should feels
intuitive, since we read left to right. Also, recall that this is different
from _redirection_ with the `<` and `>` characters. Redirection passes
output to a file or a stream, while a pipe passes output between running
processes. (A discussion on the motivation behind this distinction is
available [here](http://askubuntu.com/questions/172982).)

The way pipes are implemented is operating system-dependent, but in general,
the processes that make up a [pipeline](https://en.wikipedia.org/wiki/Pipeline_%28Unix%29)
are started at the same time. The operating system then handles connecting
streams and giving processes large buffers to avoid data loss.

### Named Pipe (a.k.a. FIFO) ###
A **named pipe** or **FIFO (First In First Out)**is a type of file used for
interprocess communication. We can refer to FIFOs by name after they are created
using the `mkfifo` command.

Since `mkfifo` produces a file, we send output to FIFOs using the `>` and `<`
characters, rather than the `|` character used above.

This example from *Advanced Programming in the Unix Environment* by W. Richard
Stevens and Steven A. Rago illustrates how a script uses a FIFO called 
`myfifo` to execute a complex operation involving redirecting input and output
to and from the named pipe:

```bash
mkfifo myfifo
./program3 < myfifo &
./program1 < input.txt | tee myfifo | ./program2
```

Note that we need to run ```./program3 < myfifo``` in the background (using `&`) 
because opening a FIFO for reading normally blocks until another process opens
the FIFO for writing and vice versa. `input.txt` is passed as input to `program1`,
and `program1`'s output is piped to the `tee` command. The `tee` command transmits
its stdin both to stdout and to the file(s) specified in the argument, in this
case, `myfifo`. Since we pass `myfifo` as an input to `program3`, `program3` 
is able to receive `program1`'s output. The stdout of `tee` is piped to `program2`, 
allowing `program2` to receive `program1`'s output as well. Nifty!

If you'd like to run this example, programs 1, 2, 3, and `input.txt` can be found
in the [recitation-L-code directory](https://github.com/cs3157/recitations/tree/master/L-IPC-TCP-IP/code).

### Sockets ###
Pipes and FIFOs are fine for local, one-way data flow, but oftentimes we want
our interprocess communication to be even more flexible. That's when we can use
sockets.

A **socket** is a more general form of a pipe that can do two additional important
things:

1. Sockets can communicate across a network, meaning that they can connect two
machines (e.g. your laptop with a server hosting `facebook.com`).
2. Sockets allow for _two-way_ interprocess communication, unlike pipes.

We'll be discussing sockets in conjunction with the TCP/IP protocol: the
standard for communication over the Internet. You'll use sockets in labs
6 and 7, but we won't go over example code here.

#### TCP/IP ####
TCP/IP is the protocol that makes the world go 'round. The Internet is powered by
IP, and almost all the traffic is TCP (some is UDP, mostly games and
video/voice calls where a small amount of data loss is acceptable).

[TCP/IP](https://en.wikipedia.org/wiki/Internet_protocol_suite) is another name
for the Internet protocol suite, which describes the protocols used to make
the Internet and other networks function.

#### How does TCP/IP make the Internet happen? ###
There are four protocol layers of TCP/IP, where each successive layer is
a higher level of abstraction:

1. Application _(highest level of abstraction)_
2. Transport, TCP (and UDP)
3. Internet, IP
4. Link _(we won't talk about this one much)_

Here is a quick pass over the 4 layers: at the bottom are simply bits on
physical wires aggregated into frames, in the physical and data layer. Above
that, IP deals with packets and routing packets to the correct IP address.
Above that, TCP and UDP use IP packets to manage sending meaningful amounts of
data, for example connecting to a specific port on a server. Finally on top
of TCP you use specific protocols like HTTP, FTP, IMAP, DNS, and SSH. 

The IP protocol handles finding where on the planet a machine with a particular
IP address is. The TCP protocol handles finding which process on that machine
to go to, once IP has brought it to the correct location.

If it helps, you can consider 
[Beej's](http://beej.us/guide/bgnet/output/html/multipage/index.html) analogy: 
an IP address is like a hotel address and a port number is like a room number in 
that hotel. Port numbers range from 0 to 65535, but we can only use ports 1024 
and above.

### But why don't I ever use IP addresses on the Internet? ###
Good catch. We just said that IP sends packets toward IP addresses. But instead
of typing `160.39.63.50`, you use a hostname, like `clac.cs.columbia.edu`
or `google.com`.

DNS, **Domain Name Service**, is a protocol and server setup that translates
hostnames into IP addresses. Every time your laptop joins a network, it gets
its own IP address, the IP address of 1-3 DNS servers, and the IP address of a
router that can forward packets on to the rest of the world. Your laptop
translates hostnames to IP addresses by talking to the DNS servers, and
communicates with the Internet by speaking to the forwarding router.

Want to find out your IP address and DNS info? From a Linux or OS X machine, run
`ifconfig` in a terminal (on Windows, use `ipconfig`). You should see something
like this:

```
en1: flags=8863<UP,BROADCAST,SMART,RUNNING,SIMPLEX,MULTICAST> mtu 1500
    ether 58:b0:35:7d:33:7e
    inet 192.168.1.183 netmask 0xffffff00 broadcast 192.168.1.255
    media: autoselect
    status: active
```

In this case `192.168.1.183` is my IP address on the `en1` network interface.

### And why don't I ever use port numbers on the Internet? ###
As for port numbers on the Internet, the Internet's application protocol, HTTP,
specifies that we should use port 80. For HTTPS, we use port 443. Since these
ports are established by convention, we can omit them when we navigate to a
webpage.

### How do sockets relate to the TCP/IP stack? ###
The sockets API sits between the transport and application layers. All the code
we write in this class sits at the application layer. Your browser and netcat
also sit at the application layer. _How the IP and TCP protocols work is outside
the scope of this class._

We'll go more in depth about the sockets API later on, but our journey into 
network programming will begin with the `netcat` tool, which deals with all the 
socket connection stuff under the hood. To quote the man page description: "The 
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

_Note that `<port>` and `<hostname or IP address>` need to be replaced with the
appropriate values._

In this example, `netcat` takes whatever it receives from stdin and sends it
out to whomever is connected to it. It also reads whatever it gets from whomever
is connected to it and outputs it to stdout. So, effectively, the `stdin` of the 
client is sent to the `stdout` of the server, and the stdin of the server is sent
to the stdout of the client. 

Now that we've learned about `netcat` and FIFOs, we have all the tools we need
to turn `mdb-lookup-cs3157` into a network server. Yippee!
