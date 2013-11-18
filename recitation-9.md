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

```cpp
struct Pt 
{
	double x;
	double y;
}
```

#### Stack Allocation in C++ ####
Here's how you allocate space for a struct Pt in C++:

```cpp
struct Pt myPt;
//in C++, you can omit the 'struct' part. 
```
It looks exactly like how we allocated it in C! Boooring. But is it really doing the same thing?

Classes/structs in C++ have **constructors** whose purpose is to initialize all data members and base classes. When we declared our `struct Pt`, `myPt`, the default `Pt` constructor was called under the covers. If we don't define any constructors for a class/struct, the C++ compiler implicitly defines a default constructor for us. The synthesized default constructor takes no arguments will call the default constructors of all members of class type and leave members of built-in type undefined. 

What if we attempted to call the default constructor like this?

```cpp
Pt myPt3();
```

Oftentimes, the synthesized default constructor is not what we want, so we define our own constructors. Let's say we want the user to be able to specify values for `Pt` members `x` and `y`. We could do so as follows:

```cpp
struct Pt
{
	double x;
	double y;

	Pt(double x, double y);
};

//we could have also made this inline
Pt::Pt(double myX, double myY)
{
	x = myX;
	y = myY;
}
```
And we can call it like this:

```cpp
Pt myPt2(4, 4);
```

When we define member functions for our classes, we can choose to define them within the class definition (the part enclosed by the curly braces of struct Pt), or just declare them within the class definition and define them elsewhere. Member functions defined within a class definition are implicitly **inline**. Inline functions are kind of like macros in that calls to them are replaced with the body of the function. Inline functions should be short. If we don't define functions in the class definition, we need to use the scope resolution operator, `::`, to indicate that it's a member of the class. 

A word of caution, though: if we define ANY constructors ourselves, we can no longer rely on the synthesized default constructor. Now that we've defined a constructor for `Pt` that takes two `double`s, we lose our synthesized default constructor. A declaration like this would be illegal now:
```
struct Pt myPt;
```
So if we want our class to have a default constructor, we'd better make sure to define it along with our other constructors, lest the compiler complain.

Hand-in-hand with constructors are **destructors**. The purpose of the destructor is to deallocate all data members. If our constructor allocated space on the heap for its data members, our destructor should free up that space. If we don't explicitly define a destructor, the compiler will synthesize one for us, which just calls the destructors of all class type members and does nothing for the built-in type members. A stack-allocated variable's destructor is called when the variable falls out of scope, after which the stack shrinks accordingly. 

#### Heap Allocation in C++ ####

Although you can still use `malloc` to allocate space on the heap, using `malloc` doesn't allow you to call the constructor of a class type object. A preferred way to do heap allocation in C++ is via the `new` operator:

```cpp
Pt myPt = new Pt();
Pt myPt = new Pt(4, 4);

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

```cpp
string myString = new string("hello");
string myStringCopy = new string(myString)
```
The copy constructor is called implicitly in a couple other scenarios: passing by value and returning by value:

```cpp
string call_copy(string myString) //copy constructor is called to create temporary copy of myString local to call_copy
{
	return myString; //copy constructor is called to return myString by value
}
```

If you don't explicitly define a copy constructor, the compiler implicitly defines one for you, which just sets all data members of the newly constructed object equal to all data members of the argument object. This may or may not be what you want. Consider this segment of our MyString class:

```cpp
class MyString
{
	char *data;
	int len;
	
	MyString(char *p);
	...

}

...

MyString::MyString(char *p)
{
	if (p)
	{
		len = strlen(p);
		data = new char[len+1];
		strcpy(data, p);
	}

	else 
	{
		data = new char[1];
		data[0] = '\0';
		len = 0;
	}

}

MyString::~MyString()
{
	delete[] data;
}
```
If we didn't define a copy constructor for MyString, initializing a new MyString from another MyString would make the new MyString's data pointer point to the same heap-allocated space as the old MyString's data pointer. Upon destruction of either MyString, the other MyString would have a data pointer pointing to a freed piece of memory: hello, memory errors!

As a rule of thumb, if your class necessitates explicit definition of a destructor, as MyString does, chances are that your class necessitates explicit definition of a copy constructor. 

So how do we define a copy constructor? We know that the copy constructor is called when we try to pass an object by value, so we can't pass a MyString object as a parameter to our copy constructor; how can we define a copy constructor while relying on the existence of a copy constructor? We need a C++ construct known as a **reference**. You can think of a reference as a dereferenced pointer to something. For example:

```cpp

int x = 5;
int& y = x; //y is a reference to x

x = 6; //y is now 6
y = 7; //x is now 7
```
`y` isn't really its own variable; it's just a synonym for `x`. So if we tried to change `y`, we'd just be changing `x`. 

The reference construct allows us to pass an argument by reference, without the need for all that pointer business we've seen before. For example, this function will increment the integer passed as an argument:

```cpp

void increment(int& x)
{
	x++;
}

...
int y = 5;
increment(y);
cout << y << endl; //prints 6
```
Using this new reference construct, we are ready to define our copy constructor:

```cpp
MyString::MyString(const MyString& s) //note that the const indicates that we will not modify the contents of s within this constructor
{
    len = s.len;
    
    data = new char[len+1];
    strcpy(data, s.data);
}
```
If your class necessitates the definition of a copy constructor, your class necessitates the definition of an **assignment operator** for the same reasons. We can write our assignment operator almost entirely the same way we wrote our copy constructor, except now we also have to deal with the existing data of the lvalue. 
