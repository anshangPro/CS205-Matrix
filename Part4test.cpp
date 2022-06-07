//
// Created by dgy on 22-6-7.
//
#include <iostream>
#include <complex>

#include "Part4.cpp"

using namespace std;

int main() {
    auto *A = new complex<double>[3 * 3];
    // 1 2 2 2 1 2 1 2 1
    A[0] = 1.0 + 2i;
    A[1] = 2.0 + 2i;
    A[2] = 2;
    A[3] = 2;
    A[4] = 1;
    A[5] = 2;
    A[6] = 1;
    A[7] = 2;
    A[8] = 1;
    auto *Q = new complex<double>[3 * 3];
    auto *R = new complex<double>[3 * 3];
    QRBreakDown(A, 3, Q, R);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << Q[i * 3 + j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << R[i * 3 + j] << " ";
        }
        cout << endl;
    }
    return 0;
}