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

#### The Copy Constructor ####

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

If you don't explicitly define a copy constructor, the compiler implicitly defines one for you, which just sets all data members of the newly constructed object equal to all data members of the argument object. This may or may not be what you want. Consider this segment of the `MyString` class from Jae's lecture notes:

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
If we didn't define a copy constructor for `MyString`, initializing a new MyString from another `MyString` would make the new MyString's data pointer point to the same heap-allocated space as the old MyString's data pointer. Upon destruction of either `MyString`, the other `MyString` would have a data pointer pointing to a freed piece of memory: hello, memory errors!

As a rule of thumb, if your class necessitates explicit definition of a destructor, as `MyString` does, chances are that your class necessitates explicit definition of a copy constructor. 

So how do we define a copy constructor? We know that the copy constructor is called when we try to pass an object by value, so we can't pass a `MyString` object as a parameter to our copy constructor; how can we define a copy constructor while relying on the existence of a copy constructor? We need a C++ construct known as a **reference**. You can think of a reference as a dereferenced pointer to something. For example:

```cpp

int x = 5;
int& y = x; //y is a reference to x

x = 6; //y is now 6
y = 7; //x is now 7
```
The reference construct allows us to pass an argument by reference, without the need for all that pointer business we've seen before. For example, this function will increment the integer passed as an argument, since the variable it's working with isn't a temporary copy of the argument--it's an alias for the argument itself!

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
MyString::MyString(const MyString& s) 
/*note that the const indicates that we will not modify
 the contents of s within this constructor*/
{
    len = s.len;
    
    data = new char[len+1];
    strcpy(data, s.data);
}
```

#### The Assignment Operator ####

If your class necessitates the definition of a copy constructor, your class necessitates the definition of an **assignment operator** for the same reasons. We can write our assignment operator almost entirely the same way we wrote our copy constructor, except now we also have to deal with the existing data of the lvalue. We can examine the contents of the lvalue via the C++ `this` pointer. `this` is a pointer to the object on which we're currently operating. The C++ `this` is not to be confused with the Java `this`, as the Java `this` is the object itself, rather than a pointer to it. 

Now that we have `this` at our disposal, we can write our assignment operator:

```cpp
MyString& MyString::operator=(const MyString& rhs)
{
    if (this == &rhs) {
	return *this;
    }

    // first, deallocate memory that 'this' used to hold

    delete[] data;

    // now copy from rhs
    
    len = rhs.len;

    data = new char[len+1];
    strcpy(data, rhs.data);

    return *this; //returns the MyString on which we are calling the assignment operator
}
```
Note that our assignment operator should return a MyString& so that we can chain calls to it:

```cpp
MyString MS("hello");
MyString MS2("world");
MyString MS3("yay");

(MS = MS2) = MS3; //MS is now "yay"
```
Make sure you understand the importance of the Basic 4 and always consider whether they're necessary for your program. Hint: they're almost always necessary. 

### Other Nifty C++ Features ###

#### Implicit Conversions ####

Recall from your lovely memories with C that there are some automatic type conversions that occur when intermixing types, for example:

```cpp
int y = 5;
double z = y; //y is coerced into double type
```
Automatic type conversions can occur for class type variables in C++. For our MyString class, we can do something like this:

```cpp
MyString s("hello");
s += "world"; 
/*compiler uses the MyString constructor that 
takes a char* to create a temporary MyString whose 
value is "world", which allows us to call our 
+= operator on two MyString objects*/

//note that the lifetime of our temporary MyString is the expression in which it was created
```

If we want automatic type conversion to occur, we need to make sure that the compiler is able to make the connection between the first type and the other, via our constructors (i.e., we can construct a MyString from a `char*`, but not from an `int`.)

#### Operators ####

C++ allows us to define our own operators for the classes we write. This means that we can do things like:

```cpp
MyString MS("hi");
MyString MS2("dude");
MyString MS += MS2;
```
You can find a list of all overloadable operators in C++ on page 553 of Lippman, 5th ed. For our MyString class, we'll be overloading `+`, `=`, `<<`, `>>`, and `[]` (plus the ones you'll overload in lab 9). 

You may find yourself running into the question of member versus nonmember implementation of your operators. Symmetric operators, operators that should allow implicit conversion of either operand, should be nonmember functions. Two examples of these are the `+` and `-` operators. Operators whose left-hand operand isn't of the class type shouldn't be members of the class, for example, the `<<` and `>>` operators of our `MyString` class. Operators that change the state of their object *should* be members. The assignment, subscript (`[]`), call (`()`), and member access arrow (`->`) operators *must* be members. 

##### Friend Declarations #####

If we want to have nonmember operators that access our non`public` data members, we need to declare them as **friend**s, as we do in `mystring.h`. 

```cpp
	// operator+
	friend MyString operator+(const MyString& s1, const MyString& s2);

	// put-to operator
	friend ostream& operator<<(ostream& os, const MyString& s);

	// get-from operator
	friend istream& operator>>(istream& is, MyString& s);
```
Remember this joke: "Only you and your friends can touch your private parts."

##### Const Member Functions #####

Note that the `const` version of the subscript operator in MyString has `const` at the end of its prototype. What's that about? A **const member function** is a member function that promises not to modify the object on which the function is being called. As such, the `const` version of the MyString subscript operator promises to not modify the contents of the MyString that it's subscripting. Note that we can cast away the `const`ness of `*this` so that we can reuse our non`const` subscript operator. 