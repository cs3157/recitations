#include <iostream>
#include <cassert>
#include "matrix.hpp"

Matrix::Matrix(int nrows, int ncols)
    // good practice to initialize members regardless of constructor body
    : nrows_(nrows), ncols_(ncols), data_(nullptr) 
{
    data_ = new int[nrows_ * ncols_]; 
}

Matrix::~Matrix()
{
    delete[] data_;
}

Matrix::Matrix(const Matrix& m)
{
    this->copy_from(m);
}

Matrix& Matrix::operator=(const Matrix& m)
{
    // If m is the same object as current object, 
    // there is nothing to do but return reference to current object.
    // If this check were not done and continued with code,
    // we would free this->data_ and copy contents of m.data_, 
    // but m.data_ points to freed memory since m and *this are the same objects!
    if (this == &m) {
        return *this;
    }

    // MUST free existing data before reassigning
    // Otherwise, memory leak!
    delete[] this->data_;
    this->copy_from(m);

    return *this;
}

void Matrix::copy_from(const Matrix& m) 
{
    this->nrows_ = m.nrows_;
    this->ncols_ = m.ncols_;
    this->data_ = new int[this->nrows_ * this->ncols_];
    std::copy(m.data_, m.data_ + m.nrows_ * m.ncols_, this->data_);
}

int& Matrix::operator()(int i, int j)
{
    assert(i < nrows_ && j < ncols_);
    return data_[i * ncols_ + j];
}

const int& Matrix::operator()(int i, int j) const
{
    // Both idiomatic and safer to use const_cast to cast away constness
    // than performing C-style casting like ((Matrix&) *this).
    // Be very careful with const_cast; this is one of the few times that its usage is considered acceptable.
    return const_cast<Matrix&>(*this)(i, j);
}

Matrix Matrix::operator+(const Matrix& m) const
{
    // assert same sizes
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

void Matrix::print() const
{
    // Print dimensions of matrix
    std::cout << nrows_ << " x " << ncols_ << std::endl;

    // Print contents of matrix
    std::cout << "[" << std::endl;
    for (int i = 0; i < nrows_; ++i) {
        for (int j = 0; j < ncols_; ++j) {
            std::cout << (*this)(i,j) << ' '; 
        }
        std::cout << std::endl;
    } 
    std::cout << "]" << std::endl;
}
