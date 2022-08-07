# C Basics

C is a general-purpose programming language developed by Dennis Ritchie
at Bell Labs in the early 1970s.
It introduced a lot of the syntactic and programming conventions we see
in the numerous programming languages it influenced,
including Java, Javascript, Go, C#, Objective-C, and of course C++.

C code maps very efficiently to lower-level machine code,
giving programmers very precise control of the execution of their program.
Because of this, it's often used in systems programming
for low-latency, low-overhead, close-to-hardware applications.

Now, without further ado, let's take a look at C!


## Types

Before going into detail about the different types available in C,
it's important to convey what we mean by the term, "**type**"
(though without getting too technical with a mathematical definition).

For our purposes, and colloquially speaking, a type in C is just
how we choose to understand the data we find in memory.
It defines _how much data_ we should be expecting to read,
and _how to understand_ the data we find. 

Now, with that in mind, let's look at some types!

### Integer Types

Integers in C all use the binary number system we discussed previously;
two's complement for signed integers, and regular binary for unsigned.
So the only difference between integer types (of the same signedness)
is their size, which is also related to the range of values they can represent.

C only defines the size of each type in relation to the others:

```c
char <= short <= int <= long <= long long
```

Technically there's nothing stopping them from all of them being the same size,
but it's all dependent on what kind of machine and compiler you're using.
CLAC machines use the following:

Type        | Size
----------- | -------
`char`      | 1 byte
`short`     | 2 bytes
`int`       | 4 bytes
`long`      | 8 bytes
`long long` | 8 bytes

On most modern machines, the sizes for `char`, `short`, and `int`
are fairly consistent, and the same as what we have on CLAC.
However, the sizes for `long` and `long long` vary a lot from system to system.

You can always test it out for yourself:

```c
#include <stdio.h>
 
int main(void) {
    printf("char: %lu\n
            short: %lu\n
            int: %lu\n
            long: %lu\n
            longlong: %lu\n",
        sizeof(char), sizeof(short), sizeof(int),
        sizeof(long), sizeof(long long));
    return 0;
}
```

There are some more technical details different ways of declaring integers,
which you can find in the Appendix.


### Floating-Point Types

There are three types for floating-point numbers in C,
for single-precision, double-precision, and extended-precision floating point.
How they're bitwise represented differs from machine to machine,
but most modern computers use the IEEE-754 floating-point standard
(if you're curious to see what that looks like in binary, see the Appendix).

Like with integers, the sizes are defined relative to each other.
They are:

```c
float <= double <= long double
```

The sizes on CLAC are as follows:

Type            | Size
--------------- | ---------
`float`         | 4 bytes
`double`        | 8 bytes
`long double`   | 16 byetes

Again, you can test it out for yourself:

```c
#include <stdio.h>

int main(void) {
    printf("float: %lu\n
            double: %lu\n
            long double: %lu\n",
        sizeof(float), sizeof(double), sizeof(long double));
    return 0;
}
```

## Declarations, Casting, Literals

### Variable Declarations

Just like in Java, we declare variables using the following syntactic structure
(note that the `[]`s indicate that the type modifiers are optional,
and the `..` indicate that there can be multiple modifiers):

    [<modifiers..>] <type> [<modifiers..>] <variable name>;

This _declares_ a variable, but _does not initialize_ it.
That is to say, we've told the compiler how much space we want
and how to read what we'll eventually put there,
but we've not actually put anything there yet!
There's no guarantee what garbage might be written in the piece of memory
we're given, so trying to access it will result in **undefined behavior**
(no guarantees for what will happen during compilation or execution;
you'll here us talk about this _a lot_, specifically about avoiding it).

```c
int x;              // x is declared, but uninitialized
printf("%d", x);    // undefined behavior; don't do this!
x = 4;              // x is now initialized to 4
```

We can also declare multiple variables of the same type all at once,
separating the variable names with a `,`:

```c
int y, z;           // y and z are declared, but both uninitialized
```

Just like in Java, we can declare and initialize our variables all at once:

```c
int x = 2;          // x is declared and initialized to 2
int y = 0, z;       // y and z are declared, only y is initialized (to 0)
```

### Type Casting

Also like in Java, we can cast variables from one type to another.
We do so with the following syntax:

    (<type>) <variable>

This comes in handy for changing the type of a variable
to suit the interface of a function we might want to call,
or to trick the compiler (as you saw before).

For example, let's say that we have a function `foo()`
that takes a single `float` as its parameter:

```c
int x = 34;
foo((float) x);
```
When we cast from an integer type to a floating-point type,
the compiler produces instructions to convert our integer representation
to floating-point representation.

Keep in mind that when we convert between integer types, 
we extend/truncate our integer in order to fit it into the size of the type
we are casting it to. Note this can lead to some strange-looking results!
For example, if we're casting from a positive `long` to an `int`,
and the `long` happened to have a 1 value at the bit position
corresponding to the MSB of an `int`, the result may be a negative number:

```c
#include <stdio.h>

int main(void) {
    char c = 4;
    int i = 4;
    long l = 3000000000;

    printf("char to int: %d\n", (int) c);       // prints 4
    printf("int to float: %f\n", (float) i);    // prints 4.000000

    printf("long (no cast): %ld\n", ll);        // prints 3000000000
    printf("long to int: %d\n", (int) ll);      // prints -1294967296

    return 0;
}
```

As you can see, downcasting the 8-byte `long` truncated our integer,
which means something very different as a signed, 4-byte integer.

When we convert between floating-point types of different levels of precision,
again the compiler helps us do the conversion, though we may lose precision
if we're casting from a more precise floating-point type to a less precise one.

We can actually use casting to "cast away" some of the things the compiler
tries to enforce for us, like pointer types and `const`ness.
Check out the Appendix for more details.


### Literals

Literals are values hard-coded into our program.
Most literals look fairly self-explanatory (especially numeric literals),
but there are some C-specific notations that we should be aware about.

#### Octal and Hexadecimal Literals

Octal (base 8) literals start with a leading `0`.
The following digits can only consist of `0` through `7`.

Hexadecimal (base 16) literals start with a leading `0x` or `0X`
The following digits can only consist of `0` through `9` and `a` through `f`
(capitalization doesn't matter).

Let's look at different ways of writing the number 42:

    42      // decimal
    052     // octal
    0X2A    // hexadecimal
    0x2a    // also hexadecimal

#### `unsigned` Literals

To specify that a number is unsigned, it should be followed by a `u` or a `U`.
For example:

    8u
    0xffffffffu

#### `long` and `long long` Literals

A number by itself is understood by the compiler to be an `int` by default.
To specify that it is a `long` or `long long`,
use `l`/`L` and `ll`/`LL` respectively by appending it to the end of the number.
For example:

    4l
    4LL
    0x4l

#### Floating-point literals

Floating numbers can be written several different ways:

- Just as a number: `42` (inferred)
- A number with a decimal: `42.`, `4.2`, `.42`
- Exponent form: `4e2`

These are all `double`s by default; one can specify `float` or `long double`
using suffixes `f`/`F` or `l/L` respectively.

#### Character literals

You might've noticed that, unlike in Python or Javascript,
in C, single quotation marks `'` aren't the same as double quoatation marks `"`.
This is becauase single quotation marks are used for single character literals,
while double quotation marks are used for string literals (see below).

C uses ASCII encoding for characters, which assigns each character an integer.
Recall that a `char` is usually 1 byte; this is because each ASCII character
can be representedy a single byte (it only specifies 128 characters).
Have a look at [The ASCII Table](asciitable.com) to see what's what.

Instead of assigning raw numbers to `char`s,
we can alternatively write them as character literals:

```c
char a = 'a';           // same as writing char a = 97
char newline = '\n';    // same as writing char newling = 10
assert(a == 97);
assert(newline == 10;
```

The backslash `\` is used to specify an **escape sequence**,
to denote characters that might be difficult to otherwise type out.
Here are some common escape sequences:

Escape Sequence | Character Description
--------------- | ---------------------
`\n`            | newline
`\r`            | carriage return
`\\`            | backslash
`\'`            | single quote
`\"`            | double quote

A `\` may also be followed by a numeric value in octal notation;
`\x` may be followed by a numeric value in hexadecimal notation.
So, consider the following:

```c
char a = 0;
char b = '0';       // 48 in binary
char c = '\0';
char d = '\x0';

assert(a != b);
assert(a == c);
assert(a == d);
```

`char` literals can be added and subtracted just like any other number,
so if you wanted to find what position in the alphabet the letter `j` is,
you could do something like the following:

    'j' - 'a'


#### String Literals

We write string literals as a sequence of valid `char` literals
(including escaped characters), surrounded by double quotation marks `"`:

    "I am a not really a 'string', just an array of characters.\n"

String literals actually represent a null-terminated array of characters,
which the compiler pre-allocates for us in static memory.


## Expressions and Statements

In C, we differentiate between **expressions** and **statements**.
Simply put, statements don't necessarily have a value, whereas expressions do.
All expressions can be statements, but not all statements can be expressions.

This will become clearer as we look at some examples.

### Expressions

A C expression is any syntactic construct that yields a value.
It can be as simple as a variable or a literal,
or it can be combinations of other expressions via operators.
Function calls are also expressions that yield value of what they return.

We're not going to go through all the operators one by one,
but we'll note some important details and gotchas.

For variables `x` and `y`, and some function `foo()`,
the following are examples of expressions:

    3157
    x
    x + y
    x = y + 3157
    x += y
    x++
    foo(x, y + 3157)
    
Note that an assignment `=` operation is also an expression!
It assigns the value of its right operand to its left operand,
and yields the value of the left operand.
This might seem weird at first, but it allows us to do things like:

```c
x = y = 3157
x = (y = 3157)
```

The second line unpacks it a little bit:
it's saying, assign `3157` to `y`, and then assign the value of that to `x`.

#### Uncommon Operators

Well, these aren't really uncommon, but it's possible you haven't seen these yet
depending on what language experience you've had before.

##### Self-assignment `+=` `-=` `*=` `/=` `%=` `<<=` `>>=` `&=` `|=`

Apply the operation before the `=` to the left and right operand,
then assign to the left operand.
So, `x += y` is the same as `x = x + y`

##### Increment/decrement `++` `--`

Used to add 1 or subtract 1 from its operand.
There are two flavors of these operators:
the prefix version `++x` `--x` (appears on the left of the operand)
increments/decrements first, and yields the value after the operation
(`x++` is equivalent to `x += 1`);
the postfix version `x++` `x--` (appears on the right of the operand)
increments/decrements as well, but yields the value _before_ the operation.

```c
int b1 = 5, a1 = 5;
int b2 = ++b1;           // b2 is assigned the value of 6
int a2 = a1++;           // a2 is assigned the value of 5
```

##### Ternary conditional operator `? :`

This is the syntax for the ternary operator:

    <expression-1> ? <expression-2> : <expression-3>

The value of a conditional expression is dependent on that of
the expression before the `?` operator.
If `<expression-1>` is non-zero, then the conditional value yields the value
of `<expression-2>`; otherwise it yields the value of `<expression-3>`.
Here's an example:

```c
int t = 1, f = 0;
int a = t ? 42 : 24;        // a is assigned the value of 42
double b = f ? 4.2 : 1e20;   // b is assigned the value of 1e20
```

It's sort of the same idea as an if/then/else, but keep in mind that
those are separate, syntactic constructs in C (which we will cover below).


#### "Boolean" operators

You've probably noticed that there is no boolean type in C.
That's we simply represent false with 0, and true with anything non-zero!
This allows for some convenient shorthand: `if (x != 0)` is the same as `if(x)`.

The comparison operators, `<` `>` `<=` `>=` `==` `=!`.

Operations that typically return boolean values in other languages
instead return 1 for true and 0 for false in C.
This includes the comparison operators, `<` `>` `<=` `>=` `==` `=!`,
and the logical operators `&&` `||` `!`.
We can confirm this with the following code:

```c
printf("'true': %d\n", 0 < 3);  // prints 1
```

##### Short circuit evaluation `&&` `||`

Usually, an expression that contains subexpressions
(as operands to an operator, or as arguments to a function call)
will first evaluate those subexpressions
before evaluating the greater overall expression.
So let us consider the following two functions:

```c
int foo(void) {
    printf("foo!\n");
    return 1;
}

int bar(void) {
    printf("bar!\n");
    return 0;
}
```

The following expression will evaluate both `foo()` and `bar()` function calls:

    foo() + bar()

We can tell by the fact that both `foo!` and `bar!` are printed.

However, `&&` and `||` use **short circuit evaluation**;
this means that their operands are evaluated only as necessary.
For example, for the expression `L && R`, if we know `L` is 0 (false),
we know the value of the logical AND expression is going to be 0
regardless of what happens with `R`.
The operators skip the operands which they know are no longer necessary.
To demonstrate:

```c
foo() && bar();     // prints foo! bar!
foo() || bar();     // only prints foo!
bar() && foo();     // only prints bar!
bar() || foo();     // prints bar! foo!
```

This means that for some short-circuited statement like `foo() || bar()`,
as long as `foo()` returns a nonzero value, `bar()` will never even be called.


#### Operator Precedence

Like in any other programming or symbolic language,
C defines an order of operations for each of its operators.
This way, both the programmer and compiler can agree on
what order to evalaute expressions.

You should be familiar with a lot of the most common rules
(like multiplication/division before addition/subtraction),
but there is one note-worthy gotcha that is quite commonly used in C:

    *p++

This doesn't increment the variable you get from dereferencing `p`;
instead, this expression takes on the _value_ of `*p`,
and then increments `p` afterwards. It's not the same as `(*p)++`;
it's more along the lines of something like, `*p, p++`,
where the two operations are done upon `p` separately.

Aside from that, C operators are pretty straightforward to read and write.
[CPP Reference](http://en.cppreference.com/w/c/language/operator_precedence)
has a pretty clear listing of each operator, their precedence,
and their associativity.


#### L-values and R-values



## Statements

### If-Else Statements

```c
if(condition)
  if(condition2) {
    printf("conditions met");
    return 0;
  }
  else
    printf("no conditions met");
```

### Switch Statements

```c
switch(v) {
  case 1: // v == 1
    printf("v is 1");
    break;
  case 2:
    printf("v is 2");
    break;
  default:
    printf("v is neither 1 nor 2");
}
```

### Loops

```c
int i;
for(i = 0; i < 10; i++) {
    // do things here
}
while(i) { //condition checked at the beginning
    //other things
    i--;
}

do {
    //more things
} while(i < 5); //condition is checked at the end
```

Using `break;` inside a loop will break out of the innermost loop. Using
`continue;` will stop executing the current iteration of the loop and skip to
the next iteration. `for(;;)` is an idiom for an infinite loop. `goto label`
will jump to a line beginning with `label: `. Be careful with gotos.


## Appendix: Optional Language Reference Material

### Integer Declarations

There are a few type modifiers we can use to specify exactly what kind
of integer we want our compiler to declare for us.

When we declare an integer type, we can modify it with the keyword
`signed` or `unsigned` to tell the compiler the signedness of the integer.
When unspecified, most integer types are signed by default.

C also allows the programmer to use `long` and `short` as modifiers for `int`,
which are the same as not having used the keyword `int` at all.
So don't be alarmed if you see a `long int` type! It's just a `long`.

Also, if we don't write `int` and only specify the signedness, it's an `int`.

The following types in each row are equivalent:

```
| `short`                 | `short int`               | `signed short`        | `signed short int`     |
| `long`                  | `long int`                | `signed long`         | `signed long int`      |
| `long long`             | `long long int`           | `signed long long`    | `signed long long int` |
| `int`                   | `signed`                  | `signed int`          |                        |
| `unsigned int`          | `unsigned`                |                       |                        |
| `unsigned short`        | `unsigned short int`      |                       |                        |
| `unsigned long`         | `unsigned long int`       |                       |                        |
| `unsigned long long`    | `unsigned long long int`  |                       |                        |
```

This is just a detail to watch out for, but not super important.
By convention, most of the time we use the notation in the leftmost column.

#### The `const` Type Qualifier

The `const` keyword tells that compiler that once a variable is initialized,
it shouldn't be assigned to again.
The type qualifier can come either before or after the type:

```c
const int x;
int const y;
```

Note that this is only compile-time enforced. We can trick the compiler in
the same way we did above in order to print floats in binary.
