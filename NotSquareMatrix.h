#ifndef NOTSQUAREMATRIX_H
#define NOTSQUAREMATRIX_H
#include <exception>
#include <cstdio>

class NotSquareMatrix: public std::exception{
private:
    size_t col, row;

public:
    NotSquareMatrix(size_t col, size_t row): col(col), row(row){}

    const char* what() const noexcept override{
        char* info = new char[100];
        sprintf(info, "This is not a square matrix %zu, %zu.", col, row);
        return info;
    }
};

#endif //NOTSQUAREMATRIX_H