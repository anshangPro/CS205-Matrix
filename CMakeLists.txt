cmake_minimum_required(VERSION 3.21)
project(project)

set(CMAKE_CXX_STANDARD 11)

add_executable(project main.cpp Matrix.cpp DivisorBeZero.h NotVector.h)
set(OpenCV_DIR D:\\opencv\\opencv\\mingw-build2)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(project ${OpenCV_LIBS})

