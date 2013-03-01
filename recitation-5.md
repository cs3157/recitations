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
to declare a collection of one or more variables grouped under a single type.

### Union ###

## Odds and Ends ##
### String Operations in C Library ###

### Const ###

