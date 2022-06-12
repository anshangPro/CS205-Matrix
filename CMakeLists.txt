cmake_minimum_required(VERSION 3.0)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
message(STATUS "opencv libs: ${OpenCV_LIBS}")
message(STATUS "opencv includes: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Matrix main.cpp)
target_link_libraries(Matrix ${OpenCV_LIBS})

add_executable(test test.cpp)
target_link_libraries(test ${OpenCV_LIBS})
