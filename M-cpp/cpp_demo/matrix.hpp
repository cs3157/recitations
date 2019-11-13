#pragma once

// Matrix is a class that represents a matrix of integers.
class Matrix 
{
public:
    Matrix() =default;
    Matrix(int nrows, int ncols);
    Matrix(const Matrix&);
    ~Matrix();
    Matrix& operator=(const Matrix&);

    int& operator()(int i, int j);
    const int& operator()(int i, int j) const;

    Matrix operator+(const Matrix&) const;

    void print() const;
    int nrows() const
    {
        return nrows_;
    }
    int ncols() const
    {
        return ncols_;
    }

private:
    void copy_helper(const Matrix&);

    int nrows_;
    int ncols_;
    int* data_;
};
