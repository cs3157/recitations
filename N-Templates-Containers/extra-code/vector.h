#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <cstdlib>  // size_t

// myvector is an array of elements of type T.
template <class T>
class myvector
{
public:

    // Constructor
    myvector()
    {
        data_ = new T[1];
        size_ = 0;
        capacity_ = 1;
    }

    // Destructor
    ~myvector()
    {
        delete[] data_;
    }

    // Append element x to the end of the vector
    void push_back(const T& x)
    {
        if (size_ >= capacity_) {
            grow();
        }
        data_[size_] = x;
        ++size_;
    }

    // Get ith element
    T& operator[](size_t i)
    {
        return data_[i];
    }

    // Get ith element (const version)
    const T& operator[](size_t i) const
    {
        return data_[i];
    }

    // Get size of vector
    size_t size() const
    {
        return size_;
    }

private:

    void grow()
    {
        // Increase capacity by twice the current capacity.
        capacity_ *= 2;

        // Allocate a new array with original array copied over.
        T* newdata_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            newdata_[i] = data_[i];
        }

        // Deallocate old array
        delete[] data_;

        // Set data_ to point to new array
        data_ = newdata_;
    }

    T* data_;           // points to array of data
    size_t size_;       // number of elements occupied
    size_t capacity_;   // max number of elements that can occupy current array
};

#endif
