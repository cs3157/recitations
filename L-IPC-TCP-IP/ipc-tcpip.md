##Interprocess Communication: pipes, FIFOs, and sockets ##

### Pipes ###
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
`program3`. We can accomplish this using a named pipe. 

### FIFO aka Named Pipe ###
A **FIFO (First In
First Out)** or **named pipe** is a type of file used for interprocess communication.
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
in the [recitation-L-code directory](https://github.com/cs3157/recitations/tree/master/L-IPC-TCP-IP/code).

Pipes and FIFOs are fine for local, one-way data flow, but oftentimes we want
our interprocess communication to be even more flexible. That's when we can use sockets.

### Sockets ###
A **socket** is a type 
of file used for network communication between processes. Sockets are 
generalizations of pipes: with sockets, we can achieve both intramachine communication, as
with our above examples, and intermachine communication. Additionally, sockets
allow for two-way interprocess communication, unlike pipes. We'll be discussing 
sockets in conjunction with the TCP/IP protocol: the standard for communication 
via the Internet. 

#### TCP/IP ####
TCP/IP is the protocol that makes the world go 'round. The internet is powered by
IP, and almost all the traffic is TCP (a small amount is UDP, mostly games and
video/voice calls where every millisecond matters, and a small amount of data
loss is acceptable).

You may have heard of the 7 layer OSI stack, well similarly TCP/IP has a 4 layer
stack which means at higher layers you generally don't need to think too many layers
lower. At the bottom are simply bits on physical wires aggregated into frames,
in the physical and data layer. Above that IP deals with packets, and routing
packets to the correct IP address. Above that TCP and UDP use IP packets to manage
sending meaningful amounts of data, for example connecting to a specific port on
a server. Finally on top of TCP you use specific protocols like HTTP, FTP, IMAP,
DNS, and SSH. 

IP sends packets towards IP addresses. However you don't want to use IP addresses,
such as `160.39.63.50`, but instead you want to use a hostname, like
`paris.clic.cs.columbia.edu`. DNS, Domain Name Service, is a protocol and server
setup that translates hostnames into IP addresses. Every time your laptop joins
a network, it gets its own IP address, the IP address of 1-3 DNS servers, and
the IP address of a router that can forward packets on to the rest of the world.

Want to find out your IP address and DNS info? On OSX and Linux run `ifconfig` in
a terminal. You should see something like the below:

```
en1: flags=8863<UP,BROADCAST,SMART,RUNNING,SIMPLEX,MULTICAST> mtu 1500
    ether 58:b0:35:7d:33:7e 
    inet 192.168.1.183 netmask 0xffffff00 broadcast 192.168.1.255
    media: autoselect
    status: active
```

In this case 192.168.1.183 is my IP address. 

#### Back to sockets ####
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
device on a TCP/IP network. A port number works together with an IP 
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
