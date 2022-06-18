//
// Created by ay871 on 2022/6/6.
//
#include <iostream>
#include <opencv2/opencv.hpp>

#include "Matrix.h"

using namespace cv;
using namespace std;

int main() {
   Matrix<float> a(4, 4);
   a.set(0, 0, 1);
   auto c = a.toCvMat();
   cout << c.rows << " " << c.cols << endl;
   cout << c << endl;
//  Matrix<float> a(4, 3);
//  a.eigenValue();
  return 0;
}

//int main()
//{
//    cv::Mat img = cv::imread("./test.jpg");
//    cv::imshow("gril", img);
//    cv::waitKey();
//    return 0;
//}