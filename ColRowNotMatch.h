//
// Created by Lenovo on 2022/6/17.
//

#ifndef MAIN_CPP_COLROWNOTMATCH_H
#define MAIN_CPP_COLROWNOTMATCH_H

#include <exception>
#include <cstdio>
class ColRowNotMatch: public std::exception{
private:
    size_t a_row, b_row;
    size_t a_col, b_col;
    bool mode;
public:
    ColRowNotMatch(size_t a_col, size_t b_row): b_row(b_row), a_col(a_col), mode(false){}
    ColRowNotMatch(size_t a_row, size_t a_col, size_t b_row, size_t b_col): a_row(a_row), a_col(a_col),
            b_row(b_row), b_col(b_col), mode(true){}

    const char* what() const noexcept override{
        char* info = new char[100];
        if (mode){
            sprintf(info, "The size of two matrix not equal, a: %zux%zu, b: %zux%zu.", a_row, a_col , b_row, b_col);
        }else{
            sprintf(info, "The row and col of two matrix not match, a: %zu, b: %zu.", a_col , b_row);
        }
        return info;
    }
};
#endif //MAIN_CPP_COLROWNOTMATCH_H
