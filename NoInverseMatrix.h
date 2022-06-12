//
// Created by dgy on 2022/6/12.
//
#include <exception>
#include <cstdio>

class NoInverseMatrix: public std::exception{
private:
    size_t col{}, row{};

public:
    NoInverseMatrix(size_t col, size_t row): col(col), row(row){}

    NoInverseMatrix();

    const char* what() const noexcept override{
        char* info = new char[100];
        sprintf(info, "The determinant of this matrix is 0, so it has no inverse matrix.");
        return info;
    }
};