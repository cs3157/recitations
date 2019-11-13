// pragma once is the C++ way of include guards.
// This guarantees that header files will be included at most once.
#pragma once

// Matrix is a class that represents a matrix of integers.
class Matrix 
{
public:
    Matrix() =default;  // tells compiler to generate default constructor.
                        // Note that if user provides a constructor (as shown in the next line of code),
                        // compiler will not generate a default constructor!
                        // Any declarations such as: 
                        //      Matrix M;
                        // will raise a compiler error since there is no default constructor.
                        // Sometimes you may not want your Matrix to have this default constructor.
                        // In this case, you may omit this line, or 
                        // as good practice, replace =default with =delete to be more explicit.
    Matrix(int nrows, int ncols);       // constructor
    Matrix(const Matrix&);              // copy constructor
    ~Matrix();                          // destructor
    Matrix& operator=(const Matrix&);   // copy assignment operator

    // operator() returns the row i, column j element of the matrix.
    // For simplicity, it is defined such that if i >= number of rows or j >= number of columns, 
    // program crashes; in practice, it is best to raise an error.
    // We return a reference to an internal data (int) so that we may write code as such:
    // 
    // M(1, 2) = 69; 
    //
    // which assigns 69 to row 2, column 3 entry of matrix M.
    // If operator() returns an int (no reference) the above code does not even compile.
    int& operator()(int i, int j);              
    const int& operator()(int i, int j) const;  // const version

    // operator+ returns a new matrix that is the matrix addition of current matrix and matrix M.
    // If the sizes do not match, program crashes; in practice, it is best to raise an error.
    Matrix operator+(const Matrix& M) const;  

    // Prints contents of current matrix.
    void print() const; 

    // Returns the number of rows.
    int nrows() const
    {
        return nrows_;
    }

    // Returns the number of columns.
    int ncols() const
    {
        return ncols_;
    }

private:
    // Helper function that deep copies another matrix into current matrix.
    // This exact logic is used in copy constructor and copy assignment.
    void copy_from(const Matrix&); 

    int nrows_; // number of rows
    int ncols_; // number of columns
    int* data_; // pointer to array containing data
};
