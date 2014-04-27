# Recitation 10 #

# C++ templates and containers #

At this point hopefully you've gotten used to writing basic classes in C++ from
our experience with MyString. At this point we can move in one of two
directions. First, we could take a more typical Object Oriented track and
discuss inheritance, polymorphism, and those sorts of things that companies love
to ask about during tech interviews. However if you've used Java at length
you're probably already somewhat comfortable with this, and (opinion waring)
it's somehow not super interesting, but incredibly complex and confusing
(multiple inheritance = head asplode).

Instead, in 3157, we're going to discuss templates and generics. The interaction
between generics and C++ is very interesting, and they work differently than in
most other languages. Consequently they're incredibly powerful, and often very
useful for programming fast and flexible libraries.

#### Recall how we created executables in C (and C++ so far) ####

If you go back to the beginning of the course, we discussed compilation as the
following steps:

1. Preprocessing (`#include`, `#define`, other `#` commands)
2. Compiling (turning raw .c files into .o object files)
    * Recall, we could also create a library `.a` file from our `.o` files,
      if we wanted. This would be an extra step after compiling, before linking
3. Linking (combining 1+ .o files into a single executable)

In this step we can throw away the source code after 2, and as long as we have
the .o and .a files we can link successfully.

#### Drawbacks to void * ####

This approach is relatively feasible in C, because it's a small language with
relatively few types. The prominence of pointers and casting - you can't write
basically any C without using them - means that using `void *` as a way of
handling unknown types is relatively natural. This is what we did in our linked
list in lab 3.

However it has some problems: it doesn't provide any type safety, you have to
constantly cast your void pointers to whatever type they really are. This means
that the compiler is essentially helpless - it can't provide the static checking
that catches errors at compile time. Additionally, the list can't provide any
guarantees about the lifetime of the things it is pointing to. As you may have
seen, it's very easy to end up with invalid pointers.

### Templates ###

(One way) C++ "solves" the problems with `void *` pointers is templates.
Templates let you write code that accepts generic data types, but provides
compile time type checks. In 3157 we'll primarily focus on class templates (like
vector), not function templates.

Before we proceed into talking about templates, a word of warning. Templates
break, or at least abuse, the standard mental model of compiling and linking
that we've established so far. They do things that "feel" like linking, but it's
actually happening during compiling. So just be aware that you'll need a new
mental bucket for thinking about templates.

Templates are kind of like madlibs. They contain almost the whole story, but
leave certain things blank. Whatever you put in the blank will complete the
story. Using templates is generally quite easy, say we want a vector (discussed
more below), we just define a vector, and specify the type of object it holds.
Let's say we want to store a bunch of ints, a bunch of MdbRecs, that's easy:

```cpp

#include <vector>
//...

vector<int> ivec;
vector<MdbRec> mdbvec;
```

But there's no need to stop there, we can go further! What if we want a vector
of vectors of MyStrings?

```cpp
vector<vector<MyString> > msvecvec;
```

So, what's the type of `ivec`? `vector`? Nope! It's type `vector<int>`. The type
of the template'd thing includes the type of the things being used in the
template! This is because templates are handled in the compilation step, and
basically generate a new type. This isn't exactly what happens, but mentally you
can think of the compiler as seeing your `vector<int>`, and creating a normal,
non-template type `vector_int`; then it goes through and replaces every instance
of the `vector<int>` template type with the `vector_int` normal type. If
elsewhere you use `vector<MyString>`, it creates an entirely separate class
called `vector_mystring`.

It helps to think about how the implementation is written. 




#### Alternate Template Motivation ####
If you'd like another reason for templates, the canonical example is writing these
two functions:

```cpp
// returns 0 if the values are equal, -1 if v1 is smaller, 1 if v2 is smaller
int compare(const string &v1, const string &v2)
{
    if (v1 < v2)
        return -1;
    if (v2 < v1)
        return 1;
    return 0;
} 
int compare(const double &v1, const double &v2)
{
    if (v2 < v1)
        return 1;
    if (v1 < v2)
        return -1;
    return 0;
}
```

Then realizing that they're nearly identical, but still having two implementations, one for strings and one for doubles, doesn't help at all for ints. If only there was a way to do the same logic, and use the already existing operator overloading to just call whatever the appropriate `operator<` function! Templates do this!

The template'd version of this is:

```cpp
template <typename T>
int compare(const T &v1, const T &v2)
{
    if (v2 < v1)
        return 1;
    if (v1 < v2)
        return -1;
    return 0;
}
```


## Containers ##

The C standard library, STL, provides containers. Containers are a standard set
of library classes for containing a bunch of objects of some type. They're
implemented with templates, and are pretty much the canonical example of
templates in the language.

One key feature of containers is that they provide **value semantics**. That is,
containers at least appear to make copies of the things you store into them, and
manage the lifetime of those copies. They guarantee that even if you destruct
the original, the copy it stored is safe. And once you destruct the vector, the
copies it made are destructed as well.

Note that Jae's lecture note 22 does a good job of explaining containers and
iterators.


#### Vector ####

Vector is the prototypical container in this class. It's a sequential container,
supporting O(1) random access to elements, and O(1) amortized appends
(`push_back()`). Under the hood it's an array with some blank spaces on the
right,  whenever it runs out of blanks it creates a new (larger) array, and
copies the data from the old to new. It manages that underlying array internally.


#### List ####

List is a linked list, like we did in lab 3 but fancier. In particular the list
class is doubly linked, so every node points not just to next, but also to
previous (ie the node that points to it). It also maintains a tail pointer in
addition to head, so it can append in O(1), constant time.

This means that list does NOT define `operator[]` or similar - it has no random
access, and it must do some pretty fancy stuff in its iterator. 

#### Dequeue ####

#### Set ####

#### Pair and Map ####


## Iterators ##

Iterators are the key feature that makes containers so useful as a group. Every
container specifies an iterator type, providing a consistent way to access every
element stored in the container. Compare the same iterator code, one written for
a vector, and the other for a dequeue. 

```cpp
for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
    *it = "";

for (dequeue<string>::iterator it = v.begin(); it != v.end(); ++it)
    *it = "";
```

iterator is a type member, which is a typedef defined INSIDE a class.

iterators act like pointers, they must provide the basics that pointers provide (some do provide other features). In particular you must be able to get the beginning, `v.begin()` and ONE PAST THE END with `v.end()`. Then to use it we 

There is also a const_iterator, which gives you const references, and behaves
exactly the same way.



## Clang ##

Clang is a newer alternative to gcc. It was designed primarily by Apple to be a
drop in replacement to gcc, but with a license apple prefers, and to support
better debugging and static analysis. Apple uses it for XCode, and it's
available on clic as well. So if you're getting crazy error messages you don't
understand, you can try changing `g++` to `clang++` in your Makefile, and seeing
if you get more easily interpreted error messages.
