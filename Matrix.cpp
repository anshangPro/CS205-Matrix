//
// Created by ay871 on 2022/6/6.
//

#include "Matrix.h"

template<class T>
bool Matrix<T>::isValid(size_t col, size_t row) const {
    return col >= 0 && col <= this->m_col && row >= 0 && row <= this->m_row;
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
    T* a = this->data;
    T* b = mat.data;
    Matrix<T> res(this->col, this->row);
    T* ans = res.data;
    for(int i = 0; i < this->size; i++){
        *ans = *a + *b;
        ans++;
        a++;
        b++;
    }
    return res;
}

template<class T>
Matrix<T>::~Matrix() {
    delete(this->data);
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
    T* temp = data;
    for(int i = 0; i < m_col; i++){
        for(int j = 0; j < m_row; j++){
            std::cout << temp++ << '\t';
        }
        std::cout << std::endl;
    }
}