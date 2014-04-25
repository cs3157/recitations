# Recitation 10 #

## C++ templates and containers ##

At this point hopefully you've gotten used to writing basic classes in C++ from
our experience with MyString. At this point we can move in one of two
directions. First, we could take a more typical Object Oriented track and
discuss inheritance, polymorphism, and those sorts of things that companies love
to ask about during tech interviews. However if you've used Java at length
you're probably already somewhat comfortable with this, and (opinion waring)
it's somehow not super interesting, but incredibly complex and confusing.

Instead, in 3157, we're going to discuss templates and generics. The interaction
between generics and C++ is very interesting, and they work differently than in
most other languages. Consequently they're incredibly powerful, and often very
useful for programming fast and flexible libraries.

#### Recall how we created executables in C (and C++ so far) ####

If you go back to the beginning of the course, we discussed compilation as the
following steps:

1. Preprocessing (`#include`, `#define`, other `#` commands)
2. Compiling (turning raw .c files into .o object files)
3. Linking (combining 1+ .o files into a single executable)
    * We could also create a library `.a` file from our `.o` files, if we wanted

