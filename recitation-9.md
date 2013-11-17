# Recitation 9 #

## Introducing C++ ##

### Strings in C ###

At this point, you're all quite familiar with C's quirks and kinks. Perhaps one of the most notable ones is the absence of a String datatype!

Recall that Strings in C are just special cases of arrays. C strings are arrays of characters with a null terminating character at the end. 

```c
char buf[50]; //stack allocation
strcpy(buf, "hello");

char *s = (char *) malloc(50); //heap allocation
strcpy(s, "hello");

//don't forget to free s when you're done!
```
But finally, after months of dealing with those pesky invalid reads, memory leaks, and so on, we can transition into a new language that permits a much friendlier way to handle strings: C++!

### Classes/Structs in C++ ###
Before we go into strings in C++, let's talk about the basics of classes and structs first. Although we can define a struct in C++ the same way we do in C, structs tend to get much more complicated in C++ than their C predecessors). Here is the struct Pt example we all know and love:

```c
struct Pt 
{
	double x;
	double y;
}
```

#### Stack Allocation in C++ ####
Here's how you allocate space for a struct Pt in C++:

```c
struct Pt myPt;
//in C++, you can omit the 'struct' part. 
```
It looks exactly like how we allocated it in C! Boooring. But is it really doing the same thing?

Classes/structs in C++ have **constructors** whose purpose is to initialize all data members and base classes. When we declared our struct Pt, myPt, the default Pt constructor was called under the covers. If we don't define any constructors for a class/struct, the C++ compiler implicitly defines a default constructor for us. The synthesized default constructor takes no arguments will call the default constructors of all members of class type and leave members of built-in type undefined. Oftentimes, the synthesized default constructor is not what we want, so we define our own constructors. A word of caution, though: if we define ANY constructors ourselves, we can no longer rely on the synthesized default constructor. So if we want our class to have a default constructor, we'd better make sure to define it along with our other constructors, lest the compiler complain. We'll look more closely at the different types of constructors when we get into our MyString example. 

Hand-in-hand with constructors are **destructors**. The purpose of the destructor is to deallocate all data members. If we don't explicitly define a destructor, the compiler will synthesize one for us, which just calls the destructors of all class type members and does nothing for the built-in type members. A stack-allocated variable's destructor is called when the variable falls out of scope, after which the stack shrinks accordingly. 

#### Heap Allocation in C++ ####

Although you can still use `malloc` to allocate space on the heap, there's a preferred way to do it in C++, via the `new` operator:

```c
Pt myPt = new Pt();

//heap-allocated array of Pt's:
Pt myPtArray = new Pt[10];
```
The `new` operator not only allocates space for myPt on the heap, but it also calls Pt's constructor, in this case, the default constructor. Like with malloc, we must remember to free up the heap space we allocated with `new`:

```c
delete myPt;
delete [] myPtArray; //deleting a heap-allocated array
```
`delete` calls the Pt destructor of myPt and frees up the heap space it was using. `new` goes hand-in-hand with `delete`, and `malloc` goes hand-in-hand with `free`. But don't try to mix the four, i.e., calling `new` and freeing the memory with `free`. 

#### classes vs. structs ####

There is a subtle, yet important difference between `class`es and `struct`s in C++. In a struct, the members defined prior to the first access specifier (e.g., `public`, `private`, etc.) are `public`. In a `class`, they are `private`. We want our members to be `private`, so we'll be writing `class`es in our labs. 

### The Basic 4 of a C++ Class ###

There are four elements of a C++ class that you should always consider:

1. Constructor
2. Destructor
3. Copy Constructor
4. Operator=()

We've already discussed constructors and destructors, but what about the other two? The **copy constructor** specifies how to construct a class type variable using an argument of that class type, i.e.: 

```c
string myString = new string("hello");
string myStringCopy = new string(myString)
```

