#include <iostream>
#include "matrix.hpp"

static const std::string BARS = "===================";

// Prints testname formatted as such:
// ===================testname test===================
void print_test(const std::string& testname)
{
    std::cout << BARS << testname << " test" << BARS << std::endl;
}

// Creates a matrix of size 3 x 2 and initializes entries.
// Returns the created matrix.
Matrix make_matrix()
{
    Matrix M(3, 2);
    M(0,0) = 1; M(0,1) = 3;
    M(1,0) = 5; M(1,1) = -2;
    M(2,0) = 9; M(2,1) = -5;
    return M;
}

// Tests constructor.
// Prints the contents of a constructed and initialized matrix.
void test_ctor()
{
    print_test("constructor");
    Matrix M(1, 2);
    M(0,0) = 6; M(0,1) = 9;
    std::cout << "Printing M:" << std::endl;
    M.print(); // prints the contents of M
}

// Tests copy constructor.
// Creates a copy constructed Matrix object from return value of make_matrix().
// Prints the contents of copy constructed object.
void test_cctor()
{
    print_test("copy constructor");
    Matrix M = make_matrix(); // copy constructed
    std::cout << "Printing copy constructed matrix:" << std::endl;
    M.print();
}

// Tests copy assignment.
// Creates Matrix M from return value of make_matrix(), Matrix A, and copy assigns M to A.
// Prints the contents of M and the contents of A before and after copy assignment.
void test_cass()
{
    print_test("copy assignment");
    Matrix M = make_matrix();
    Matrix A(1, 2);
    A(0,0) = 10; A(0,1) = -3;
    std::cout << "Printing A:" << std::endl;
    A.print();
    std::cout << "Printing M:" << std::endl;
    M.print();
    std::cout << "Printing A after copy assigned from M:" << std::endl;
    A = M; // copy assignment
    A.print();
}

// Tests adding Matrix M with a nontrivial matrix.
// We chose the nontrivial matrix to be
// [
//  0, 1
//  1, 2
//  2, 3
// ]
void test_add()
{
    print_test("add");
    Matrix M = make_matrix();
    Matrix N(3, 2);
    N(0,0) = 0; N(0,1) = 1;
    N(1,0) = 1, N(1,1) = 2;
    N(2,0) = 2; N(2,1) = 3;

    Matrix res = M + N;
    
    std::cout << "Printing M:" << std::endl;
    M.print();
    
    std::cout << "Printing N:" << std::endl;
    N.print();

    std::cout << "Printing M + N:" << std::endl;
    res.print();
}

int main()
{
    // run tests
    test_ctor();
    test_cctor();
    test_cass();
    test_add();

    return 0;
}
