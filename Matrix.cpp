//
// Created by ay871 on 2022/6/6.
//

#include "Matrix.h"

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
    this->data = malloc(size * sizeof(T));
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &a) {
    this->col = a.col;
    this->row = a.row;
    this->size = a.size;
    this->data = malloc(size * sizeof(T));
    memcpy(this->data, a.data, size);
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &mat) const {
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
Matrix<T>::~Matrix() {
    delete (this->data);
    this->data = nullptr;
}

template<class T>
T Matrix<T>::get(size_t col, size_t row) const {
    if (!isValid(col, row)) throw IndexOutOfBound(col, row);
    return *(data + col * this->m_col + row);
}

template<class T>
void Matrix<T>::set(size_t col, size_t row, T value) const {
    if (!isValid(col, row)) throw IndexOutOfBound(col, row);
    *(data + col * this->m_col + row) = value;
}

template<class T>
void Matrix<T>::print() const {
    T *temp = data;
    for (int i = 0; i < m_col; i++) {
        for (int j = 0; j < m_row; j++) {
            std::cout << temp++ << '\t';
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
Matrix<T> convolution(Matrix<T> a, Matrix<T> b) {

}