#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>

#include "vertex.h"

class Matrix
{
public:
    Matrix(const Vertex &vertex);

    ~Matrix();
private:
    double **elements;
    size_t rows;
    size_t columns;
};

#endif // MATRIX_H
