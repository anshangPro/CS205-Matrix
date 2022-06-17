//
// Created by Lenovo on 2022/6/17.
//

#ifndef MAIN_CPP_DIVISORBEZERO_H
#define MAIN_CPP_DIVISORBEZERO_H
#include <exception>
#include <cstdio>

class DivisorBeZero: public std::exception{

public:
    const char* what() const noexcept override{
        char* info = new char[100];
        sprintf(info, "Divisor can not be zero");
        return info;
    }
};
#endif //MAIN_CPP_DIVISORBEZERO_H
