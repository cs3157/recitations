# Recitation 10 #

## C++ templates and containers ##

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
compile time type checks.

Note: For some people templates break, or at least abuse, the standard mental
model of compiling and linking above. They do things that "feel" like linking,
but it's actually happening during compiling.



