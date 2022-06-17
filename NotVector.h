//
// Created by Lenovo on 2022/6/17.
//

#ifndef MAIN_CPP_NOTVECTOR_H
#define MAIN_CPP_NOTVECTOR_H
#include <exception>
#include <cstdio>

class NotVector: public std::exception{
private:
    size_t col;

public:
    explicit NotVector(size_t col): col(col){}

    const char* what() const noexcept override{
        char* info = new char[100];
        sprintf(info, "This is not a vector", col);
        return info;
    }
};
#endif //MAIN_CPP_NOTVECTOR_H
