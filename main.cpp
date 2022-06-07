//
// Created by ay871 on 2022/6/6.
//
#include <iostream>
#include "Matrix.h"
#include "Matrix.cpp"
using namespace std;
int main(){
    Matrix<int> a(2,3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            a.set(i,j,1);
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << a.get(i,j)<<" ";
        }
        cout <<endl;
    }
    const Matrix<int>& b(a);
    Matrix<int> c = a + b;
    a.print();
    b.print();
    c.print();
    return 0;
}