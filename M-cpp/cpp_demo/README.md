# Matrix Demo

This demo shows how a user can define a matrix class in C++.
Similar to Jae's `MyString`, `Matrix` class defined in `matrix.hpp` encapsulates all the memory management as seen in the constructor and destructor.
We added a few more functionalities such as overloading `operator+` to show how we can also implement addition of two matrices.
Note that the user of this class `Matrix` does not need to know **how** memory management or addition are done,
but only that such functionalities exist.
This is one of the hallmarks of object-oriented programming (OOP).

### Matrix Addition
See the following [link](https://en.wikipedia.org/wiki/Matrix_(mathematics)#Addition,_scalar_multiplication,_and_transposition) for an explanation and an example of how to add two matrices.

## Run
Type `make` to build the executable and run `./cpp_demo`.
