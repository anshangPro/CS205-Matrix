//
// Created by ay871 on 2022/6/6.
//
#include <iostream>
#include "Matrix.h"
#include "Matrix.cpp"
using namespace std;
int main(){
    int temp = 1;
    Matrix<int> a(2,3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            a.set(j,i,temp++);
        }
    }
    int temp1 = 1;
    Matrix<int> b(1,2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 1; ++j) {
            b.set(j,i,temp1++);
        }
    }
    Matrix<int> c = Matrix<int>::conjugation(a);
    a.print();
    cout<<endl;
    b.print();
    cout<<endl;
    c.print();
    /*double temp = 1;
    complex<double> complex1{1,temp};
    Matrix<complex<double>> a(2,3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            a.set(j,i,complex1);
            complex1.imag(++temp);
        }
    }
    Matrix<complex<double>> c = Matrix<complex<double>>::conjugation(a);
    a.print();
    cout<<endl;
    c.print();*/
    return 0;
}