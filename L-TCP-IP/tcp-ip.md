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
