#include "matrix.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>

// Constructor
Matrix::Matrix(int nrows, int ncols)
    : nrows_(nrows), ncols_(ncols), data_(nullptr)
{
    data_ = new int[nrows_ * ncols_]; 
}

// Destructor
Matrix::~Matrix()
{
    delete[] data_;
}

// Copy constructor
Matrix::Matrix(const Matrix& m)
{
    this->copy_helper(m);
}

// Copy assignment
Matrix& Matrix::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }

    delete[] this->data_;
    this->copy_helper(m);

    return *this;
}

// Helper function that deep copies another matrix into current matrix.
// This exact logic is used twice: copy constructor, copy assignment.
void Matrix::copy_helper(const Matrix& m) 
{
    this->nrows_ = m.nrows_;
    this->ncols_ = m.ncols_;
    this->data_ = new int[this->nrows_ * this->ncols_];
    std::copy(m.data_, m.data_ + m.nrows_ * m.ncols_, this->data_);
}

// operator() is overloaded to return the i,j element of the matrix
// If i >= number of rows or j >= number of columns, program crashes (in practice we want to raise error).
int& Matrix::operator()(int i, int j)
{
    assert(i < this->nrows_ && j < this->ncols_);
    return data_[i * ncols_ + j];
}

const int& Matrix::operator()(int i, int j) const
{
    return const_cast<Matrix&>(*this)(i, j);
}

// operator+ is overloaded to return a new matrix that is the mathematical
// addition of current matrix and another matrix.
// If the sizes do not match, program crashes (in practice we want to raise error).
Matrix Matrix::operator+(const Matrix& m) const
{
    assert(this->nrows_ == m.nrows_);
    assert(this->ncols_ == m.ncols_);
    Matrix res(this->nrows_, this->ncols_);
    for (int i = 0; i < this->nrows_; ++i) {
        for (int j = 0; j < this->ncols_; ++j) {
            res(i,j) = (*this)(i,j) + m(i,j);
        }
    }
    return res;
}

////////////////////////////////////////////////
// DO NOT WORRY ABOUT CODE FROM HERE
////////////////////////////////////////////////

// Prints the contents of the matrix
void Matrix::print() const
{
    std::cout << nrows_ << " x " << ncols_ << std::endl;
    std::cout << "[" << std::endl;
    for (int i = 0; i < nrows_; ++i) {
        for (int j = 0; j < ncols_; ++j) {
            std::cout << std::setfill(' ')
                    << std::setw(5)
                    << (*this)(i,j); 
        }
        std::cout << std::endl;
    } 
    std::cout << "]" << std::endl;
}
