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

class Matrix
{
public:
    double elements[SIZE][SIZE];

public:
    Matrix();

    static Matrix getScalingMatrix(const Object& object);
    static Matrix getTranslationMatrix(const Object& object);
    static Matrix getTranslationMatrix(const double x,
                                        const double y,
                                        const double z);
    static Matrix getRotationMatrix(const Object& object);

    static Matrix getLookAtMatrix(Vertex& eye, Vertex& target,
                                Vertex& up);
    static Matrix getProjectionMatrix(double fov, double aspect,
                                       double znear, double zfar);

    Matrix operator * (const Matrix &matrix);
    Vector4d operator * (const Vector4d &vector);

    ~Matrix()
    {

    }
};

#endif // MATRIX_H
