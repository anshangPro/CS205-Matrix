//
// Created by ay871 on 2022/6/6.
//
#include <opencv2/opencv.hpp>

int main()
    {
    cv::Mat img = cv::imread("./test.jpg");
    cv::imshow("gril", img);
    cv::waitKey();
    return 0;
}