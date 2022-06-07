//
// Created by ay871 on 2022/6/6.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <malloc.h>

#include <cstring>
#include <iostream>

#include "IndexOutOfBound.h"

template <class T>
class Matrix {
 private:
  T *data;
  size_t size;
  size_t m_col, m_row;
  bool isValid(size_t col, size_t row) const;

 public:
  Matrix() : data(nullptr), size(0), m_col(0), m_row(0) {}

  Matrix(size_t col, size_t row);

  Matrix(Matrix<T> const &a);

  Matrix<T> operator+(Matrix<T> const &mat) const;

  T get(size_t col, size_t row) const;

  void set(size_t col, size_t row, T value) const;

  void print() const;

  void reshape(size_t col, size_t row);

  Matrix<T> slicing(size_t col_begin, size_t col_end, size_t row_begin,
                    size_t row_end);

  Matrix<T> vigenvalue();

  Matrix<T> vigenvector();

  ~Matrix();
};

template <typename T>
Matrix<T> convolution(Matrix<T> a, Matrix<T> b);

#endif  // MATRIX_MATRIX_H
