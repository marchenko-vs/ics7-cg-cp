#ifndef MATRIX_H
#define MATRIX_H

#define SIZE 4

#include "vertex.h"

class Vector4d
{
public:
    double x, y, z, w;
public:
    Vector4d();
    Vector4d(const Vertex &vertex);
};

class BaseMatrix
{
public:
    double elements[SIZE][SIZE];

public:
    BaseMatrix();

    BaseMatrix operator * (const BaseMatrix &matrix);
    Vector4d operator * (const Vector4d &vector);

    ~BaseMatrix()
    {

    }
};

class TranslationMatrix : public BaseMatrix
{
public:
    TranslationMatrix();
    TranslationMatrix(const Vertex &vertex);
};

class ScaleMatrix : public BaseMatrix
{
public:
    ScaleMatrix();
    ScaleMatrix(const Vertex &vertex);
};

class ViewMatrix : public BaseMatrix
{
public:
    ViewMatrix();
};

class ProjectionMatrix : public BaseMatrix
{
public:
    ProjectionMatrix();
};

#endif // MATRIX_H
