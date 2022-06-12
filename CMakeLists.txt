cmake_minimum_required(VERSION 3.0)
project(Matrix)

set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/include/opencv4/opencv2/")
include_directories("/usr/include/opencv4/")

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lopencv_core -lopencv_highgui -lopencv_imgcodecs")
add_executable(Matrix main.cpp)

add_executable(test test.cpp)