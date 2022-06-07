//
// Created by ay871 on 2022/6/7.
//

#ifndef MATRIX_SIZENOTEQUAL_H
#define MATRIX_SIZENOTEQUAL_H

class SizeNotEqual: public std::exception{
private:
    size_t a_size, b_size;

public:
    SizeNotEqual(size_t a_size, size_t b_size): a_size(a_size), b_size(b_size){}

    const char* what() const noexcept override{
        char* info = new char[100];
        sprintf(info, "The size of two matrix not equal: %zu, %zu.", a_size, b_size);
        return info;
    }
};

#endif //MATRIX_SIZENOTEQUAL_H
