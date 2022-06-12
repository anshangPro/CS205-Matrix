#ifndef Part4_H
#define Part4_H

#include <malloc.h>
#include <cstring>
#include <iostream>
#include "IndexOutOfBound.h"
#include "Matrix.h"
#include "NotSquareMatrix.h"
#include "NoInverseMatrix.h"

template<class T>
class Matrix {
private:
    T *data;
    size_t size;
    size_t m_col, m_row;
    bool isValid(size_t col, size_t row) const;
public:
    Matrix() : data(nullptr), size(0), m_col(0), m_row(0) {}

    Matrix(size_t col, size_t row);

    Matrix(Matrix const &a);

    Matrix operator+(Matrix const &mat) const;

    T get(size_t col, size_t row) const;

    void set(size_t col, size_t row, T value) const;

    void print() const;

    ~Matrix();
};


#endif //Part4_H