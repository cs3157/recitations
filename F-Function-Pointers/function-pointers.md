_The main topics for these notes will be those useful for lab 3, material from
lecture note 9, and useful information for the practice midterm._

## Function Pointers (K&R 5.11) ##
When writing a program, you'll often want your program to offer different 
possible behaviors, but it's difficult to anticipate what behaviors users might 
desire. For example, when writing a sort function, you could include a
parameter that allows users them choose between sorting ascending and descending.
However, what if a user wanted to sort characters by unicode value instead of
lexicographically? For this, the user has to supply their own functionality.
This is an example of where a function pointer is useful, as they allow you to
pass in different functions for different jobs. Some higher level (read:
lambda-programming languages) support this is in a more 'native' way, but C
does a pretty good job, too.

In short, *function pointers make it easier to swap out functions called 
from other functions*. Making parts of your code easy to swap out makes your
code more modular and extensible. These are characteristics of good code.

### Accepting functions as a parameter to your function ###
Function pointers allow you to accept functions as a parameter to your function. 
Here's an example of that functionality:

```c
void notifier(int (*fn)());

void notifier(int (*fn)()) {
  printf("Starting\n");
  fn();                   // calling function passed in as a parameter
  printf("Finished\n");
}
```

Let's examine this more closely. We have a function called `notifier` whose only
parameter is another function. When we include a function pointer in a method
declaration, we specify what type of function it accepts. 

The layout for a function pointer type is:
```
  returntype (*functionName)(parameter1type, parameter2type, ...)
``` 
**The type of our function pointer is denoted by its return type.**  
The name of the function being preceded with an asterisk tells us its a pointer. 
The function is surrounded by parentheses so that the compiler doesn't think 
we've got a variable `returntype *functionName`. The parentheses following the 
declaration are necessary as well, even if the function we want to accept 
doesn't have any arguments. 

Notice that the parameters do not have names. Only their types are declared so 
that the compiler can check these.

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

Notice the function called `wasteTime`.When we follow `wasteTime` with
parentheses, the function is called. When we don't include parentheses,
`wasteTime` is automatically a function pointer. Why is this?

Well everything in the program is stored in memory, even the functions, which
means even they have an address. So `wasteTime` has an address in memory. When
you follow `wasteTime` with parentheses (`wasteTime()`), C goes to the address
and executes the function. If you think of `wasteTime` as storing a pointer to a
function, then you can think of `wasteTime()` as dereferencing the pointer.
Therefore, when we call `notifier` and pass it `wasteTime` without parentheses, it
passes the address to `wasteTime` to the `notifier` function.

### Calling functions from pointers ###
While we can't declare a function from the body of a method, we can declare and
initialize function pointers. Let's expand on the code we've written so far:

```c
int main(int argc, char **argv) {
  int (*f1)();                        // declare function pointer
  char *(*f2)(char *, const char *);
  char arr[5] = "bann";               // initialize string

  f1 = wasteTime;                     // assign already defined function to function pointer
  f2 = strcpy;

  notifier(f1);                       // pass function as a parameter
  f2(arr, "hihi");                    // invoke function using a pointer to it, rather than its actual name, strcpy
  printf("%s\n", arr);
}
```

As you can see from the above code, you can declare variables of type "function
pointer" and assign functions to their values. Then you can call
those functions simply by adding parentheses to the end of the variable name.
Make sure to check out Jae's notes (lecture 7) for more complicated examples of
this. Notice that we did the same thing when calling `fn()` in our `notifier`
function.


### Functions vs Pointers to Functions ###
Functions aren't quite like regular variables, so function pointers aren't quite
like regular pointers either. Think about this small program:

```c
void myFunc(int x) {
  x++; 
}

int functionAcceptor(void (*f)(int), void (*g)(int)) {
  return f == g;
}

int main() {
  char *s = functionAcceptor(myFunc, &myFunc) ? "They're the same thing." :
    "They're totally different.";
  printf("%s", s);
}
```

What will this program print? Notice the line where we're comparing 
`myFunc` and `&myFunc`.

```
They're the same thing.
```

Why? Because **referencing a pointer to a function just gets you the same
pointer back**. It has no effect. How boring.

### Bonus: Functions with Variable Arguments ###

This will come up again later on in the semester, but know that C (like Java)
can have functions with a varible number of functions. If you think about it,
`printf()` is a good example: you could have `printf("%d\n" &x)` or 
`printf("%d and %d\n", &x, &y)`. Once you've enumerated all the required
arguments, you can specify that you would like to also accept variable arguments
with an ellipsis (`...`):

    int myFWithVarArgs(int a, int b, ...);

To reiterate, this will be brought up again later in the semester, but it's good to acclimate to this syntax. *Bonus:* the e;lipsis works in Java function declarations too!


### Some Notes About Lab 4 ###
If you plan on doing the pair option and would like to 
[procure a private GitHub repo](https://github.com/edu), please request one ASAP,
because it takes a few days to process. Additionally, if you're new to GitHub/BitBucket,
you may find the [Git Documentation](http://git-scm.com/book), the 
[GitHub Help page](https://help.github.com/), and the 
[BitBucket Documentation](https://confluence.atlassian.com/display/BITBUCKET/Bitbucket+Documentation+Home)
handy.

Whether you choose to do the pair option or the solo option, you may wish to 
review each of the I/O functions we've learned in lecture note 9. Be sure that 
you understand the differences between them and note that there are certain situations
when some are more appropriate than others, and vice versa (ex., `fgets()` vs. `fread()`).
