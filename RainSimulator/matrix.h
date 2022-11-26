#ifndef MATRIX_H
#define MATRIX_H

#define SIZE 4

#include <iostream>

#include "vertex.h"
#include "object.h"

class Vector4d
{
public:
    double x, y, z, w;
public:
    Vector4d();
    Vector4d(const double x, const double y, const double z,
             const double w);
    Vector4d(const Vertex &vertex);

    void normalize(void);

    Vector4d operator + (const Vector4d &vertex);
    Vector4d operator - (const Vector4d &vertex);
    Vector4d operator * (const double multiplier);
    Vector4d operator ^ (const Vector4d &vertex);
    double operator * (const Vector4d &vertex);
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
    TranslationMatrix(const Object& object);
};

class ScaleMatrix : public BaseMatrix
{
public:
    ScaleMatrix();
    ScaleMatrix(const Object& object);
};

class RotateMatrix : public BaseMatrix
{
public:
    RotateMatrix();
    RotateMatrix(const Object& object);
    RotateMatrix(const double phi_x,
                               const double phi_y,
                               const double phi_z);
};

class ViewMatrix : public BaseMatrix
{
public:
    ViewMatrix();
    ViewMatrix(Vertex& eye, Vertex& target,
               Vertex& up);
};

class ProjectionMatrix : public BaseMatrix
{
public:
    ProjectionMatrix(double fov, double aspect,
                     double znear, double zfar);
};

#endif // MATRIX_H
