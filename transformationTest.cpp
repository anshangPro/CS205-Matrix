#include <iostream>

#include "Matrix.h"
#include "testbench.h"

using namespace std;
void testcase1() {
  cout << "This is the test for Matrix to OpenCV:" << endl;
  Matrix<float> a(4, 4);
  a.set(0, 0, 1);
  auto c = a.toCvMat();
  assertEquales(1, a, c);
}

void testcase2() {
  cout << "This is the test for OpenCV to our Matrix" << endl;
  cv::Mat mat_src = cv::Mat::eye(3, 3, CV_32F);
  auto a = Matrix<float>(mat_src);
  assertEquales(2, a, mat_src);
}

int main() {
  testcase1();
  testcase2();
}