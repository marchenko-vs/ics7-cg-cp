#include "matrix.h"
#include "vertex.h"

Matrix::Matrix(const Vertex &vertex)
{
    this->rows = 4;
    this->columns = 1;

    this->elements = new double*[this->rows];

    for (size_t i = 0; i < this->rows; i++)
        this->elements[i] = new double[this->columns];

    this->elements[0][0] = vertex.x;
    this->elements[0][1] = vertex.y;
    this->elements[0][2] = vertex.z;
    this->elements[0][3] = 1.0;
}
