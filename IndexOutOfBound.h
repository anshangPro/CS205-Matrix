//
// Created by ay871 on 2022/6/6.
//
#include <exception>
#include <stdio.h>

class IndexOutOfBound: public std::exception{
private:
    size_t col, row;

public:
    IndexOutOfBound(size_t col, size_t row): col(col), row(row){}

    const char * what(){
        char* info = new char[100];
        sprintf(info, "Index out of matrix bound: %zu, %zu.", col, row);
        return info;
    }
};