#ifndef MATRIX_H
#define MATRIX_H

#define SIZE 4

#include <iostream>

#include "vertex.h"
#include "object.h"
#include "vector4d.h"

class Matrix
{
public:
    Matrix();
    static Matrix getScalingMatrix(const Object& object);
    static Matrix getTranslationMatrix(const Object& object);
    static Matrix getTranslationMatrix(const double x,
                                       const double y,
                                       const double z);
    static Matrix getRotationMatrix(const double phi_x, const double phi_y, const double phi_z);
    static Matrix getRotationMatrix(const Object& object);
    static Matrix getLookAtMatrix(Vertex& eye, Vertex& target,
                                  Vertex& up);
    static Matrix getProjectionMatrix(double fov, double aspect,
                                      double znear, double zfar);
    Matrix operator * (const Matrix &matrix);
    Vector4d operator * (const Vector4d &vector);
    ~Matrix() { }

private:
    double elements[SIZE][SIZE];
};

#endif // MATRIX_H
