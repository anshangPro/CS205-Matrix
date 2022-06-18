//
// Created by dgy on 22-6-12.
//

#ifndef CPP_COMPARE_H
#define CPP_COMPARE_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <complex>

using namespace std;


template<typename T>
bool compare(T *A, T *B, int dim) {
    for (int i = 0; i < dim*dim; i++) {
        if (A[i] - B[i] > 0.00001 || A[i] - B[i] < -0.00001) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool compare(complex<T> *A, complex<T> *B, int dim) {
    for (int i = 0; i < dim*dim; i++) {
        if (A[i].real() - B[i].real() > 0.00001 || A[i].real() - B[i].real() < -0.00001) {
            return false;
        }else if(A[i].imag() - B[i].imag() > 0.00001 || A[i].imag() - B[i].imag() < -0.00001){
            return false;
        }
    }
    return true;
}

#endif //CPP_COMPARE_H
