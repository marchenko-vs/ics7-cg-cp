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

TranslationMatrix::TranslationMatrix(const Object& object)
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

    this->elements[0][3] = object.get_dx();
    this->elements[1][3] = object.get_dy();
    this->elements[2][3] = object.get_dz();
}

RotateMatrix::RotateMatrix(const double phi_x,
                           const double phi_y,
                           const double phi_z)
{
    BaseMatrix rotate_x, rotate_y, rotate_z;
    BaseMatrix result;

    for (std::size_t i = 0; i < SIZE; i++)
    {
        for (std::size_t j = 0; j < SIZE; j++)
        {
            if (i == j)
            {
                rotate_x.elements[i][j] = 1.0;
                rotate_y.elements[i][j] = 1.0;
                rotate_z.elements[i][j] = 1.0;
                this->elements[i][j] = 1.0;
            }
            else
            {
                rotate_x.elements[i][j] = 0.0;
                rotate_y.elements[i][j] = 0.0;
                rotate_z.elements[i][j] = 0.0;
                this->elements[i][j] = 0.0;
            }
        }
    }

    rotate_x.elements[1][1] = cos(phi_x);
    rotate_x.elements[1][2] = -sin(phi_x);
    rotate_x.elements[2][2] = cos(phi_x);
    rotate_x.elements[2][1] = sin(phi_x);

    rotate_y.elements[0][0] = cos(phi_y);
    rotate_y.elements[0][2] = sin(phi_y);
    rotate_y.elements[2][2] = cos(phi_y);
    rotate_y.elements[2][0] = -sin(phi_y);

    rotate_z.elements[0][0] = cos(phi_z);
    rotate_z.elements[0][1] = -sin(phi_z);
    rotate_z.elements[1][1] = cos(phi_z);
    rotate_z.elements[1][0] = sin(phi_z);

    result = rotate_x * rotate_y * rotate_z;

    for (std::size_t i = 0; i < SIZE; i++)
        for (std::size_t j = 0; j < SIZE; j++)
            this->elements[i][j] = result.elements[i][j];
}

RotateMatrix::RotateMatrix(const Object& object)
{
    BaseMatrix rotate_x, rotate_y, rotate_z;
    BaseMatrix result;

    for (std::size_t i = 0; i < SIZE; i++)
    {
        for (std::size_t j = 0; j < SIZE; j++)
        {
            if (i == j)
            {
                rotate_x.elements[i][j] = 1.0;
                rotate_y.elements[i][j] = 1.0;
                rotate_z.elements[i][j] = 1.0;
                this->elements[i][j] = 1.0;
            }
            else
            {
                rotate_x.elements[i][j] = 0.0;
                rotate_y.elements[i][j] = 0.0;
                rotate_z.elements[i][j] = 0.0;
                this->elements[i][j] = 0.0;
            }
        }
    }

    rotate_x.elements[1][1] = cos(object.get_phi_x());
    rotate_x.elements[1][2] = -sin(object.get_phi_x());
    rotate_x.elements[2][2] = cos(object.get_phi_x());
    rotate_x.elements[2][1] = sin(object.get_phi_x());

    rotate_y.elements[0][0] = cos(object.get_phi_y());
    rotate_y.elements[0][2] = sin(object.get_phi_y());
    rotate_y.elements[2][2] = cos(object.get_phi_y());
    rotate_y.elements[2][0] = -sin(object.get_phi_y());

    rotate_z.elements[0][0] = cos(object.get_phi_z());
    rotate_z.elements[0][1] = -sin(object.get_phi_z());
    rotate_z.elements[1][1] = cos(object.get_phi_z());
    rotate_z.elements[1][0] = sin(object.get_phi_z());

    result = rotate_x * rotate_y * rotate_z;

    for (std::size_t i = 0; i < SIZE; i++)
        for (std::size_t j = 0; j < SIZE; j++)
            this->elements[i][j] = result.elements[i][j];
}

ScaleMatrix::ScaleMatrix(const Object& object)
{
    for (std::size_t i = 0; i < SIZE; i++)
        for (std::size_t j = 0; j < SIZE; j++)
            this->elements[i][j] = 0.0;

    this->elements[0][0] = object.get_kx();
    this->elements[1][1] = object.get_ky();
    this->elements[2][2] = object.get_kz();
    this->elements[3][3] = 1.0;
}

ViewMatrix::ViewMatrix(Vertex& eye, Vertex& target,
                       Vertex& up)
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

    Vertex forward = target - eye;
    forward.normalize();
    Vertex result2 = up ^ forward;
    result2.normalize();
    Vertex result3 = forward ^ result2;
    result3.normalize();

    this->elements[0][0] = result2.x;
    this->elements[1][0] = result2.y;
    this->elements[2][0] = result2.z;

    this->elements[0][1] = result3.x;
    this->elements[1][1] = result3.y;
    this->elements[2][1] = result3.z;

    this->elements[0][2] = forward.x;
    this->elements[1][2] = forward.y;
    this->elements[2][2] = forward.z;

    this->elements[3][0] = result2 * eye;
    this->elements[3][1] = result3 * eye;
    this->elements[3][2] = forward * eye;

    this->elements[3][0] = -this->elements[3][0];
    this->elements[3][1] = -this->elements[3][1];
    this->elements[3][2] = -this->elements[3][2];
}

ProjectionMatrix::ProjectionMatrix(double fov, double aspect,
                                   double znear, double zfar)
{
    double num1 = (double)(1.0 / tan(fov * 0.5));
    double num2 = zfar / (zfar - znear);

    for (std::size_t i = 0; i < SIZE; i++)
        for (std::size_t j = 0; j < SIZE; j++)
            this->elements[i][j] = 0.0;

    this->elements[0][0] = num1 / aspect;
    this->elements[1][1] = num1;
    this->elements[2][2] = num2;
    this->elements[2][3] = 1.0;
    this->elements[3][2] = -num2 * znear;;
}
