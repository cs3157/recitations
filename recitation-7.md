# Recitation 7 #

## size_t ##

`size_t` shows up all over the place in memory operations. `malloc` expects its
parameters to be of this form, and certain file operation functions will return
the number of bytes read in this formed. What you need to know about `size_t` is
that its an unsigned integer type. This means it works like an integer but
**cannot represent negative values**. So, while the following is okay:

```c
size_t x = 5;
size_t y = 3;
int z = x + y;
```

The following is not (and wouldn't be a good idea even if the value was
positive):

```c
size_t x = 5;
size_t y = 3;
int z = y - x;
```

Other than that you can treat `size_t` as any other integer type.

## File operations ##

All of the following are defined in `stdio.h` and therefore
to use them you must `#include <stdio.h>` to use them.

### FILE * ###

`FILE` is a typedef'ed structure in `stdio.h`. Whenever you use it, you'll use a
`FILE *` though because you'll always be getting a value back from/passing it to
common file operating functions. Why a pointer? Because these functions will
modify the internal values of the `FILE` value. So while you could copy them
because its a struct and C would be fine with passing it by value, things like
your place in the file would not be maintained.

### fopen and fclose ###

```c
FILE *fopen(char *name, char *mode);
int fclose(FILE *fp);
```

The above structure should look a tiny bit familiar. Knowing what we know about
`FILE *`s you might see the likeness here to:

```c
void *malloc(size_t size);
int free(void *p);
```

That's because fopen and fclose create a new `FILE` structure on the heap so
that the status of the open file can be maintained. This means that **if you
don't `fclose` your `FILE *`s, you'll have memory leaks**. Be careful about
this.

### fgets and fputs ###

**THESE FUNCTIONS ARE FOR LINE INPUT AND LINE OUTPUT**

What's that you ask? It means they're really good at reading in lines, but bad
for everything else. Only use these functions if lines are a logical way to
delimit chunks of the file you're reading.

```c
char *fgets(char *line, int maxline, FILE *fp);
int fputs(char *line, FILE *fp);
```

`fgets` reads the next *line* from the input file in `fp` into the memory
location pointed to by `line`. If all is successful, it reads at most
`maxline-1` characters out of the file, and returns `line` as well. If something
goes wrong (on end of file, or error) it returns `NULL`. It will keep the
newline character it reads if it gets to one before it reaches `maxline-1`
characters. It also ALWAYS appends the null character to the end of the string.

`fputs` returns EOF if there's an error and 0 otherwise. This will not append a
newline to the file, nor does your string need to contain a newline character.

**Watch out!** `gets` and `puts` work very similarly for `stdin` and `stdout`
but `gets` will not give you the newline character.

### fread and fwrite ###

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

Each of these functions accept pointers of type `void`. So if you want each item
to be read into the right size memory space, you'll need to tell it the `size`
of each item, and the number of items `nmemb` to read/write from/to the
`stream`. `fwrite` promises not to modify the data that `ptr` references as
well. The return the number of bytes read/written. If its anything less than
what you expected, you should check what happened using `ferror` or `feof`.

### fseek ###

```c
int fseek(FILE *stream, long offset, int origin);
```

This handy dandy function lets you hop through a file without doing anything
other than changing the position in the `FILE` structure. You can use any
`stream` of your choosing, but pay attention to whether or not its a binary
stream. If its a binary stream, `offset` can be any number of bytes/characters from
`origin` which should be set to either `SEEK_SET` (a constant representing the
beginning of the file), `SEEK_CUR` (a constant representing the current
position), or `SEEK_END` (the end of the file).

If you're reading a text stream, `offset` must either be zero or the current
position as returned by a call to `ftell` (see below). In this case, always set
origin to `SEEK_SET`.

```c
FILE *text = fopen("myfile", "r");
FILE *binary = fopen("myfile", "rb");

fseek(text, ftell(text), SEEK_SET);
fseek(binary, -100, SEEK_END);
```

### feof and ferror ###

```c
int feof(FILE *stream);
int ferror(FILE *stream);
```

So you didn't get what you were expecting from one of the above functions. What
do you do? You call `feof` or `ferror`. These two functions let you know what
happened. `feof` returns true if the end of the `stream` has been reached, and
`ferror` returns true if there was an error reading the `stream`.

## TCP/IP ##
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
