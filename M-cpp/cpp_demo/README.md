# Matrix Demo

This demo shows how a user can define a matrix class in C++.
Similar to Jae's `MyString`, `Matrix` class defined in `matrix.hpp` encapsulates all the memory management as seen in the constructor and destructor.
We added a few more functionalities such as overloading `operator+` to show how we can also implement addition of two matrices.
Note that the user of this class `Matrix` does not need to know **how** memory management or addition are done,
but only that such functionalities exist.
This is one of the hallmarks of object-oriented programming (OOP).

# Run
There are several tests defined in `cpp_demo.cpp` with the following names:
```
CTOR: tests constructor and initialization of a Matrix object
CCTOR: tests copy constructor
CASS: tests copy assignment
ADD: tests addition of two matrices
```

Simply choose any subset of the tests and run the following command:
```
make all ADDED_CXXFLAGS="-D<T1> -D<T2> ..."
```
As an example, to run test `CTOR` and `ADD`, run:
```
make all ADDED_CXXFLAGS="-DCTOR -DADD"
```
