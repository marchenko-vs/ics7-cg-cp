#include <cstdlib>
#include <cmath>

#include "matrix.h"

Vector4d::Vector4d()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
    this->w = 1;
}

Vector4d::Vector4d(const Vertex &vertex)
{
    this->x = vertex.x;
    this->y = vertex.y;
    this->z = vertex.z;
    this->w = 1;
}

BaseMatrix::BaseMatrix()
{
    for (std::size_t i = 0; i < SIZE; i++)
        for (std::size_t j = 0; j < SIZE; j++)
            this->elements[i][j] = 0.0;
}

BaseMatrix BaseMatrix::operator * (const BaseMatrix &matrix)
{
    BaseMatrix result;

    for (std::size_t i = 0; i < SIZE; i++)
    {
        for (std::size_t j = 0; j < SIZE; j++)
        {
            double sum = 0.0;

            for (std::size_t k = 0; k < SIZE; k++)
            {
                sum += this->elements[i][k] * matrix.elements[k][j];
            }

            result.elements[i][j] = sum;
        }
    }

    return result;
}

Vector4d BaseMatrix::operator * (const Vector4d &vector)
{
    Vector4d result;

    result.x = this->elements[0][0] * vector.x +
               this->elements[0][1] * vector.y +
               this->elements[0][2] * vector.z +
               this->elements[0][3] * vector.w;
    result.y = this->elements[1][0] * vector.x +
               this->elements[1][1] * vector.y +
               this->elements[1][2] * vector.z +
               this->elements[1][3] * vector.w;
    result.z = this->elements[2][0] * vector.x +
               this->elements[2][1] * vector.y +
               this->elements[2][2] * vector.z +
               this->elements[2][3] * vector.w;
    result.w = this->elements[3][0] * vector.x +
               this->elements[3][1] * vector.y +
               this->elements[3][2] * vector.z +
               this->elements[3][3] * vector.w;

    return result;
}

TranslationMatrix::TranslationMatrix(const Vertex &vertex)
{
    for (std::size_t i = 0; i < SIZE; i++)
    {
        for (std::size_t j = 0; j < SIZE; j++)
        {
            if (i == j)
                this->elements[i][j] = 1.0;
            else
                this->elements[i][j] = 0.0;
        }
    }

    this->elements[0][3] = vertex.dx;
    this->elements[1][3] = vertex.dy;
    this->elements[2][3] = vertex.dz;
}

ScaleMatrix::ScaleMatrix(const Vertex &vertex)
{
    for (std::size_t i = 0; i < SIZE; i++)
        for (std::size_t j = 0; j < SIZE; j++)
            this->elements[i][j] = 0.0;

    this->elements[0][0] = vertex.kx;
    this->elements[1][1] = vertex.ky;
    this->elements[2][2] = vertex.kz;
    this->elements[3][3] = 1.0;
}

ViewMatrix::ViewMatrix()
{
    this->elements[0][0] = 0.0;
    this->elements[0][1] = 3.0;
    this->elements[0][2] = -5.0;
    this->elements[0][3] = 0.0;

    this->elements[1][0] = 0.0;
    this->elements[1][1] = 0.0;
    this->elements[1][2] = 0.0;
    this->elements[1][3] = 0.0;

    this->elements[2][0] = 0.0;
    this->elements[2][1] = 1.0;
    this->elements[2][2] = 0.0;
    this->elements[2][3] = 0.0;

    this->elements[3][0] = 0.0;
    this->elements[3][1] = 0.0;
    this->elements[3][2] = 0.0;
    this->elements[3][3] = 1.0;
}

ProjectionMatrix::ProjectionMatrix()
{
    double phi = 90.0 / 2;
    int n = 1, f = 2;

    for (std::size_t i = 0; i < SIZE; i++)
        for (std::size_t j = 0; j < SIZE; j++)
            this->elements[i][j] = 0.0;

    this->elements[0][0] = 1 / tan(phi);
    this->elements[1][1] = 1.0 / tan(phi);
    this->elements[2][2] = f / (f - n);

    this->elements[2][3] = -n * (f - n);
    this->elements[3][2] = 1.0;
}
