#include <cmath>

#include "vertex.h"

Vertex::Vertex()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Vertex::Vertex(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vertex::get_x() const
{
    return this->x;
}

double Vertex::get_y() const
{
    return this->y;
}

double Vertex::get_z() const
{
    return this->z;
}

void Vertex::set_x(double x)
{
    this->x = x;
}

void Vertex::set_y(double y)
{
    this->y = y;
}

void Vertex::set_z(double z)
{
    this->z = z;
}

void Vertex::change_x(double x)
{
    this->x += x;
}

void Vertex::change_y(double y)
{
    this->y += y;
}

void Vertex::change_z(double z)
{
    this->z += z;
}

Vertex Vertex::operator + (const Vertex &vertex)
{
    Vertex result;

    result.x = vertex.x + this->x;
    result.y = vertex.y + this->y;
    result.z = vertex.z + this->z;

    return result;
}

Vertex Vertex::operator - (const Vertex &vertex)
{
    Vertex result;

    result.x = this->x - vertex.x;
    result.y = this->y - vertex.y;
    result.z = this->z - vertex.z;

    return result;
}

Vertex Vertex::operator * (const double multiplier)
{
    Vertex result;

    result.x = this->x * multiplier;
    result.y = this->y * multiplier;
    result.z = this->z * multiplier;

    return result;
}

Vertex Vertex::operator ^ (const Vertex &vertex)
{
    Vertex result;

    result.x = this->y * vertex.z - this->z * vertex.y;
    result.y = -(this->x * vertex.z - this->z * vertex.x);
    result.z = this->x * vertex.y - this->y * vertex.x;

    return result;
}

double Vertex::operator * (const Vertex &vertex)
{
    double result = this->x * vertex.x +
                    this->y * vertex.y +
                    this->z * vertex.z;

    return result;
}

void Vertex::normalize(void)
{
    double vector_length = sqrt(this->x * this->x +
                                this->y * this->y +
                                this->z * this->z);

    this->x /= vector_length;
    this->y /= vector_length;
    this->z /= vector_length;
}

Vertex::~Vertex()
{

}
