//
// Created by ay871 on 2022/6/12.
//
#include "Matrix.h"
#include <complex>

using namespace std;

int main(){
    Matrix<std::complex<double>> a(4, 4);
    int temp = 1;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            a.set(j, i, temp++);
        }
    }
    Matrix<std::complex<double>> core(3, 3);
    core.set(0, 0, -1);
    core.set(1, 0, -2);
    core.set(2, 0, -1);
    core.set(0, 2, 1);
    core.set(1, 2, 2);
    core.set(2, 2, 1);

    cout << "==========MatA==========" << endl;
    a.print();
    cout << "==========MatCore==========" << endl;
    core.print();
    cout << "==========Convolution==========" << endl;
    Matrix<std::complex<double>> res = Matrix<std::complex<double>>::convolution(a, core);
    res.print();
    cout << "==========Slicing(1)==========" << endl;
    try{
        auto tempN = res.slicing(1, 2, 0, 3);
        tempN.print();
        cout << "==========Slicing(2)==========" << endl;
        auto tempM = res.slicing(0, 4, 0, 3);
        tempM.print();
    } catch (IndexOutOfBound& e) {
        cout << e.what() << endl;
    }
    cout << "==========Reshape(1)==========" << endl;
    try{
        res.reshape(8, 2);
        res.print();
        cout << "==========Reshape(2)==========" << endl;
        res.reshape(1,1);
    } catch (SizeNotEqual& e) {
        cout << e.what() << endl;
    }

    return 0;
}