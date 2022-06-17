//
// Created by ay871 on 2022/6/6.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "Part4new.h"
#include <malloc.h>

#include <cstring>
#include <iostream>

#include "IndexOutOfBound.h"
#include "SizeNotEqual.h"

template <class T> class Matrix {

private:
  // std::unique_ptr<T[]> data;
  T *data;
  size_t size;
  size_t m_col, m_row;
  bool isValid(size_t col, size_t row) const;
  bool isValid(size_t col_begin, size_t col_end, size_t row_begin,
               size_t row_end) const;

public:
  Matrix() : data(nullptr), size(0), m_col(0), m_row(0) {}

  Matrix(size_t col, size_t row);

  Matrix(const Matrix<T> &a); // copy constructor

  Matrix(Matrix<T> &&a) noexcept; // move constructor

  Matrix<T> &operator=(Matrix<T> &matrix); // copy assignment

  Matrix<T> &operator=(Matrix<T> &&matrix) noexcept; // move assignment

  Matrix<T> operator+(Matrix<T> const &mat) const;

  T get(size_t col, size_t row) const;

  T *getData() const;

  void set(size_t col, size_t row, T value) const;

  void print() const;

  void reshape(size_t col, size_t row);

  Matrix<T> slicing(size_t col_begin, size_t col_end, size_t row_begin,
                    size_t row_end);

  Matrix<T> eigenValue();

  Matrix<T> eigenValue(int times);

  Matrix<T> eigenVector();

  Matrix<T> eigenVector(int times);

  Matrix<T> inverse();

  long long getDeterminant() const;

  long long getTrace() const;

  static Matrix<T> convolution(Matrix<T> const &a, Matrix<T> const &kernel);

  static Matrix<T> flip(Matrix<T> const &kernel);

  ~Matrix();
};

template <class T> bool Matrix<T>::isValid(size_t col, size_t row) const {
  return col >= 0 && col < this->m_col && row >= 0 && row < this->m_row;
}

template <class T>
bool Matrix<T>::isValid(size_t col_begin, size_t col_end, size_t row_begin,
                        size_t row_end) const {
  return col_begin >= 0 && col_end < this->m_col && row_begin >= 0 &&
         row_end < this->m_row && col_begin <= col_end && row_begin <= row_end;
}

template <class T>
Matrix<T>::Matrix(size_t col, size_t row)
    : size(col * row), m_col(col), m_row(row) {
  this->data = (T *)malloc(size * sizeof(T));
  memset(this->data, 0, size * sizeof(T));
  // std::cout << "Matrix Allocated: " << this << " data_ptr:" << this->data
  //           << std::endl;
}

template <class T> Matrix<T>::Matrix(const Matrix<T> &a) {
  std::cout << "Matrix Copy Constructor from:" << &a << " to:" << this
            << std::endl;
  this->m_col = a.m_col;
  this->m_row = a.m_row;
  this->size = a.size;
  this->data = (T *)malloc(size * sizeof(T));
  memcpy(this->data, a.data, size * sizeof(T));
}
template <class T> Matrix<T>::Matrix(Matrix<T> &&a) noexcept {
  std::cout << "Matrix Move Constructor from:" << &a << " to:" << this
            << std::endl;
  if (&a != this) {
    this->m_col = a.m_col;
    this->m_row = a.m_row;
    this->size = a.size;
    this->data = a.data;
    a.data = nullptr;
  }
}

template <class T> Matrix<T> &Matrix<T>::operator=(Matrix<T> &a) {
  // copy assignment
  std::cout << "Matrix Copy Assignment from:" << &a << " to:" << this
            << std::endl;
  this->~Matrix();
  this->m_col = a.m_col;
  this->m_row = a.m_row;
  this->size = a.size;
  this->data = (T *)malloc(size * sizeof(T));
  memcpy(this->data, a.data, size * sizeof(T));
  return *this;
}

template <class T> Matrix<T> &Matrix<T>::operator=(Matrix<T> &&a) noexcept {
  // copy assignment
  std::cout << "Matrix Move Assignment from:" << &a << " to:" << this
            << std::endl;
  if (&a != this) {
    this->~Matrix();
    this->m_col = a.m_col;
    this->m_row = a.m_row;
    this->size = a.size;
    this->data = a.data;
    a.data = nullptr;
  }
  return *this;
}

template <class T> Matrix<T> Matrix<T>::operator+(const Matrix<T> &mat) const {
  std::cout << "Matrix add " << this << " " << &mat << std::endl;
  T *a = this->data;
  T *b = mat.data;
  Matrix<T> res(this->m_col, this->m_row);
  T *ans = res.data;
  for (int i = 0; i < this->size; i++) {
    *ans = *a + *b;
    ans++;
    a++;
    b++;
  }
  return res;
}

template <class T> Matrix<T>::~Matrix() {
  // std::cout << "Matrix Destructor:" << this << " data_ptr:" << this->data
  //           << std::endl;
  delete (this->data);
  this->data = nullptr;
}

template <class T> T Matrix<T>::get(size_t col, size_t row) const {
  if (!isValid(col, row))
    throw IndexOutOfBound(col, row);
  return *(data + row * this->m_col + col);
}

template <class T> T *Matrix<T>::getData() const { return this->data; }

template <class T> void Matrix<T>::set(size_t col, size_t row, T value) const {
  if (!isValid(col, row))
    throw IndexOutOfBound(col, row);
  *(data + row * this->m_col + col) = value;
}

template <class T> void Matrix<T>::print() const {
  T *temp = data;
  for (int i = 0; i < m_row; i++) {
    for (int j = 0; j < m_col; j++) {
      std::cout << *temp++ << '\t';
    }
    std::cout << std::endl;
  }
}

template <class T> void Matrix<T>::reshape(size_t col, size_t row) {
  if ((col * row) != (m_col * m_row))
    throw SizeNotEqual(m_col * m_row, col * row);
  m_col = col;
  m_row = row;
}

template <class T> Matrix<T> Matrix<T>::eigenValue() {
  SMatrix<T> A(this->data, this->m_col);
  auto eigValue = matrixEigValue(A, 1000);
  Matrix<T> res(eigValue.size, 1);
  for (int i = 0; i < eigValue.size; i++) {
    res.set(i, 0, eigValue[i][i]);
  }
  return res;
}

template <class T> 
Matrix<T> Matrix<T>::eigenValue(int times) {
  SMatrix<T> A(this->data, this->m_col);
  auto eigValue = matrixEigValue(A, times);
  Matrix<T> res(eigValue.size, 1);
  for (int i = 0; i < eigValue.size; i++) {
    res.set(i, 0, eigValue[i][i]);
  }
  return res;
}
template <class T> 
Matrix<T> Matrix<T>::eigenVector() {
  SMatrix<T> A(this->data, this->m_col);
  auto eigValue = matrixEigValue(A, 1000);
  auto eigVector = matrixEigVector(A, eigValue, 1000);
  Matrix<T> res(eigVector.size, eigVector.size);
  //memcpy(res.data, eigVector.data.get(), eigVector.size * sizeof(T));
  for (int i = 0; i < eigVector.size; i++) {
    for (int j = 0; j < eigVector.size; j++) {
      res.set(i, j, eigVector[i][j]);
    }
  }
  return res;
}

template <class T>
Matrix<T> Matrix<T>::slicing(size_t col_begin, size_t col_end, size_t row_begin,
                             size_t row_end) {
  if (!isValid(col_begin, col_end, row_begin, row_end))
    throw IndexOutOfBound(col_begin, col_end, row_begin, row_end);
  size_t col = col_end - col_begin + 1, row = row_end - row_begin + 1;
  Matrix<T> res(col, row);
  T *temp = this->data + col_begin + this->m_col * row_begin;
  T *res_data = res.data;
  for (int i = 0; i < row; i++) {
    memcpy(res_data, temp, col * sizeof(T));
    temp += this->m_col;
    res_data += col;
  }
  return res;
}

template <class T>
Matrix<T>
Matrix<T>::convolution(const Matrix<T> &a,
                       const Matrix<T> &kernel) { // need square and odd kernel
  Matrix<T> extended(a.m_col + kernel.m_col - 1, a.m_row + kernel.m_row - 1);
  T *p_e =
      extended.data + extended.m_row * (kernel.m_row / 2) + kernel.m_col / 2;
  T *p_a = a.data;
  for (int i = 0; i < a.m_row; i++) {
    memcpy(p_e, p_a, a.m_col * sizeof(T));
    p_a += a.m_col;
    p_e += extended.m_col;
  }
  Matrix<T> res(a.m_col, a.m_row);
  p_e = extended.data;
  Matrix<T> kernel_flip = flip(kernel);
  T *p_k = kernel_flip.data;
  T temp;
  for (int i = 0; i < a.m_row; i++) {
    for (int j = 0; j < a.m_col; j++) {
      temp = 0;
      for (int p = 0; p < kernel.m_row; p++) {
        for (int q = 0; q < kernel.m_col; q++) {
          temp += *(p_k + kernel.m_col * p + q) *
                  *(p_e + extended.m_col * (i + p) + j + q);
        }
      }
      res.set(j, i, temp);
    }
  }
  return res;
}

template <class T> Matrix<T> Matrix<T>::flip(const Matrix<T> &kernel) {
  Matrix<T> res(kernel.m_col, kernel.m_row);
  T *ori = kernel.data + kernel.size - 1;
  T *dst = res.data;
  for (int i = 0; i < kernel.size; i++) {
    *dst++ = *ori--;
  }
  return res;
}

#endif // MATRIX_MATRIX_H
