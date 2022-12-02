#include <cmath>

#include "vertex.h"
#include "vector4d.h"

Vector4d::Vector4d()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
    this->w = 1;
}

Vector4d::Vector4d(const Vertex &vertex)
{
    this->x = vertex.get_x();
    this->y = vertex.get_y();
    this->z = vertex.get_z();
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
