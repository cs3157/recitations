#include <iostream>
#include "matrix.hpp"
#include "test_tools.hpp"

void test_ctor(const Matrix& M)
{
    utils::print_test("constructor");
    std::cout << "Printing M:" << std::endl;
    // print contents
    M.print();
}

void test_cctor(const Matrix& M)
{
    utils::print_test("copy constructor");
    // copy constructor
    Matrix tmp = M;
    std::cout << "Printing M:" << std::endl;
    M.print();
    std::cout << "Printing copy constructed matrix:" << std::endl;
    tmp.print();
}

void test_cass(const Matrix& M)
{
    utils::print_test("copy assignment");
    Matrix A(1, 2);
    A(0,0) = 10;
    A(0,1) = -3;
    std::cout << "Printing A:" << std::endl;
    A.print();
    std::cout << "Printing M:" << std::endl;
    M.print();
    std::cout << "Printing A after copy assigned from M:" << std::endl;
    // copy assignment
    A = M;
    A.print();
}

// Add M with a nontrivial matrix.
void test_add(const Matrix& M)
{
    utils::print_test("add");
    Matrix N(3, 2);
    // initialization
    for (int i = 0; i < N.nrows(); ++i) {
        for (int j = 0; j < N.ncols(); ++j) {
            N(i,j) = i + j;
        }
    }
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
    // constructor
    Matrix M(3, 2);
    // initialization
    M(0,0) = 1;
    M(0,1) = 3;
    M(1,0) = 5;
    M(1,1) = -2;
    M(2,0) = 9;
    M(2,1) = -5;

#ifdef CTOR
    test_ctor(M);
#endif
    
#ifdef CCTOR
    test_cctor(M);
#endif

#ifdef CASS
    test_cass(M);
#endif

#ifdef ADD
    test_add(M);
#endif

    return 0;
}
