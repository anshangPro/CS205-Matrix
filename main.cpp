//
// Created by ay871 on 2022/6/6.
//
#include <iostream>
#include <opencv2/opencv.hpp>

#include "Matrix.h"

using namespace cv;
using namespace std;

int main() {
     /*Matrix<float> a(4, 4);
     a.set(0, 0, 1);
     auto c = a.toCvMat();
     cout << c.rows << " " << c.cols << endl;
     cout << c << endl;
    Matrix<float> a(3, 3);
    a.set(0, 0, 1);
    a.set(0, 1, 2);
    a.set(0, 2, 3);
    a.set(1, 0, 4);
    a.set(1, 1, 5);
    a.set(1, 2, 4);
    a.set(2, 0, 7);
    a.set(2, 1, 8);
    a.set(2, 2, 8);
    auto b = a.eigenValue();
    a.print();
    b.print();*/
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
    Matrix<int> c = conjugation(a);
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
    Matrix<complex<double>> b(3,2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            b.set(j,i,complex1);
            complex1.imag(++temp);
        }
    }
    Matrix<complex<double>> c = conjugation(a);
    a.print();
    cout<<endl;
    c.print();
     */
    return 0;
}

//int main()
//{
//    cv::Mat img = cv::imread("./test.jpg");
//    cv::imshow("gril", img);
//    cv::waitKey();
//    return 0;
//}