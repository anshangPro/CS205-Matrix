//
// Created by ay871 on 2022/6/6.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <malloc.h>

#include <cstring>
#include <iostream>
#include <complex>
#include "IndexOutOfBound.h"
#include "SizeNotEqual.h"
#include "DivisorBeZero.h"
#include "NotVector.h"
template <class T>
class Matrix {
  
private:
    T *data;
    size_t size;
    size_t m_col, m_row;
    bool isValid(size_t col, size_t row) const;
    bool isValid(size_t col_begin, size_t col_end, size_t row_begin, size_t row_end) const;
  
 public:
  Matrix() : data(nullptr), size(0), m_col(0), m_row(0) {}

  Matrix(size_t col, size_t row);

  Matrix(Matrix<T> const &a);

  Matrix<T> operator+(Matrix<T> const &mat) const;

    //3)
    Matrix operator-(Matrix const &mat) const;

    static Matrix scalarMultiplication(double const &k, Matrix const &mat);

    static Matrix scalarDivision(double const &k, Matrix const &mat);

    static Matrix transposition(Matrix const &mat);

    static Matrix conjugation(Matrix const &mat);


    static Matrix elementMultiplication(Matrix const &mat_a, Matrix const &mat_b);

    static Matrix matrixMultiplication(Matrix const &mat_a, Matrix const &mat_b);

    static Matrix vectorMultiplication(Matrix const &mat_a, Matrix const &vec);

    static Matrix dotProduct(Matrix const &mat_a, Matrix const &mat_b);

    static Matrix crossProduct(Matrix const &mat_a, Matrix const &mat_b);
    //3)

  T get(size_t col, size_t row) const;

  void set(size_t col, size_t row, T value) const;

  void print() const;

  void reshape(size_t col, size_t row);

  Matrix<T> slicing(size_t col_begin, size_t col_end, size_t row_begin,
                    size_t row_end);

  Matrix<T> vigenValue();

  Matrix<T> vigenVector();

  Matrix<T> inverse();

  long long getDeterminant() const;

  long long getTrace() const;

  ~Matrix();
};

template<typename T>
static Matrix<std::complex<T>> conjugation(Matrix<std::complex<T>> const &mat){
    std::complex<T> *a;
    Matrix<std::complex<T>> res(mat.m_row, mat.m_col);
    std::complex<T> *ans = res.data;
    for (int i = 0; i < mat.m_col; ++i) {
        a = mat.data + i;
        for (int j = 0; j < mat.m_row; j++) {
            *ans = *a;
            ans++;
            a += mat.m_col;
        }
    }
    std::complex<T> *ans1 = res.data;
    for (int k = 0; k < res.size; ++k) {
        *ans1 = conj(*ans1);
        ans1++;
    }
    return res;
}
template<typename T>
Matrix<T> convolution(Matrix<T> a, Matrix<T> kernel);

#endif  // MATRIX_MATRIX_H
