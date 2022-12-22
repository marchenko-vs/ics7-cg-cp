#include <cstdlib>
#include <cmath>

#include "matrix.h"
#include "mainwindow.h"

Matrix::Matrix()
{
    for (std::size_t i = 0; i < SIZE; i++)
        for (std::size_t j = 0; j < SIZE; j++)
            this->elements[i][j] = 0.0;
}

Matrix Matrix::operator * (const Matrix &matrix)
{
    Matrix result;

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

Vector4d Matrix::operator * (const Vector4d &vector)
{
    Vector4d result;
    result.set_x(this->elements[0][0] * vector.get_x() +
               this->elements[0][1] * vector.get_y() +
               this->elements[0][2] * vector.get_z() +
               this->elements[0][3] * vector.get_w());
    result.set_y(this->elements[1][0] * vector.get_x() +
               this->elements[1][1] * vector.get_y() +
               this->elements[1][2] * vector.get_z() +
               this->elements[1][3] * vector.get_w());
    result.set_z(this->elements[2][0] * vector.get_x() +
               this->elements[2][1] * vector.get_y() +
               this->elements[2][2] * vector.get_z() +
               this->elements[2][3] * vector.get_w());
    result.set_w(this->elements[3][0] * vector.get_x() +
               this->elements[3][1] * vector.get_y() +
               this->elements[3][2] * vector.get_z() +
               this->elements[3][3] * vector.get_w());
    return result;
}

Matrix Matrix::getTranslationMatrix(const Object& object)
{
    Matrix result;

    for (std::size_t i = 0; i < SIZE; i++)
        for (std::size_t j = 0; j < SIZE; j++)
            if (i == j)
                result.elements[i][j] = 1.0;

    result.elements[0][3] = object.get_dx();
    result.elements[1][3] = object.get_dy();
    result.elements[2][3] = object.get_dz();

    return result;
}

Matrix Matrix::getTranslationMatrix(const double x,
                                    const double y,
                                    const double z)
{
    Matrix result;

    for (std::size_t i = 0; i < SIZE; i++)
        for (std::size_t j = 0; j < SIZE; j++)
            if (i == j)
                result.elements[i][j] = 1.0;

    result.elements[0][3] = x;
    result.elements[1][3] = y;
    result.elements[2][3] = z;

    return result;
}

Matrix Matrix::getRotationMatrix(const double phi_x, const double phi_y, const double phi_z)
{
    Matrix rotate_x, rotate_y, rotate_z;
    Matrix result;

    rotate_x.elements[1][1] = cos(phi_x);
    rotate_x.elements[1][2] = -sin(phi_x);
    rotate_x.elements[2][2] = cos(phi_x);
    rotate_x.elements[2][1] = sin(phi_x);
    rotate_x.elements[0][0] = 1.0;
    rotate_x.elements[3][3] = 1.0;

    rotate_y.elements[0][0] = cos(phi_y);
    rotate_y.elements[0][2] = sin(phi_y);
    rotate_y.elements[2][2] = cos(phi_y);
    rotate_y.elements[2][0] = -sin(phi_y);
    rotate_y.elements[1][1] = 1.0;
    rotate_y.elements[3][3] = 1.0;

    rotate_z.elements[0][0] = cos(phi_z);
    rotate_z.elements[0][1] = -sin(phi_z);
    rotate_z.elements[1][1] = cos(phi_z);
    rotate_z.elements[1][0] = sin(phi_z);
    rotate_z.elements[2][2] = 1.0;
    rotate_z.elements[3][3] = 1.0;

    result = rotate_x * rotate_y * rotate_z;
    return result;
}

Matrix Matrix::getRotationMatrix(const Object& object)
{
    Matrix rotate_x, rotate_y, rotate_z;
    Matrix result;

    rotate_x.elements[1][1] = cos(object.get_phi_x());
    rotate_x.elements[1][2] = -sin(object.get_phi_x());
    rotate_x.elements[2][2] = cos(object.get_phi_x());
    rotate_x.elements[2][1] = sin(object.get_phi_x());
    rotate_x.elements[0][0] = 1.0;
    rotate_x.elements[3][3] = 1.0;

    rotate_y.elements[0][0] = cos(object.get_phi_y());
    rotate_y.elements[0][2] = sin(object.get_phi_y());
    rotate_y.elements[2][2] = cos(object.get_phi_y());
    rotate_y.elements[2][0] = -sin(object.get_phi_y());
    rotate_y.elements[1][1] = 1.0;
    rotate_y.elements[3][3] = 1.0;

    rotate_z.elements[0][0] = cos(object.get_phi_z());
    rotate_z.elements[0][1] = -sin(object.get_phi_z());
    rotate_z.elements[1][1] = cos(object.get_phi_z());
    rotate_z.elements[1][0] = sin(object.get_phi_z());
    rotate_z.elements[2][2] = 1.0;
    rotate_z.elements[3][3] = 1.0;

    result = rotate_x * rotate_y * rotate_z;
    return result;
}

Matrix Matrix::getScalingMatrix(const Object& object)
{
    Matrix result;

    result.elements[0][0] = object.get_kx();
    result.elements[1][1] = object.get_ky();
    result.elements[2][2] = object.get_kz();
    result.elements[3][3] = 1.0;

    return result;
}

Matrix Matrix::getLookAtMatrix(Vertex& from, Vertex& to,
                               Vertex& up)
{
    Matrix result;

    Vertex forward = from - to;
    forward.normalize();
    Vertex right = up ^ forward;
    right.normalize();
    Vertex new_up = forward ^ right;
    //new_up.normalize();

    result.elements[0][0] = right.get_x();
    result.elements[0][1] = right.get_y();
    result.elements[0][2] = right.get_z();

    result.elements[1][0] = new_up.get_x();
    result.elements[1][1] = new_up.get_y();
    result.elements[1][2] = new_up.get_z();

    result.elements[2][0] = forward.get_x();
    result.elements[2][1] = forward.get_y();
    result.elements[2][2] = forward.get_z();

    result.elements[3][0] = from.get_x();
    result.elements[3][1] = from.get_y();
    result.elements[3][2] = from.get_z();
    result.elements[3][3] = 1.0;

    return result;
}

Matrix Matrix::getProjectionMatrix(double fov, double aspect,
                                   double znear, double zfar)
{
    Matrix result;

    double fov_radians = 1.0 / tan(fov * 3.14 / 360);
    double new_z = -zfar / (zfar - znear);

    result.elements[0][0] = fov_radians / aspect;
    result.elements[1][1] = fov_radians;
    result.elements[2][2] = -new_z;
    result.elements[3][2] = 1.0;
    result.elements[2][3] = new_z * znear;

    return result;
}
