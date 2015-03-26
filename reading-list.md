### [The Descent to C](http://www.chiark.greenend.org.uk/~sgtatham/cdescent/) ###
by Simon Tatham (author of PuTTY)

An "orientation" to C for those coming from a higher level language (e.g., Java
or Python). It helps explain why C is different, and how that's good (at least
for some things). Probably most useful around lab 2, once you've actually 
writen some C code. May also be useful as a review for midterm #1.


### [Reading C Type Declarations](http://unixwiz.net/techtips/reading-cdecl.html) ###
Strategy for dissecting complex C declarations.

### [*The Perils of Java Schools*](http://www.joelonsoftware.com/articles/ThePerilsofJavaSchools.html) ###
Jae's favorite article on CS education. It talks about why Java is a dangerous language to learn with, and C is important for education. 


### [Standard Input](http://www.linfo.org/standard_input.html) ###

Totally confused by UNIX stdin, stdout, etc? This short article may help clarify
how standard input and output work for processes in UNIX.


### [Learn C the Hard Way](http://c.learncodethehardway.org/book/) ###


### [*Why Mobile Web Apps are Slow*](http://sealedabstract.com/rants/why-mobile-web-apps-are-slow/) ###
by Drew Crawford

This is a lonng article, probably best to read toward the end of the class.
Comments by Jonathan Balsano.

Why?

It touches on some really important technical aspects of mobile programming
that you'll learn about as part of your CS education here. (Also, you probably
didn't think you were going to need those concepts in the developer world -
they're probably only useful for academia, right?) After AP you should be able
to get through it, but you might be a little confused. I encourage you to hold
onto the article, though, because after you take courses like Fundamentals, OS,
and PLT, more and more of the article will make sense and tie together the
ideas you've learned in a very real and applicable way. In a really nerdy way,
I was excited while reading it because I could feel all these seemingly
unrelated things coming together in a very technical way.

Also, I've heard people complain you learn things you'll never use again in
this class, like C, memory management, etc. "Garbage collected languages like
Ruby, Python, and Java are the way of the future" they say. My response to this
has always been that its still important to learn the languages because its not
just about the language, but the abstractions C and C++ are built around. In
particular, C's (and in turn C++'s) syntax and constructs are so tightly linked
to the OS underneath its impossible to learn pointers and arrays without
understanding some essential OS concepts (like memory).

What?

A lot of things, but the last part about memory management is most applicable
to what we've learned in this class.

"Why's he keep bringing up memory?" you're thinking. It's because the third
argument in the article, the part about Garbage Collection and Automatic
Reference Counting (ARC, basically smart pointers in Objective C). Here's my
quick summary that's surely missing about 95% of the information in the
article:

In a world that's becoming increasingly mobile, we're hitting up against a lot
of the boundaries of processing power, in part because of the need for
portability. Over the past decade, our answer to making things faster has often
been "Just throw more CPUs/servers/computers at it" but that's not really
possible in the mobile world due to size and power constraints. Unfortunately,
in memory constricted environments (like your phone) being oblivious to memory
isn't going to work. 

In these cases, you're going to have to understand how memory works. Whether
you're working on Android (with garbage collection) or iOS (ARC), you need to
know how much memory you're using underneath, because for the next 5-10 years
(at least) the mobile memory problem seems unlikely to change.

### C vs C++: Linus' perspective ###
Linus Torvalds, the man who wrote Git and Linux kernel, is a famous
C++ hater.  Here is his famous hate mail on C++: http://article.gmane.org/gmane.comp.version-control.git/57918

### AT&T Labs Video on UNIX ###
http://www.youtube.com/watch?v=tc4ROCJYbm0

It is a 1982 video from AT&T introducing their shinny new invention: UNIX.  It talks about some of the things we covered/will cover this week and next week, but you get to hear it from the true giants in the field: the late Dennis Ritchie (the inventor of C & co-inventor of UNIX), Ken Thompson (co-inventor of UNIX), Brian Kernighan (the K in K&R), and our own Professor Al Aho (the A in AWK, the grand daddy of all modern scripting languages).


### [WWWDaemon](https://github.com/NotTheRealTimBL/WWWDaemon/blob/master/old/V0.1/daemon.c) ###
The original (ok, a very early version, 0.1) HTTP web server by Tim Berner's Lee. Very similar to lab7 server.


### [Stanford CS106L Course Reader](http://web.stanford.edu/class/cs106l/course_reader.html) ###
Stanford's intro C++ class has a lab section, 106L. They've written a ~600 page textbook, but it's an incredibly good resource for learning all about everything we've done. For example, they have pages and pages on how linking works. Highly recommended, but be aware it's focused only on C++, so most of the stuff applies to C, but not all.

### [You Can't Dig Upwards](http://www.evanmiller.org/you-cant-dig-upwards.html) ###
An article about why only knowing Python is like only knowing how to drive an automatic transmission car. Basically, python is too easy, and you don't understand how a computer actually works.

### [Valgrind is NOT a Leak Checker](http://maintainablecode.logdown.com/posts/245425-valgrind-is-not-a-leak-checker) ###
An article about why leak checking is one of the less useful features Valgrind offers. 

# To Add #
* Heartbleed and goto fail writeups
* The Unreasonable Effectiveness of C

# To Vet #
* C++ Value Semantics: http://akrzemi1.wordpress.com/2012/02/03/value-semantics/
* Integer Represenations: http://pages.cs.wisc.edu/~smoler/x86text/lect.notes/represent.html
* Why should I use a pointer, rather than an object?: http://stackoverflow.com/questions/22146094/why-should-i-use-a-pointer-rather-than-the-object-itself
* How to debug small programs: http://ericlippert.com/2014/03/05/how-to-debug-small-programs/#
* C structure packing http://www.catb.org/esr/structure-packing/
* * Implementing malloc: http://danluu.com/malloc-tutorial/
* 21st Century C: O'Reilly book about how we're all dinosaurs for returning 0 from main http://clio.columbia.edu/catalog/10816384?counter=1
* [Was C for Hipsters?](http://timkellogg.me/blog/2015/02/08/history-of-C/)
* [HTTP Made Really Easy](http://www.jmarshall.com/easy/http/)
* [A Guide to Undefined Behavior in C and C++](http://blog.regehr.org/archives/213)
* [I Do Not Know C](http://kukuruku.co/hub/programming/i-do-not-know-c) -- Q&A with some tricky undefined behavior questions.
* [What a C programmer should know about memory](http://marek.vavrusa.com/c/memory/2015/02/20/memory/)
* [Are pointers and arrays equivalent in C?](http://eli.thegreenplace.net/2009/10/21/are-pointers-and-arrays-equivalent-in-c)
