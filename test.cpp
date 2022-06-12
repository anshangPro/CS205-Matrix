//
// Created by ay871 on 2022/6/6.
//
#include <opencv2/opencv.hpp>

#include "IndexOutOfBound.h"

int main() {
  throw IndexOutOfBound(1, 2);
  return 0;
}