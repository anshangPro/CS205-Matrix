//
// Created by dgy on 22-6-7.
//
#include <iostream>
#include <complex>

#include "Part4.cpp"

using namespace std;

int main() {
    auto *A = new double[3 * 3];
    // 1 2 2 2 1 2 1 2 1
    A[0] = 12;
    A[1] = 22;
    A[2] = 32;
    A[3] = 4;
    A[4] = 25;
    A[5] = 6;
    A[6] = 7;
    A[7] = 8;
    A[8] = 9;
    auto *Q = new double[3 * 3];
    auto *R = new double[3 * 3];
    //QRBreakDown(A, 3, Q, R);
    JacbiCor(A, 3, Q, R, 0.00001, 100);
    cout<<determinant(A, 3)<<endl;
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