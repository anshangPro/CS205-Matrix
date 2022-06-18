cmake_minimum_required(VERSION 3.21)
project(PROJECT)

set(CMAKE_CXX_STANDARD 11)

add_executable(PROJECT main.cpp)
set(OpenCV_DIR D:\\opencv\\opencv\\mingw-build2)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(PROJECT ${OpenCV_LIBS})