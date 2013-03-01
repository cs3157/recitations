# Recitation 5 #
Though late, I want to make sure you all have a secondary resource for this
topic. The main topics for these notes will be those covered in lecture 7 and
useful for lab 3.

## Function Pointers (K&R 5.11) ##
It is often the case in programming that you'll want your program to change its
behavior for the person using your program but have no idea how they may want to
do this. For example, when writing a sort function, you could just specify a
parameter that let's them choose between sorting ascending and descending.
However, what if they wanted to sort characters by their unicode value instead of
lexicographically? For this, the user has to supply their own functionality.
That's where you need function pointers. Some higher level (read
lambda-programming languages) support this is in a more intuitive way, but C
does a pretty good job itself.

### Accepting functions as a parameter to your function ###

Function pointers allow you to accept as a parameter to your function, another
function. Let's start out with accepting functions as a parameter:

```c
void notifier(int (*fn)()) {
  printf("Starting\n");
  fn();
  printf("Finished\n");
}
```

Let's examine this more closely. We have a function called notifier whose only
parameter is another function. How do we do this? we specify what kind of
function it accepts. The basic layout for a function pointer type is `returntype
(*functionName)(parameter1type, parameter2type, ...)`. Why? Well the returntype
denotes the type of the function. The name of the function being preceded with
an asterisk tells us its a pointer. The function is surrounded by parentheses so
that the compiler doesn't think we've got a variable `returntype *functionName`.
The parenthese following the declaration are necessary as well, even if the
function we want to accept doesn't have any arguments. The parameter's only need
their types declared so that the compiler can check these. Since you won't have
access to the code you don't need to worry about what to call them.

### Passing a function as a parameter ###

```c
int wasteTime() {
  int i = 0;
  while(i < 1000000)
    i++;
  return i;
}

int main(int argc, char **argv) {
  wasteTime();
  notifier(wasteTime);
  return 0;
}
```

Notice how we have a function `wasteTime`. And when we follow it with
perentheses it gets called. When we don't, it is automatically a function
pointer. Why is this?

Well everything in the program is stored in memory, even the functions, which
means even they have an address. So `wasteTime` has an address in memory. When
you follow `wasteTime` with perentheses (`wasteTime()`), C goes to the address
and executes the function. If you think of `wasteTime` as storing a pointer to a
function, then you can think of `wasteTime()` as dereferencing the pointer.
Therefore, when we call `notifier` and pass it `wasteTime` without parentheses, it
passes the address to `wasteTime` to the `notifier` function.

### Calling functions from pointers ###
We could further use the functions above as follows:

```c
int main(int argc, char **argv) {
  int (*f1)();
  char *(*f2)(char *, const char *);
  char arr[5] = "bann"

  f1 = wasteTime;
  f2 = strcpy;

  notifier(f1);
  f2(arr, "hihi");
}
```

As you can see from the above code, you can declare variables of "function
pointer" type and assign function pointers to their values. Then you can call
those functions simply by adding parentheses to the end of the variable name.
Make sure to check out Jae's notes (lecture 7) for more complicated examples of
this. Notice that we did the same thing when calling `fn()` in our `notifier`
function.

## Structs (K&R 6) ##

Structs are kind of like Java's objects but for C. Fundamentally, they allow you
to declare a collection of one or more variables grouped under a single type. A
struct cannot, however, contain functions/methods. A struct can only contain
other datatypes such as `int` `char` `float` or even other structs. An example
struct:

```c
struct point {
  int x;
  int y;
}
```

and usage

```c
struct point pt;
pt = {50, 100};
pt.x == 50; // 1
pt.y = 3;
pt.y == 100; // 0
```

Notice that values within a struct can be accessed and modified using the `.`
operator in the form `structure-name.member`. We can declare another structure
that uses the one we already have.

```c
struct rect {
  struct point p1;
  struct point p2;
}
// Usage:
struct point leftTop = {50, 50};
struct point rightBottom = {100, 0};
struct rect myRect = {leftTop, rightBottom};
```

Structs, like everything in C, are passed by value. This means if you pass a
structure as a parameter to a function, the function will receive a copy of the
struct, with all its values copied by value. This means if your struct contains
a pointer, the value of the pointer will be copied (and it will point to the
same location in memory). If you want to pass a pointer to a struct, you can
dereference it with the `&` operator. Pointers to structure are frequently used,
so there is a shorthand for accessing their members:

```c
struct point pt = {50, 50};
struct point *ppt = &pt;
ppt->x = 25;
ppt->x == (*ppt).x; // 1
```

The shorthand just saves you the hassle of writing out line 4 of the code above.
Also, if you don't want to write out the keyword `struct` everytime, you can
just declare your struct as follows:

```c
typedef struct {
  int x;
  int y;
} Point;

Point pt = {50, 50};
```

Make sure to read the K&R on this to learn some interesting use cases for
structures. Note that a struct can contain a member of its own type. This is
particular useful for data structures like trees.

```c
typedef struct {
  void *value;
  Node *parent;
} Node;

Node root, child1, child2, child3, child4;
child4.parent = child2;
child3.parent = child2;
child2.parent = root;
child1.parent = root;
```

### Union ###

A union is really nifty. It's like a structure, but, wait for it, all of its
members are stored at the same location in memory. This means when you allocate
a union, enough space is allocated for the largest member's type. This means if
you were to declare a type as follows, you could use it to store any one of the
three types.

```c
union u_tag {
  int integer_value;
  float float_value;
  char *string_value;
}

union u_tag u;
u.integer_value = 5;
int x = u.integer_value;
u.float_value = 3.14f;
float f = u.float_value;
```

Union's are nifty for situations where you don't know just yet what kind of data
you need to store but want to be smart about the space you allocate. Just be
careful that you don't store something as one type and then read it out as
another. While possible, the behavior is compiler dependent.

## Odds and Ends ##
### String Operations in C Library ###

### Const ###

