## Structs (K&R 6) ##

Structs are kind of like Java's objects but for C. Fundamentally, they allow you
to declare a collection of one or more variables grouped under a single type. A
struct cannot, however, contain functions/methods. A struct can only contain
other datatypes such as pointers, `int`, `char`, `float` or even other structs. An
example struct:

```c
struct point {
  int x;
  int y;
};
```

and usage

```c
struct point pt = {50, 100};
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
};
// Usage:
struct point leftTop = {50, 40};
struct point rightBottom = {100, 0};
struct rect myRect = {leftTop, rightBottom};
myRect.p1.x += 5; //now 55
```

Structs, like everything in C, are passed by value. This means if you pass a
structure as a parameter to a function, the function will receive a copy of the
struct, with all its values copied by value. This means if your struct contains
a pointer, the value of the pointer will be copied (and it will point to the
same location in memory). If you want to pass a pointer to a struct, you can
dereference it with the `&` operator as you can with all data types. Pointers to
structure are frequently used, so there is a shorthand for accessing their
members:

```c
struct point pt = {50, 50};
struct point *ppt = &pt;
ppt->x = 25;
ppt->x == (*ppt).x; // 1
```

The shorthand just saves you the hassle of writing out line 4 of the code above.
Also, if you don't want to write out the keyword `struct` every time, you can
just declare your struct as follows:

```c
typedef struct {
  int x;
  int y;
} Point;

Point pt = {50, 50};
```

Make sure to read the K&R on this to learn some interesting use cases for
structures. Note that a struct can contain a pointer to its own type (but not
directly a member of its own type). This is particular useful for data
structures like trees.

```c
typedef struct Node_t {
  void *value;
  struct Node_t *parent;
} Node;

Node root, child1, child2, child3, child4;
child4.parent = &child2;
child3.parent = &child2;
child2.parent = &root;
child1.parent = &root;
```

Bad:

```c
/* this won't work */
typedef struct {
  void *value;
  Node *parent;
} Node;

/* neither will this */
struct {
    void *value;
    Node parent;
} Node;
```
### Union (optional) ###

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
Jae has some functions listed in the notes from the Standard C Library for
string operations. I'm not going to explain them all here, but I will point out
some nasty little things to be aware of.

  - `strlen` runs in O(n) because you can't know the length of a string without
    traversing it to find the null character.
  - `strcpy` and `strncpy` require that there is enough space in your
    destination memory location for the source string. Also watch out when using
    `strncpy` that all your strings are null terminated.
  - `strcat` runs in O(n) too. So if you're running lots of strcats, watch out
    because you could end up with tons of passes over a single string.
    Exponential even.
  - `memcpy` is great for cleaning things up. Just sayin'.

### Const ###

`const` is a keyword for types in C that prevents them from being modified. It's
important to understand that this means once the variable is declared, the
memory it is referring to cannot be modified. Some examples:

```c
int x = 1;
int y = 2;

const int *const_val = &x;
*const_val = 3; //invalid: value in memory is constant
const_val = &y; //valid: value of pointer, ie. memory location, is not constant

int *const const_ptr = &x;
const_ptr = &y; //invalid: value of pointer, is constant
*const_ptr = 4; //valid: value in memory is not constant

const char *const why = "You'll never change anything about me. Ever";
```

### Struct padding ###
For performance and for compatibility between different types of machines, C
compilers will sometimes add padding to structs. For example:

```c
struct test {
    char c;
    int n;
};
```

The int takes up 4 bytes and the char takes up one byte. However,
`sizeof(struct test)` on CLAC is `8`. Although it's useful to know that
padding can happen, it isn't covered in this class, and for all intents and
purposes you can assume that structs have no padding if you're ever asked
about them.
