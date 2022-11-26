#include <cstdlib>
#include <cmath>

#include "matrix.h"
#include "mainwindow.h"

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

Vector4d::Vector4d(const double x, const double y, const double z,
                   const double w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4d Vector4d::operator + (const Vector4d &vertex)
{
    Vector4d result;

    result.x = vertex.x + this->x;
    result.y = vertex.y + this->y;
    result.z = vertex.z + this->z;
    result.w = vertex.w + this->w;

    return result;
}

Vector4d Vector4d::operator - (const Vector4d &vertex)
{
    Vector4d result;

    result.x = this->x - vertex.x;
    result.y = this->y - vertex.y;
    result.z = this->z - vertex.z;
    result.w = this->w - vertex.w;

    return result;
}

Vector4d Vector4d::operator * (const double multiplier)
{
    Vector4d result;

    result.x = this->x * multiplier;
    result.y = this->y * multiplier;
    result.z = this->z * multiplier;
    result.w = this->w * multiplier;

    return result;
}

Vector4d Vector4d::operator ^ (const Vector4d &vertex)
{
    Vector4d result;

    result.x = this->y * vertex.z - this->z * vertex.y;
    result.y = -(this->x * vertex.z - this->z * vertex.x);
    result.z = this->x * vertex.y - this->y * vertex.x;
    result.w = 1.0;

    return result;
}

double Vector4d::operator * (const Vector4d &vertex)
{
    double result = this->x * vertex.x +
                    this->y * vertex.y +
                    this->z * vertex.z +
                    this->w * vertex.w;

    return result;
}

void Vector4d::normalize(void)
{
    double vector_length = sqrt(this->x * this->x +
                                this->y * this->y +
                                this->z * this->z +
                                this->w * this->w);

    this->x /= vector_length;
    this->y /= vector_length;
    this->z /= vector_length;
    this->w /= vector_length;
}

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

    result.elements[0][0] = right.x;
    result.elements[0][1] = right.y;
    result.elements[0][2] = right.z;

    result.elements[1][0] = new_up.x;
    result.elements[1][1] = new_up.y;
    result.elements[1][2] = new_up.z;

    result.elements[2][0] = forward.x;
    result.elements[2][1] = forward.y;
    result.elements[2][2] = forward.z;

    result.elements[3][0] = from.x;
    result.elements[3][1] = from.y;
    result.elements[3][2] = from.z;
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
