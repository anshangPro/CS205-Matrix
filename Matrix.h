//
// Created by ay871 on 2022/6/6.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "Part4new.h"
#include <malloc.h>
#include <opencv2/opencv.hpp>

#include <cstring>
#include <iostream>

#include "IndexOutOfBound.h"
#include "NotSquareMatrix.h"
#include "SizeNotEqual.h"
#include "DivisorBeZero.h"
#include "NotVector.h"
#include "ColRowNotMatch.h"

template<typename T>
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

    explicit Matrix(const cv::Mat &mat); // 构造函数，将cv::Mat转换为Matrix

    Matrix(const Matrix<T> &a); // copy constructor

    Matrix(Matrix<T> &&a) noexcept; // move constructor

    Matrix<T> &operator=(Matrix<T> const &a); // copy assignment

    Matrix<T> &operator=(Matrix<T> &&a) noexcept; // move assignment

    Matrix<T> operator+(Matrix<T> const &mat) const;

    Matrix<T> operator-(Matrix const &mat) const;

    static Matrix scalarMultiplication(double const &k, Matrix const &mat);

    static Matrix scalarDivision(double const &k, Matrix const &mat);

    static Matrix transposition(Matrix const &mat);

    static Matrix elementMultiplication(Matrix const &mat_a, Matrix const &mat_b);

    static Matrix matrixMultiplication(Matrix const &mat_a, Matrix const &mat_b);

    static Matrix vectorMultiplication(Matrix const &mat_a, Matrix const &vec);

    static Matrix dotProduct(Matrix const &mat_a, Matrix const &mat_b);

    static Matrix crossProduct(Matrix const &mat_a, Matrix const &mat_b);

    cv::Mat toCvMat() const;

    T get(size_t col, size_t row) const;

    T *getData() const;

    size_t getCol() const;

    size_t getRow() const;

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

    T getDeterminant() const;

    T getTrace() const;

    static Matrix<T> convolution(Matrix<T> const &a, Matrix<T> const &kernel);

    static Matrix<T> flip(Matrix<T> const &kernel);

    ~Matrix();
};

template<class T>
void Matrix<T>::print() const {
    T *temp = data;
    for (int i = 0; i < m_row; i++) {
        for (int j = 0; j < m_col; j++) {
            std::cout << *temp++ << '\t';
        }
        std::cout << std::endl;
    }
}

template<class T>
cv::Mat Matrix<T>::toCvMat() const {
    cv::Mat mat(m_row, m_col, CV_32FC1);
    T *temp = data;
    for (int i = 0; i < m_row; i++) {
        for (int j = 0; j < m_col; j++) {
            mat.at<float>(i, j) = *temp++;
        }
    }
    return mat;
}

template<class T>
bool Matrix<T>::isValid(size_t col, size_t row) const {
    return col >= 0 && col < this->m_col && row >= 0 && row < this->m_row;
}

template<class T>
bool Matrix<T>::isValid(size_t col_begin, size_t col_end, size_t row_begin,
                        size_t row_end) const {
    return col_begin >= 0 && col_end < this->m_col && row_begin >= 0 &&
           row_end < this->m_row && col_begin <= col_end && row_begin <= row_end;
}

template<class T>
Matrix<T>::Matrix(size_t col, size_t row)
        : size(col * row), m_col(col), m_row(row) {
    this->data = (T *) malloc(size * sizeof(T));
    memset(this->data, 0, size * sizeof(T));
    // std::cout << "Matrix Allocated: " << this << " data_ptr:" << this->data
    //           << std::endl;
}

template<class T>
Matrix<T>::Matrix(const cv::Mat &mat) {
    this->m_col = mat.cols;
    this->m_row = mat.rows;
    this->size = this->m_col * this->m_row;
    this->data = (T *) malloc(size * sizeof(T));
    memset(this->data, 0, size * sizeof(T));
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            this->set(j, i, mat.at<float>(i, j));
        }
    }
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &a) {
    //    std::cout << "Matrix Copy Constructor from:" << &a << " to:" << this
    //              << std::endl;
    this->m_col = a.m_col;
    this->m_row = a.m_row;
    this->size = a.size;
    this->data = (T *) malloc(size * sizeof(T));
    memcpy(this->data, a.data, size * sizeof(T));
}

template<class T>
Matrix<T>::Matrix(Matrix<T> &&a) noexcept {
    //    std::cout << "Matrix Move Constructor from:" << &a << " to:" << this
    //              << std::endl;
    if (&a != this) {
        this->m_col = a.m_col;
        this->m_row = a.m_row;
        this->size = a.size;
        this->data = a.data;
        a.data = nullptr;
    }
}

template<class T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> const &a) {
    // copy assignment
    if (a == this)
        return *this;
    this->~Matrix();
    this->m_col = a.m_col;
    this->m_row = a.m_row;
    this->size = a.size;
    this->data = (T *) malloc(size * sizeof(T));
    memcpy(this->data, a.data, size * sizeof(T));
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&a) noexcept {
    // copy assignment
    //    std::cout << "Matrix Move Assignment from:" << &a << " to:" << this
    //              << std::endl;
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

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &mat) const {
    if (mat.m_col != this->m_col || mat.m_row != this->m_row) {
        throw ColRowNotMatch(mat.m_row, mat.m_col, this->m_row, this->m_col);
    }
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

template<class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> const &mat) const {
    if (mat.m_col != this->m_col || mat.m_row != this->m_row) {
        throw ColRowNotMatch(mat.m_row, mat.m_col, this->m_row, this->m_col);
    }
    T *a = this->data;
    T *b = mat.data;
    Matrix<T> res(this->m_col, this->m_row);
    T *ans = res.data;
    for (int i = 0; i < this->size; i++) {
        *ans = *a - *b;
        ans++;
        a++;
        b++;
    }
    return res;
}

template<class T>
size_t Matrix<T>::getCol() const { return m_col; }

template<class T>
size_t Matrix<T>::getRow() const { return m_row; }

template<class T>
Matrix<T>::~Matrix() {
    delete (this->data);
    this->data = nullptr;
}

template<class T>
T Matrix<T>::get(size_t col, size_t row) const {
    if (!isValid(col, row))
        throw IndexOutOfBound(col, row);
    return *(data + row * this->m_col + col);
}

template<class T>
T *Matrix<T>::getData() const { return this->data; }

template<class T>
void Matrix<T>::set(size_t col, size_t row, T value) const {
    if (!isValid(col, row))
        throw IndexOutOfBound(col, row);
    *(data + row * this->m_col + col) = value;
}

template<class T>
void Matrix<T>::reshape(size_t col, size_t row) {
    if ((col * row) != (m_col * m_row))
        throw SizeNotEqual(m_col * m_row, col * row);
    m_col = col;
    m_row = row;
}

template<class T>
Matrix<T> Matrix<T>::eigenValue() {
    if (this->m_col != this->m_row) {
        throw NotSquareMatrix(this->m_col, this->m_row);
    }
    SMatrix<T> A(this->data, this->m_col);
    auto eigValue = matrixEigValue(A, 1000);
    Matrix<T> res(eigValue.size, 1);
    for (int i = 0; i < eigValue.size; i++) {
        res.set(i, 0, eigValue[i][i]);
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::eigenValue(int times) {
    if (this->m_col != this->m_row) {
        throw NotSquareMatrix(this->m_col, this->m_row);
    }
    SMatrix<T> A(this->data, this->m_col);
    auto eigValue = matrixEigValue(A, times);
    Matrix<T> res(eigValue.size, 1);
    for (int i = 0; i < eigValue.size; i++) {
        res.set(i, 0, eigValue[i][i]);
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::eigenVector() {
    if (this->m_col != this->m_row) {
        throw NotSquareMatrix(this->m_col, this->m_row);
    }
    SMatrix<T> A(this->data, this->m_col);
    auto eigValue = matrixEigValue(A, 1000);
    auto eigVector = matrixEigVector(A, eigValue, 1000);
    Matrix<T> res(eigVector.size, eigVector.size);
    memcpy(res.data, eigVector.data.get(),
           eigVector.size * eigVector.size * sizeof(T));
    return res;
}

template<class T>
Matrix<T> Matrix<T>::eigenVector(int times) {
    if (this->m_col != this->m_row) {
        throw NotSquareMatrix(this->m_col, this->m_row);
    }
    SMatrix<T> A(this->data, this->m_col);
    auto eigValue = matrixEigValue(A, times);
    auto eigVector = matrixEigVector(A, eigValue, times);
    Matrix<T> res(eigVector.size, eigVector.size);
    memcpy(res.data, eigVector.data.get(),
           eigVector.size * eigVector.size * sizeof(T));
    return res;
}

template<class T>
Matrix<T> Matrix<T>::inverse() {
    if (this->m_col != this->m_row) {
        throw NotSquareMatrix(this->m_col, this->m_row);
    }
    SMatrix<T> A(this->data, this->m_col);
    auto inv = matrixInverse(A);
    Matrix<T> res(inv.size, inv.size);
    memcpy(res.data, inv.data.get(), inv.size * inv.size * sizeof(T));
    return res;
}

template<class T>
T Matrix<T>::getTrace() const {
    if (this->m_col != this->m_row) {
        throw NotSquareMatrix(this->m_col, this->m_row);
    }
    T *matrix = this->data;
    int n = this->m_col;
    T trace = 0;
    for (int i = 0; i < n; i++) {
        trace += matrix[i * n + i];
    }
    return trace;
}

template<class T>
T Matrix<T>::getDeterminant() const {
    if (this->m_col != this->m_row) {
        throw NotSquareMatrix(this->m_col, this->m_row);
    }
    T *matrix = this->data;
    int n = this->m_col;
    T det = 0;
    T *submatrix = new T[(n - 1) * (n - 1)];
    if (n == 2) {
        return ((matrix[0] * matrix[3]) - (matrix[2] * matrix[1]));
    } else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x) {
                        continue;
                    }
                    submatrix[subi * (n - 1) + subj] = matrix[i * n + j];
                    subj++;
                }
                std::cout << std::endl;
            }
        }
    }
    return det;
}

template<class T>
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

template<class T>
Matrix<T>
Matrix<T>::convolution(const Matrix<T> &a,
                       const Matrix<T> &kernel) {
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

template<class T>
Matrix<T> Matrix<T>::flip(const Matrix<T> &kernel) {
    Matrix<T> res(kernel.m_col, kernel.m_row);
    T *ori = kernel.data + kernel.size - 1;
    T *dst = res.data;
    for (int i = 0; i < kernel.size; i++) {
        *dst++ = *ori--;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::scalarMultiplication(double const &k, Matrix<T> const &mat) {
    T *a = mat.data;
    Matrix<T> res(mat.m_col, mat.m_row);
    T *ans = res.data;
    for (int i = 0; i < mat.size; i++) {
        *ans = *a * k;
        ans++;
        a++;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::scalarDivision(double const &k, Matrix<T> const &mat) {
    if (k == 0) {
        throw DivisorBeZero();
    }
    T *a = mat.data;
    Matrix<T> res(mat.m_col, mat.m_row);
    T *ans = res.data;
    for (int i = 0; i < mat.size; i++) {
        *ans = *a / k;
        ans++;
        a++;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::transposition(Matrix<T> const &mat) {
    T *a;
    Matrix<T> res(mat.m_row, mat.m_col);
    T *ans = res.data;
    for (int i = 0; i < mat.m_col; ++i) {
        a = mat.data + i;
        for (int j = 0; j < mat.m_row; j++) {
            *ans = *a;
            ans++;
            a += mat.m_col;
        }
    }

    return res;
}

template<class T>
Matrix<T> conjugation(Matrix<T> const &mat);

template<class T>
Matrix<T> conjugation(Matrix<T> const &mat) {
    T *a;
    Matrix<T> res(mat.getRow(), mat.getCol());
    T *ans = res.getData();
    for (int i = 0; i < mat.getCol(); ++i) {
        a = mat.getData() + i;
        for (int j = 0; j < mat.getRow(); j++) {
            *ans = *a;
            ans++;
            a += mat.getCol();
        }
    }
    return res;
}

template<class T>
Matrix<std::complex<T>> conjugation(Matrix<std::complex<T>> const &mat) {
    std::complex<T> *a;
    Matrix<std::complex<T>> res(mat.getRow(), mat.getCol());
    std::complex<T> *ans = res.getData();
    for (int i = 0; i < mat.getCol(); ++i) {
        a = mat.getData() + i;
        for (int j = 0; j < mat.getRow(); j++) {
            *ans = *a;
            ans++;
            a += mat.getCol();
        }
    }
    std::complex<T> *ans1 = res.getData();
    for (int k = 0; k < res.getCol() * res.getRow(); ++k) {
        *ans1 = conj(*ans1);
        ans1++;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::elementMultiplication(Matrix<T> const &mat_a, Matrix<T> const &mat_b) {
    if (mat_a.m_col != mat_b.m_col || mat_a.m_row != mat_b.m_row) {
        throw ColRowNotMatch(mat_a.m_row, mat_a.m_col, mat_b.m_row, mat_b.m_col);
    }
    T *a = mat_a.data;
    T *b = mat_b.data;
    Matrix<T> res(mat_a.m_col, mat_a.m_row);
    T *ans = res.data;
    for (int i = 0; i < mat_a.size; i++) {
        *ans = *a * *b;
        ans++;
        a++;
        b++;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::matrixMultiplication(Matrix<T> const &mat_a, Matrix<T> const &mat_b) {
    if (mat_a.m_col != mat_b.m_row) {
        throw ColRowNotMatch(mat_a.m_col, mat_b.m_row);
    }
    T *a = mat_a.data;
    T *b = mat_b.data;
    Matrix<T> res(mat_b.m_col, mat_a.m_row);
    T *ans = res.data;
    for (int i = 0; i < res.m_row; i++) {
        for (int j = 0; j < res.m_col; ++j) {
            for (int k = 0; k < mat_a.m_col; ++k) {
                *ans += *(a + k + (i * mat_a.m_col)) * *(b + j + (k * mat_b.m_col));
            }
            ans++;
        }
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::vectorMultiplication(Matrix<T> const &mat_a, Matrix<T> const &vec) {
    if (vec.m_col != 1 || vec.m_row <= 0) {
        throw NotVector(vec.m_col);
    }
    if (mat_a.m_col != vec.m_row) {
        throw ColRowNotMatch(mat_a.m_col, vec.m_row);
    }
    T *a = mat_a.data;
    T *b = vec.data;
    Matrix<T> res(vec.m_col, mat_a.m_row);
    T *ans = res.data;
    for (int i = 0; i < res.m_row; i++) {
        for (int j = 0; j < res.m_col; ++j) {
            for (int k = 0; k < mat_a.m_col; ++k) {
                *ans += *(a + k + (i * mat_a.m_col)) * *(b + j + (k * vec.m_col));
            }
            ans++;
        }
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::dotProduct(Matrix<T> const &mat_a, Matrix<T> const &mat_b) {
    if (mat_a.m_col != mat_b.m_col || mat_a.m_row != mat_b.m_row) {
        throw ColRowNotMatch(mat_a.m_row, mat_a.m_col, mat_b.m_row, mat_b.m_col);
    }
    T *a = mat_a.data;
    T *b = mat_b.data;
    Matrix<T> res(mat_a.m_col, mat_a.m_row);
    T *ans = res.data;
    for (int i = 0; i < mat_a.size; i++) {
        *ans = *a * *b;
        ans++;
        a++;
        b++;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::crossProduct(Matrix<T> const &mat_a, Matrix<T> const &mat_b) {
    if (mat_a.m_col != mat_b.m_row) {
        throw ColRowNotMatch(mat_a.m_col, mat_b.m_row);
    }
    T *a = mat_a.data;
    T *b = mat_b.data;
    Matrix<T> res(mat_b.m_col, mat_a.m_row);
    T *ans = res.data;
    for (int i = 0; i < res.m_row; i++) {
        for (int j = 0; j < res.m_col; ++j) {
            for (int k = 0; k < mat_a.m_col; ++k) {
                *ans += *(a + k + (i * mat_a.m_col)) * *(b + j + (k * mat_b.m_col));
            }
            ans++;
        }
    }
    return res;
}

template<class T>
Matrix<T> initial(size_t col, size_t row, T data[]){
    Matrix<T> res(col, row);
    size_t temp = 0;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            res.set(j, i, data[temp++]);
        }
    }
    return res;
}

template<class T>
T getMax(Matrix<T> &mat) {
    T max = mat.get(0, 0);
    for(int i = 0; i < mat.getCol(); i++){
        for(int j = 0; j < mat.getRow(); j++) {
            if (max < mat.get(i, j)) max = mat.get(i, j);
        }
    }
    return max;
}

template<class T>
T getMin(Matrix<T> &mat) {
    T min = mat.get(0, 0);
    for(int i = 0; i < mat.getCol(); i++){
        for(int j = 0; j < mat.getRow(); j++) {
            if (min > mat.get(i, j)) min = mat.get(i, j);
        }
    }
    return min;
}

template<class T>
std::complex<T> getMax(Matrix<std::complex<T>> &mat) {
    std::complex<T> max = mat.get(0, 0);
    for(int i = 0; i < mat.getCol(); i++){
        for(int j = 0; j < mat.getRow(); j++) {
            if (abs(max) < abs(mat.get(i, j))) max = mat.get(i, j);
        }
    }
    return max;
}

template<class T>
std::complex<T> getMin(Matrix<std::complex<T>> &mat) {
    std::complex<T> min = mat.get(0, 0);
    for(int i = 0; i < mat.getCol(); i++){
        for(int j = 0; j < mat.getRow(); j++) {
            if (abs(min) > abs(mat.get(i, j))) min = mat.get(i, j);
        }
    }
    return min;
}

template<class T>
T getAvg(Matrix<T> mat)  {
    return getSum(mat) / (mat.getRow() * mat.getCol());
}

template<class T>
std::complex<T> getAvg(Matrix<std::complex<T>> mat)  {
    return getSum(mat) / std::complex<T>(mat.getRow() * mat.getCol(), 0);
}

template<class T>
T getSum(Matrix<T> mat) {
    T sum = 0;
    for(int i = 0; i < mat.getCol(); i++){
        for(int j = 0; j < mat.getRow(); j++) {
            sum += mat.get(i, j);
        }
    }
    return sum;
}

template<class T>
T getMax(Matrix<T> mat, size_t col_begin, size_t col_end, size_t row_begin, size_t row_end) {
    Matrix<T> temp = mat.slicing(col_begin, col_end, row_begin, row_end);
    return getMax(temp);
}

template<class T>
T getMin(Matrix<T> mat, size_t col_begin, size_t col_end, size_t row_begin, size_t row_end) {
    Matrix<T> temp = mat.slicing(col_begin, col_end, row_begin, row_end);
    return getMin(temp);
}

template<class T>
T getAvg(Matrix<T> mat, size_t col_begin, size_t col_end, size_t row_begin, size_t row_end) {
    Matrix<T> temp = mat.slicing(col_begin, col_end, row_begin, row_end);
    return getAvg(temp);
}

template<class T>
T getSum(Matrix<T> mat, size_t col_begin, size_t col_end, size_t row_begin, size_t row_end) {
    Matrix<T> temp = mat.slicing(col_begin, col_end, row_begin, row_end);
    return getSum(temp);
}

#endif  // MATRIX_MATRIX_H
