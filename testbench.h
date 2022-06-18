#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <iostream>
#include <opencv2/opencv.hpp>

#include "Matrix.h"
#include "NotSquareMatrix.h"

using namespace std;

const double MIN_DOUBLE = 1E-3;

void printFailure(int n, string msg) {
  cout << "\033[31m"
       << "Test " << n << " failed: " << msg << "\033[0m" << endl;
}

void printSuccess(int n, string msg = "") {
  cout << "\033[32m"
       << "Test " << n << " passed: " << msg << "\033[0m" << endl;
}

template <typename T>
void assertEquales(int num, const Matrix<T> &a, const cv::Mat &b) {
  if (a.getRow() != b.rows || a.getCol() != b.cols) {
    printFailure(num, "Matrix size not equal");
    return;
  }
  for (int i = 0; i < a.getRow(); i++) {
    for (int j = 0; j < a.getCol(); j++) {
      if (abs(a.get(i, j) - b.at<T>(i, j)) > MIN_DOUBLE) {
        printFailure(num, "Matrix value not equal");
        return;
      }
    }
  }
  printSuccess(num);
}

//通过int指示测试哪一个函数
// 1： eigenValue()
// 2： eigenValue(int)
// 3:  eigenVector()
// 4:  eigenVector(int)
// 5:  inverse()
// 6:  getTrace()
// 7:  getDeterminant()
template <typename T> void testNotSquareMatrix(int num, int n, Matrix<T> a) {
  try {
    switch (n) {
    case 1:
      a.eigenValue();
      break;
    case 2:
      a.eigenValue(1);
      break;
    case 3:
      a.eigenVector();
      break;
    case 4:
      a.eigenVector(1);
      break;
    case 5:
      a.inverse();
      break;
    case 6:
      a.getTrace();
      break;
    case 7:
      a.getDeterminant();
      break;
    default:
      break;
    }
  } catch (NotSquareMatrix e) {
    printSuccess(num, "NotSquareMatrix Exception");
    return;
  } catch (exception e1) {
    printFailure(num, e1.what());
    return;
  }
}




#endif // TESTBENCH_H
