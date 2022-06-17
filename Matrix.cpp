//
// Created by ay871 on 2022/6/6.
//

#include "Matrix.h"
#include <iostream>
#include <complex>
#include <exception>
using namespace std;

template<class T>
bool Matrix<T>::isValid(size_t col, size_t row) const {
    return col >= 0 && col <= this->m_col && row >= 0 && row <= this->m_row;
}

template<class T>
bool Matrix<T>::isValid(size_t col_begin, size_t col_end, size_t row_begin, size_t row_end) const {
    return col_begin >= 0 && col_end <= this->m_col && row_begin >= 0
           && row_end <= this->m_row && col_begin <= col_end && row_begin <= row_end;
}

template<class T>
Matrix<T>::Matrix(size_t col, size_t row): size(col * row), m_col(col), m_row(row) {
    this->data = (T*)malloc(size * sizeof(T));
    memset(this->data,0,size*sizeof(T));
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &a) {
    this->m_col = a.m_col;
    this->m_row = a.m_row;
    this->size = a.size;
    this->data = (T*)malloc(size * sizeof(T));
    memcpy(this->data, a.data, size * sizeof(T));
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &mat) const {
    if (mat.m_col != this->m_col || mat.m_row != this->m_row){
        throw SizeNotEqual(mat.size,this->size);
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
Matrix<T> Matrix<T>::operator-(Matrix<T> const &mat) const{
    if (mat.m_col != this->m_col || mat.m_row != this->m_row){
        throw SizeNotEqual(mat.size,this->size);
    }
    T* a = this->data;
    T* b = mat.data;
    Matrix<T> res(this->m_col, this->m_row);
    T* ans = res.data;
    for(int i = 0; i < this->size; i++){
        *ans = *a - *b;
        ans++;
        a++;
        b++;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::scalarMultiplication(double const &k, Matrix<T> const &mat){
    T* a = mat.data;
    Matrix<T> res(mat.m_col, mat.m_row);
    T* ans = res.data;
    for(int i = 0; i < mat.size; i++){
        *ans = *a * k;
        ans++;
        a++;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::scalarDivision(double const &k, Matrix<T> const &mat){
    if (k == 0){
        throw DivisorBeZero();
    }
    T* a = mat.data;
    Matrix<T> res(mat.m_col, mat.m_row);
    T* ans = res.data;
    for(int i = 0; i < mat.size; i++){
        *ans = *a / k;
        ans++;
        a++;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::transposition(Matrix<T> const &mat){
    T* a;
    Matrix<T> res(mat.m_row, mat.m_col);
    T* ans = res.data;
    for (int i = 0; i < mat.m_col; ++i) {
        a = mat.data + i;
        for(int j = 0; j < mat.m_row; j++){
            *ans = *a;
            ans++;
            a += mat.m_col;
        }
    }

    return res;
}

template<class T>
Matrix<T> Matrix<T>::conjugation(Matrix<T> const &mat) {
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
    T *ans1 = res.data;
    for (int k = 0; k < res.size; ++k) {
        *ans1 = conj(*ans1);
        ans1++;
    }
    return res;
}
template<class T>
Matrix<T> Matrix<T>::elementMultiplication(Matrix<T> const &mat_a, Matrix<T> const &mat_b){
    if (mat_a.m_col != mat_b.m_col || mat_a.m_row != mat_b.m_row){
        throw SizeNotEqual(mat_a.size,mat_b->size);
    }
    T* a = mat_a.data;
    T* b = mat_b.data;
    Matrix<T> res(mat_a.m_col, mat_a.m_row);
    T* ans = res.data;
    for(int i = 0; i < mat_a.size; i++){
        *ans = *a * *b;
        ans++;
        a++;
        b++;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::matrixMultiplication(Matrix<T> const &mat_a, Matrix<T> const &mat_b){
    if (mat_a.m_col != mat_b.m_row){
        throw SizeNotEqual(mat_a.size,mat_b->size);
    }
    T* a = mat_a.data;
    T* b = mat_b.data;
    Matrix<T> res(mat_b.m_col, mat_a.m_row);
    T* ans = res.data;
    for(int i = 0; i < res.m_row; i++){
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
Matrix<T> Matrix<T>::vectorMultiplication(Matrix<T> const &mat_a, Matrix<T> const &vec){
    if (vec.m_col != 1){
        throw NotVector(vec.m_col);
    }
    if (mat_a.m_col != vec.m_row){
        throw SizeNotEqual(mat_a.size,vec.size);
    }
    T* a = mat_a.data;
    T* b = vec.data;
    Matrix<T> res(vec.m_col, mat_a.m_row);
    T* ans = res.data;
    for(int i = 0; i < res.m_row; i++){
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
Matrix<T> Matrix<T>::dotProduct(Matrix<T> const &mat_a, Matrix<T> const &mat_b){
    if (mat_a.m_col != mat_b.m_col || mat_a.m_row != mat_b.m_row){
        throw SizeNotEqual(mat_a.size,mat_b->size);
    }
    T* a = mat_a.data;
    T* b = mat_b.data;
    Matrix<T> res(mat_a.m_col, mat_a.m_row);
    T* ans = res.data;
    for(int i = 0; i < mat_a.size; i++){
        *ans = *a * *b;
        ans++;
        a++;
        b++;
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::crossProduct(Matrix<T> const &mat_a, Matrix<T> const &mat_b){
    if (mat_a.m_col != mat_b.m_row){
        throw SizeNotEqual(mat_a.size,mat_b->size);
    }
    T* a = mat_a.data;
    T* b = mat_b.data;
    Matrix<T> res(mat_b.m_col, mat_a.m_row);
    T* ans = res.data;
    for(int i = 0; i < res.m_row; i++){
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
Matrix<T>::~Matrix() {
    delete (this->data);
    this->data = nullptr;
}

template<class T>
T Matrix<T>::get(size_t col, size_t row) const {
    if (!isValid(col, row)) throw IndexOutOfBound(col, row);
    return *(data + row * this->m_col + col);
}

template<class T>
void Matrix<T>::set(size_t col, size_t row, T value) const {
    if (!isValid(col, row)) throw IndexOutOfBound(col, row);
    *(data + row * this->m_col + col) = value;
}

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
void Matrix<T>::reshape(size_t col, size_t row) {
    if ((col * row) != (m_col * m_row)) throw SizeNotEqual(m_col * m_row, col * row);
    m_col = col;
    m_row = row;
}

template<class T>
Matrix<T> Matrix<T>::slicing(size_t col_begin, size_t col_end, size_t row_begin, size_t row_end) {
    if (!isValid(col_begin, col_end, row_begin, row_end)) throw IndexOutOfBound(col_begin, col_end, row_begin, row_end);
    size_t col = col_end - col_begin, row = row_end - row_begin;
    Matrix<T> res(col, row);
    T *temp = this->data + col_begin;
    T *res_data = res.data;
    for (int i = 0; i < row; i++) {
        memcpy(res_data, temp, row * sizeof(T));
        temp += this->m_row;
        res_data += row;
    }
}

template<typename T>
Matrix<T> convolution(Matrix<T> a, Matrix<T> kernel) {

}