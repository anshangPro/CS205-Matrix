//
// Created by ay871 on 2022/6/18.
//

#include "Matrix.h"
using namespace std;

void exception1(){ // ColRowNotMatch
    Matrix<int> a(4, 6);
    Matrix<int> b(6, 4);
    a + b;
}

void exception2(){ // IndexOutOfBound
    Matrix<int> a(4, 6);
    int b = a.get(5, 0);
}

void exception3(){ // SizeNotEqual
    Matrix<int> a(4, 6);
    a.reshape(5,1);
}

void exception4(){ // NotSquareMatrix
    Matrix<int> a(4, 6);
    a.eigenValue();
}

void exception5(){ // IndexOutOfBound
    Matrix<int> a(5, 5);
    a.slicing(-1, 1, 1, 1);
}

void exception6(){ // DivisorBeZero
    Matrix<int> a(5, 5);
    Matrix<int>::scalarDivision(0, a);
}

void exception7(){ // ColRowNotMatch
    Matrix<int> a(5, 5);
    Matrix<int> b(6, 6);
    Matrix<int>::elementMultiplication(a, b);
}

void exception8(){ // ColRowNotMatch
    Matrix<int> a(5, 5);
    Matrix<int> b(6, 6);
    Matrix<int>::matrixMultiplication(a, b);
}

void exception9(){ // NotVector
    Matrix<int> a(5, 5);
    Matrix<int> vector(2,2);
    Matrix<int>::vectorMultiplication(a, vector);
}

void exception10(){ // ColRowNotMatch
    Matrix<int> a(5, 5);
    Matrix<int> vector(1,2);
    Matrix<int>::vectorMultiplication(a, vector);
}