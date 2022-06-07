//
// Created by ay871 on 2022/6/6.
//

#ifndef MATRIX_INDEXOUTOFBOUND_H
#define MATRIX_INDEXOUTOFBOUND_H

#include <exception>
#include <cstdio>

class IndexOutOfBound : public std::exception {
private:
    size_t col{}, row{};
    bool mode;
    size_t col_begin{}, col_end{}, row_begin{}, row_end{};

public:
    IndexOutOfBound(size_t col, size_t row) : col(col), row(row), mode(false) {}

    IndexOutOfBound(size_t col_begin, size_t col_end, size_t row_begin, size_t row_end) :
            col_begin(col_begin), col_end(col_end), row_begin(row_begin), row_end(row_end), mode(true) {}

    const char *what() const noexcept override {
        char *info = new char[100];
        if (mode)
            sprintf(info, "Index out of matrix bound: col_begin(%zu), col_end(%zu), row_begin(%zu), row_end(%zu).",
                    col_begin, col_end, row_begin, row_end);
        else sprintf(info, "Index out of matrix bound: col(%zu), row(%zu).", col, row);
        return info;
    }
};

#endif //MATRIX_INDEXOUTOFBOUND_H
