# C++ templates and containers #

So far, we know how to write classes in C++ from our experience with `MyString`.
Since you already know about object orientation (inheritance and things like
that) from previous courses, we'll talk about generics instead.

## What is generic programming? ##

**Generic programming** is when a single algorithm is written to work on many
data types. As programmers, we only have to write the algorithm once: the
compiler takes care of generating the code for each data type, reducing the need
to write duplicate code.


### `void *`: Drawbacks of generic programming in C ###

In the mylist lab, we created a linked list library that could handle many data
types by using `void *`. However, this approach has some problems: it doesn't
provide any type safety. **Type safety** is the ability of a compiler to ensure
that types match. For example, this means it will print an error if an `int`
variable is used when a `std::string` is expected.

Remember how we retrieved items from the linked list? We had to cast the `void
*` to the type of the item we put into the list. For example, if we added a
`double *`, the linked list would give us a `void *`, and we would cast it back
with `(double *)`.

If we accidentally wrote the wrong type, the program might crash or produce the
wrong output. The compiler couldn't provide type safety to our linked list
library because once the pointer is cast to `void *`, it loses the original type
information.

In summary, the C compiler is helpless once data is cast to `void *` — it can't
catch type errors at compile time.


## Using templates with classes ##

C++ implements generic programming using templates. **Templates** let us write
code so that the compiler can "fill in the blanks" with the requested type when
we use the code. So for a list library, the compiler would use the template to
generate a different copy of the list code for each type we want to store in it
(`double`, `MdbRec`, etc).

Here's an example of using a templated class in C++. `vector` is an expandable
array in C++, like `ArrayList` in Java or `list` in Python. (We'll see later how
to write templated classes.)

```cpp
#include <iostream>
#include <vector>

vector<int> ivec; // This vector holds items of type int
vector<MdbRec> mdbvec; // This vector holds items of type MdbRec
vector<vector<MyString>> msvecvec; // vector holds vectors of MyString
```

The type of `ivec` is `vector<int>`. This not the same type as `mdbvec`, which
has type `vector<MdbRec>`. The type of the templated object includes the types
we want the compiler to fill into the template.

Now let's see how to write a templated class. We use the `template` keyword
before the class definition:

```cpp
template <typename T> // "T" is the type to be "filled in"
class vector {
  public:
    void push_back(const T& x);
    T& at(size_t index);

  private:
    T *a;
    size_t size;
    size_t capacity;
    void grow();
};
```

When we ask the compiler for a `vector<int>`, it "fills in" `int` whenever it
finds `T`, and compiles the resulting class. This happens every time we use
`vector` with a new type.

If we have a `vector<int>`, the compiler knows that we'll always get an `int&`
back when we call the `at()` method. If we try to store the result into, for
example, an `MdbRec`, the compiler will give us an error.


## Using templates with functions ##

Just like with classes, we can also use templates to write generic functions.
Let's say we want to write a comparison function that works for many types. We
could write it out by hand:

```cpp
// returns 0 if the values are equal, -1 if v1 is smaller, 1 if v2 is smaller
int compare(const string &v1, const string &v2)
{
  cout << "Now comparing: " << v1 << " and " << v2 << "\n";
  if (v1 < v2)
    return -1;
  if (v2 < v1)
    return 1;
  return 0;
} 
int compare(const double &v1, const double &v2)
{
  cout << "Now comparing: " << v1 << " and " << v2 << "\n";
  if (v2 < v1)
    return 1;
  if (v1 < v2)
    return -1;
  return 0;
}
```

These functions are identical, which is bad because we've copied and pasted
code. We'd have to copy and paste a third time if we wanted to compare a new
type, such as `int`. Furthermore, every time we want to change the algorithm, we
would have to modify each copy, increasing the likelihood of bugs.

Since `string`, `double`, and `int` all have `operator<` defined and can all be
printed with `cout`, we can condense the functions above into a template:

```cpp
template <typename T>
int compare(const T &v1, const T &v2)
{
  cout << "Now comparing: " << v1 << " and " << v2 << "\n";
  if (v2 < v1)
    return 1;
  if (v1 < v2)
    return -1;
  return 0;
}
```


## Templates under the hood ##

Templates aren't like any other language feature we've seen so far, so they
complicate the compilation process. But understanding this complexity enables us
to write concise, high-performance programs that are impossible in many other
languages.

Read through this section if you're curious about how the C++ compiler achieves
this. It may also help you debug weird template-related error messages.

### The compilation process, so far ###

If you go back to the beginning of the course, we discussed compilation as the
following steps:

1. Preprocessing (`#include`, `#define`, other `#` directives)
2. Compiling (turning .c files into .o object files)
    * Recall, we could also create a library `.a` file from our `.o` files,
      if we wanted. This would be an extra step after compiling, before linking
3. Linking (combining multiple .o files into a single executable)

In this compilation process, we can throw away the source code after 2, and as
long as we have the .o or .a files we can link successfully. Also, the compiler
does not need to see the body of a function when compiling code that calls it
— it only needs the header, which tells the argument and return types of the
functions.

The same is not true of C++ templates. When we use a template, the compiler must
have access to the original source code to "fill in" the types — it is
generating entirely new classes and functions. So, we cannot put templates into
.cpp files and turn them into .o files to be used later. There is no such thing
as `vector.o`. Instead, we put the templates in header files, and include them
wherever they are used.

What if multiple .cpp files are using the same instantiation of a template? For
example, let's say we have `foo.cpp` and `bar.cpp`, which both use
`vector<int>`. After compiling `foo.o` and `bar.o`, we'll have one copy of
`vector<int>` in each file. The duplicates are removed when we link `foo.o` and
`bar.o` together into an executable. This is known as the **Borland model**.
It's inefficient because the compiler duplicates work, but is simpler to
implement.

One consequence is that the C model of separating interfaces (.h files) and
implementations (.c files) no longer holds in C++. According to Jae, this is one
of the things in C++ that is fundamentally incompatible with C, and no matter
what you do you'll end up with a kludge.

Further reading:
- GCC manual section 7.5, ["Where's the Template?"](https://gcc.gnu.org/onlinedocs/gcc/Template-Instantiation.html)
- The end of Lippman 5th ed 16.1.1, "Template Compilation"


### Note: Why go through this trouble? Templates are fast! ###

Although templates take a long time to compile, they're incredibly fast when
running. Unlike other languages' implementations of generics, there is literally
no overhead during execution for a templated class, because they're just turned
into the code that you would have written by hand. This is an example of a
**zero-overhead abstraction:** templating makes programming easier, but don't
make our programs slower when they run.

There's a really cool Bayesian statistics project at Columbia run by Andrew
Gelman's group called [Stan](http://mc-stan.org/). Stan runs complicated
statistical models very quickly: under a second for moderate sizes, where
competitors would take several minutes. One reason for the speed is extensive
use of C++ templates.

However, this comes at the cost of taking 30--60 seconds to compile models (even
just a tiny tweak). Remember when we said that a new class gets generated every
time you use a template with a new type? With templates, it's very easy to make
the compiler generate a lot of classes with a small amount of code.

But it's worth it: the code is tricker to write and takes longer to compile, but
the end result is execution times that are as fast as hand written code, with
significantly more flexibility for the end user. This lets them have end users
write whatever models they want at no performance cost.


### What's with that weird double template stuff for ostream? ###

Check out this discussion about [overloading `operator<<` in a templated
class](http://www.cplusplus.com/forum/general/45776/). Here's what's going on:

Sometimes you need to define _function_ templates in association with a _class_
template. This is a friend function that depends on the specific type of the
class. If we look at Jae's stack example from lecture note 22, he declares 

```cpp
template <typename T>
ostream& operator<<(ostream& os, const Stack<T>& rhs)
```

There's one function for each type used, ie there's a
operator<<_for_stack_of_int, and operator<<_for_stack_of_strings. Those are
different functions, and each needs to be created as separate function
templates. However they're friends, they aren't member functions, hence they
need to be declared as separate templates with respect to the class.


## Containers ##

The C standard library, STL, provides
[containers](http://www.cplusplus.com/reference/stl/). Containers are a standard
set of library classes for containing a bunch of objects of some type. They're
implemented with templates, and are pretty much the canonical example of
templates in the language.

### Value Semantics ###

One key feature of containers is that they provide **value semantics**. That is,
containers at least appear to make copies of the things you store into them, and
manage the lifetime of those copies. They guarantee that even if you destruct
the original, the copy it stored is safe. And once you destruct the vector, the
copies it made are destructed as well.

Understanding value semantics is key for lab 10, and helps explain why they're
so handy. Something about STL containers could easily be a final question. 

Note that Jae's lecture note 22 does a good job of explaining containers and
iterators.

### What can you do with containers? ###

Iterators, of course, but also: things like sorting, inserting, swapping,
splicing, merging, etc, etc. You can pass them into functions that will sort, or
print, or whatever you could want.


#### Vector ####

Vector is the prototypical container in this class. It's a sequential container,
supporting O(1) random access to elements, and O(1) amortized appends
(`push_back()`). Under the hood it's an array with some blank spaces on the
right;  whenever it runs out of blanks it creates a new (larger) array, and
copies the data from the old to new. It manages that underlying array
internally.


#### List ####

List is a linked list, like we did in lab 3 but fancier. In particular the list
class is doubly linked, so every node points not just to next, but also to
previous (i.e., the node that points to it). It also maintains a tail pointer in
addition to head, so it can append in O(1) constant time.

This means that list does NOT define `operator[]` or anything similar - it has
no random access, and it must do some pretty fancy stuff in its iterator.

#### Deque ####

Also known as deque, and pronounced "deck", it's a doubly ended queue: like a
vector with space on both the left and the right. (Deque is actually implemented
differently, but it's a good mental model.)

#### Derived Containers ####

Based on vector, list, and deque, there are several derived containers that use
one of those as the underlying container. They include queue (uses either list
or deque), priority queue (using vector or deque), and stack (using any).

#### Set ####

Sets provide very efficient lookup to see if an element is in the set, along
with mathematical set operations like union, intersection, etc. They keep the
elements sorted using the operator< function. (Unimportant detail: internally
they use some type of self balancing binary search tree.)

There's also an unordered set (unimportant detail: that uses a hash table). 

#### Pair and Map ####

We discuss pair and map because it's useful to understand the flexibility and
total genericness of the STL containers. Absolute understanding of how they work
isn't important for 3157.

A pair is a class that lets you group two objects together, potentially of
different types. A simple implementation is just:

```cpp
    template <class T1, class T2>
    struct pair {
        T1 first;
        T2 second;
    };

    pair<string,int>  prez("obama", 1961);
    pair<string,int>  veep("biden", 1942);
```

Pairs are useful because they're often a natural extension of generic containers.
We want to store an int plus some value instead of just an int. Pairs
provide a convenient way to do that. 

One use is in map, which maps keys to values. It will return pairs when it wants
to return (key, value) tuples.


```cpp
  map<string,int>  word_count;
  string word;
  while (cin >> word)
      word_count[word]++;

  map<string,int>::iterator it;
  for (it = word_count.begin(); it != word_count.end(); ++it) {
      cout << it->first << " occurs ";          //recall that it->first is (*it).first
      cout << it->second << " times." << endl;
  }
```


## Iterators ##

Iterators are the key feature that makes containers so useful as a group. Every
container specifies an iterator type, providing a consistent way to access every
element stored in the container. Compare the same iterator code, one written for
a vector, and the other for a dequeue: 

```cpp
for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
    *it = "";

for (dequeue<string>::iterator it = v.begin(); it != v.end(); ++it)
    *it = "";
```

`iterator` is a type member, which is a typedef defined *inside* a class.

`iterator`s act like pointers: they must provide the basics that pointers
provide (some do provide other features). In particular you must be able to get
the beginning, `v.begin()` and *one past the end* with `v.end()`. Both of these
functions return `iterator`s. However it's only valid to dereference the
returned value of `begin()`, because `end()` points past the end of the
container.

The iterator has to define three functions to be useful: `*`, `++` and `!=`.
With only those three we can do our entire iteration with any container, even
ones like trees that aren't strictly sequential.

- `operator*` returns a reference to the object to which the iterator is
currently pointing. In a `vector` the iterator is actually a pointer, so it
works without any code. In another class, say a linked list, the code has to do
more work to figure out what the object being stored is, and return that.

- `operator++` advances the iterator to the next element. Again, how it actually
happens depends entirely on what the container holds.

- `operator!=` is important, because for some container types the idea of
`operator<` doesn't really make sense. Hashmaps, for example, are entirely
unordered, so we can only really test whether two iterators are not equal, not
whether one is less than the other.

There is also a `const_iterator`, which gives you const references, and behaves
exactly the same way conceptually.


## Clang ##

Clang is a newer alternative to gcc. It was designed primarily by Apple to be a
drop in replacement to gcc, but with a license apple prefers, and to support
better debugging and static analysis. Apple uses it for XCode, and it's
available on CLAC as well. So if you're getting crazy error messages you don't
understand, you can try changing `g++` to `clang++` in your Makefile, and seeing
if you get more easily interpreted error messages.
